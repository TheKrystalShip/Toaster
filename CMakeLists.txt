cmake_minimum_required(VERSION 3.28)
project(toaster VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-Wall -Wno-unused-but-set-variable")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(SOURCES
    src/AudioEngine.cpp
    src/Camera2D.cpp
    src/DebugRenderer.cpp
    src/Errors.cpp
    src/GLSLProgram.cpp
    src/ImageLoader.cpp
    src/IMainGame.cpp
    src/InputManager.cpp
    src/IOManager.cpp
    src/Particle2D.cpp
    src/ParticleBatch2D.cpp
    src/ParticleEngine2D.cpp
    src/picoPNG.cpp
    src/ResourceManager.cpp
    src/ScreenList.cpp
    src/Sprite.cpp
    src/SpriteBatch.cpp
    src/SpriteFont.cpp
    src/TextureCache.cpp
    src/Timing.cpp
    src/Toaster.cpp
    src/Window.cpp
)

# Object library target: compiles the sources only once
add_library(objlib OBJECT ${SOURCES})

target_include_directories(objlib PUBLIC
    include
    include/Toaster
    ${SDL2_ttf_INCLUDE_DIRS}
    ${SDL2_mixer_INCLUDE_DIRS}
)

target_link_libraries(objlib PUBLIC
    ${SDL2_LIBRARIES}
    ${OPENGL_LIBRARIES}
    ${GLEW_LIBRARIES}
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
)
set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)

# shared and static libraries built from the same object files
add_library(${PROJECT_NAME} SHARED $<TARGET_OBJECTS:objlib>)
add_library(${PROJECT_NAME}s STATIC $<TARGET_OBJECTS:objlib>)
set_target_properties(${PROJECT_NAME}s PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
