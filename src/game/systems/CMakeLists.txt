add_library(systems "")

target_include_directories(systems INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(systems
        PUBLIC
        SDL2::SDL2
        SDL2_image::SDL2_image
        engine
        components
)

target_sources(systems
        PUBLIC
        snakeSystem.cpp
        render2DSystem.cpp
        collisionSystem.cpp
)

install(TARGETS systems DESTINATION systems)
