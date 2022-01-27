
AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

check_PROGRAMS = v0
TESTS= $(check_PROGRAMS)


v0_LDFLAGS =
v0_LDADD = $(CUNIT_LIBS) $(top_builddir)/src/liboctetos-EC.la
v0_CPPFLAGS = $(CUNIT_CFLAGS) -I$(top_srcdir)/src -I$(top_builddir)/src 
v0_SOURCES = v0.cc v0-sudoku.cc
