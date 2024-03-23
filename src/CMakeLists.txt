add_library(toaster SHARED Camera2D.cpp
                           Errors.cpp
                           GLSLProgram.cpp
                           ImageLoader.cpp
                           IOManager.cpp
                           picoPNG.cpp
                           ResourceManager.cpp
                           Sprite.cpp
                           SpriteBatch.cpp
                           TextureCache.cpp
                           Timing.cpp
                           Toaster.cpp
                           Window.cpp
)
target_include_directories(toaster PRIVATE ${CMAKE_SOURCE_DIR}/include)
set_target_properties(toaster PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(toaster PROPERTIES OUTPUT_NAME_DEBUG toaster-d)
set_target_properties(toaster PROPERTIES OUTPUT_NAME_RELEASE toaster)
target_link_libraries(toaster PRIVATE SDL2 GL)

# Static lib
add_library(toaster-static STATIC Camera2D.cpp
                                  Errors.cpp
                                  GLSLProgram.cpp
                                  ImageLoader.cpp
                                  IOManager.cpp
                                  picoPNG.cpp
                                  ResourceManager.cpp
                                  Sprite.cpp
                                  SpriteBatch.cpp
                                  TextureCache.cpp
                                  Timing.cpp
                                  Toaster.cpp
                                  Window.cpp
)
target_include_directories(toaster-static PRIVATE ${CMAKE_SOURCE_DIR}/include)
set_target_properties(toaster-static PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(toaster-static PROPERTIES OUTPUT_NAME_DEBUG toaster-static-d)
set_target_properties(toaster-static PROPERTIES OUTPUT_NAME_RELEASE toaster-static)
target_link_libraries(toaster-static PRIVATE SDL2 GL)
