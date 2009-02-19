SUBDIRS = plugins
lib_LTLIBRARIES = libtotem.la
noinst_LTLIBRARIES =				\
	libbaconmessageconnection.la		\
	libtotem_player.la

common_defines = \
	-D_REENTRANT					\
	-DDBUS_API_SUBJECT_TO_CHANGE			\
	-DGNOMELOCALEDIR=\""$(datadir)/locale"\"	\
	-DGCONF_PREFIX=\""/apps/totem"\"		\
	-DDATADIR=\""$(datadir)"\"			\
	-DLIBEXECDIR=\""$(libexecdir)"\"		\
	-DBINDIR=\""$(bindir)"\"			\
	-DLOGO_PATH=DATADIR\"\"G_DIR_SEPARATOR_S\"totem\"G_DIR_SEPARATOR_S\"totem_logo.png\"	\
	$(DISABLE_DEPRECATED)

modules_flags = -export_dynamic -avoid-version -module -no-undefined

# Bacon message connection ltlibrary

BACON_MESSAGE_CONNECTION = \
	bacon-message-connection.c \
	bacon-message-connection.h

libbaconmessageconnection_la_SOURCES =	\
	$(BACON_MESSAGE_CONNECTION)

libbaconmessageconnection_la_CPPFLAGS = \
	$(common_defines)	\
	$(AM_CPPFLAGS)

libbaconmessageconnection_la_CFLAGS = \
	$(GTK_CFLAGS)		\
	$(WARN_CFLAGS)		\
	$(DBUS_CFLAGS)		\
	$(AM_CFLAGS)

libbaconmessageconnection_la_LDFLAGS = \
	-no-undefined \
	$(AM_LDFLAGS)


BACONDIR=$(srcdir)/../../libbacon/src
regenerate-built-sources:
	EGGFILES="$(BACON_MESSAGE_CONNECTION)" EGGDIR="$(BACONDIR)" $(srcdir)/update-from-egg.sh || true

TOTEMMARSHALFILES = 						\
	totemobject-marshal.c totemobject-marshal.h		\
	totemplaylist-marshal.c totemplaylist-marshal.h		\
	totemvideolist-marshal.c totemvideolist-marshal.h
GLIB_GENMARSHAL=`pkg-config --variable=glib_genmarshal glib-2.0`
BUILT_SOURCES = $(TOTEMMARSHALFILES)

totemobject-marshal.h: totemobject-marshal.list Makefile
	( $(GLIB_GENMARSHAL) --prefix=totemobject_marshal $(srcdir)/totemobject-marshal.list --header > totemobject-marshal.h )
totemobject-marshal.c: totemobject-marshal.h Makefile
	( $(GLIB_GENMARSHAL) --prefix=totemobject_marshal $(srcdir)/totemobject-marshal.list --header --body > totemobject-marshal.c )
totemplaylist-marshal.h: totemplaylist-marshal.list Makefile
	( $(GLIB_GENMARSHAL) --prefix=totemplaylist_marshal $(srcdir)/totemplaylist-marshal.list --header > totemplaylist-marshal.h )
totemplaylist-marshal.c: totemplaylist-marshal.h Makefile
	( $(GLIB_GENMARSHAL) --prefix=totemplaylist_marshal $(srcdir)/totemplaylist-marshal.list --header --body > totemplaylist-marshal.c )
totemvideolist-marshal.h: totemvideolist-marshal.list Makefile
	( $(GLIB_GENMARSHAL) --prefix=totemvideolist_marshal $(srcdir)/totemvideolist-marshal.list --header > totemvideolist-marshal.h )
totemvideolist-marshal.c: totemvideolist-marshal.h Makefile
	( $(GLIB_GENMARSHAL) --prefix=totemvideolist_marshal $(srcdir)/totemvideolist-marshal.list --header --body > totemvideolist-marshal.c )

# Totem UI ltlibrary

