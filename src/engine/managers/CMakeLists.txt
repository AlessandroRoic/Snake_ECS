add_library(managers "")

target_include_directories(managers INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(managers
        PUBLIC
        SDL2::SDL2
)

target_link_libraries(managers
        INTERFACE
        debuggers
        ecs
)

target_sources(managers
        PUBLIC
        keyboardManager.cpp
        resourceManager.cpp
)

install(TARGETS managers DESTINATION managers)
