

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = ae

ae_SOURCES = core.cc GA.cc sudoku.cc main.cc 
ae_LDFLAGS = 
ae_CXXFLAGS = $(OCTETOS_CORE_CFLAGS) $(OCTETOS_COREUTILS_CFLAGS) $(ZLIB_CFLAGS)
ae_LDADD = $(OCTETOS_CORE_LIBS) $(OCTETOS_COREUTILS_LIBS) $(ZLIB_LIBS)


