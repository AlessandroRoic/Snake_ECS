add_library(components
        INTERFACE
        sprite.hpp
        transform.hpp
        snake.hpp
        gameOverScreen.hpp
        collider.hpp)

target_link_libraries(components
        INTERFACE
        math
        SDL2::SDL2
)

install(TARGETS components DESTINATION components)
