/*
    Narayan™, a library for simulating artificial life in big cities.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _RULE_PARSER_H_
#define _RULE_PARSER_H_

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Parser base class...
    #include "RuleParserBase.h"

    // CAVEAT: between the baseclass-include directive and the #undef directive
    // in the previous line references to RuleParser are read as RuleParserBase.
    // If you need to include additional headers in this file you should do so
    // after these comment-lines.
    #undef RuleParser

    // Lexer user class...
    #include "RuleLexer.h"

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Forward declarations the compiler can expect within the Narayan namespace...
namespace Narayan { class RuleParser; }

// Rule parser class...
class Narayan::RuleParser : public Narayan::RuleParserBase
{
    // Public methods...
    public:

        // Default constructor expecting input from stdin...
        RuleParser() = default;

        // Constructor expecting path to input file...
        RuleParser(const std::string &InputFile);

        // Parse input...
        int parse();

    // Private methods...
    private:

        // Called on syntax errors...
        void error();

        // Returns the next token from the lexical scanner...
        int lex();

        void print();                   // use, e.g., d_token, d_loc

        // Semantic error raised an exception during a semantic action...
        void exceptionHandler(std::exception const &exc);

    // Support functions for parse()...
    void executeAction__(int ruleNr);
    void errorRecovery__();
    void nextCycle__();
    void nextToken__();
    void print__();

    // Protected attributes...
    protected:

        // Lexer...
        RuleLexer   d_scanner;
};

#endif

