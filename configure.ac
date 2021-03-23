

AC_INIT(ae, 0.1.0-alpha, azael.devel@gmail.com)

AC_CONFIG_HEADERS([config.h])

AM_INIT_AUTOMAKE([1.11])

AM_SILENT_RULES([yes])

AC_PROG_CXX








LT_INIT

PKG_CHECK_MODULES(OCTETOS_CORE,octetos-core)

PKG_CHECK_MODULES(OCTETOS_COREUTILS,octetos-coreutils)

AC_SEARCH_LIBS([tar_open], [libtar tar], [], [AC_MSG_ERROR([unable to find the tar_open() function])])
AC_CHECK_HEADERS([libtar.h],[libtar.h=yes; break;])

AC_OUTPUT([
Makefile
src/Makefile

])
