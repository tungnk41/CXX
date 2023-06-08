#!/bin/bash

modules=( 
	"thermal-ext:libthermalext0_1.0-r0_armv7at2hf-neon.ipk"
        "thermal-service:thermal-service_1.0-r0_armv7at2hf-neon.ipk"
        "thermal-service-interface:libithermal0_1.0-r0_armv7at2hf-neon.ipk" 
)

host="worker@tung6-nguyen-24dcm-tn.vbee.lge.com"
port="42113"
adb="_adb"

DOWNLOAD_IPK(){
	model="sa515m"
	version_module="1.0-r0"
	deploy_target="armv7at2hf-neon"

	rm -rf tmp
	mkdir tmp
	cd tmp

	for pair in "${modules[@]}"; do
    		KEY="${pair%%:*}"
    		VALUE="${pair##*:}"
		module=$KEY
		ipk_file=$VALUE
		rm -rf $ipk_file
		echo 
		path="~/build-24dcm/nad/$model/${model^^}_apps/apps_proc/build/tmp-glibc/work/armv7at2hf-neon-oe-linux-gnueabi/$module/$version_module/deploy-ipks/$deploy_target/$ipk_file"
		echo $path
		scp -P $port $host:$path . 
		echo
	done
	cd ..
}

PUSH_IPK(){
	./root.bat
	cd tmp
	for pair in "${modules[@]}"; do
    		KEY="${pair%%:*}"
    		VALUE="${pair##*:}"
		module=$KEY
		ipk_file=$VALUE
		echo 
		echo "Uploading ...... "
		$adb push $ipk_file tmp/
		$adb shell opkg install --force-reinstall --force-overwrite tmp/$ipk_file
		$adb shell rm -rf $ipk_file
		$adb shell sync	
		echo
	done
	cd ..	
}

FORWARD_LOG(){
	echo "Forward Port: 3490 =>>> DLT LOG"
	adb forward tcp:3490 tcp:3490
}

ALL(){
FORWARD_LOG
DOWNLOAD_IPK
PUSH_IPK
}

Exit(){
	echo "Exit"
	exit
}

#Loop 
while :
do
	echo "1. All"
	echo "2. Download IPK"
	echo "3. Push IPK"
	echo "4. Forward Log"
	echo "5. Exit"
	read -p "Option : " option

	case $option in
		2)
		DOWNLOAD_IPK
		;;
		3)
		PUSH_IPK
		;;
		4)
		FORWARD_LOG
		;;
		1)
		ALL
		;;
		5)
		Exit
		;;
		*)	
		echo "*******"
		;;
	esac
done
