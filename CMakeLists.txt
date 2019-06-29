cmake_minimum_required(VERSION 3.11)

project(n-body LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Quick REQUIRED)
find_package(OpenGL)

# course files
file(GLOB_RECURSE HDRS "src/*.hh" "src/*.h")
file(GLOB_RECURSE SRCS "src/*.cpp")

# qml files
set(QML "qml/qml.qrc")

# other files
set(OTHER_FILES "README.md")

add_executable(${PROJECT_NAME} ${SRCS} ${HDRS} ${QML} ${OTHER_FILES})
target_compile_definitions(${PROJECT_NAME} PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Quick)
target_link_libraries(${PROJECT_NAME} PRIVATE ${OPENGL_gl_LIBRARY})
