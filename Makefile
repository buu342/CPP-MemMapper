BUILD=release
WXPATH = "${WXWIDGETS}"
prefix = /usr/local
exec_prefix = ${prefix}
datarootdir = ${prefix}/share
INSTALL = /usr/bin/install -c
EXEEXT = 
WINDRES = 
NM = nm
BK_DEPS = $(WXPATH)bk-deps
srcdir = .
top_srcdir = ../..
LIBS = -lz -llzma -lm
LDFLAGS_GUI = 
CXX = g++
CXXFLAGS = 
CPPFLAGS = 
LDFLAGS = 
USE_DPI_AWARE_MANIFEST = 2
WX_LIB_FLAVOUR = 
TOOLKIT = GTK
TOOLKIT_LOWERCASE = gtk
TOOLKIT_VERSION = 3
TOOLCHAIN_FULLNAME = gtk3-unicode-3.1
EXTRALIBS = -pthread   -Wl,--version-script,$(wx_top_builddir)/version-script -lz -llzma -lm 
EXTRALIBS_XML =  -lexpat
EXTRALIBS_GUI = -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lgthread-2.0 -pthread -lglib-2.0 -lX11 -lSM -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lXtst -lpangoft2-1.0 -lpango-1.0 -lgobject-2.0 -lglib-2.0 -lharfbuzz -lfontconfig -lfreetype -lpng -lz -ljpeg -ltiff -llzma -ljbig
WX_CPPFLAGS = -I${wx_top_builddir}/lib/wx/include/gtk3-unicode-3.1 -I${top_srcdir}/include -D_FILE_OFFSET_BITS=64 -pthread -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/fribidi -I/usr/include/atk-1.0 -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/x86_64-linux-gnu -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include 
WX_CXXFLAGS = -pthread -Wall -Wundef -Wunused-parameter -Wno-ctor-dtor-privacy -Woverloaded-virtual -Wno-deprecated-declarations -O2 -I/usr/include/pango-1.0 -I/usr/include/harfbuzz -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/fribidi -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gtk-3.0/unix-print -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gio-unix-2.0 -I/usr/include/atk-1.0 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/x86_64-linux-gnu  -fvisibility=hidden -fvisibility-inlines-hidden
WX_LDFLAGS = -pthread  
HOST_SUFFIX = 
SAMPLES_RPATH_FLAG = -Wl,-rpath,$(wx_top_builddir)/lib
SAMPLES_CXXFLAGS =  -fPIC -DPIC
wx_top_builddir = $(WXPATH)

### Variables: ###

DESTDIR = 
WX_RELEASE = 3.1
WX_VERSION = $(WX_RELEASE).5
LIBDIRNAME = $(wx_top_builddir)/lib
memmapper_CXXFLAGS = $(WX_CPPFLAGS) -D__WX$(TOOLKIT)__ $(__WXUNIV_DEFINE_p) \
	$(__DEBUG_DEFINE_p) $(__EXCEPTIONS_DEFINE_p) $(__RTTI_DEFINE_p) \
	$(__THREAD_DEFINE_p) -I$(srcdir) $(__DLLFLAG_p) -I$(srcdir)/../../samples \
	$(WX_CXXFLAGS) $(SAMPLES_CXXFLAGS) $(CPPFLAGS) $(CXXFLAGS)
memmapper_OBJECTS =  \
	app.o \
	main.o \
	item.o \
	$(__memmapper___win32rc) 

### Conditionally set variables: ###


CXXC = $(BK_DEPS) $(CXX)

PORTNAME = $(TOOLKIT_LOWERCASE)$(TOOLKIT_VERSION)

WXUNICODEFLAG = u

EXTRALIBS_FOR_BASE = $(EXTRALIBS)

EXTRALIBS_FOR_GUI = $(EXTRALIBS_GUI)

__DLLFLAG_p = -DWXUSINGDLL
__DLLFLAG_p_1 = --define WXUSINGDLL

COND_PLATFORM_OS2_1___memmapper___os2_emxbindcmd = $(NM) memmapper$(EXEEXT) | if \
	grep -q pmwin.763 ; then emxbind -ep memmapper$(EXEEXT) ; fi

COND_MONOLITHIC_0___WXLIB_CORE_p = \
	-lwx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)_core-$(WX_RELEASE)$(HOST_SUFFIX)
__WXLIB_CORE_p = $(COND_MONOLITHIC_0___WXLIB_CORE_p)
COND_MONOLITHIC_0___WXLIB_BASE_p = \
	-lwx_base$(WXBASEPORT)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
__WXLIB_BASE_p = $(COND_MONOLITHIC_0___WXLIB_BASE_p)
COND_MONOLITHIC_1___WXLIB_MONO_p = \
	-lwx_$(PORTNAME)$(WXUNIVNAME)$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)

COND_wxUSE_REGEX_builtin___LIB_REGEX_p = \
	-lwxregex$(WXUNICODEFLAG)$(WXDEBUGFLAG)$(WX_LIB_FLAVOUR)-$(WX_RELEASE)$(HOST_SUFFIX)
__LIB_REGEX_p = $(COND_wxUSE_REGEX_builtin___LIB_REGEX_p)

all: memmapper$(EXEEXT) $(__memmapper_bundle___depname)

install: 

uninstall: 

install-strip: install

clean: 
	rm -rf ./.deps ./.pch
	rm -f ./*.o
	rm -f memmapper$(EXEEXT)
	rm -rf memmapper.app

distclean: clean
	rm -f config.cache config.log config.status bk-deps bk-make-pch shared-ld-sh Makefile

memmapper$(EXEEXT): $(memmapper_OBJECTS) $(__memmapper___win32rc)
	$(CXX) -o $@ $(memmapper_OBJECTS)    -L$(LIBDIRNAME)  $(LDFLAGS_GUI) $(SAMPLES_RPATH_FLAG) $(LDFLAGS)  $(WX_LDFLAGS) $(__WXLIB_CORE_p)  $(__WXLIB_BASE_p)  $(__WXLIB_MONO_p) $(__LIB_SCINTILLA_IF_MONO_p) $(__LIB_TIFF_p) $(__LIB_JPEG_p) $(__LIB_PNG_p)  $(EXTRALIBS_FOR_GUI) $(__LIB_ZLIB_p) $(__LIB_REGEX_p) $(__LIB_EXPAT_p) $(EXTRALIBS_FOR_BASE) $(LIBS)
	$(__memmapper___os2_emxbindcmd)

app.o: $(srcdir)/app.cpp
	echo $(WXWIDGETS)
	echo $(WXPATH)
	echo
	$(CXXC) -c -o $@ $(memmapper_CXXFLAGS) $(srcdir)/app.cpp

main.o: $(srcdir)/memmapper.cpp
	$(CXXC) -c -o $@ $(memmapper_CXXFLAGS) $(srcdir)/main.cpp

item.o: $(srcdir)/memmapper.cpp
	$(CXXC) -c -o $@ $(memmapper_CXXFLAGS) $(srcdir)/item.cpp

settings.o: $(srcdir)/memmapper.cpp
	$(CXXC) -c -o $@ $(memmapper_CXXFLAGS) $(srcdir)/settings.cpp

# Include dependency info, if present:
-include ./.deps/*.d

.PHONY: all install uninstall clean distclean memmapper_bundle
