# Narayan™, a library for simulating artificial life in big cities.
# Copyright (C) 2017-2018 Cartesian Theatre™. All rights reserved.

# Minimum version of Autoconf used to successfully process configure.ac...
AC_PREREQ([2.67])

# Initialize Autoconf...
AC_INIT(
    [narayan],
    [0.0.000],
    [https://github.com/cartesiantheatre/narayan/issues],
    [narayan],
    [https://www.cartesiantheatre.com])

# Clear default C / C++ compiler flags. Otherwise -g -O2 is automatically set
#  for the GNU C++ by AC_PROG_CC and AC_PROG_CXXCPP. Can still be overridden by
#  user. This needs to be right here after AC_INIT or these variables will get
#  clobbered...
: ${CFLAGS=""}
: ${CXXFLAGS=""}

# Location to find auxiliary automake scripts...
AC_CONFIG_AUX_DIR([Auxiliary])

# Location to find Autoconf plugins...
AC_CONFIG_MACRO_DIR([Macros])

# Sanity check to ensure generated ./configure script knows the directory on
#  which it is being executed is actually the project directory by providing any
#  unique source file...
AC_CONFIG_SRCDIR([Source/Narayan.cpp])

# Preserve all arguments for products that want them into config.h...
config_flags="$0 $*"
AC_DEFINE_UNQUOTED(
    [CONFIGURATION_FLAGS],
    ["$config_flags"],
    [All flags that were passed to configure at configuration time.])

# Store build date stamp...
package_build_date=$(date --rfc-2822)
AC_DEFINE_UNQUOTED(
    [PACKAGE_BUILD_DATE],
    ["$package_build_date"],
    [Date and time this package was built.])
AC_SUBST([PACKAGE_BUILD_DATE], [$package_build_date])

# Copyright notice...
copyright_notice="Copyright (C) 2017-2018 Cartesian Theatre™."
AC_COPYRIGHT([$copyright_notice])
AC_DEFINE_UNQUOTED(
    [COPYRIGHT_NOTICE],
    ["$copyright_notice"],
    [Upstream vendor's copyright notice.])
AC_SUBST([COPYRIGHT_NOTICE], [$copyright_notice])

# Initialize Automake...

    # Setup flags. Add std-options later...
    AM_INIT_AUTOMAKE([
        color-tests     \
        dist-bzip2      \
        foreign         \
        no-dist-gzip    \
        silent-rules    \
        subdir-objects  \
        tar-pax         \
        -Wall           \
        -Werror])

    # Set by default to use silent build rules...
    AM_SILENT_RULES([yes])

    # Always enable maintainer mode, but allow user the option to disable it...
    AM_MAINTAINER_MODE([enable])

# Initialize libtool...

    # To build a 
    AM_PROG_AR

    # Minimum version required...
    LT_PREREQ([2.4.6])

    # Initialize with support for dynamic object loading at runtime. By default
    #  we disable static library generation, but this can be overridden...
    LT_INIT([disable-static])
    
    # C++ language support should be enabled automatically, so this isn't really
    #  necessary...
    LT_LANG([C++])

# Prepare canonical values for the platform we are compiling on and the platform
#  to host the generated files on...
AC_CANONICAL_BUILD
AC_CANONICAL_HOST

# Configure config.h...

    # Location to generate headers from templates containing Autoconf
    #  substitution variables...
    AC_CONFIG_HEADERS([Source/config.h])

# Check for command-line options...

    # Bash completion...
    AC_ARG_ENABLE([bash-completion],
        [AS_HELP_STRING([--enable-bash-completion],
            [enable bash completion @<:@default: yes@:>@])], # Quadrigraph escaped
        [enable_bash_completion=${enableval}],
        [enable_bash_completion="yes"])
    AM_CONDITIONAL(USE_BASH_COMPLETION, [test x"$enable_bash_completion" = "xyes"])

    # Unit tests...
    AC_ARG_ENABLE([tests],
        [AS_HELP_STRING([--enable-tests],
            [enable unit tests @<:@default: yes@:>@])], # Quadrigraph escaped
        [enable_tests=${enableval}],
        [enable_tests="yes"])
    AM_CONDITIONAL(ENABLE_TESTS, [test x"$enable_tests" = "xyes"])

# Initialize i18n from GNU gettext...

    # Version 0.19.7 forward supports GtkBuilder XML, .desktop files, GSettings
    #  schemas, AppData, and Custom XML formats with ITS rules...
    #  Note: No white space indentation because of
    #  <https://savannah.gnu.org/bugs/index.php?52424>
AM_GNU_GETTEXT([external], [need-ngettext])
AM_GNU_GETTEXT_VERSION([0.19.8])

    # These options get passed to xgettext. These are the full GLib-approved
    #  list of options for use in a Gtk+ project...
    AM_XGETTEXT_OPTION([--from-code=UTF-8 --keyword=_ --keyword=N_ --keyword=C_:1c,2 --keyword=NC_:1c,2 --keyword=g_dngettext:2,3 --add-comments])

# Make sure paths are sane...

    # Alert user...
    AC_MSG_CHECKING([whether paths are sane...])

    # Build directory must not contain spaces...
    if echo $PWD | grep -E ' ' >/dev/null ; then
        AC_MSG_RESULT([no])
        AC_MSG_ERROR([your build path must not contain spaces...])
    fi

    # Source directory must not contain spaces...
    if echo $srcdir | grep -E ' ' >/dev/null ; then
        AC_MSG_RESULT([no])
        AC_MSG_ERROR([your source path must not contain spaces...])
    fi
    
    # Paths are sane...
    AC_MSG_RESULT([yes])

# Checks for programs needed to build everything and perform unit tests...

    # Bison C++ parser generator...
    AX_PROG_BISONCPP([6.01.01])
    AC_PATH_PROG([BISONCPP], [bisonc++])

    # chmod...
    AC_PATH_PROG([CHMOD], [chmod])

    # C++17 compiler with strict conformance required...
    AC_PROG_CXX
    AX_CXX_COMPILE_STDCXX_17([noext], [mandatory])

    # C++ preprocessor...
    AC_PROG_CXXCPP

    # Flex C++ lexer generator...
    AX_PROG_FLEXCPP([2.06.02])
    AC_PATH_PROG([FLEXCPP], [flexc++])

    # grep(1) required for test suite...
    AC_PROG_GREP

    # install(1) utility to copy files and set attributes...
    AC_PROG_INSTALL

    # mkdir -p functionality required in several places...
    AC_PROG_MKDIR_P

    # mktemp(1) tool required to perform test suite...
    AC_PATH_PROG([MKTEMP], [mktemp])
    if test "x$MKTEMP" = "x"; then
        AC_MSG_ERROR([mktemp tool is required to perform test suite...])
    fi

    # rmdir(1) necessary in various places...
    AC_PATH_PROG([RMDIR], [rmdir])
    if test "x$RMDIR" = "x"; then
        AC_MSG_ERROR([rmdir required, but unavailable...])
    fi

    # sed(1) tool...
    AC_PROG_SED

    # sort(1) command...
    AC_PATH_PROG([SORT], [sort])
    if test "x$SORT" = "x"; then
        AC_MSG_ERROR([sort required, but unavailable...])
    fi

    # Valgrind optional, but used in unit testing if enabled by default...
    AX_VALGRIND_CHECK
    if test "x$enable_valgrind" = "xyes" && test "$VALGRIND" = ""; then
        AC_MSG_ERROR([valgrind required to perform test suite, but not found; either install or reconfigure with --disable-valgrind])
    fi

# Select our native language of C++ to perform tests in, unless we specify
#  otherwise later...
AC_LANG([C++])

# Substitute autoconfig macros in various non-make related files...

    # Pkg-config...
    AC_CONFIG_FILES([narayan.pc])

    # Update version string...
    AC_CONFIG_FILES([Source/Version.h])

# Checks for system headers and features...

    # SIMD extensions...
    AX_CHECK_X86_FEATURES
    AC_LANG([C++]) # The above clobbers AC_LANG...

    # Figure out how to set a software traps on this particular hardware...
    AC_MSG_CHECKING([how to trigger software traps on $host_cpu])
    BREAKPOINT_TRAP=""
    case "$host_cpu" in
        arm*)   BREAKPOINT_TRAP="asm volatile(\"bkpt\");" ;;
        mips*)  BREAKPOINT_TRAP="asm volatile(\"teq \$0, \$0\");" ;;
        *i?86)   ;&
        x86_64) BREAKPOINT_TRAP="asm volatile(\"int \$0x03\");" ;;
    esac
    AC_DEFINE_UNQUOTED([BREAKPOINT_TRAP], $BREAKPOINT_TRAP, [Trigger a software trap on this architecture...])
    AC_MSG_RESULT([$BREAKPOINT_TRAP])

    # Function constructor attributes...
    AC_MSG_CHECKING([for function constructor attribute])
    AX_VAR_PUSHVALUE([CXXFLAGS],[-Werror=attributes])
    AC_RUN_IFELSE(
        [AC_LANG_PROGRAM(
        [
            #include <cstdlib>
            int works = 2;
            void __attribute__((constructor)) Initialize() { --works; }
            void __attribute__((destructor)) Cleanup() { --works; exit(works == 0 ? EXIT_SUCCESS : EXIT_FAILURE); }
        ],
        [
            return EXIT_FAILURE;
        ])],
        [
            AC_DEFINE([NARAYAN_DEFINE_FUNCTION_CONSTRUCTOR(_Name)], [static void __attribute__((constructor)) _Name(void);], [A function with a constructor attribute...])
            AC_DEFINE([NARAYAN_DEFINE_FUNCTION_DESTRUCTOR(_Name)], [static void __attribute__((destructor)) _Name(void);], [A function with a destructor attribute...])
            AC_MSG_RESULT([supported])
        ],
        [AC_MSG_ERROR([not supported...])])
    AX_VAR_POPVALUE([CXXFLAGS])

    # Standard C++ headers...
    AC_CHECK_HEADERS(
        [cassert cerrno cstddef cctype iostream stdexcept memory],
        [], [AC_MSG_ERROR([missing some required standard C++ headers...])])

    # Check for thread local storage...
    AX_VAR_PUSHVALUE([CXXFLAGS],[""])
    AX_TLS([], [AC_MSG_ERROR([thread local storage is not available on your compiler...])])
    AX_VAR_POPVALUE([CXXFLAGS])

    # POSIX headers for all sub-projects...
    AC_LANG_PUSH([C])
    AC_CHECK_HEADERS([getopt.h unistd.h], [],
        [AC_MSG_ERROR([missing a required POSIX header...])])
    AC_LANG_POP([C])

    # Locates pkg-config tool on system, checks compatibility, verifies sane...
    PKG_PROG_PKG_CONFIG([0.25])

    # Bash completion requested...
    if test "x${enable_bash_completion}" = xyes; then

        # Initialize path for bash completion scripts to be installed to...
        bash_completiondir=$sysconfdir/bash_completion.d
        AC_SUBST(bash_completiondir)

    fi

# Check for headers and libraries...

    # CppUnit for unit testing if unit tests were enabled. We want the
    #  freedesktop.org version, but not clear if there is any way to verify that
    #  this is their fork. Note that we don't append the global compilation and
    #  link flags with cppunit's because they're only needed for unit tests...
    if test x"$enable_tests" = "xyes"; then
        PKG_CHECK_MODULES(
            [cppunit], [cppunit >= 1.14.0], [],
            [AC_MSG_ERROR([cppunit >= 1.14.0 not found...])])
    fi

    # OpenCL dispatch library (loader) acts as a proxy to the actual vendor
    #  implementation. The dispatch library is what we link to, but the actual
    #  vendor implementation (ICD), or Installable Client Driver, comes in the
    #  form of...
    #
    #   [Package]           [Maintainer]    [Hardware]      [License]
    #
    #   amd-opencl-icd      AMD             AMD             non-free
    #   beignet-opencl-icd  fd.o            Intel           free
    #   mesa-opencl-icd     Mesa            AMD / Radeon    free
    #   nvidia-opencl-icd   nVidia          nVidia          non-free
    #   pocl-opencl-icd     pocl            Software based  free
    #

        # First try to find loader via pkg-config...
        PKG_CHECK_MODULES(
            [libOpenCL], [OpenCL >= 2.1], 
            
            # Found it...
            [
                # Save compiler and linker flags...
                CXXFLAGS="$CXXFLAGS $libOpenCL_CFLAGS"
                LIBS="$LIBS $libOpenCL_LIBS"
            ],
            
            # Didn't find it...
            [
                # Notify user...
                AC_MSG_NOTICE([OpenCL dispatch library detected via pkg-config, attempting manual fallback...])

                # Try compiling and linking against any available OpenCL library
                #  installed on the system. Then try dynamically loading an
                #  expecting function. If successful store compiler and linker
                #  flags...
                AC_CHECK_LIB(
                    [OpenCL], [clGetPlatformInfo], 
                    [],
                    [AC_MSG_ERROR([missing OpenCL dispatch library or no clGetPlatformfInfo function found...])])
            ])

    # OpenCL C++ headers...
    AC_CHECK_HEADERS(
        [CL/cl2.hpp],
        [], [AC_MSG_ERROR([missing OpenCL 2.0 header...])])

    # YAML C++ headers and libraries...
    PKG_CHECK_MODULES(
        [libyaml_cpp], [yaml-cpp >= 0.5.2], [],
        [AC_MSG_ERROR([yaml-cpp >= 0.5.2 not found...])])
    CXXFLAGS="$CXXFLAGS $libyaml_cpp_CFLAGS"
    LIBS="$LIBS $libyaml_cpp_LIBS"

# Checks for typedefs, structures, and compiler characteristics...

    # Endianness...
    AC_C_BIGENDIAN
    
    # Signedness of char...
    AC_C_CHAR_UNSIGNED

    # Fixed width primitives...
    AC_TYPE_INT8_T
    AC_TYPE_INT16_T
    AC_TYPE_INT32_T
    AC_TYPE_UINT8_T
    AC_TYPE_UINT16_T
    AC_TYPE_UINT32_T

    # Other basic types...
    AC_TYPE_SIZE_T

# Checks for individual functions within libraries...

    # POSIX, Standard C, GNU C library extensions...
    AC_CHECK_FUNCS([clock getenv getopt_long realpath sigaction], [],
        [AC_MSG_ERROR([missing some POSIX, standard C, or GNU C library functions...])])

# Set additional compilation flags...

    # Enable all warnings and treat them as errors...
    CXXFLAGS="$CXXFLAGS -Wall -Werror -Wshadow -Wextra"

# Generate makefiles from templates containing Autoconf substitution variables
#  for root makefile...
AC_CONFIG_FILES([                                                               \
    Makefile                                                                    \
    Tests/Makefile                                                              \
    Translations/Makefile.in])

# Generates config.status which generates all files from templates...
AC_OUTPUT

# Show a user summary of the configuration...
echo \
"-----------------------------------------------------

${PACKAGE_NAME} ${PACKAGE_VERSION}
$copyright_notice

Prefix........................: $prefix

Optional package features:
    Bash completion...........: $enable_bash_completion
    Native language support...: $USE_NLS
    Unit tests................: $enable_tests
        Valgrind unit test....: $enable_valgrind

Compiler......................: $CXX
Linker........................: $LD

C++ Flags.....................: $CFLAGS $CXXFLAGS
C++ Preprocessor..............: $CPPFLAGS
Linker Flags..................: $LDFLAGS
Linker Libs...................: $LIBS

Now type 'make @<:@<target>@:>@' where the optional
<target> is:
    all            ...builds all products (default)
    check          ...perform all self diagnostics
    clean          ...clean the build
    dist           ...builds redistributable archive
    distcheck      ...self diagnostics on previous
    install        ...install to $prefix

-----------------------------------------------------"

