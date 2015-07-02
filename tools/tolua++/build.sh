#!/bin/sh
cd "$( dirname "${BASH_SOURCE[0]}" )"
./tolua++mac -t -D -L basic.lua -o ../../lua/support/LuaCocos2d.cpp Cocos2d.pkg
./tolua++mac -t -D -L basic.lua -o ../../lua/support/LuaCode.cpp LuaCode.pkg
