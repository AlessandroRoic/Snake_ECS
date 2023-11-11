add_subdirectory(ecs)
add_subdirectory(math)
add_subdirectory(debuggers)
add_subdirectory(managers)
add_subdirectory(utils)

add_library(engine "")

target_include_directories(engine INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(engine
        PUBLIC
        managers
        utils
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer
)

target_link_libraries(engine
        INTERFACE
        components
        ecs
        math
        debuggers
)

target_sources(engine
        PUBLIC
        engine.cpp
)

install(TARGETS engine DESTINATION engine)