libtotem_player_la_SOURCES =		\
	$(TOTEMMARSHALFILES)	\
	totem-object.c			\
	totem-action.c			\
	totem-uri.c				\
   	totem-uri.h				\
	totem-playlist.c 		\
	totem-playlist.h		\
	totem-statusbar.c		\
	totem-statusbar.h		\
	totem-interface.c		\
	totem-interface.h		\
	totem-fullscreen.c		\
	totem-fullscreen.h		\
	totem-time-label.c		\
	totem-time-label.h

libtotem_player_la_CPPFLAGS = \
	-I$(top_srcdir)/src/backend			\
	-I$(srcdir)/plugins			\
	-I$(top_builddir)/data		\
	-I$(srcdir)/			\
	$(common_defines)			\
	$(AM_CPPFLAGS)

libtotem_player_la_CFLAGS = \
	$(DEPENDENCY_CFLAGS)	\
	$(WARN_CFLAGS)		\
	$(AM_CFLAGS)

libtotem_player_la_LDFLAGS = \
	-no-undefined \
	$(AM_LDFLAGS)

# libtotem

libtotem_la_SOURCES = 					\
	totem.c totem.h					\
	totem-private.h					\
	totem-preferences.c totem-preferences.h		\
	totem-dnd-menu.c totem-dnd-menu.h 		\
	totem-options.c totem-options.h			\
	eggfileformatchooser.c eggfileformatchooser.h	\
	totem-session.c totem-session.h	\
	totem-sidebar.c totem-sidebar.h \
	totem-open-location.c totem-open-location.h \
	totem-menu.c totem-menu.h	\
	ev-sidebar.c ev-sidebar.h	\
	totem-subtitle-encoding.c	\
	totem-subtitle-encoding.h	\
	totem-cell-renderer-video.c	\
	totem-cell-renderer-video.h	\
	totem-video-list.c		\
	totem-video-list.h		\
	totem-dvb-setup.c		\
	totem-dvb-setup.h

libtotem_la_CPPFLAGS = \
	-I$(srcdir)/		\
	-I$(top_srcdir)/src/backend		\
	-I$(srcdir)/plugins		\
	$(common_defines)		\
	$(AM_CPPFLAGS)

libtotem_la_CFLAGS = \
	$(WARN_CFLAGS)			\
	$(DEPENDENCY_CFLAGS)		\
	$(DBUS_CFLAGS)			\
	$(MISSING_PLUGINS_CFLAGS) \
	$(AM_CFLAGS)

libtotem_la_LDFLAGS = \
    -no-undefined \
	$(AM_LDFLAGS)

libtotem_la_LIBADD =						\
	$(top_builddir)/src/backend/libbaconvideowidget.la			\
	plugins/libtotemmodule.la			\
	libbaconmessageconnection.la			\
	libtotem_player.la				\
	$(DEPENDENCY_LIBS)				\
	$(XVIDMODE_LIBS)				\
	$(DBUS_LIBS)					\
	$(XTEST_LIBS)					\
	$(X_LIBS)

if WITH_SMCLIENT
libtotem_la_SOURCES += \
	eggdesktopfile.c \
	eggdesktopfile.h \
	eggsmclient.c \
	eggsmclient.h \
	eggsmclient-private.h \
	$(NULL)
libtotem_la_CFLAGS += $(SMCLIENT_CFLAGS)
libtotem_la_LIBADD += $(SMCLIENT_LIBS)

if WITH_SMCLIENT_XSMP
libtotem_la_SOURCES += eggsmclient-xsmp.c
libtotem_la_CPPFLAGS += -DEGG_SM_CLIENT_BACKEND_XSMP
endif
if WITH_SMCLIENT_WIN32
libtotem_la_SOURCES += eggsmclient-win32.c
endif
if WITH_SMCLIENT_QUARTZ
libtotem_la_SOURCES += eggsmclient-osx.c
endif
endif

if ENABLE_PYTHON
libtotem_la_LIBADD += \
	$(PYTHON_LIBS)			\
	$(top_builddir)/bindings/python/totem-python.la
endif

EXTRA_DIST = 				\
	totemobject-marshal.list	\
	totemvideolist-marshal.list	\
	totemplaylist-marshal.list
