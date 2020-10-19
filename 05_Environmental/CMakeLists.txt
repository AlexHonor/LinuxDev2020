cmake_minimum_required(VERSION 2.6)
project(environmental)

add_custom_target(allclean
    COMMAND rm -rf CMakeFiles *.cmake CMakeCache.txt environmental Makefile
)

INCLUDE(CheckIncludeFiles)

option(without-UTF "Don't use PCRE2_UCP")

if (NOT without-UTF)
    remove_definitions(-DPCRE2_UCP)
endif()

find_library(NCURSESW_LIBRARY ncursesw)
find_library(PCRE2_LIBRARY pcre2-8)

CHECK_INCLUDE_FILES("ncurses.h" NCURSES_HEADER)
CHECK_INCLUDE_FILES("pcre2.h" PCRE2_HEADER)

if ((NOT NCURSES_HEADER) OR (NOT PCRE2_HEADER))
    message(STATUS "Includes not found")
endif ()

add_executable(environmental Window.c)

target_link_libraries(environmental ${NCURSESW_LIBRARY} ${PCRE2_LIBRARY})
