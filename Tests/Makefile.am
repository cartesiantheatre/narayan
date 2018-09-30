#
#   Narayan™, a library for simulating artificial life in big cities.
#   Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
#

# If unit tests were enabled, define a list of targets to create and test...
if ENABLE_TESTS

# TODO: Add some tests incorporating tools from gettext-lint package...

# Product list of programs to build during check target...
check_PROGRAMS =                            \
    TestGraph                               \
    TestRuleLexer                           \
    TestRuleParser                          \
    TestRuntimeSane

# Product list of scripts to generate during check target, including pattern
#  matching stems...
check_SCRIPTS =                             \
    TestRuleLexerParser

# GCS § 7.2.6 requires a check target. Targets to execute for check target...
TESTS =                                     \
    TestGraph                               \
    TestRuntimeSane                         \
    Rules/Map/GrowGrass.nl                  \
    Rules/Unit/CreateAlloy.nl               \
    Rules/Unit/GoToWork.nl                  \
    Rules/Unit/MustardFactory.nl            \
    Rules/Unit/ProducePower.nl              \
    Rules/Zone/DevelopHouses.nl

endif

# Custom test runner for rule scripts per Automake §15.2.3...
TEST_EXTENSIONS = .nl
NL_LOG_COMPILER  = $(top_builddir)/Tests/TestRuleLexerParser

# Preprocessor flags for all tests. Note that the include search paths are
#  paired between source and build directory as per Automake §8.7 to facilitate
#  VPATH builds...
AM_CPPFLAGS =                                                                   \
    -DSYSCONFDIR='"$(sysconfdir)"'                                              \
    -I$(top_srcdir)/Source/                                                     \
    -I$(top_builddir)/Source/

# Libraries to add for all tests. For some reason Automake doesn't have an
#  AM_LDADD, so we use LDADD per Automake §8.1.2...
LDADD = $(top_builddir)/libnarayan.la $(cppunit_LIBS)

# Preprocessor flags...
AM_CXXFLAGS = $(cppunit_CFLAGS)

# Test programs...
TestGraph_SOURCES           = TestGraph.cpp
TestRuleLexer_SOURCES       = TestRuleLexer.cpp
TestRuleParser_SOURCES      = TestRuleParser.cpp
TestRuntimeSane_SOURCES     = TestRuntimeSane.cpp

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
    TestRuleLexerParser                     \
    $(check_PROGRAMS)

# If valgrind was enabled, perform its unit test...
#if VALGRIND_ENABLED
#check_SCRIPTS += Valgrind.sh
#endif

# This script is used as a test harness for each rule script to test. It runs
#  the latter through both the lexer and parser to verify successful
#  consumption...
TestRuleLexerParser: TestRuleLexer TestRuleParser
	$(AM_V_GEN)echo 'set -e -u' > $@; \
	echo './TestRuleLexer "$$1"' >> $@; \
	echo './TestRuleParser "$$1"' >> $@; \
	$(CHMOD) +x $@

