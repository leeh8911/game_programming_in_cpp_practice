cmake_minimum_required(VERSION 3.11.3)

cmake_path(GET CMAKE_SOURCE_DIR FILENAME PROJECT_NAME)

project(${PROJECT_NAME} LANGUAGES CXX)

if (MSVC)
    add_compile_options(/W4 /WX /MDd /Wv:18)
else()
    add_compile_options(-Wall -Wextra -pedantic)
endif()

set(PROJECT_LIB ${PROJECT_NAME}_lib)
set(PROJECT_TEST ${PROJECT_NAME}_test)
set(PROJECT_APP ${PROJECT_NAME}_app)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

option(BUILD_APP "Build example" OFF)
option(BUILD_TEST "Build example" OFF)
option(BUILD_DOC "Build example" OFF)

set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(${BUILD_DOC})
add_subdirectory(docs)
endif()

if (${BUILD_TEST} OR ${BUILD_APP})
    include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
    conan_basic_setup()

    add_subdirectory(src)

    if(${BUILD_TEST})
        add_subdirectory(test)
    endif(${BUILD_TEST})

    if(${BUILD_APP})
        add_subdirectory(app)
        add_dependencies(${PROJECT_APP} ${PROJECT_LIB})
    endif(${BUILD_APP})

endif(${BUILD_TEST} OR ${BUILD_APP})
