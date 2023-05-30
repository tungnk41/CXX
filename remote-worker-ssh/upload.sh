#!/bin/bash

scp -P 42113 worker@tung6-nguyen-24dcm-tn.vbee.lge.com:~/build-24dcm/nad/sa515m/SA515M_apps/apps_proc/build/tmp-glibc/work/armv7at2hf-neon-oe-linux-gnueabi/thermal-ext/1.0-r0/deploy-ipks/armv7at2hf-neon/libthermalext0_1.0-r0_armv7at2hf-neon.ipk .
scp -P 42113 worker@tung6-nguyen-24dcm-tn.vbee.lge.com:~/build-24dcm/nad/sa515m/SA515M_apps/apps_proc/build/tmp-glibc/work/armv7at2hf-neon-oe-linux-gnueabi/thermal-service/1.0-r0/deploy-ipks/armv7at2hf-neon/thermal-service_1.0-r0_armv7at2hf-neon.ipk .
scp -P 42113 worker@tung6-nguyen-24dcm-tn.vbee.lge.com:~/build-24dcm/nad/sa515m/SA515M_apps/apps_proc/build/tmp-glibc/work/armv7at2hf-neon-oe-linux-gnueabi/thermal-service-interface/1.0-r0/deploy-ipks/armv7at2hf-neon/libithermal0_1.0-r0_armv7at2hf-neon.ipk .


abc root
abc shell mount -o remount, rw /

abc push libiantenna0_1.0-r0_armv7at2hf-neon.ipk /tmp/
abc shell opkg install --force-reinstall --force-overwrite /tmp/libiantenna0_1.0-r0_armv7at2hf-neon.ipk
abc shell sync

abc push libsystemhal0_1.0-r0_armv7at2hf-neon.ipk /tmp/
abc shell opkg install --force-reinstall --force-overwrite /tmp/libsystemhal0_1.0-r0_armv7at2hf-neon.ipk
abc shell sync

pause
