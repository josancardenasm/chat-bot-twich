cmake_minimum_required(VERSION 3.16)

project(chat-bot-twich VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick WebSockets)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appchat-bot-twich
    main.cpp
)

qt_add_qml_module(appchat-bot-twich
    URI chat-bot-twich
    VERSION 1.0
    QML_FILES Main.qml AuthorizationForm.qml MainScreenForm.qml Screen01.qml ChatMsgItem.qml
    SOURCES chatbot.h chatbot.cpp
    SOURCES twichircclient.h twichircclient.cpp
    SOURCES twichapi.h twichapi.cpp
    SOURCES chatmsg.h chatmsg.cpp
    SOURCES chatmsgmodel.h chatmsgmodel.cpp
    SOURCES chatmsgdatasource.h chatmsgdatasource.cpp
    SOURCES filterdatasource.h filterdatasource.cpp
    RESOURCES resources/icon_trash.svg
)

# QML_IMPORT_PATH()

# qt6_add_qml_module(appchat-bot-twich
#   URI com.geeking.qmlcomponents
#   VERSION 1.0
# )

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appchat-bot-twich PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appchat-bot-twich
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appchat-bot-twich PRIVATE
    Qt6::Quick
    Qt6::Qml
    Qt6::WebSockets
)

include(GNUInstallDirs)
install(TARGETS appchat-bot-twich
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
