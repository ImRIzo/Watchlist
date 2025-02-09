cmake_minimum_required(VERSION 3.16)

project(Watchlist VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Network)
find_package(Qt6 REQUIRED COMPONENTS Core Gui Sql)

set(PROJECT_SOURCES
        main.cpp
        watchlist.cpp
        watchlist.h
        watchlist.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Watchlist
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        serverdata.h serverdata.cpp
        moviemodel.h moviemodel.cpp
        moviedelegate.h moviedelegate.cpp
        resources.qrc
        localdatabse.h localdatabse.cpp
        dialog.ui

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET Watchlist APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(Watchlist SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(Watchlist
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(Watchlist PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(Watchlist PRIVATE Qt6::Core Qt6::Gui Qt6::Network)
target_link_libraries(Watchlist PRIVATE Qt6::Core Qt6::Gui Qt6::Sql)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.Watchlist)
endif()
set_target_properties(Watchlist PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS Watchlist
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Watchlist)
endif()
