cmake_minimum_required(VERSION 3.10)
project(MACER VERSION 0.0.1 DESCRIPTION "Mumu Assisting Code Exploiting Ragnarok Online: X")

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# 设置构建过程输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/.debug/build")
# set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/.debug/bin)

# 添加项目内 include 目录
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/src/main
    ${PROJECT_SOURCE_DIR}/src/core/class
    ${PROJECT_SOURCE_DIR}/src/core/exception
    ${PROJECT_SOURCE_DIR}/src/core/platform
    ${PROJECT_SOURCE_DIR}/src/core/utility
    ${PROJECT_SOURCE_DIR}/src/module
)

# 查找 OpenCV 库
find_package(OpenCV REQUIRED PATHS $ENV{OpenCV_DIR} NO_DEFAULT_PATH)
if(OpenCV_FOUND)
    message(STATUS "Found OpenCV: ${OpenCV_VERSION}")
    message(STATUS "OpenCV cmake dir: $ENV{OpenCV_DIR}")
    message(STATUS "OpenCV include dirs: ${OpenCV_INCLUDE_DIRS}")
    message(STATUS "OpenCV libraries: ${OpenCV_LIBS}")
    foreach(LIB ${OpenCV_LIBS})
        message(STATUS "Library path: ${LIB}")
    endforeach()
    # include_directories(${OpenCV_INCLUDE_DIRS})
else()
    message(FATAL_ERROR "OpenCV not found")
endif()

# 设置源文件
file(GLOB_RECURSE SOURCES "src/*.cc")
file(GLOB_RECURSE HEADERS "include/*.h")

# 构建 exe，设置输出目录
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
# set_target_properties(${PROJECT_NAME} PROPERTIES
    # RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/.debug/bin"
# )

# 链接 OpenCV 库
target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS})

# 编译器标志（示例：开启优化，关闭无关警告）
if(MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE "/wd4819")
endif()

# 打印出链接器文件路径
message(STATUS "Linker file: ${CMAKE_LINKER}")