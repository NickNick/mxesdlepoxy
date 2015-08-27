cmake_minimum_required(VERSION 3.1)

include(${PROJECT_SOURCE_DIR}/wubwubcmake/wub_find_modules.cmake)
include(${PROJECT_SOURCE_DIR}/wubwubcmake/enable_cpp14.cmake)

find_package(SDL2 REQUIRED)
find_package(epoxy REQUIRED)

add_executable(sdl_epoxy sdl_epoxy.cpp)
target_include_directories(sdl_epoxy PRIVATE ${SDL2_INCLUDE_DIRS} ${epoxy_INCLUDE_DIRS})

target_link_libraries(sdl_epoxy PRIVATE ${SDL2_LIBRARIES} ${epoxy_LIBRARIES})
if(MSYS)
	target_link_libraries(sdl_epoxy PRIVATE -Wl,-Bstatic imm32 version winmm)
endif()

