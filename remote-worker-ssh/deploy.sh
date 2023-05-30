#!/bin/bash

modules=( 
	"thermal-ext:libthermalext0_1.0-r0_armv7at2hf-neon.ipk"
        "thermal-service:thermal-service_1.0-r0_armv7at2hf-neon.ipk"
        "thermal-service-interface:libithermal0_1.0-r0_armv7at2hf-neon.ipk" 
)

host="worker@tung6-nguyen-24dcm-tn.vbee.lge.com"
port="42113"

DOWNLOAD_IPK(){
	model="sa515m"
	version_module="1.0-r0"
	deploy_target="armv7at2hf-neon"
	for pair in "${modules[@]}"; do
    		KEY="${pair%%:*}"
    		VALUE="${pair##*:}"
		module=$KEY
		ipk_file=$VALUE
		rm -rf $ipk_file
		echo 
		echo "Downloading ...... "
		path="~/build-24dcm/nad/$model/${model^^}_apps/apps_proc/build/tmp-glibc/work/armv7at2hf-neon-oe-linux-gnueabi/$module/$version_module/deploy-ipks/$deploy_target/$ipk_file"
		echo $path
		scp -P $port $host:$path . 
		echo
	done
}

PUSH_IPK(){
	
	adb="_adb"
	cmd
	$adb root
	$adb shell mount -o remount,rw /
	bash
	for pair in "${modules[@]}"; do
    		KEY="${pair%%:*}"
    		VALUE="${pair##*:}"
		module=$KEY
		ipk_file=$VALUE
		echo 
		echo "Uploading ...... "
		cmd
		$adb push $ipk_file tmp/
		$adb shell opkg install --force-reinstall --force-overwrite tmp/$ipk_file
		$adb shell rm -rf $ipk_file
		$adb shell sync
		bash
		echo
	done	
}

#DOWNLOAD_IPK
PUSH_IPK
