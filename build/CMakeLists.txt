
cmake_minimum_required (VERSION 2.8)
project(Sanntid_miniproject)

include_directories (../src/ )
include_directories (../miniproject-files/network/ )




file (GLOB_RECURSE PROJECT_HEADERS ../src/*.h  ../miniproject-files/network/*.h)
file (GLOB_RECURSE PROJECT_SOURCES ../src/*.c  ../miniproject-files/network/*.c)
file (GLOB         PROJECT_CONFIGS CMakeLists.txt
                                  .gitmodules)





source_group ("headers" FILES ${PROJECT_HEADERS})
source_group ("sources" FILES ${PROJECT_SOURCES})

# set(SELF_MADE_FLAGS " -std=gnu11 -pthread -lm -lcomedi")
# set(SELF_MADE_FLAGS " -std=gnu11 -pthread -lm")
set(SELF_MADE_FLAGS "")


add_definitions(${SELF_MADE_FLAGS})
# SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${SELF_MADE_FLAGS}")
SET(CMAKE_CXX_FLAGS  " ${CMAKE_CXX_FLAGS} ${SELF_MADE_FLAGS}")
SET(CMAKE_EXE_LINKER_FLAGS  "${CMAKE_EXE_LINKER_FLAGS} ${SELF_MADE_FLAGS}")

add_definitions (-DPROJECT_SOURCE_DIR=\"${PROJECT_SOURCE_DIR}\")
add_executable (${PROJECT_NAME} ${PROJECT_SOURCES} ${PROJECT_HEADERS} ${PROJECT_CONFIGS})
target_link_libraries (${PROJECT_NAME})
set_target_properties (${PROJECT_NAME} PROPERTIES
RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${PROJECT_NAME})
