

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = ea-sudoku ea-sudoku-serie develop
lib_LTLIBRARIES = libGP.la

libGP_la_SOURCES = core.cc GA.cc GA-sudoku.cc GA-trans.cc GA-trans-region.cc


ea_sudoku_SOURCES = ea-sudoku.cc
ea_sudoku_LDFLAGS = 
ea_sudoku_CXXFLAGS = $(OCTETOS_CORE_CFLAGS) $(OCTETOS_COREUTILS_CFLAGS) $(ZLIB_CFLAGS)
ea_sudoku_LDADD = $(OCTETOS_CORE_LIBS) $(OCTETOS_COREUTILS_LIBS) $(ZLIB_LIBS) libGP.la


develop_SOURCES = main.cc 
develop_LDFLAGS = 
develop_CXXFLAGS = $(OCTETOS_CORE_CFLAGS) $(OCTETOS_COREUTILS_CFLAGS) $(ZLIB_CFLAGS)
develop_LDADD = $(OCTETOS_CORE_LIBS) $(OCTETOS_COREUTILS_LIBS) $(ZLIB_LIBS) libGP.la

ea_sudoku_serie_SOURCES = ea-sudoku-serie.cc 
ea_sudoku_serie_LDFLAGS = 
ea_sudoku_serie_CXXFLAGS = $(OCTETOS_CORE_CFLAGS) $(OCTETOS_COREUTILS_CFLAGS) $(ZLIB_CFLAGS)
ea_sudoku_serie_LDADD = $(OCTETOS_CORE_LIBS) $(OCTETOS_COREUTILS_LIBS) $(ZLIB_LIBS) libGP.la


