cmake_minimum_required(VERSION 3.14)
project(NpcBattle LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
add_executable(npc_battle
    main.cpp
    src/npc.cpp
    src/squirrel.cpp
    src/druid.cpp
    src/ork.cpp
)
target_include_directories(npc_battle PRIVATE include)
add_executable(npc_tests
    test/main_test.cpp
    src/npc.cpp
    src/squirrel.cpp
    src/druid.cpp
    src/ork.cpp
)
target_include_directories(npc_tests PRIVATE include)
target_link_libraries(npc_tests PRIVATE gtest gtest_main pthread)