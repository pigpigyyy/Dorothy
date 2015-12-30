if not _PREMAKE_VERSION then
	os.execute('premake4 vs2013')
	return
end


newoption
{
	trigger = "to",
	value   = "path",
	description = "Set the output location for the generated files"
}


solution "Dorothy-premake"
	configurations { "Debug", "Release" }

	location ("build")

	language "C++"

	includedirs {
		"cocos2dx",
		"cocos2dx/include",
		"cocos2dx/extensions",
		"cocos2dx/kazmath/include",
		"cocos2dx/platform",

		"cocos2dx/platform/win32",
		"cocos2dx/platform/third_party/win32",
		"cocos2dx/platform/third_party/win32/*",

		"external/sqlite3/include",
		"external/Box2D",
		"external",

		"cocosDenshion/include",
	}

	buildoptions {
		"/MTd",--vs only
	}


	defines {
		"_WINDOWS", "WIN32", "COCOS2D_STATIC", "_CRT_SECURE_NO_WARNINGS"
	}


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

	project "libCocos2d"
		kind "StaticLib"

		files {
			"cocos2dx/**.c",
			"cocos2dx/**.cpp",
			"cocos2dx/**.h",
		}

		excludes {
			"cocos2dx/platform/third_party/**.*",
			"cocos2dx/platform/ios/**.*",
			"cocos2dx/platform/android/**.*",
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

		files {
			"cocosDenshion/win32/*.*",
			"cocosDenshion/include/*.*",
		}

	project "Dorothy"
		kind "ConsoleApp"--"WindowedApp"

		debugdir "project/Resources"

		files {
			"project/Classes/*.cpp",
			"project/proj.win32/*.cpp",
		}

		includedirs {
			"project/Classes",
			unpack(lua_inc),
		}

		libdirs {
			"lua/lib/win32",
			"cocos2dx/platform/third_party/win32/libraries"
		}

		local function T(d)
			return path.translate(path.join(os.getcwd(), d), "\\")
		end

		prelinkcommands {
			'xcopy /Y /Q ' .. T("cocos2dx\\platform\\third_party\\win32\\libraries\\*.dll") ..  ' "$(OutDir)"',
			'xcopy /Y /Q ' .. T("external\\sqlite3\\libraries\\win32\\*.*") .. ' "$(OutDir)"',
		}

		links {
			"libCocos2d",
			"libDorothy",
			"libBox2D",
			"libLua",
			"libCocosDenshion",

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
