set ADB=_adb

@echo off
SET /A "index = 1"
SET /A "count = 1000000"
:while
if %index% leq %count% (
	%ADB% wait-for-device forward  tcp:3490 tcp:3490
	echo %index%
	sleep 1
	SET /A "index = index + 1"
	goto :while
)

pause