#!/bin/bash

host="worker@tung6-nguyen-24dcm-tn.vbee.lge.com"
port="32528"
adb="_adb"

ipkMapThermal=( 
	"thermal-ext:libthermalext0_1.0-r0_armv7at2hf-neon.ipk"
        "thermal-service:thermal-service_1.0-r0_armv7at2hf-neon.ipk"
        "thermal-service-interface:libithermal0_1.0-r0_armv7at2hf-neon.ipk" 
)
ipkMapHMI=( 
	"hmi-service-variant:libhmihal0_1.0-r0_armv7at2hf-neon.ipk"
        "hmi-service:hmi-service_1.0-r0_armv7at2hf-neon.ipk"
        "hmi-service-interface:libihmi0_1.0-r0_armv7at2hf-neon.ipk" 
)
ipkMapDCMPFAPI=( 
	"dcmpfapi:dcmpfapi_1.0-r0_armv7at2hf-neon.ipk"
)
ipkMapDCMPFSLDD=( 
	"dcmpfsldd:dcmpfsldd_1.0-r0_armv7at2hf-neon.ipk"
)
ipkMapDCMPFTCLI=( 
	"dcmpftcli:dcmpftcli_1.0-r0_armv7at2hf-neon.ipk"
)
ipkMapAppMgr=( 
	"app-service:app-service_1.0-r0_armv7at2hf-neon.ipk"
    "app-service-lib:libapplication0_1.0-r0_armv7at2hf-neon.ipk"
    "app-service-interface:libiapplication0_1.0-r0_armv7at2hf-neon.ipk" 
)
ipkMapSLDD=( 
	"sldd:sldd_1.0-r0_armv7at2hf-neon.ipk"
)

ipkMap=("${ipkMapHMI[@]}")
model=sa515m

DOWNLOAD_IPK(){
	if [ ! -d "tmp" ]; then
		mkdir tmp
	else
		rm -rf tmp/*.ipk
	fi
	for pair in "${ipkMap[@]}"; do
    		KEY="${pair%%:*}"
    		VALUE="${pair##*:}"
		ipkMapKey=$KEY
		ipkMapValue=$VALUE
		echo 
		path="~/build-24dcm/nad/$model/${model^^}_apps/apps_proc/build/tmp-glibc/work/armv7at2hf-neon-oe-linux-gnueabi/$ipkMapKey/1.0-r0/deploy-ipks/armv7at2hf-neon/$ipkMapValue"
		echo $path
		scp -P $port $host:$path tmp
		echo
	done
}

ENABLE_ROOT() {
	root.bat
}

PUSH_IPK(){
	ENABLE_ROOT
	for pair in "${ipkMap[@]}"; do
    		KEY="${pair%%:*}"
    		VALUE="${pair##*:}"
		ipkMapKey=$KEY
		ipkMapValue=$VALUE
		echo 
		echo "Uploading ...... "
		$adb push tmp/$ipkMapValue tmp
		$adb shell opkg install --force-reinstall --force-overwrite tmp/$ipkMapValue
		$adb shell rm -rf tmp/$ipkMapValue
		$adb shell sync	
		echo
	done
}

DOWNLOAD_PUSH_IPK() {
	DOWNLOAD_OPTION
	DOWNLOAD_IPK
	PUSH_IPK
	$adb shell reboot
}

DOWNLOAD_OPTION() {
	clear
	echo "1. HMI"
	echo "2. Thermal"
	echo "3. DCMPFAPI"
	echo "4. DCMPFSLDD"
	echo "5. DCMPFTCLI"
	echo "6. AppMgr"
	echo "7. SLDD"
	read -p "Option : " option
	case $option in
		1)
		ipkMap=("${ipkMapHMI[@]}")
		;;
		2)
		ipkMap=("${ipkMapThermal[@]}")
		;;
		3)
		ipkMap=("${ipkMapDCMPFAPI[@]}")
		;;
		4)
		ipkMap=("${ipkMapDCMPFSLDD[@]}")
		;;
		5)
		ipkMap=("${ipkMapDCMPFTCLI[@]}")
		;;
		6)
		ipkMap=("${ipkMapAppMgr[@]}")
		;;
		7)
		ipkMap=("${ipkMapSLDD[@]}")
		;;
	esac
}

FORWARD_LOG(){
	echo "Forward Port: 3490 =>>> DLT LOG"
	start cmd.exe /c "cmd.exe /c start /min forward-log.bat"
}

RUN_CMD(){
	ENABLE_ROOT
	start cmd.exe /c "start cmd.exe /k _adb shell"
}

DOWNLOAD_FILE_FROM_PATH() {
	read -p "Remote Path : " path
   	scp -r -P $port $host:$path .
}

DOWNLOAD_FOLDER_FROM_PATH() {
	read -p "Remote Path : " path
   	scp -r $port $host:$path .
}

REMOVE_DLT() {
	ENABLE_ROOT
	reduce-dlt.bat
}

Exit(){
	echo "Exit"
	exit
}

MAIN() {
	cd "/c/Users/tung6.nguyen/Documents/CXX/remote-worker-ssh"
	clear
	#Loop 
	while :
	do
		echo "1. Download-Push IPK"
		echo "2. Download Folder From Path"
		echo "3. Download Folder From Path"
		echo "4. Forward Log"
		echo "5. Run shell"
		echo "6. Remove DLT Log Context"
		echo "7. Exit"
		read -p "Option : " option

		case $option in
			1)
			DOWNLOAD_PUSH_IPK
			;;
			2)
			DOWNLOAD_FOLDER_FROM_PATH
			;;
			3)
			DOWNLOAD_FILE_FROM_PATH
			;;
			4)
			FORWARD_LOG
			;;
			5)
			RUN_CMD
			;;
			6)
			REMOVE_DLT
			;;
			7)
			Exit
			;;
			*)	
			echo "*******"
			;;
		esac
	done
}

MAIN


