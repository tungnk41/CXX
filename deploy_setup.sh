#!/bin/bash
Bin_path="/home/bienhust/Public/BUILD_BINARY/AppSetup/app/bin" 
Bin_name="AppSetup"
QML_folder_path="/home/bienhust/Public/GEN5_MASTTER/AppSetup"
QML_folder_name="AppSetup"

#Input board address
if [ "$1" = "1" ]
then
	host="root@192.168.1.100"
else
	host="root@10.34.196."$1
fi
echo $host

if [ "$2" = "1" ]
then
	suffix="_2"
else
	suffix=""
fi
QML_folder_path=$QML_folder_path$suffix

echo -e "Pushed folder : \033[1;32m$QML_folder_name$suffix\033[m"

#Function push
Bin(){
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/bin/$Bin_name"
	strip $Bin_path/$Bin_name
	scp -r $Bin_path/$Bin_name $host:/app/bin/$Bin_name
	ssh -o "StrictHostKeyChecking no" $host "chmod +x /app/bin/$Bin_name"
}

Localization(){
	tarFile=qml.tar
	cd $QML_folder_path
	cp -r res/data $QML_folder_path
	tar -cf $tarFile localization
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/$QML_folder_name/localization"
	scp -r $QML_folder_path/$tarFile $host:/app/share/AppSetup
	ssh -o "StrictHostKeyChecking no" $host "tar -xf /app/share/$QML_folder_name/$tarFile -C /app/share/$QML_folder_name"
	rm  $QML_folder_path/$tarFile
	rm -r -rf $QML_folder_path/data
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/AppSetup/$tarFile"
}


QML(){
	tarFile=qml.tar
	cd $QML_folder_path
	cp -r res/data $QML_folder_path
	tar -cf $tarFile qml_new2.0 qml qml_eco3.0 qml_genesis data Js
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/$QML_folder_name/qml_new2.0"
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/$QML_folder_name/qml"
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/$QML_folder_name/qml_eco3.0"
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/$QML_folder_name/qml_genesis"
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/$QML_folder_name/data"
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/$QML_folder_name/Js"
	scp -r $QML_folder_path/$tarFile $host:/app/share/AppSetup
	ssh -o "StrictHostKeyChecking no" $host "tar -xf /app/share/$QML_folder_name/$tarFile -C /app/share/$QML_folder_name"
	rm  $QML_folder_path/$tarFile
	rm -r -rf $QML_folder_path/data
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/AppSetup/$tarFile"
}

DBSearch(){
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/AppSetup/data/setup_database.db"
	cd /home/bienhust/Public/GEN5_MASTTER/AppSetup/res/data
	scp -r setup_database.db $host:/app/share/AppSetup/data
}

All(){
Bin
QML
DBSearch
Localization
}

IMAGE_USM(){
	model=kmc
	color=night
	echo "1. HMC Night - New 2.0 USM"
	echo "2. KMC Night - New 2.0 USM"
	echo "3. Genesis USM"
	echo "4. ECO 3.0 USM"
	read -p "Select model GUI :" gui
	case $gui in
	1)
#New2.0
	model=hmc
	color=night
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/images/new_gui/new2.0/$model/$color/setup/usm"
	cd /home/bienhust/Public/GEN5_MASTTER/AppSetup/res/images/new_gui/new2.0/$model/$color/setup
	scp -r usm $host:/app/share/images/new_gui/new2.0/$model/$color/setup
	;;
	2)
#New2.0
	model=kmc
	color=night
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/images/new_gui/new2.0/$model/$color/setup/usm"
	cd /home/bienhust/Public/GEN5_MASTTER/AppSetup/res/images/new_gui/new2.0/$model/$color/setup
	scp -r usm $host:/app/share/images/new_gui/new2.0/$model/$color/setup
	;;
	3)
#Genesis
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/images/genesis/setup/usm"
	cd /home/bienhust/Public/GEN5_MASTTER/AppSetup/res/images/genesis/setup
	scp -r usm $host:/app/share/images/genesis/setup
	;;
	4)
