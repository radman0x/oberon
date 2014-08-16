
-----------------------------------------------------------------------------------------------------------------------
project "basic_2"
  language "C++"
  kind "ConsoleApp"

  files { "*.cpp", "*.hpp" }

  libdirs { "../../boost/stage/lib" }
  includedirs { "../../boost", "../../" }

  links { "oberon" }

  targetdir( "../../builds/basic_2")

  configuration { "gmake" }
    linkoptions { "-static -pthread" }
    buildoptions { "-std=c++11" }

  configuration "Debug"
       defines { "DEBUG" }
       flags { "Symbols" }

  configuration "Release"
      defines { "NDEBUG" }
      flags { "Optimize" }


-----------------------------------------------------------------------------------------------------------------------
