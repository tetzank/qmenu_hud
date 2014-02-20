qmenu_hud
=========

a small menu search program, similar to Unity's HUD

based on appmenu-runner, a krunner plugin for the same purpose

Currently it just runs dmenu with the menu entries obtained from dbus.


Dependencies
------------

- Qt4
- libdbusmenu-qt
- dmenu


Compile
-------

```
$ mkdir build
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

It was only tested under Awesome WM on Arch Linux with KDE applications. To
enable it for KDE4 applications, install appmenu-qt. Set a global keyboard
shortcut for qmenu_hud. Now you have to start the registrar dbus service. There
are two ways of doing this: Run qmenu_registrar or use the kded module
'appmenu'. qmenu_registrar is recommended as the kded module crashes when you
try to get the menu of a window which isn't exporting its menu.

Just run qmenu_registrar before any gui application when starting up, e.g.
.xinitrc:
```
qmenu_registrar &
konsole &

exec awesome
```

To use the kded module 'appmenu' just change some settings in System Settings:

https://wiki.archlinux.org/index.php/Kde#Adding_a_Global_Menu_to_the_desktop
> To export the menus to your global menu, go to
> *System Settings > Application Appearance > Style*.
> Now click the fine-tuning tab and use the drop-down list to select *only
> export* as your menubar style.

You can also start it by hand (kded needs to be running):
```
$ dbus-send --type=method_call --print-reply --dest=org.kde.kded /kded org.kde.kded.loadModule string:appmenu
```

Either way, all menubars should now be hidden and you can press the global
shortcut to start qmenu_hud and get a searchable list of all menu entries.

