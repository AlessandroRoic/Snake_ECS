add_library(components
        INTERFACE
        sprite.hpp
        transform.hpp
        snake.hpp)

target_link_libraries(components
        INTERFACE
        math
)

install(TARGETS components DESTINATION components)
