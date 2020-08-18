if("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
	cmake_minimum_required(VERSION 2.8.9)
	set(CMAKE_BUILD_TYPE Release)
	if(WIN32)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
		set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
	else()
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
		set(CMAKE_EXECUTABLE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")
	endif()
endif()

if(NOT TARGET CommonUtils)
	execute_process(COMMAND git clone https://github.com/sumitdhyani/CommonUtils.git "${CMAKE_SOURCE_DIR}/CommonUtils")
endif()

if("${CMAKE_CURRENT_SOURCE_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
	add_subdirectory(CommonUtils)	
endif()

set (ALL_SOURCES ConsoleOutputStreamDecorator.hpp
FileOutputStreamDecorator.hpp
ILogger.hpp
IOutputStream.hpp
IOutputStreamFactory.hpp
Logger.hpp
LoggerCommon.hpp
)

project(Logger)
add_library("${PROJECT_NAME}" STATIC "${ALL_SOURCES}")

add_dependencies("${PROJECT_NAME}" CommonUtils)
#Needed for quaified paths, for protejects which have external dependencies
target_include_directories("${PROJECT_NAME}" PUBLIC "${CMAKE_SOURCE_DIR}" "$ENV{BOOST_ROOT}")
set_target_properties("${PROJECT_NAME}" PROPERTIES LINKER_LANGUAGE CXX)
