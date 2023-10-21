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
        inputManager.cpp
        resourceManager.cpp
        windowManager.cpp
        eventManager.cpp
        renderManager.cpp
)

install(TARGETS managers DESTINATION managers)
