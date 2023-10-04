add_library(utils "")

target_include_directories(utils INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(utils
        PUBLIC
        SDL2::SDL2
        SDL2_image::SDL2_image
)

target_sources(utils
        PUBLIC
        deltaTimer.cpp
        timer.cpp
)

install(TARGETS utils DESTINATION utils)
