cmake_minimum_required(VERSION 3.28)
project(random_2d_plant_generator)

set(CMAKE_CXX_STANDARD 23)

add_executable(
	# TODO: Use variable.
	random_2d_plant_generator
	main.cpp
	random_2d_plant_generator/plant.cpp
	random_2d_plant_generator/branch.cpp
)

target_sources(
	${CMAKE_PROJECT_NAME}
	PUBLIC FILE_SET CXX_MODULES TYPE CXX_MODULES FILES
	random_2d_plant_generator/random_2d_plant_generator.cppm
	random_2d_plant_generator/plant.cppm
	random_2d_plant_generator/branch.cppm
)

include(FetchContent)

set(BUILD_SHARED_LIBS OFF)

FetchContent_Declare(
	SFML
	GIT_REPOSITORY
	https://github.com/SFML/SFML.git GIT_TAG 2.6.1
)

FetchContent_MakeAvailable(SFML)

target_link_libraries(
	${CMAKE_PROJECT_NAME}
	sfml-graphics
)