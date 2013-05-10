include $(ROOTDIR)/makefiles/arch/unix.mk

ifeq "$(INSTALLDIR)" ""
  INSTALLDIR=/usr
endif
IMAGEDIR = $(INSTALLDIR)/share/pixmaps
APPIMAGEDIR = $(INSTALLDIR)/share/pixmaps/%APPLICATION_NAME%

CC = ccache gcc
AR = ar rsu
LD = g++

CFLAGS = -pipe -fno-exceptions -Wall -Wno-ctor-dtor-privacy -W -DLIBICONV_PLUG
LDFLAGS =

ifeq "$(UI_TYPE)" "qt"
  MOC = moc-qt3
  QTINCLUDE = -I /usr/include/qt3
else
  MOC = /root/qte/build/qtopiacore/host/bin/moc
  QTINCLUDE = -fno-rtti -DQT_SHARED -I/root/qte/build/sdk/qtopiacore/target/include -I/root/qte/build/sdk/qtopiacore/target/include/QtCore -I/root/qte/build/sdk/qtopiacore/target/include/QtGui -I/root/qte/build/sdk/include/qtopia -I/root/qte/build/sdk/include/qtopiabase -I/root/qte/build/sdk/include/qtopiawhereabouts
endif

GTKINCLUDE = $(shell pkg-config --cflags gtk+-2.0 libpng xft)

ifeq "$(UI_TYPE)" "qt"
  UILIBS = -lqt-mt
endif

ifeq "$(UI_TYPE)" "qt4"
  UILIBS = -L/root/qte/build/sdk/qtopiacore/target/lib -L/root/qte/build/sdk/lib -lQtCore -lQtGui -lqtopia -lqtopiagfx -lqtopiabase -lqtopiawhereabouts
endif

ifeq "$(UI_TYPE)" "gtk"
  UILIBS = $(shell pkg-config --libs gtk+-2.0 gio-2.0) -lpng -ljpeg
endif

RM = rm -rvf
RM_QUIET = rm -rf
