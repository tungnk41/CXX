_adb shell mv /etc/dlt-runtime-context.cfg /etc/dlt-runtime-context.cfg.bak
_adb push dlt-runtime-context.cfg /etc
_adb shell sync
