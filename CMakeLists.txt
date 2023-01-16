cmake_minimum_required(VERSION 3.21)
project(alpha LANGUAGES CXX)

set (CMAKE_CXX_STANDARD 23)
set (CMAKE_BUILD_TYPE RelWithDebInfo)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

add_executable(alpha src/main.cpp )

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})

target_include_directories(alpha PRIVATE "include")
target_include_directories(alpha PRIVATE "include/Core")
target_include_directories(alpha PRIVATE "assets")
target_link_libraries(alpha PRIVATE sfml-graphics sfml-window sfml-audio)

if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET alpha POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:alpha> $<TARGET_FILE_DIR:omega> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS alpha)