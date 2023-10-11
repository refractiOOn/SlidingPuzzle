project(app VERSION 1.0 LANGUAGES CXX)

set(CPP_PRECOMPILED_HEADER pch.hpp)
set(CPP_SOURCE_FILES
    GameModel.hpp GameModel.cpp
    GameTile.hpp GameTile.cpp
)
set(QML_SOURCE_FILES
    qmlfiles/GameArea.qml
    qmlfiles/GameBoard.qml
    qmlfiles/GameTileDelegate.qml
)

qt_add_library(${PROJECT_NAME} STATIC)

qt_add_qml_module(${PROJECT_NAME}
    URI ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    QML_FILES ${QML_SOURCE_FILES}
    SOURCES ${CPP_SOURCE_FILES}
)

target_precompile_headers(${PROJECT_NAME} PRIVATE ${CPP_PRECOMPILED_HEADER})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Quick
)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})