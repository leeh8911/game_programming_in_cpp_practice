SET(VERSION_SDL2 release-2.26.5)
SET(VERSION_SDL2_IMAGE release-2.6.3)

FetchContent_Declare(
    SDL2main
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG ${VERSION_SDL2}
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    OVERRIDE_FIND_PACKAGE
)
FetchContent_MakeAvailable(SDL2main)

list(APPEND CPP_INCLUDE_DIRS ${sdl2main_SOURCE_DIR}/include)
list(APPEND CPP_LIBS ${PROJECT_SOURCE_DIR}/build/Debug/SDL2maind.lib)
list(APPEND CPP_LIBS ${PROJECT_SOURCE_DIR}/build/Debug/SDL2-staticd.lib)
list(APPEND CPP_LIBS ${PROJECT_SOURCE_DIR}/build/Debug/SDL2d.lib)

set(SDL2IMAGE_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE)
FetchContent_Declare(
    sdl2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG ${VERSION_SDL2_IMAGE}
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(sdl2_image)
list(APPEND CPP_INCLUDE_DIRS ${sdl2_image_SOURCE_DIR}/include)
