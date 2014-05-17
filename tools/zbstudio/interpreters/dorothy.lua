local dorothy
local win = ide.osname == "Windows"
local mac = ide.osname == "Macintosh"

return {
	name = "Dorothy",
	description = "Dorothy game engine",
	api = {"baselib", "dorothy"},
	frun = function(self,wfilename,rundebug)
		dorothy = dorothy or ide.config.path.dorothy -- check if the path is configured
		if not dorothy then
			local sep = win and ';' or ':'
			local default =
				win and ([[C:\Program Files\Dorothy]]..sep..[[D:\Program Files\Dorothy]]..sep..
						[[C:\Program Files (x86)\Dorothy]]..sep..[[D:\Program Files (x86)\Dorothy]]..sep)
				or mac and ('/Applications/dorothy.app/Contents/MacOS'..sep)
				or ''
			local path = default
							..(os.getenv('PATH') or '')..sep
							..(GetPathWithSep(self:fworkdir(wfilename)))..sep
							..(os.getenv('HOME') and GetPathWithSep(os.getenv('HOME'))..'bin' or '')
			local paths = {}
			for p in path:gmatch("[^"..sep.."]+") do
				dorothy = dorothy or GetFullPathIfExists(p, win and 'Dorothy.exe' or 'Dorothy')
				table.insert(paths, p)
			end
			if not dorothy then
				DisplayOutput("Can't find dorothy executable in any of the following folders: "
					..table.concat(paths, ", ").."\n")
				return
			end
		end

		if not GetFullPathIfExists(self:fworkdir(wfilename), 'main.lua') then
			DisplayOutput("Can't find 'main.lua' file in the current project folder.\n")
			return
		end

		if rundebug then
			DebuggerAttachDefault({runstart = ide.config.debugger.runonstart == true})
		end

		local cmd = ('"%s" "%s"%s'):format(dorothy,
			self:fworkdir(wfilename), rundebug and ' -debug' or '')
		-- CommandLineRun(cmd,wdir,tooutput,nohide,stringcallback,uid,endcallback)
		return CommandLineRun(cmd,self:fworkdir(wfilename),true,false,nil,nil,
			function() ide.debugger.pid = nil end)
	end,
	fprojdir = function(self,wfilename)
		return wfilename:GetPath(wx.wxPATH_GET_VOLUME)
	end,
	fworkdir = function(self,wfilename)
		return ide.config.path.projectdir or wfilename:GetPath(wx.wxPATH_GET_VOLUME)
	end,
	hasdebugger = true,
	fattachdebug = function(self) DebuggerAttachDefault() end,
	scratchextloop = true,
}
