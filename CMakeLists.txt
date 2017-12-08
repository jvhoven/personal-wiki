cmake_minimum_required(VERSION 3.8)
project(PersonalWiki)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake_modules)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wextra")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic-errors")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-c99-extensions")

find_package(CURL REQUIRED)
find_package(Curses REQUIRED)
find_package(ZLib REQUIRED)
find_package(SQLite3 REQUIRED)

include_directories(libs ${ZLIB_INCLUDE_DIRS} ${SQLITE3_INCLUDE_DIRS})

set(SOURCE_FILES src/main.cpp)
add_executable(PersonalWiki ${SOURCE_FILES})
target_link_libraries(PersonalWiki ${CURL_LIBRARIES} ${ZLIB_LIBRARIES} sqlite3)