add_library(ecs INTERFACE
        ECSManager.hpp
        types.hpp
        entityManager.hpp
        componentArray.hpp
        componentManager.hpp
        system.hpp
        systemManager.hpp
)

install(TARGETS ecs DESTINATION ecs)
