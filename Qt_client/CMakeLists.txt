cmake_minimum_required(VERSION 3.16)

project(Qt_client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Quick Charts Mqtt Sql Qml QuickControls2)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appQt_client
    main.cpp
    mqttmanager.cpp
    mqttmanager.h
)

qt_add_qml_module(appQt_client
    URI Qt_client
    VERSION 1.0
    QML_FILES Main.qml
    SOURCES mqttmanager.cpp

)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appQt_client PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appQt_client
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appQt_client
    PRIVATE Qt6::Core Qt6::Quick Qt6::Charts Qt6::Mqtt Qt6::Sql Qt6::Qml Qt6::QuickControls2
)

# Include the Qt resource file
qt_add_resources(appQt_client "resources"
    PREFIX /
    FILES Main.qml
)

include(GNUInstallDirs)
install(TARGETS appQt_client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

#Copy the SQLite database to the build directory
# add_custom_command(TARGET appQt_client POST_BUILD
#     COMMAND ${CMAKE_COMMAND} -E copy_if_different
#     ${CMAKE_SOURCE_DIR}/sensordata.db
#     $<TARGET_FILE_DIR:appQt_client>
# )
