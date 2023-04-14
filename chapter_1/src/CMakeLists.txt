file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library(${PROJECT_LIB} STATIC 
    ${SRC_FILES}
    )

target_include_directories(${PROJECT_LIB} PUBLIC
                            ${CONAN_INCLUDE_DIRS}
                            ${CMAKE_SOURCE_DIR}
                        )

target_link_libraries(${PROJECT_LIB} PUBLIC
                        ${CONAN_LIBS}
                        )