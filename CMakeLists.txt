cmake_minimum_required(VERSION 3.20)
project(clox)

add_executable(clox src/main.cpp src/token.cpp)

include(FetchContent)
set(BUILD_SHARED_LIBS ON CACHE BOOL "" FORCE)
FetchContent_Declare(
	fmt
	GIT_REPOSITORY https://github.com/fmtlib/fmt
	GIT_TAG 12.0.0
)
FetchContent_MakeAvailable(fmt)

target_include_directories(clox PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(clox PRIVATE fmt::fmt)