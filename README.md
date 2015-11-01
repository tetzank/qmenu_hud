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
shortcut for qmenu_hud. Now you have to start the registrar dbus service by
executing qmenu_registrar. 

Just run qmenu_registrar before any gui application when starting up, e.g.
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

Appmenu isn't used by GTK anymore. The Unity GTK module has its own dbus
interface, which is an implementation detail and can break any minute.
Experimental support for this was now added. Be happy if it works.

Install the Unity GTK module, AUR:
https://aur.archlinux.org/packages/unity-gtk-module-standalone-bzr/

Start a GTK application and press the qmenu_hud shortcut, e.g. gimp:
```
GTK_MODULES="unity-gtk-module" gimp
```

Add this change to GTK_MODULES to .profile or .xinitrc.
```
if [ -n "$GTK_MODULES" ]; then
    GTK_MODULES="${GTK_MODULES}:unity-gtk-module"
else
    GTK_MODULES="unity-gtk-module"
fi

if [ -z "$UBUNTU_MENUPROXY" ]; then
    UBUNTU_MENUPROXY=1
fi
```
The AUR package does this for you. Just log out and back in.

Similar project
----------------

i3-hud-menu:
https://github.com/RafaelBocquet/i3-hud-menu
