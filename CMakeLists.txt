cmake_minimum_required(VERSION 2.8.8)

# build type defaults to release
if(NOT DEFINED CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build, options are: None(CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used) Debug Release RelWithDebInfo MinSizeRel.")
endif(NOT DEFINED CMAKE_BUILD_TYPE)
if(NOT DEFINED CMAKE_CXX_FLAGS)
	set(CMAKE_CXX_FLAGS "-std=c++11 -Wl,--as-needed" CACHE STRING "")
endif()

project(qmenu_hud)


set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Core CONFIG REQUIRED)
find_package(Qt5DBus CONFIG REQUIRED)
find_package(Qt5Gui CONFIG REQUIRED)
find_package(X11 REQUIRED)

find_package(PkgConfig REQUIRED)
pkg_check_modules(DBUSMENUQT REQUIRED dbusmenu-qt5>=0.6.0)

find_program(DMENU_PATH dmenu)
if(NOT DMENU_PATH)
	message(STATUS "Couldn't find dmenu. Using plain \"dmenu\" which needs to be in PATH.")
	set(DMENU_PATH "dmenu" CACHE FILEPATH "" FORCE)
endif(NOT DMENU_PATH)

configure_file(${CMAKE_SOURCE_DIR}/projectConfig.h.in ${CMAKE_BINARY_DIR}/projectConfig.h)

include_directories(
   ${CMAKE_SOURCE_DIR}
   ${CMAKE_BINARY_DIR}
   ${DBUSMENUQT_INCLUDE_DIRS}
   ${X11_INCLUDE_DIRS}
   )

# testing libdbusmenu-qt which is for qt4
# -> can't use it, lazily fills menu, need all entries for search
#add_executable(dbusmenu_test dbusmenu_test.cpp)
#target_link_libraries(dbusmenu_test ${DBUSMENUQT_LIBRARIES} ${QT_LIBRARIES})

# use krunner method, rips code from libdbusmenu-qt

set(qmenu_hud_SRCS qmenu_hud.cpp dbusmenutypes_p.cpp dbusmenushortcut_p.cpp gtkmenutypes.cpp)

set(appmenu_xml com.canonical.AppMenu.Registrar.xml)
set_source_files_properties(${appmenu_xml} PROPERTIES INCLUDE "dbusmenutypes_p.h")
qt5_add_dbus_interface(qmenu_hud_SRCS ${appmenu_xml} app_menu)

set(dbusmenu_xml com.canonical.dbusmenu.xml)
set_source_files_properties(${dbusmenu_xml} PROPERTIES INCLUDE "dbusmenutypes_p.h")
qt5_add_dbus_interface(qmenu_hud_SRCS ${dbusmenu_xml} dbus_menu)

set(gtk_action_xml org.gtk.Actions.xml)
set_source_files_properties(${gtk_action_xml} PROPERTIES INCLUDE "gtkmenutypes.h")
qt5_add_dbus_interface(qmenu_hud_SRCS ${gtk_action_xml} gtk_action)
set(gtk_menu_xml org.gtk.Menus.xml)
set_source_files_properties(${gtk_menu_xml} PROPERTIES INCLUDE "gtkmenutypes.h")
qt5_add_dbus_interface(qmenu_hud_SRCS ${gtk_menu_xml} gtk_menu)

add_executable(qmenu_hud ${qmenu_hud_SRCS})
# only link against qtcore and qt dbus lib
# libdbusmenu-qt isn't needed, but a header is included, so it could
# -> -Wl,--as-needed takes care of it
target_link_libraries(qmenu_hud ${DBUSMENUQT_LIBRARIES} Qt5::Core Qt5::DBus Qt5::Gui ${X11_LIBRARIES})


set(qmenu_registrar_SRCS qmenu_registrar.cpp registrar.cpp
	dbusmenutypes_p.cpp dbusmenushortcut_p.cpp)
qt5_add_dbus_adaptor(qmenu_registrar_SRCS ${appmenu_xml} registrar.h Registrar)

add_executable(qmenu_registrar ${qmenu_registrar_SRCS})
target_link_libraries(qmenu_registrar ${DBUSMENUQT_LIBRARIES} Qt5::Core Qt5::DBus Qt5::Gui)

install(TARGETS qmenu_hud qmenu_registrar DESTINATION bin)
