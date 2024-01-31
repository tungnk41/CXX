set ADB=_adb
%ADB% wait-for-device
timeout /t 6 > nul
%ADB% shell sldd hmi tc 91 203
%ADB% shell sldd hmi tc 91 204
%ADB% shell sldd hmi tc 91 205
%ADB% shell sldd hmi tc 95 21 1
pause
