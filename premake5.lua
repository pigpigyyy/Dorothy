if not _PREMAKE_VERSION then
	os.execute('premake5 tolua')
	os.execute('premake5 vs2015')
	return
end

local function runCmd(...)
	local cmd = string.format(...)
	print(cmd)
	os.execute(cmd)
end

newaction {
	trigger     = "tolua",
	description = "binding cpp to lua",
	execute     = function ()
			if os.is('windows') then
				local toluapp = path.join(os.getcwd(), 'tools/tolua++/tolua++.exe')
				runCmd('%s -t -D -L tools/tolua++/basic.lua -o "lua/support/LuaCocos2d.cpp" tools/tolua++/Cocos2d.pkg', toluapp)
				runCmd('%s -t -D -L tools/tolua++/basic.lua -o "lua/support/LuaCode.cpp" tools/tolua++/LuaCode.pkg', toluapp)
		else
			error "this action not impl yet."
		end
	end
}

newaction {
	trigger		= 'ndkbuild',
	description = "android ndk build.",
	execute     = function ()
		local APP_ANDROID_ROOT = path.join(os.getcwd(), 'project', 'proj.android')
		local NDK_DEBUG = 1
		local NDK_MODULE_PATH = {
			os.getcwd(),
		}
		runCmd("cd project\\proj.android &ndk-build -j4 NDK_DEBUG=%d -C %s NDK_MODULE_PATH=%s", NDK_DEBUG, APP_ANDROID_ROOT, table.concat(NDK_MODULE_PATH, ';'))
	end
}

newaction {
	trigger		= 'apk',
	description = 'pack apk.',
	execute		= function()
		runCmd("gradlew build")
	end
}

newoption 
{
	trigger = "to",
	value   = "path",
	description = "Set the output location for the generated files"
}


solution "Dorothy-premake"
	configurations { "Debug", "Release" }

	location (path.join(_OPTIONS['to'] or "build", _ACTION))

	language "C++"

	includedirs {
		"cocos2dx",
		"cocos2dx/include",
		"cocos2dx/extensions",
		"cocos2dx/kazmath/include",
		"cocos2dx/platform",

		"external/sqlite3/include",
		"external/Box2D",
		"external",

		"cocosDenshion/include",
	}

	defines { "COCOS2D_STATIC", }

	configuration "Debug"
		targetdir "bin/debug"
		objdir	  "bin/obj/debug"

  		defines { "_DEBUG" }
		flags   { "Symbols" }

	configuration "Release"
		targetdir   "bin/release"
		objdir		"bin/obj/release"

		defines     { "NDEBUG" }
		flags       { "OptimizeSize" }

	configuration "vs*"
		buildoptions { "/MTd" }
		defines { "_CRT_SECURE_NO_WARNINGS" }

	configuration "windows"
		defines { "_WINDOWS", "WIN32", }

		includedirs {
			"cocos2dx/platform/win32",
			"cocos2dx/platform/third_party/win32",
			"cocos2dx/platform/third_party/win32/*",
		}
	configuration "android"
		includedirs {
			"cocos2dx/platform/android",
			"cocos2dx/platform/third_party/android/prebuilt/libcurl/include",
		}


	project "libCocos2d"
		kind "StaticLib"

		files {
			"cocos2dx/**.c",
			"cocos2dx/**.cpp",
			"cocos2dx/**.h",
		}

		configuration "windows"
			excludes {
				"cocos2dx/platform/third_party/**.*",
				"cocos2dx/platform/ios/**.*",
				"cocos2dx/platform/android/**.*",
				"cocos2dx/platform/mac/**.*",
			}
		configuration "android"
			excludes {
				"cocos2dx/platform/third_party/**.*",
				"cocos2dx/platform/ios/**.*",
				"cocos2dx/platform/win32/**.*",
				"cocos2dx/platform/mac/**.*",
			}

	project "libDorothy"
		kind "StaticLib"

		files  {
			"dorothy/**.cpp",
			"dorothy/**.h",
		}

		includedirs {
			"dorothy"
		}

	project "libBox2D"
		kind "StaticLib"

		files  {
			"external/Box2D/**.cpp",
			"external/Box2D/**.h",
		}

	project "libLua"
		kind "StaticLib"

		files {
			"lua/**.c",
			"lua/**.cpp",
			"lua/**.h",
		}

		local lua_inc = {
			"lua",
			"lua/tolua",
			"lua/support",
			"lua/lpeg",
			"lua/lib/include",

			"dorothy",
		}

		includedirs (lua_inc)

	project "libCocosDenshion"
		kind "StaticLib"

		files { "cocosDenshion/include/*.*", }

		configuration "windows"
			files { "cocosDenshion/win32/*.*", }
		configuration "android"
			files { "cocosDenshion/android/*.*", }

	project "Dorothy"

		debugdir "project/Resources"

		files { "project/Classes/*.cpp", }

		links {
			"libCocos2d",
			"libDorothy",
			"libBox2D",
			"libLua",
			"libCocosDenshion",
		}

		includedirs {
			"project/Classes",
			unpack(lua_inc),
		}

		configuration "windows"
			kind "ConsoleApp"--"WindowedApp"

			files { "project/proj.win32/**.cpp", "project/proj.win32/**.rc",}
			
			libdirs { "lua/lib/win32", "cocos2dx/platform/third_party/win32/libraries" }

			local function T(d) return path.translate(path.join(os.getcwd(), d), "\\") end

			prelinkcommands {
				'xcopy /Y /Q ' .. T("cocos2dx\\platform\\third_party\\win32\\libraries\\*.dll") ..  ' "$(OutDir)"',
				'xcopy /Y /Q ' .. T("external\\sqlite3\\libraries\\win32\\*.*") .. ' "$(OutDir)"',
			}

			links {
				"opengl32",
				"ws2_32",
		        "wsock32",
		        -- sound.
		        "Strmiids",
				"winmm",
				"Ole32",
				"dsound",

				"lua51",
				"libcurl_imp",
				"libiconv",
				"pthreadVCE2",
				"glew32",
				"libzlib",
			}

		configuration "android"
			kind "SharedLib"
			files { "project/proj.android/**.cpp",}


if _ACTION == "clean" then
	os.rmdir("bin")
	os.rmdir("build")
end