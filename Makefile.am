#
#   Narayan™, a library for simulating artificial life in big cities.
#   Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
#

# Run the requested make target recursively on child makefiles. By default
#  Automake generates Makefiles that recurse in depth-first postfix order, but
#  we need to build current directory first, so the . changes to prefix
#  ordering. It is customary to list unit tests last since they are meant to
#  test what was constructed (Automake manual §7.1)...
SUBDIRS =                                                                       \
    .                                                                           \
    Translations                                                                \
    Tests

# Preprocessor definitions to pass down to the compiler...
DEFS=
DEFS+= -DSYSCONFDIR='"$(sysconfdir)"' -DLOCALEDIR="\"$(localedir)\"" @DEFS@

# Product list containing only libnarayan shared library destined for the
#  library prefix...
lib_LTLIBRARIES = libnarayan.la

# Source files for rule lexer clobbered by each flexc++(1) invocation.
#  These should always be created within $(builddir)...
lexer_clobbered_source_files_only =                                             \
    RuleLexerBase.cpp                                                           \
    RuleLexerBase.h

lexer_clobbered_source_full_paths =                                             \
    Source/RuleLexerBase.cpp                                                    \
    Source/RuleLexerBase.h

# Source files for rule lexer generated once by flexc++(1), but subsequently
#  owned by the user. These should always be maintained within $(sourcedir)...
lexer_unclobbered_source_files_only =                                           \
    RuleLexer.h                                                                 \
    RuleLexer.ih

lexer_unclobbered_source_full_paths =                                           \
    Source/RuleLexer.h                                                          \
    Source/RuleLexer.ih

# Source files for rule parser clobbered by each bisonc++(1) invocation. These
#  should always be created within $(builddir)...
parser_clobbered_source_files_only =                                            \
    RuleParserBase.h                                                            \
    RuleParser.cpp

parser_clobbered_source_full_paths =                                            \
    Source/RuleParserBase.h                                                     \
    Source/RuleParser.cpp

# Source files for rule parser generated once by bisonc++(1), but subsequently
#  owned by the user. These should always be maintained within $(sourcedir)...
parser_unclobbered_source_files_only =                                          \
    RuleParser.h                                                                \
    RuleParser.ih

parser_unclobbered_source_full_paths =                                          \
    Source/RuleParser.h                                                         \
    Source/RuleParser.ih

# Headers to distribute for the public interface....
pkginclude_HEADERS =                                                            \
    Source/Simulation.h                                                         \
    Source/Version.h

# narayan-designer product option variables containing list of sources that need
#  to be compiled and linked to produce the product...
libnarayan_la_SOURCES =                                                         \
    $(lexer_unclobbered_source_full_paths)                                      \
    $(parser_unclobbered_source_full_paths)                                     \
    Source/FiniteStateMachine.h                                                 \
    Source/FiniteStateMachine.inl                                               \
    Source/gettext.h                                                            \
    Source/Graph.inl                                                            \
    Source/Graph.h                                                              \
    Source/Narayan.cpp                                                          \
    Source/Simulation.cpp                                                       \
    Source/Simulation.h

# Get build flags...
libnarayan_la_CFLAGS     = $(AM_CFLAGS)
libnarayan_la_CXXFLAGS   = $(AM_CXXFLAGS)
libnarayan_la_LDFLAGS    = $(AM_LDFLAGS)
libnarayan_la_LIBADD     = liblexerparser.la

# Preprocessor flags. Note that the include search paths are paired between
#  source and build directory as per Automake manual §8.7 to facilitate VPATH
#  builds...
libnarayan_la_CPPFLAGS   =                                                      \
    -DSYSCONFDIR='"$(sysconfdir)"'                                              \
    -I$(srcdir)/Source/                                                         \
    -I$(builddir)/Source/                                                       \
    $(AM_CPPFLAGS)

