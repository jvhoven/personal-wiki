cmake_minimum_required(VERSION 3.8)
project(PersonalWiki)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)
find_package(Curses REQUIRED)

set(SOURCE_FILES main.cpp src/entry.hpp src/strategy/strategy.hpp src/strategy/text.hpp src/strategy/web.hpp src/wiki.hpp)
add_executable(PersonalWiki ${SOURCE_FILES})
target_link_libraries(PersonalWiki ${CURL_LIBRARIES})