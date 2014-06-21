lib_LTLIBRARIES = customview.la

customview_la_SOURCES = customview.c \
        $(sylplugin_factory_source_dir)/src/sylplugin_factory.c \
        $(sylplugin_factory_source_dir)/src/sylplugin_factory.h

customview_la_LDFLAGS = -module -no-undefined -avoid-version

AM_CPPFLAGS = \
	$(GTK_CFLAGS) \
	-I$(includedir) \
	-I$(sylpheed_build_dir) \
	-I$(sylpheed_build_dir)/libsylph \
	-I$(sylpheed_build_dir)/src \
	-I$(sylplugin_factory_source_dir)/src

customview_la_LIBADD = \
	$(GTK_LIBS) \
	$(sylpheed_build_dir)/src/libsylpheed-plugin-0.la \
	$(sylpheed_build_dir)/libsylph/libsylph-0.la

install:
install-plugin: install-am
