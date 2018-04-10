
Debian
====================
This directory contains files used to package eletacoind/eletacoin-qt
for Debian-based Linux systems. If you compile eletacoind/eletacoin-qt yourself, there are some useful files here.

## eletacoin: URI support ##


eletacoin-qt.desktop  (Gnome / Open Desktop)
To install:

	sudo desktop-file-install eletacoin-qt.desktop
	sudo update-desktop-database

If you build yourself, you will either need to modify the paths in
the .desktop file or copy or symlink your eletacoin-qt binary to `/usr/bin`
and the `../../share/pixmaps/eletacoin128.png` to `/usr/share/pixmaps`

eletacoin-qt.protocol (KDE)

