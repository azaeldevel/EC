

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = ec-sudoku develop
lib_LTLIBRARIES = libEC.la

libEC_la_SOURCES = core.cc GA.cc GA-sudoku.cc GA-trans.cc GA-trans-region.cc


ec_sudoku_SOURCES = ec-sudoku.cc
ec_sudoku_LDFLAGS = 
ec_sudoku_CXXFLAGS = $(OCTETOS_CORE_CFLAGS) $(OCTETOS_COREUTILS_CFLAGS) $(ZLIB_CFLAGS)
ec_sudoku_LDADD = $(OCTETOS_CORE_LIBS) $(OCTETOS_COREUTILS_LIBS) $(ZLIB_LIBS) libEC.la


develop_SOURCES = main.cc 
develop_LDFLAGS = 
develop_CXXFLAGS = $(OCTETOS_CORE_CFLAGS) $(OCTETOS_COREUTILS_CFLAGS) $(ZLIB_CFLAGS)
develop_LDADD = $(OCTETOS_CORE_LIBS) $(OCTETOS_COREUTILS_LIBS) $(ZLIB_LIBS) libEC.la



