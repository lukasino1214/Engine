# Project definition
cmake_minimum_required(VERSION 3.9)

#set(CMAKE_TOOLCHAIN_FILE "C:/dev/scripts/buildsystems/vcpkg.cmake")

project(Engine)

# Source files
#set(CMAKE_BUILD_TYPE Debug)
set(dir ${CMAKE_CURRENT_SOURCE_DIR})
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/source")
set(LIB_DIR "${CMAKE_CURRENT_SOURCE_DIR}/libraries")

#file(COPY ${SRC_DIR}/res DESTINATION ${dir}/build)
file(REMOVE_RECURSE  ${dir}/build/Debug/res)
file(COPY ${dir}/resources DESTINATION ${dir}/build/Debug)


file(GLOB APP_S "${SRC_DIR}/*.cpp")
file(GLOB APP_H "${SRC_DIR}/*.h")

file(GLOB REN_S "${SRC_DIR}/Rendering/*.cpp")
file(GLOB REN_H "${SRC_DIR}/Rendering/*.h")

file(GLOB GUI_S "${SRC_DIR}/GUI/*.cpp")
file(GLOB GUI_H "${SRC_DIR}/GUI/*.h")

find_package(imgui CONFIG REQUIRED)
find_path(STB_INCLUDE_DIRS "stb.h")
find_package(glm CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glfw3 CONFIG REQUIRED)

add_executable(${PROJECT_NAME} ${APP_S} ${APP_H} ${REN_S} ${REN_H} ${GUI_S} ${GUI_H})
target_include_directories(${PROJECT_NAME} PRIVATE "${SRC_DIR}")
set_property(TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 17)

target_include_directories(${PROJECT_NAME} PRIVATE ${STB_INCLUDE_DIRS})  
target_link_libraries(${PROJECT_NAME} PRIVATE glm::glm)  
target_link_libraries(${PROJECT_NAME} PRIVATE imgui::imgui)   
target_link_libraries(${PROJECT_NAME} PRIVATE glad::glad)  
target_link_libraries(${PROJECT_NAME} PRIVATE glfw) 

file(COPY ${dir}/resources DESTINATION ${dir}/build/Debug)