#ECO3.0
	model=hmc
	color=night
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/images/new_gui/eco3.0/$model/$color/setup/usm"
	cd /home/bienhust/Public/GEN5_MASTTER/AppSetup/res/images/new_gui/eco3.0/$model/$color/setup
	scp -r usm $host:/app/share/images/new_gui/eco3.0/$model/$color/setup
	model=hmc
	color=day
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/images/new_gui/eco3.0/$model/$color/setup/usm"
	cd /home/bienhust/Public/GEN5_MASTTER/AppSetup/res/images/new_gui/eco3.0/$model/$color/setup
	scp -r usm $host:/app/share/images/new_gui/eco3.0/$model/$color/setup
	;;
	*)
	echo "*******"
	;;
	esac	
}

IMAGE_SETUP(){
	model=kmc
	color=night
	echo "1. HMC Night - New 2.0 SETUP"
	echo "2. KMC Night - New 2.0 SETUP"
	echo "3. Genesis SETUP"
	echo "4. ECO 3.0 SETUP"
	read -p "Select model GUI :" gui
	case $gui in
	1)
#New2.0
	model=hmc
	color=night
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/images/new_gui/new2.0/$model/$color/setup"
	cd /home/bienhust/Public/GEN5_MASTTER/AppSetup/res/images/new_gui/new2.0/$model/$color
	scp -r setup $host:/app/share/images/new_gui/new2.0/$model/$color
	;;
	2)
#New2.0
	model=kmc
	color=night
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/images/new_gui/new2.0/$model/$color/setup"
	cd /home/bienhust/Public/GEN5_MASTTER/AppSetup/res/images/new_gui/new2.0/$model/$color
	scp -r setup $host:/app/share/images/new_gui/new2.0/$model/$color
	;;
	3)
#Genesis
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/images/genesis/setup"
	cd /home/bienhust/Public/GEN5_MASTTER/AppSetup/res/images/genesis
	scp -r setup $host:/app/share/images/genesis
	;;
	4)
#ECO3.0
	model=hmc
	color=night
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/images/new_gui/eco3.0/$model/$color/setup"
	cd /home/bienhust/Public/GEN5_MASTTER/AppSetup/res/images/new_gui/eco3.0/$model/$color
	scp -r setup $host:/app/share/images/new_gui/eco3.0/$model/$color
	model=hmc
	color=day
	ssh -o "StrictHostKeyChecking no" $host "rm -r -rf /app/share/images/new_gui/eco3.0/$model/$color/setup"
	cd /home/bienhust/Public/GEN5_MASTTER/AppSetup/res/images/new_gui/eco3.0/$model/$color
	scp -r setup $host:/app/share/images/new_gui/eco3.0/$model/$color
	;;
	*)
	echo "*******"
	;;
	esac	
}

Exit(){
	echo "Exit"
	exit
}

#Loop 
while :
do
	echo "1. Bin"
	echo "2. QML"
	echo "3. Localization"
	echo "4. DB Search Setting"
	echo "5. All"
	echo "6. Bin + QML"
	echo "7. Images"
	echo "8. Exit"
	ssh -o "StrictHostKeyChecking no" $host "mount -o remount,rw /"
	ssh -o "StrictHostKeyChecking no" $host "mount -o remount,rw /navi"
	ssh -o "StrictHostKeyChecking no" $host "mount -o remount,rw /navi2"
	read -p "DO YOU WANT TO PUSH : " option

	case $option in
		1)
		Bin
		;;
		2)
		QML
		;;
		3)
		Localization
		;;
		4)
		Bin
		DBSearch
		;;
		5)
		All
		;;
		6)
		Bin
		QML
		;;
		7)
		IMAGE_SETUP
		;;
		8)
		Exit
		;;
		*)	
		echo "*******"
		;;
	esac
	ssh -o "StrictHostKeyChecking no" $host 'sync'
	read -p "DO YOU WANT TO REBOOT BOARD ? [y/n]" response2
	if [ "${response2^}" = "Y" ]
	then
		ssh -o "StrictHostKeyChecking no" $host "/sbin/reboot"
		exit
	fi
	clear
done

	





