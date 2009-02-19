SUBDIRS = backend libtotem plugins 

bin_PROGRAMS = totem totem-video-thumbnailer totem-video-indexer totem-audio-preview
libexec_PROGRAMS =

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

#totem

totem_SOURCES = main.c
totem_LDADD =						\
	$(top_builddir)/src/backend/libbaconvideowidget.la	\
	libtotem/libtotem.la					\
	$(DEPENDENCY_LIBS)				\
	$(XVIDMODE_LIBS)				\
	$(DBUS_LIBS)					\
	$(XTEST_LIBS)					\
	$(X_LIBS)

# Totem video thumbnailer

totem_video_thumbnailer_SOURCES =	\
	totem-video-thumbnailer.c	\
	totem-resources.c		\
	totem-resources.h

totem_video_thumbnailer_CPPFLAGS = \
	-I$(top_srcdir)/	\
	-I$(srcdir)/backend	\
	$(common_defines)	\
	$(AM_CPPFLAGS)

totem_video_thumbnailer_CFLAGS = \
	$(DEPENDENCY_CFLAGS)	\
	$(WARN_CFLAGS)		\
	$(AM_CFLAGS)

totem_video_thumbnailer_LDFLAGS = \
	$(AM_LDFLAGS)

totem_video_thumbnailer_LDADD =			\
	$(top_builddir)/src/backend/libbaconvideowidget.la		\
	$(DEPENDENCY_LIBS)			\
	$(EXTRA_BACKEND_LIBS) 			\
	$(XTEST_LIBS)				\
	$(XVIDMODE_LIBS)			\
	$(X_LIBS)

# Nautilus Property Page

if HAVE_NAUTILUS

nautilusdir = $(NAUTILUSDIR)
nautilus_LTLIBRARIES = libtotem-properties-page.la

libtotem_properties_page_la_SOURCES = 	\
	totem-properties-main.c		\
	totem-properties-view.c		\
	totem-properties-view.h

libtotem_properties_page_la_CPPFLAGS =		\
	-I$(srcdir)/backend			\
	-I$(top_srcdir)/			\
	-I$(srcdir)/plugins/properties		\
	-I$(top_builddir)/data			\
	$(common_defines)			\
	$(AM_CPPFLAGS)

libtotem_properties_page_la_CFLAGS = \
	$(WARN_CFLAGS)		\
	$(DEPENDENCY_CFLAGS)	\
	$(NAUTILUS_CFLAGS)	\
	$(AM_CFLAGS)

libtotem_properties_page_la_LDFLAGS = \
	$(modules_flags)	\
	$(AM_LDFLAGS)

libtotem_properties_page_la_LIBADD =				\
	$(top_builddir)/src/backend/libbaconvideowidget.la				\
	$(top_builddir)/src/plugins/properties/libbaconvideowidgetproperties.la	\
	libtotem/libtotem_player.la					\
	$(DEPENDENCY_LIBS)					\
	$(NAUTILUS_LIBS)					\
	$(XTEST_LIBS)						\
	$(XVIDMODE_LIBS)					\
	$(X_LIBS)

noinst_PROGRAMS = test-properties-page

test_properties_page_SOURCES =		\
	totem-properties-main.c		\
	totem-properties-view.c		\
	totem-properties-view.h		\
	test-properties-page.c

test_properties_page_CPPFLAGS = 		\
	-I$(srcdir)/backend			\
	-I$(top_srcdir)/			\
	-I$(top_builddir)/data			\
	-I$(srcdir)/plugins/properties		\
	$(common_defines)			\
	$(AM_CPPFLAGS)

test_properties_page_CFLAGS = \
	$(WARN_CFLAGS)		\
	$(DEPENDENCY_CFLAGS)	\
	$(NAUTILUS_CFLAGS)	\
	$(AM_CFLAGS)

test_properties_page_LDFLAGS = \
	$(AM_LDFLAGS)

test_properties_page_LDADD = 					\
	backend/libbaconvideowidget.la				\
	plugins/properties/libbaconvideowidgetproperties.la	\
	libtotem_player.la					\
	$(DEPENDENCY_LIBS)					\
	$(NAUTILUS_LIBS)					\
	$(XTEST_LIBS)						\
	$(XVIDMODE_LIBS)					\
	$(X_LIBS)

endif # HAVE_NAUTILUS

# Totem Video Indexer

totem_video_indexer_SOURCES =		\
	totem-video-indexer.c		\
	totem-resources.c		\
	totem-resources.h

totem_video_indexer_CPPFLAGS = \
	-I$(top_srcdir)/	\
	-I$(srcdir)/backend	\
	-I$(top_builddir)/data	\
	$(common_defines)	\
	$(AM_CPPFLAGS)

totem_video_indexer_CFLAGS = \
	$(WARN_CFLAGS)		\
	$(DEPENDENCY_CFLAGS)	\
	$(AM_CFLAGS)

totem_video_indexer_LDFLAGS = \
	$(AM_LDFLAGS)

totem_video_indexer_LDADD = \
	backend/libbaconvideowidget.la	\
	$(DEPENDENCY_LIBS)		\
	$(EXTRA_BACKEND_LIBS)		\
	$(XTEST_LIBS)			\
	$(XVIDMODE_LIBS)		\
	$(X_LIBS)

# Totem Audio Preview for nautilus
totem_audio_preview_SOURCES =		\
	totem-audio-preview.c		\
	totem-resources.c		\
	totem-resources.h

totem_audio_preview_CPPFLAGS =	\
	-I$(top_srcdir)/	\
	-I$(srcdir)/backend	\
	-I$(top_builddir)/data	\
	$(common_defines)	\
	$(AM_CPPFLAGS)

totem_audio_preview_CFLAGS = \
	$(WARN_CFLAGS)		\
	$(DEPENDENCY_CFLAGS)	\
	$(AM_CFLAGS)

totem_audio_preview_LDFLAGS = \
	$(AM_LDFLAGS)

totem_audio_preview_LDADD = \
	backend/libbaconvideowidget.la	\
	$(DEPENDENCY_LIBS)		\
	$(EXTRA_BACKEND_LIBS)		\
	$(XTEST_LIBS)			\
	$(XVIDMODE_LIBS)		\
	$(X_LIBS)

CLEANFILES =			\
	*.bak			\
	core*			\
	*.orig			\
	*~			\
	$(desktop_DATA)		\
	$(BUILT_SOURCES)
