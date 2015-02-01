#!/bin/sh
SRC_PATH="$( dirname "${BASH_SOURCE[0]}" )"
cd $SRC_PATH/../../tools/zbstudio/api/lua
$SRC_PATH/bin/lua-mac $SRC_PATH/bin/convert.lua
cd $SRC_PATH/bin
./lua-mac ldoc.lua .
