add_library(spawners "")

target_link_libraries(spawners
        PUBLIC
        engine
        components
        SDL2::SDL2
)
target_sources(spawners PUBLIC playerSpawner.cpp appleSpawner.cpp)

install(TARGETS spawners DESTINATION player)
