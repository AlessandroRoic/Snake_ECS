add_library(player "")

target_link_libraries(player
        PUBLIC
        engine
        components
        SDL2::SDL2
)
target_sources(player PUBLIC playerController.cpp)

install(TARGETS player DESTINATION player)
