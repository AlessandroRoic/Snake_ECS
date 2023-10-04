add_library(components
        INTERFACE
        transform.hpp
        renderable.hpp)

target_link_libraries(components
        INTERFACE
        math
)

install(TARGETS components DESTINATION components)
