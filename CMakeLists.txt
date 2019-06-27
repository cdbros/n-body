cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)

## only for deep cuz he got custom installation lol
set(CMAKE_PREFIX_PATH /Users/deep/Qt/5.13.0/clang_64/lib/cmake/Qt5)

project(n-body LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)

file(GLOB_RECURSE SRCS "src/*.cpp")
set(QML "qml/qml.qrc")

add_executable(${PROJECT_NAME} ${SRCS} ${QML})
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick)
