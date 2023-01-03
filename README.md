qmenu_hud
=========

a small menu search program, similar to Unity's HUD

based on appmenu-runner, a krunner plugin for the same purpose

Currently it just runs dmenu with the menu entries obtained from dbus.


Dependencies
------------

- cmake
- Qt6 (core, gui, dbus)
- libdbusmenu-qt6
- dmenu


Compile
-------

```
$ mkdir build
$ cd build
$ cmake ..
$ make
```

Set `CMAKE_INSTALL_PREFIX` in cmake and run `make install` to install it.

Two programs get compiled qmenu_hud and qmenu_registrar. qmenu_registrar is a
dbus service where other programs which export their menus have to register.
qmenu_hud shows all menu entries of the focused window in a searchable list
using dmenu.


Usage
-----

It was tested under Awesome WM on Arch Linux mostly with KDE applications. To
enable it for KDE4 applications, install appmenu-qt4. It works out-of-the-box
in KDE5/Qt5 applications. appmenu-qt5 breaks it.

Set a global keyboard shortcut for qmenu_hud. Refer to the documentation of
your WM or DE how to do that. Now you have to start the registrar dbus service
by executing qmenu_registrar.

You can add qmenu_registrar to the startup of the graphical environment, e.g.
.xinitrc:
```
qmenu_registrar &
konsole &

exec awesome
```

All menubars should now be hidden and you can press the global shortcut to
start qmenu_hud and get a searchable list of all menu entries.


Experimental GTK support
------------------------

Experimental support for GTK was added. Be happy if it works.

On Arch, install the package appmenu-gtk-module.

Start a GTK application and press the qmenu_hud shortcut, e.g. gimp:
```
GTK_MODULES="appmenu-gtk-module" gimp
```

The package provides a configuration file. Include it in .xinitrc:
```
source /etc/X11/xinit/xinitrc.d/80-appmenu-gtk-module
```


Similar project
----------------

i3-hud-menu:
https://github.com/RafaelBocquet/i3-hud-menu
