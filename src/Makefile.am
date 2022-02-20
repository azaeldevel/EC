

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = ec-sudoku ec-trans ec-max
noinst_PROGRAMS = develop
lib_LTLIBRARIES = liboctetos-EC.la

liboctetos_EC_la_SOURCES = ec.cc sudoku.cc trans.cc trans-region.cc max.cc 
liboctetos_EC_la_LDFLAGS = $(OCTETOS_EC_CFLAGS)
liboctetos_EC_la_LIBADD = $(OCTETOS_EC_LIBS) 

ec_sudoku_SOURCES = ec-sudoku.cc
ec_sudoku_LDFLAGS = 
ec_sudoku_CXXFLAGS = $(OCTETOS_EC_CFLAGS) $(ZLIB_CFLAGS)
ec_sudoku_LDADD = $(OCTETOS_EC_LIBS) $(ZLIB_LIBS) liboctetos-EC.la

ec_trans_SOURCES = ec-trans.cc
ec_trans_LDFLAGS = 
ec_trans_CXXFLAGS = $(OCTETOS_EC_CFLAGS) $(ZLIB_CFLAGS)
ec_trans_LDADD = $(OCTETOS_EC_LIBS) $(ZLIB_LIBS) liboctetos-EC.la

ec_max_SOURCES = ec-max.cc
ec_max_LDFLAGS = 
ec_max_CXXFLAGS = $(OCTETOS_EC_CFLAGS) $(ZLIB_CFLAGS)
ec_max_LDADD = $(OCTETOS_EC_LIBS) $(ZLIB_LIBS) liboctetos-EC.la


develop_SOURCES = main.cc 
develop_LDFLAGS = 
develop_CXXFLAGS = $(OCTETOS_EC_CFLAGS) $(ZLIB_CFLAGS)
develop_LDADD = $(OCTETOS_EC_LIBS) $(ZLIB_LIBS) liboctetos-EC.la

octetos_EC_includedir = $(includedir)/octetos/EC
octetos_EC_include_HEADERS = ec.hh max.hh sudoku.hh

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = octetos-EC.pc

EXTRA_DIST = octetos-EC.pc.in

