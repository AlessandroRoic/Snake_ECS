add_library(interfaces INTERFACE
        observer.hpp
        subscriber.hpp
)

install(TARGETS interfaces DESTINATION interfaces)
