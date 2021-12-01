

AM_CPPFLAGS = \
	-DPACKAGE_LOCALE_DIR=\""$(localedir)"\" \
	-DPACKAGE_SRC_DIR=\""$(srcdir)"\" \
	-DPACKAGE_DATA_DIR=\""$(pkgdatadir)"\"

AM_CFLAGS =\
	 -Wall\
	 -g

bin_PROGRAMS = ec-sudoku ec-trans ec-max ec-schedule
noinst_PROGRAMS = develop
lib_LTLIBRARIES = libEC.la

libEC_la_SOURCES = ec.cc GA.cc GA-sudoku.cc GA-trans.cc GA-trans-region.cc GA-max.cc GA-schedule.cc
libEC_la_LDFLAGS = $(OCTETOS_CORE_CFLAGS) $(OCTETOS_COREUTILS_CFLAGS)
libEC_la_LIBADD = $(OCTETOS_CORE_LIBS) $(OCTETOS_COREUTILS_LIBS)

ec_sudoku_SOURCES = ec-sudoku.cc
ec_sudoku_LDFLAGS = 
ec_sudoku_CXXFLAGS = $(OCTETOS_CORE_CFLAGS) $(OCTETOS_COREUTILS_CFLAGS) $(ZLIB_CFLAGS)
ec_sudoku_LDADD = $(OCTETOS_CORE_LIBS) $(OCTETOS_COREUTILS_LIBS) $(ZLIB_LIBS) libEC.la

ec_trans_SOURCES = ec-trans.cc
ec_trans_LDFLAGS = 
ec_trans_CXXFLAGS = $(OCTETOS_CORE_CFLAGS) $(OCTETOS_COREUTILS_CFLAGS) $(ZLIB_CFLAGS)
ec_trans_LDADD = $(OCTETOS_CORE_LIBS) $(OCTETOS_COREUTILS_LIBS) $(ZLIB_LIBS) libEC.la

ec_max_SOURCES = ec-max.cc
ec_max_LDFLAGS = 
ec_max_CXXFLAGS = $(OCTETOS_CORE_CFLAGS) $(OCTETOS_COREUTILS_CFLAGS) $(ZLIB_CFLAGS)
ec_max_LDADD = $(OCTETOS_CORE_LIBS) $(OCTETOS_COREUTILS_LIBS) $(ZLIB_LIBS) libEC.la

ec_schedule_SOURCES = ec-schedule.cc
ec_schedule_LDFLAGS = 
ec_schedule_CXXFLAGS = $(OCTETOS_CORE_CFLAGS) $(OCTETOS_COREUTILS_CFLAGS) $(ZLIB_CFLAGS)
ec_schedule_LDADD = $(OCTETOS_CORE_LIBS) $(OCTETOS_COREUTILS_LIBS) $(ZLIB_LIBS) libEC.la

develop_SOURCES = main.cc 
develop_LDFLAGS = 
develop_CXXFLAGS = $(OCTETOS_CORE_CFLAGS) $(OCTETOS_COREUTILS_CFLAGS) $(ZLIB_CFLAGS)
develop_LDADD = $(OCTETOS_CORE_LIBS) $(OCTETOS_COREUTILS_LIBS) $(ZLIB_LIBS) libEC.la



