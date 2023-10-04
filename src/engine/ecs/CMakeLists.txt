add_library(ecs INTERFACE
        types.hpp
        entityManager.hpp
        componentArray.hpp
        componentManager.hpp
        system.hpp
        systemManager.hpp
        ecsPlaceholder.hpp
)

install(TARGETS ecs DESTINATION ecs)
