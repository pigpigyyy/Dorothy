--[[--
  Use this file to specify System preferences.
  Review [examples](+F:\Desktop\Estrela Editor\cfg\user-sample.lua) or check [online documentation](http://studio.zerobrane.com/documentation.html) for details.
--]]--
editor.usetabs = true
editor.tabwidth = 4
editor.calltipdelay = 2000
editor.fontsize = 18
editor.fontname = "新宋体"
editor.showfncall = false

local G = ...
styles = G.loadfile('cfg/tomorrow.lua')('TomorrowNightBlue')
stylesoutshell = styles
