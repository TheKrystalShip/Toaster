cmake_minimum_required(VERSION 3.28)
project(toaster VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "-Wall -Wno-unused-but-set-variable")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include(CTest)
enable_testing()

set(SOURCES src/AudioEngine.cpp
            src/Camera2D.cpp
            src/Errors.cpp
            src/GLSLProgram.cpp
            src/ImageLoader.cpp
            src/InputManager.cpp
            src/IOManager.cpp
            src/picoPNG.cpp
            src/ResourceManager.cpp
            src/Sprite.cpp
            src/SpriteBatch.cpp
            src/SpriteFont.cpp
            src/TextureCache.cpp
            src/Timing.cpp
            src/Toaster.cpp
            src/Window.cpp
)

add_library(toaster SHARED ${SOURCES})
target_include_directories(toaster PUBLIC include ${SDL2_ttf_INCLUDE_DIRS} ${SDL2_mixer_INCLUDE_DIRS})
target_link_libraries(toaster PUBLIC ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer)
set_target_properties(toaster PROPERTIES LINKER_LANGUAGE CXX)

# Static lib
add_library(toaster-static STATIC ${SOURCES})
target_include_directories(toaster-static PUBLIC include)
target_link_libraries(toaster-static PUBLIC ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
set_target_properties(toaster-static PROPERTIES LINKER_LANGUAGE CXX)


install(TARGETS toaster
    LIBRARY DESTINATION bin
    ARCHIVE DESTINATION bin
)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
