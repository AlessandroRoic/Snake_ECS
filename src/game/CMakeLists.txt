add_library(game "")

target_include_directories(game INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(game
        PRIVATE
        engine
        SDL2::SDL2
        SDL2_image::SDL2_image
        SDL2_ttf::SDL2_ttf
        SDL2_mixer::SDL2_mixer)

target_sources(game
        PUBLIC
        gameManager.cpp
)

install(TARGETS game DESTINATION game)
