solution "Solution"
    location("builds")
    configurations { "Debug", "Release" }
    
-----------------------------------------------------------------------------------------------------------------------
project "oberon"
    language "C++"
    kind "StaticLib" 
    
    files { "oberon/*.cpp", "oberon/*.hpp" } 
    
    libdirs { "boost/stage/lib" }
              
    includedirs { "boost", "." }
 
    links { "boost_chrono",
            "boost_date_time", 
            "boost_filesystem", 
            "boost_program_options", 
            "boost_system" }

    buildoptions { "-std=c++11" }
 
    configuration "Debug"
         targetdir( "builds/oberon")
         defines { "DEBUG" }
         flags { "Symbols" }
         
    configuration "Release"
         targetdir ("builds/oberon")
         defines { "NDEBUG" }
         flags { "Optimize" }

-----------------------------------------------------------------------------------------------------------------------

include "examples/basic_1"
include "examples/basic_2"
include "examples/subversion_clone"

