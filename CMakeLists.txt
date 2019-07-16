cmake_minimum_required(VERSION 3.10)

project(n-body LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(OpenGL REQUIRED)

# source files
file(GLOB_RECURSE HDRS "src/*.hh" "src/*.h")
file(GLOB_RECURSE SRCS "src/*.cpp" "src/*.c")

# other files
set(OTHER_FILES "README.md")

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS} ${QML} ${OTHER_FILES})

if (WIN32)
    set_property(TARGET ${PROJECT_NAME} PROPERTY WIN32_EXECUTABLE true)
endif (WIN32)

target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE OpenGL::GL)
