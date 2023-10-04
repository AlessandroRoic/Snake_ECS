add_library(debuggers "")

target_link_libraries(debuggers
        PUBLIC
        SDL2::SDL2
)
target_sources(debuggers PUBLIC logger.cpp)

install(TARGETS debuggers DESTINATION debuggers)
