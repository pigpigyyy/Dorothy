#!/bin/sh
cd "$( dirname "${BASH_SOURCE[0]}" )"
./tolua++mac -t -D -L basic.lua -o ../../lua/support/LuaBinding.cpp LuaBinding.pkg
./tolua++mac -t -D -L basic.lua -o ../../lua/support/LuaCode.cpp LuaCode.pkg
