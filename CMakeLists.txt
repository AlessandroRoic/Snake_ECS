cmake_minimum_required(VERSION 3.26)
project(Snake_ECS)
set(CMAKE_CXX_STANDARD 20)

add_subdirectory(src)

install(TARGETS Snake_ECS DESTINATION .)

include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "Snake_ECS")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_GENERATOR "ZIP")
include(CPack)
