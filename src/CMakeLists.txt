project(SlidingPuzzle VERSION 1.0 LANGUAGES CXX)

set(CPP_SOURCE_FILES main.cpp)
set(QML_SOURCE_FILES Main.qml)

qt_standard_project_setup(REQUIRES 6.6)

qt_add_executable(${PROJECT_NAME})

qt_add_qml_module(${PROJECT_NAME}
    URI ${PROJECT_NAME}
    VERSION ${PROJECT_VERSION}
    QML_FILES ${QML_SOURCE_FILES}
    SOURCES ${CPP_SOURCE_FILES}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
    app
    appplugin
)

set_target_properties(${PROJECT_NAME} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER refractiOOn.${PROJECT_NAME}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

add_subdirectory(app)
