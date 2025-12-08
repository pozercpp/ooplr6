cmake_minimum_required(VERSION 3.10)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror=maybe-uninitialized")

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY false
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(npc_lib
    src/squirrel.cpp
    src/druid.cpp
    src/ork.cpp
    src/npc.cpp
)
target_include_directories(npc_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(patterns_lib 
  src/factory.cpp
  src/observers.cpp
)
target_include_directories(patterns_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(patterns_lib PUBLIC npc_lib)

add_executable(main main.cpp)
target_link_libraries(main patterns_lib npc_lib)