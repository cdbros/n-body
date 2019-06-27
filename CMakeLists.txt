cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/mini-cmake-qt/cmake)
set(CMAKE_PREFIX_PATH /Users/deep/Qt/5.13.0/clang_64/lib/cmake/Qt5)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

include(QtCommon)

file(GLOB_RECURSE SRCS "src/*.cpp")

set(SOURCE_FILES ${SRC})

add_project_meta(META_FILES_TO_INCLUDE)

set(RESOURCE_FILES project.qrc)

find_package(Qt5 COMPONENTS Core REQUIRED)
find_package(Qt5 COMPONENTS Quick REQUIRED)

add_executable(${PROJECT_NAME} ${OS_BUNDLE} # Expands to WIN32 or MACOS_BUNDLE depending on OS
        ${SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES}
        )
