cmake_minimum_required(VERSION 3.26)
project(SlidingPuzzle VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

set(CPP_SOURCE_FILES
    main.cpp
    GameModel.hpp GameModel.cpp
    Tile.hpp Tile.cpp
)
set(QML_SOURCE_FILES
    Main.qml
    Tile.qml
    GameArea.qml
    GameBoard.qml
    GameController.qml
)

qt_add_executable(${PROJECT_NAME} ${CPP_SOURCE_FILES})

qt_add_qml_module(${PROJECT_NAME}
    URI SlidingPuzzle
    VERSION 1.0
    QML_FILES ${QML_SOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
