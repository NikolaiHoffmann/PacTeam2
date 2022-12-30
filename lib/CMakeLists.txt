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
        Astar.cpp
        Astar.hpp
        BFS.cpp
        BFS.hpp
        Board.cpp
        Board.hpp
        Direction.cpp
        Direction.hpp
        Entity.cpp
        Entity.hpp
        Evaluation.cpp
        Evaluation.hpp
        EvaluationFunction.cpp
        EvaluationFunction.hpp
        Game.cpp
        Game.hpp
        PacmanAgent.cpp
        PacmanAgent.hpp
        PacmanKeyBoardAgent.cpp
        PacmanKeyBoardAgent.hpp
        PacmanMiniMaxAgent.cpp
        PacmanMiniMaxAgent.hpp
        PieceBoard.cpp
        PieceBoard.hpp
        Position.cpp
        Position.hpp
        )

add_library(lib_core ${LIB_SOURCES})
target_include_directories(lib_core PUBLIC ${CMAKE_SOURCE_DIR})

#add_clang_tidy_target(lint_lib_core ${LIB_SOURCES})
#add_dependencies(lint lint_lib_core)

#target_link_libraries(PacTeam2 PUBLIC lib_core)