# Both flexc++(1) and bisonc++(1) at the time of writing emit code that can
#  raise warnings, or even errors in the case of -Werror, when used with GCC 7
#  series compilers. I have submitted a number of patches to upstream with
#  varying degrees of success to address various issues. In the interim, the
#  best thing to do is to compartmentalize the necessary compilation flags for
#  code emitted by these two tools into a static libtool convenience library. 
#  This has the benefit of isolating the potential harm within the convenience
#  library that may have spilled over to other application code whenever
#  explicitly disabling useful safety measures, such as -Wall -Werror -Wshadow
#  -Wextra switches that raise issues like switch-case fall throughs, unused
#  variables, and so forth...
noinst_LTLIBRARIES = liblexerparser.la
nodist_liblexerparser_la_SOURCES   =                                            \
    $(lexer_clobbered_source_full_paths)                                        \
    $(parser_clobbered_source_full_paths)
liblexerparser_la_CXXFLAGS  = -Wimplicit-fallthrough=0 -Wno-unused-parameter
liblexerparser_la_CPPFLAGS  =                                                   \
    -DSYSCONFDIR='"$(sysconfdir)"'                                              \
    -I$(srcdir)/Source/                                                         \
    -I$(builddir)/Source/                                                       \
    $(AM_CPPFLAGS)

# Extend silent mode for flexc++(1) inputs per Automake manual §21.3...
AX_V_FLEXCPP = $(AX_V_FLEXCPP_@AM_V@)
AX_V_FLEXCPP_ = $(AX_V_FLEXCPP_@AM_DEFAULT_V@)
AX_V_FLEXCPP_0 = @echo "  FLEXCPP  $(lexer_clobbered_source_full_paths)";

# Extend silent mode for bisonc++(1) inputs per Automake manual §21.3...
AX_V_BISONCPP = $(AX_V_BISONCPP_@AM_V@)
AX_V_BISONCPP_ = $(AX_V_BISONCPP_@AM_DEFAULT_V@)
AX_V_BISONCPP_0 = @echo "  BISONCPP $(parser_clobbered_source_full_paths)";

# Temporary directory to place flexc++(1) and bisonc++(1) generated files...
COMPILER_TMP=$(builddir)/Source/tmp

# Locale directory...
localedir = $(datadir)/locale

# pkgconfig data...
pkgconfigdir    = $(libdir)/pkgconfig
pkgconfig_DATA  = narayan.pc

# Miscellaneous data files...
dist_pkgdata_DATA =                                                             \
    Authors                                                                     \
    News                                                                        \
    ReadMe

