cmake_minimum_required(VERSION 3.11.0)
project(TimeSystem VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY https://github.com/google/googletest.git
   GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

set(PROJECT_SOURCES
   reminder.h reminder.cpp
   calendar.h calendar.cpp
   pomodoro.h pomodoro.cpp
   event.h event.cpp
   task.h task.cpp
   plan.h plan.cpp
   interface.h interface.cpp
   functions.h functions.cpp
   user.h
   modes.h modes.cpp)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/usersData)

add_executable(TimeSystem main.cpp ${PROJECT_SOURCES})

# Add a custom command to create users.txt with the specified content
add_custom_command(
    TARGET TimeSystem POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "User name: korni" > ${CMAKE_BINARY_DIR}/testUsers.txt
)

add_executable(testGoogle
   testInterface.cpp
   testPomodoro.cpp
   testReminder.cpp
   testEvent.cpp
   testTask.cpp
   testCalendar.cpp
   testUser.cpp ${PROJECT_SOURCES})
target_link_libraries(testGoogle PUBLIC gtest_main)
