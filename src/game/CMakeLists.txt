add_subdirectory(spawners)
add_subdirectory(systems)
add_subdirectory(components)

add_library(game "")

target_include_directories(game INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(game
        PRIVATE
        spawners
        systems
        components
        engine
)

target_sources(game
        PUBLIC
        gameManager.cpp
)

install(TARGETS game DESTINATION game)
