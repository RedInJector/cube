cmake_minimum_required(VERSION 3.0)

project(Bresenham_cube)

set(CMAKE_BUILD_TYPE Debug)

set("SOURCE_FILES"  cube.cpp 
					Bresenham.cpp
					Math3d.cpp
					engine.cpp
	)
add_executable(cube ${SOURCE_FILES})
target_include_directories(cube PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(cube PRIVATE SDL2::SDL2)

install(TARGETS cube DESTINATION ${CUBE_INSTALL_BIN_DIR})

project(Bresenham_line)

set("SOURCE_FILES"  line.cpp 
					Bresenham.cpp
	)

add_executable(line ${SOURCE_FILES})
target_include_directories(line PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(line PRIVATE SDL2::SDL2)

install(TARGETS line DESTINATION ${CUBE_INSTALL_BIN_DIR})



project(test)
set("SOURCE_FILES"  test.cpp 
					Math3d.cpp
					engine.cpp
	)

add_executable(test ${SOURCE_FILES})
target_include_directories(test PUBLIC ${SDL2_INCLUDE_DIRS})
target_link_libraries(test PRIVATE SDL2::SDL2)

install(TARGETS test DESTINATION ${CUBE_INSTALL_BIN_DIR})
