#!/bin/sh
cd "$( dirname "${BASH_SOURCE[0]}" )"
./tolua++mac -t -D -L basic.lua -o ../../lua/cocos2dx_support/LuaCocos2d.cpp Cocos2d.pkg
./tolua++mac -t -D -L basic.lua -o ../../lua/cocos2dx_support/LuaCode.cpp LuaCode.pkg
