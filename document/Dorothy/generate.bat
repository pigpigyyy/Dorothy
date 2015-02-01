set SRC_PATH=%~dp0
cd %SRC_PATH%/bin
cd %SRC_PATH%/../../tools/zbstudio/api/lua
%SRC_PATH%/bin/lua.exe %SRC_PATH%/bin/convert.lua
cd %SRC_PATH%/bin
lua.exe ldoc.lua .
pause