# List of files to clean up during clean target...
CLEANFILES =                                                                    \
    Source/lexer.stamp                                                          \
    Source/parser.stamp                                                         \
    $(lexer_clobbered_source_full_paths)                                        \
    narayan.pc                                                                  \
    $(parser_clobbered_source_full_paths)                                       \
	Translations/*.gmo

# Additional files left behind during dist target that need to be cleaned...
DISTCLEANFILES =                                                                \
    Source/lexer.stamp                                                          \
    Source/parser.stamp                                                         \
	_configs.sed                                                                \
    $(PACKAGE_TARNAME)-$(PACKAGE_VERSION).tar.*

# These files must exist before anything is compiled. Can be machine
#  generated...
BUILT_SOURCES =                                                                 \
    Source/lexer.stamp                                                          \
    Source/parser.stamp                                                         \
    $(lexer_clobbered_source_full_paths)                                        \
    $(parser_clobbered_source_full_paths)                                       \
    Source/Version.h

# Manually add these non-source files to distribution package when dist target is run...
EXTRA_DIST =                                                                    \
    Source/RuleLexer.lpp                                                        \
    Source/RuleParser.ypp                                                       \
    Authors                                                                     \
    ChangeLog                                                                   \
    Copying                                                                     \
    Install                                                                     \
    narayan.pc.in                                                               \
    News                                                                        \
    ReadMe

# Make sure gettext is present...
check-gettext:
	@if test x$(USE_NLS) != "xyes" ; then echo "Missing gettext. Re-run configure and check for" \
	"'checking whether to use NLS... yes'!" ; exit 1 ; fi

# Before we prepare a distribution, run this hook...
dist-hook:
	$(RM) -r `find $(distdir) -name .git`
	$(RM) -r `find $(distdir) -name .hg`
	$(RM) -r `find $(distdir) -name .svn`

# Force an update to the machine dependent message catalogs...
force-update-gmo: check-gettext
	find Translations/ -type f -name "*.po" -execdir touch {} \;
	cd Translations && $(MAKE) $(AM_MAKEFLAGS) update-gmo

# Maintainer clean local hook to remove Autotools configuration output files...
maintainer-clean-local:
	$(RM) -r '$(srcdir)/autom4te.cache'

# Generate the Narayan Logic lexer source from its regular expression token
#  descriptions via flexc++, using that file as a witness. After that generate
#  a stamp target for the entire set of derived lexer files...
$(lexer_clobbered_source_full_paths): Source/lexer.stamp
Source/lexer.stamp: Source/RuleLexer.lpp Source/parser.stamp
	@$(MKDIR_P) $(COMPILER_TMP)
	$(AX_V_FLEXCPP)$(FLEXCPP) --target-directory=$(COMPILER_TMP) $<
	@for lexer_file in $(lexer_clobbered_source_files_only); do \
		mv $(COMPILER_TMP)/$$lexer_file Source/; \
	done
	@rm -Rf $(COMPILER_TMP)
	@echo "timestamp for $^" > $@

# Generate the Narayan Logic parser source from its Backus-Naur grammar rules
#  via bisonc++, using that file as a witness. After that generate a stamp 
#  target for the entire set of derived lexer files...
$(parser_clobbered_source_full_paths): Source/parser.stamp
Source/parser.stamp: Source/RuleParser.ypp
	@$(MKDIR_P) $(COMPILER_TMP)
	$(AX_V_BISONCPP)$(BISONCPP) --target-directory=$(COMPILER_TMP) $<
	@for parser_file in $(parser_clobbered_source_files_only); do \
		mv $(COMPILER_TMP)/$$parser_file Source/; \
	done
	@rm -Rf $(COMPILER_TMP)
	@echo "timestamp for $^" > $@

# Update the machine dependent message catalogs...
update-gmo: check-gettext
	cd Translations && $(MAKE) $(AM_MAKEFLAGS) update-gmo

# Update the list of files to translate in POTFILES.in and then update the .pot
#  message translation template file..
update-po: check-gettext
	@echo "Checking if POTFILES.in needs to be updated..."
	@cd $(srcdir) ; \
	find Source \( -iname "*.lpp" -o -iname "*.ypp" \) -print >> Translations/POTFILES.in.2 ; \
	find Source \( -iname "*.cpp" -o -iname "*.cpp.in" -o -iname "*.inl" \) -print >> Translations/POTFILES.in.2 ; \
	find Source \( -iname "*.h" -o -iname "*.h.in" -o -iname "*.ih" \) -print >> Translations/POTFILES.in.2 ; \
	$(SED) -i '/config.h$$/d' Translations/POTFILES.in.2 ; \
	$(SED) -i '/RuleLexerBase.cpp/d' Translations/POTFILES.in.2 ; \
	$(SED) -i '/RuleLexerBase.h/d' Translations/POTFILES.in.2 ; \
	$(SED) -i '/RuleParserBase.h/d' Translations/POTFILES.in.2 ; \
	$(SED) -i '/RuleParser.cpp/d' Translations/POTFILES.in.2 ; \
	$(SED) -i '/Version.h$$/d' Translations/POTFILES.in.2 ; \
	$(SORT) Translations/POTFILES.in.2 --output=Translations/POTFILES.in.2 ; \
	if diff Translations/POTFILES.in Translations/POTFILES.in.2 >/dev/null 2>&1 ; then \
		echo "No update to POTFILES.in required..." ; \
		$(RM) -f Translations/POTFILES.in.2 ; \
	else \
		echo "POTFILES.in updated..." ; \
		mv -v Translations/POTFILES.in.2 Translations/POTFILES.in ; \
	fi
	cd Translations && $(MAKE) $(AM_MAKEFLAGS) update-po

# Targets which aren't actually files...
.PHONY: check-gettext force-update-gmo maintainer-clean-local update-gmo update-po

