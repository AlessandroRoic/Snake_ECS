add_library(game "")

target_include_directories(game INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(game
        PRIVATE
        engine
)

target_sources(game
        PUBLIC
        gameManager.cpp
)

install(TARGETS game DESTINATION game)
