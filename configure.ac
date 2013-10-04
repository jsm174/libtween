dnl Process this file with autoconf to produce a configure script

dnl ------------------------------------------------
dnl Initialization and Versioning
dnl ------------------------------------------------

AC_INIT([libtween],[0.1])

AC_CANONICAL_HOST
AC_CANONICAL_TARGET

AC_CONFIG_SRCDIR([libtween/tween.c])
AM_INIT_AUTOMAKE
AM_MAINTAINER_MODE

dnl Library versioning

TWEEN_LIB_CURRENT=0
TWEEN_LIB_REVISION=1
TWEEN_LIB_AGE=0
AC_SUBST(TWEEN_LIB_CURRENT)
AC_SUBST(TWEEN_LIB_REVISION)
AC_SUBST(TWEEN_LIB_AGE)

dnl --------------------------------------------------  
dnl Check for programs
dnl --------------------------------------------------  

AC_PROG_CC

LT_INIT

dnl Add parameters for aclocal

AC_CONFIG_MACRO_DIR([m4])

dnl --------------------------------------------------
dnl Checks for support libraries and headers
dnl --------------------------------------------------

dnl check for SDL2

HAVE_SDL2=no
SDL2_VERSION=2.0.0
AM_PATH_SDL2([$SDL2_VERSION], [HAVE_SDL2=yes], [HAVE_SDL2=no])

dnl --------------------------------------------------
dnl Overall build configuration options
dnl --------------------------------------------------

dnl Configuration option for examples

ac_enable_examples=yes
AC_ARG_ENABLE(examples,
     AS_HELP_STRING([--disable-examples], [Disable examples]),
     [ac_enable_examples=$enableval], [ac_enable_examples=yes] )

if test "x${ac_enable_examples}" != "xno"; then
   if test "x$HAVE_SDL2" = "xno"; then
      ac_enable_examples=no
      AC_MSG_WARN([*** Unable to find SDL2 -- Examples will not be built ***])
   fi
fi

AM_CONDITIONAL(TWEEN_ENABLE_EXAMPLES, [test "x${ac_enable_examples}" != xno])

AC_CONFIG_FILES([
  Makefile 
  libtween/Makefile
  examples/Makefile
  m4/Makefile
])

AC_OUTPUT

AS_AC_EXPAND(LIBDIR, ${libdir})
AS_AC_EXPAND(INCLUDEDIR, ${includedir})


AC_MSG_RESULT([
------------------------------------------------------------------------
  $PACKAGE $VERSION:  Automatic configuration OK.

  General configuration:

    Build examples: .............. ${ac_enable_examples}

  Installation paths:

    libtween: .................... ${LIBDIR}
    C header files: .............. ${INCLUDEDIR}/libtween

  Building:

    Type 'make' to compile $PACKAGE.

    Type 'make install' to install $PACKAGE.

------------------------------------------------------------------------
])
