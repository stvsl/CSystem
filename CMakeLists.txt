cmake_minimum_required(VERSION 3.5)
project(CSystem-Qt6 VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
# set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Sql REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS WebEngine REQUIRED)
find_package(Qt5Charts)    

include_directories( ${QT_INCLUDE_DIR} )
set (LIBS ${LIBS} ${Qt5Charts_LIBRARIES} )

find_package(Qt5 COMPONENTS WebEngineWidgets REQUIRED)
find_package(OpenSSL REQUIRED)
if(OPENSSL_FOUND)
  include_directories(${OPENSSL_INCLUDE_DIRS})
  message(STATUS "OpenSSL Found!")
endif()


set(TS_FILES CSystem-Qt6_zh_CN.ts)

set(PROJECT_SOURCES
       dataChecker/datachecker.cpp
       configManager/configmanager.cpp
       configManager/encryptionconfig.cpp
       csystemmain/accountmanagement.cpp
       csystemmain/dataview.cpp
       csystemmain/mapsetting.cpp
       csystemmain/csystemmain.cpp
       csystemmain/mapview.cpp
       csystemmain/nodeinformation.cpp
       csystemmain/nodeinstall.cpp
       csystemmain/servicecontrol.cpp
       csystemmain/serviceimformation.cpp
       csystemmain/systemsetting.cpp
       csystemmain/login.cpp
       RSA/rsa.cpp
       AES/aes.cpp
       main.cpp
       netWorkUtils/netWorkUtils.cpp
       netWorkUtils/userinterface.cpp
       netWorkUtils/security.cpp
       netWorkUtils/nodeinterface.cpp
       DButils/dbutils.cpp
       dataChecker/datachecker.h
       configManager/configmanager.h
       configManager/mapconfig.h
       configManager/encryptionconfig.h
       cacheManager/CacheManager.h
       csystemmain/accountmanagement.h
       csystemmain/dataview.h
       csystemmain/mapsetting.h
       csystemmain/csystemmain.h
       csystemmain/mapview.h
       csystemmain/nodeinformation.h
       csystemmain/nodeinstall.h
       csystemmain/servicecontrol.h
       csystemmain/serviceimformation.h
       csystemmain/systemsetting.h
       csystemmain/login.h
       RSA/rsa.h
       AES/aes.h
       main.h
       netWorkUtils/netWorkUtils.h
       netWorkUtils/userinterface.h
       netWorkUtils/security.h
       netWorkUtils/nodeinterface.h
       netWorkUtils/nodeinterface.h
       DButils/dbutils.h
       csystemmain/accountmanagement.ui
       csystemmain/csystemmain.ui
       csystemmain/dataview.ui
       csystemmain/mapsetting.ui
       csystemmain/mapview.ui
       csystemmain/nodeinformation.ui
       csystemmain/nodeinstall.ui
       csystemmain/servicecontrol.ui
       csystemmain/serviceimformation.ui
       csystemmain/systemsetting.ui
       csystemmain/login.ui
       source/source.qrc
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(CSystem-Qt6
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
    set_property(TARGET CSystem-Qt6 APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(CSystem-Qt6 SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(CSystem-Qt6
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

target_link_libraries(CSystem-Qt6 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(CSystem-Qt6 PRIVATE Qt${QT_VERSION_MAJOR}::Sql)
target_link_libraries(CSystem-Qt6 PRIVATE Qt${QT_VERSION_MAJOR}::Network)
target_link_libraries(CSystem-Qt6 PRIVATE Qt5::WebEngineWidgets)
target_link_libraries(CSystem-Qt6 PRIVATE Qt5::WebChannel)
target_link_libraries(CSystem-Qt6 PRIVATE Qt5::Charts)
target_link_libraries(CSystem-Qt6 PRIVATE OpenSSL::Crypto OpenSSL::SSL)


target_include_directories(CSystem-Qt6 PRIVATE "${CMAKE_BINARY_DIR}/Test_autogen/include_Debug")


set_target_properties(CSystem-Qt6 PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER stvsljl.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(CSystem-Qt6)
endif()

set(CMAKE_EXPORT_COMPILECOMMANDS ON)
