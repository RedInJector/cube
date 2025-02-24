cmake_minimum_required(VERSION 3.0)

project(Bresenham_cube)

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
