qmenu_hud
=========

a small menu search program, similar to Unity's HUD

based on appmenu-runner, a krunner plugin for the same purpose

Currently it just runs dmenu with the menu entries obtained from dbus.


Dependencies
------------

- Qt4
- libdbusmenu-qt


Compile
-------

```shell
$ mkdir build
$ cmake ..
$ make
```

There's no install target yet. Just copy it somewhere accesible and add a
global keyboard shortcut for it.


Usage
-----

It was only tested under Awesome WM on Arch Linux with KDE applications. To
enable it for KDE4 applications, install appmenu-qt and do the following in
System Settings.

https://wiki.archlinux.org/index.php/Kde#Adding_a_Global_Menu_to_the_desktop
> To export the menus to your global menu, go to
> *System Settings > Application Appearance > Style*.
> Now click the fine-tuning tab and use the drop-down list to select *only
> export* as your menubar style.

Now all menubars should be hidden and you can press the global shortcut to get
a searchable list of all menu entries.

