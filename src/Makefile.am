lib_LTLIBRARIES = customview.la

customview_la_SOURCES = customview.c

customview_la_LDFLAGS = -module -no-undefined -avoid-version

AM_CPPFLAGS = \
	$(GTK_CFLAGS) \
	-I$(includedir) \
	$(SYLPHEED_CFLAGS) \
	$(SYLPF_CFLAGS)

customview_la_LIBADD = \
	$(GTK_LIBS) \
	$(SYLPHEED_LIBS) \
	$(SYLPF_LIBS)

install:
install-plugin: install-am
