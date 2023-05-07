SET(VERSION_SDL2 release-2.26.x)
SET(VERSION_SDL2_image SDL2)

set(BUILD_STATIC_LIBS ON CACHE BOOL INTERNAL "Build as a static library.")
# set(BUILD_SHARED_LIBS OFF CACHE BOOL INTERNAL "Build as a shared library.")

set(SDL2IMAGE_SAMPLES OFF CACHE BOOL "" FORCE)
set(SDL2IMAGE_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG ${VERSION_SDL2}
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
    OVERRIDE_FIND_PACKAGE
)
FetchContent_Declare(
    SDL2_image
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_image.git
    GIT_TAG ${VERSION_SDL2_image}
    GIT_SHALLOW TRUE
    GIT_PROGRESS TRUE
)

FetchContent_MakeAvailable(SDL2)
FetchContent_MakeAvailable(SDL2_image)

# list(APPEND CPP_LIBS SDL2d.lib)
message(STATUS SDL2_image_SOURCE_DIR ${SDL2_image_SOURCE_DIR})
message(STATUS sdl2_SOURCE_DIR ${sdl2_SOURCE_DIR})

list(APPEND CPP_INCLUDE_DIRS ${sdl2_SOURCE_DIR}/include ${SDL2_image_SOURCE_DIR})
list(APPEND CPP_LIBS SDL2::SDL2 SDL2::SDL2main SDL2_image)
