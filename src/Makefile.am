

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = ea-sudoku

ea_sudoku_SOURCES = core.cc GA.cc sudoku.cc ea-sudoku.cc 
ea_sudoku_LDFLAGS = 
ea_sudoku_CXXFLAGS = $(OCTETOS_CORE_CFLAGS) $(OCTETOS_COREUTILS_CFLAGS) $(ZLIB_CFLAGS)
ea_sudoku_LDADD = $(OCTETOS_CORE_LIBS) $(OCTETOS_COREUTILS_LIBS) $(ZLIB_LIBS)


