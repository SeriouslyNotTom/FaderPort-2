cmake_minimum_required (VERSION 3.8)
project(FaderPort2 VERSION 0.0.0.1) # MAJOR.MINOR.PATCH.TWEAK

include_directories("src")

file(GLOB_RECURSE SRC
    "src/*"
)

add_executable (${PROJECT_NAME} ${SRC} "src/fp2.h")

#paths for build outputs
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/output/debug/build_files)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/output/debug/)


############################ Library Compiling and/or Linking ############################

if(WIN32)

	target_link_libraries(FaderPort2 Winmm.lib)
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")

endif(WIN32)

if(UNIX)

endif(UNIX)