cmake_minimum_required(VERSION 3.14)


set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set (Freezer_VERSION_MAJOR 1)
set (Freezer_VERSION_MINOR 0)

project(freezer-android VERSION ${Freezer_VERSION_MAJOR}.${Freezer_VERSION_MINOR} LANGUAGES CXX)

enable_testing()


# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package(...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick REQUIRED)


include_directories(${CMAKE_CURRENT_SOURCE_DIR})

set(OCUtils ${CMAKE_CURRENT_SOURCE_DIR}/utils/OCUtils)
include_directories(${OCUtils}/src)
include_directories(${OCUtils}/include)


set (PROJECT_DIR ${PROJECT_SOURCE_DIR})
set (PROJECT_LIB_DIR ${PROJECT_DIR}/lib)
set (PROJECT_INCLUDE_DIR ${PROJECT_DIR}/include)

link_directories(${PROJECT_LIB_DIR})


set (PROJECT_TEST_DIR ${PROJECT_SOURCE_DIR}/tests)
set (PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}/src)


add_subdirectory(${PROJECT_SOURCE_DIR})
add_subdirectory(${PROJECT_TEST_DIR})

set(PROJECT_SOURCES
        main.cpp
        ${Freezer_RESOURCES}
        $<TARGET_OBJECTS:model>
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(freezer-android
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(freezer-android SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(freezer-android
          ${PROJECT_SOURCES}
        )
    endif()
endif()

target_compile_definitions(freezer-android
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(freezer-android
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick)

set_target_properties(freezer-android PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(freezer-android)
    qt_finalize_executable(freezer-android)
endif()



set(CONFIGURED_ONCE TRUE CACHE INTERNAL
    "A flag showing that CMake has configured at least once.")

