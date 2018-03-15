#
#   Narayan™, a library for simulating artificial life in big cities.
#   Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
#

# If unit tests were enabled, define a list of targets to create and test...
if ENABLE_TESTS

# TODO: Add some tests incorporating tools from gettext-lint package...

# Product list of programs to build during check target...
check_PROGRAMS =                            \
    TestLexer                               \
    TestParser                              \
    TestRuntimeSane

# Product list of scripts to generate during check target, including pattern
#  matching stems...
check_SCRIPTS =                             \
    TestNarayanLogic

# GCS § 7.2.6 requires a check target. Targets to execute for check target...
TESTS =                                     \
    TestRuntimeSane                         \
    Rules/Map/GrowGrass.nl                  \
    Rules/Unit/CreateAlloy.nl               \
    Rules/Unit/GoToWork.nl                  \
    Rules/Unit/MustardFactory.nl            \
    Rules/Unit/ProducePower.nl              \
    Rules/Zone/DevelopHouses.nl

endif

# Custom test runner for NarayanLogic scripts per Automake §15.2.3...
TEST_EXTENSIONS = .nl
NL_LOG_COMPILER  = $(top_builddir)/Tests/TestNarayanLogic

# Preprocessor flags for all tests. Note that the include search paths are
#  paired between source and build directory as per Automake §8.7 to facilitate
#  VPATH builds...
AM_CPPFLAGS =                                                                   \
    -DSYSCONFDIR='"$(sysconfdir)"'                                              \
    -I$(top_srcdir)/Source/                                                     \
    -I$(top_builddir)/Source/

# Libraries to add for all tests. For some reason Automake doesn't have an
#  AM_LDADD, so we use LDADD per Automake §8.1.2...
LDADD = $(top_builddir)/libnarayan.la

# Test programs...
TestLexer_SOURCES       = TestLexer.cpp
TestParser_SOURCES      = TestParser.cpp
TestRuntimeSane_SOURCES = TestRuntimeSane.cpp

# Manually add these things to distribution package when dist target is run...
EXTRA_DIST =                                \
    Rules/Unit/CreateAlloy.nl               \
    Rules/Zone/DevelopHouses.nl             \
    Rules/Unit/GoToWork.nl                  \
    Rules/Map/GrowGrass.nl                  \
    Rules/Unit/MustardFactory.nl            \
    Rules/Unit/ProducePower.nl

# List of files to clean up during clean target...
CLEANFILES =                                \
    TestLexer                               \
    TestNarayanLogic                        \
    TestParser                              \
    TestRuntimeSane

# If valgrind was enabled, perform its unit test...
#if VALGRIND_ENABLED
#check_SCRIPTS += Valgrind.sh
#endif

# This script is used as a test harness for each Narayan Logic script to test.
#  It runs the latter through both the lexer and parser to verify successful
#  consumption...
TestNarayanLogic: TestLexer TestParser
	$(AM_V_GEN)echo 'set -e -u' > $@; \
	echo './TestLexer "$$1"' >> $@; \
	echo './TestParser "$$1"' >> $@; \
	$(CHMOD) +x $@

