
-----------------------------------------------------------------------------------------------------------------------

project "basic_1"
  language "C++"
  kind "ConsoleApp"

  files { "*.cpp", "*.hpp" }
  libdirs { "../../boost/stage/lib" }

  includedirs { "../../boost", "../../" }

  links { "oberon",
          "boost_chrono",
          "boost_date_time", 
          "boost_filesystem", 
          "boost_regex", 
          "boost_program_options", 
          "boost_system" }

  buildoptions { "-std=c++11" }
  linkoptions { "-static -pthread" }

  configuration "Debug"
       targetdir( "../../builds/basic_1")
       defines { "DEBUG" }
       flags { "Symbols" }
       
  configuration "Release"
       targetdir ("../../builds/basic_1")
       defines { "NDEBUG" }
       flags { "Optimize" }


----------------------------------------------------------------------------------------------------------------------
