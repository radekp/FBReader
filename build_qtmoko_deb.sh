#!/bin/sh
export INSTALLDIR=/opt/qtmoko
export IMAGEDIR=/opt/qtmoko/pics
export APPIMAGEDIR=/opt/qtmoko/pics/FBReader
export UI_TYPE=qt4
export TARGET_ARCH=desktop
dpkg-buildpackage -d
