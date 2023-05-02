cmake_minimum_required(VERSION 3.11.3)

cmake_path(GET CMAKE_SOURCE_DIR FILENAME PROJECT_NAME)

project(${PROJECT_NAME} LANGUAGES CXX)

set(PROJECT_LIB ${PROJECT_NAME}_lib)
set(PROJECT_TEST ${PROJECT_NAME}_test)
set(PROJECT_APP ${PROJECT_NAME}_app)

message("CMAKE_C_FLAGS_RELEASE >>> "  ${CMAKE_C_FLAGS_RELEASE})
message("CMAKE_C_FLAGS >>> "  ${CMAKE_C_FLAGS})
message("CMAKE_CXX_FLAGS >>> "  ${CMAKE_CXX_FLAGS})
message("CMAKE_CONFIGURATION_TYPES >>> "  ${CMAKE_CONFIGURATION_TYPES})
message("CMAKE_CFG_INTDIR >>> "  ${CMAKE_CFG_INTDIR})
message("CMAKE_CUDA_FLAGS >>> "  ${CMAKE_CUDA_FLAGS})
message("CMAKE_Fortran_FLAGS >>> "  ${CMAKE_Fortran_FLAGS})

message("CMAKE_CURRENT_SOURCE_DIR  >>>  " ${CMAKE_CURRENT_SOURCE_DIR})
message("CMAKE_CURRENT_BINARY_DIR  >>>  " ${CMAKE_CURRENT_BINARY_DIR})

# must set output build dir by default is none. user must config manual
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

message("CMAKE_ARCHIVE_OUTPUT_DIRECTORY: ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}") # workspace/build/Debug
message("CMAKE_LIBRARY_OUTPUT_DIRECTORY: ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}")
message("CMAKE_RUNTIME_OUTPUT_DIRECTORY: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

# folders, files, libs
set(CPP_INCLUDE_DIRS "")
set(CPP_HEADER_FILES "")
set(CPP_SOURCE_FILES "")
set(CPP_LIBS "")

set(BUILD_SHARED_LIBS FALSE)

if (MSVC)
    add_compile_options(/W3)
    set(COMPILE_OPTIONS "/W4 /WX /Wv:18")
else()
    set(COMPILE_OPTIONS "-Wall -Wextra -pedantic")
endif()

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
    include(FetchContent)
    include(cmake/fetch_googletest.cmake)
    include(cmake/fetch_sdl.cmake)
    # include(sdl)
    include(googletest)
    list(APPEND SOURCE_LIB sdl)
    list(APPEND SOURCE_LIB googletest)


    add_subdirectory(src)

    if(${BUILD_TEST})
        add_subdirectory(test)
    endif(${BUILD_TEST})

    if(${BUILD_APP})
        add_subdirectory(app)
        add_dependencies(${PROJECT_APP} ${PROJECT_LIB})
    endif(${BUILD_APP})

endif(${BUILD_TEST} OR ${BUILD_APP})
