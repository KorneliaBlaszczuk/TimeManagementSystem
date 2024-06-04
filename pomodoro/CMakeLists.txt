cmake_minimum_required(VERSION 3.11.0)
project(pomodoro VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

set(PROJECT_SOURCES pomodoro.h pomodoro.cpp)
add_executable(pomodoro test.cpp ${PROJECT_SOURCES})

add_executable(testGoogle testPomodoro.cpp ${PROJECT_SOURCES})
target_link_libraries(testGoogle PUBLIC gtest_main)