set(LIB_SOURCES
        ghosts/BlueGhost.cpp
        ghosts/BlueGhost.hpp
        ghosts/DefaultGhost.cpp
        ghosts/DefaultGhost.hpp
        ghosts/Ghost.cpp
        ghosts/Ghost.hpp
        ghosts/OrangeGhost.cpp
        ghosts/OrangeGhost.hpp
        ghosts/PinkGhost.cpp
        ghosts/PinkGhost.hpp
        ghosts/RedGhost.cpp
        ghosts/RedGhost.hpp
        )

add_library(lib_core ${LIB_SOURCES})
target_include_directories(lib_core PUBLIC ${CMAKE_SOURCE_DIR})

#add_clang_tidy_target(lint_lib_core ${LIB_SOURCES})
#add_dependencies(lint lint_lib_core)

#target_link_libraries(PacTeam2 PUBLIC lib_core)
