/*
    Narayan™, a library for simulating artificial life in big cities.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Multiple include protection...
#ifndef _RULE_LEXER_H_
#define _RULE_LEXER_H_

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Lexer base class...
    #include "RuleLexerBase.h"

    // All the token definitions needed for print()...
    #include "RuleParserBase.h"

    // Standard C++ / POSIX system headers...
    #include <sstream>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Forward declarations the compiler can expect within the Narayan namespace...
namespace Narayan { class RuleLexer; }

// Rule lexer class...
class Narayan::RuleLexer : public Narayan::RuleLexerBase
{
    // Public methods...
    public:

        // Constructor takes an input stream to parse and an output stream to
        //  write to...
        explicit RuleLexer(std::istream &in = std::cin,
                                std::ostream &out = std::cout);

        // Same as previous constructor but uses files...
        RuleLexer(std::string const &infile, std::string const &outfile = "-");
        
        // Wrapper around flexc++ generated lex__() to retrieve the next token,
        //  or zero if there are no more...
        int lex();

        // Enable printing of token and matching value...
        void setPrint(const bool Enabled = true) { m_Print = Enabled; }

    // Private methods...
    private:

        // Rretrieve the next token, or zero if there are no more...
        int lex__();

        // Execute an action for a given matched rule...
        int executeAction__(size_t ruleNr);

        // Print the token...
        void print();

        // Executed before a pattern match starts...
        void preCode();

        // Executed after a rule's action is executed...
        void postCode(PostEnum__ type);

    // Protected attributes...
    protected:

        // Print token and matching value...
        bool    m_Print;
};

// Situate within the Narayan namespace...
namespace Narayan
{

// $insert scannerConstructors
inline RuleLexer::RuleLexer(std::istream &in, std::ostream &out)
:
    RuleLexerBase(in, out),
    m_Print(false)
{}

inline RuleLexer::RuleLexer(std::string const &infile, std::string const &outfile)
:
    RuleLexerBase(infile, outfile),
    m_Print(false)
{}

// Retrieve the next token, or zero if there are no more...
inline int RuleLexer::lex()
{
    // Try to retrieve the next token...
    try
    {
        // Extract from stream...
        const auto Value = lex__();
        
        // Return it to parser...
        return Value;
    }
    
    // Something went wrong...
    catch(const std::runtime_error &Error)
    {
        // Prefix filename, line number, message, and offending text...
        std::stringstream BetterErrorMessage;
        BetterErrorMessage
            << filename() << ":"
            << lineNr() << ": "
            << Error.what() 
            << ": \'" << matched() << "\'";

        // Propagate exception up...
        throw std::runtime_error(BetterErrorMessage.str());
    }
}

// Executed before a pattern match starts...
inline void RuleLexer::preCode() 
{

}

// Executed after a rule's action is executed...
inline void RuleLexer::postCode(PostEnum__ /*type*/) 
{

}

// Print the token and matching text...
inline void RuleLexer::print() 
{
    // Not enabled, skip...
    if(not m_Print)
        return;

    // Storage for token identifier...
    std::string Token;
    
    // Storage for the value of the token...
    std::string Value = matched();

    // Convert the token symbolic identifier to a string because C++14 still
    //  can't do this at compile time in 2017...
    switch(d_token__)
    {
        case RuleParserBase::Tokens__::AGENT_OPTIONS:           Token = "AGENT_OPTIONS "; break;
        case RuleParserBase::Tokens__::APPLY_COUNT:             Token = "APPLY_COUNT"; break;
        case RuleParserBase::Tokens__::CHAIN:                   Token = "CHAIN"; break;
        case RuleParserBase::Tokens__::CREATE_UNIT:             Token = "CREATE_UNIT"; break;
        case RuleParserBase::Tokens__::DAY:                     Token = "DAY"; break;
        case RuleParserBase::Tokens__::EVENT_FAIL:              Token = "EVENT_FAIL"; break;
        case RuleParserBase::Tokens__::EVENT_SUCCESS:           Token = "EVENT_SUCCESS"; break;
        case RuleParserBase::Tokens__::EVENT_TYPE_ALERT:        Token = "EVENT_TYPE_ALERT"; break;
        case RuleParserBase::Tokens__::EVENT_TYPE_AUDIO:        Token = "EVENT_TYPE_AUDIO"; break;
        case RuleParserBase::Tokens__::EVENT_TYPE_EFFECT:       Token = "EVENT_TYPE_EFFECT"; break;
        case RuleParserBase::Tokens__::EXECUTE_RULE_ON_FAIL:    Token = "EXECUTE_RULE_ON_FAIL"; break;
        case RuleParserBase::Tokens__::HOUR:                    Token = "HOUR"; break;
        case RuleParserBase::Tokens__::IDENTIFIER:              Token = "IDENTIFIER"; break;
        case RuleParserBase::Tokens__::IN:                      Token = "IN"; break;
        case RuleParserBase::Tokens__::MAX_APPLY_COUNT:         Token = "MAX_APPLY_COUNT"; break;
        case RuleParserBase::Tokens__::NEW_LINE:                Token = "NEW_LINE"; Value = "\\n"; break;
        case RuleParserBase::Tokens__::NUMBER:                  Token = "NUMBER"; break;
        case RuleParserBase::Tokens__::OPTION_COUNT:            Token = "OPTION_COUNT"; break;
        case RuleParserBase::Tokens__::OPTION_ID:               Token = "OPTION_ID"; break;
        case RuleParserBase::Tokens__::OPTION_OR:               Token = "OPTION_OR"; break;
        case RuleParserBase::Tokens__::OPTION_REPEAT_AFTER:     Token = "OPTION_REPEAT_AFTER"; break;
        case RuleParserBase::Tokens__::OPTION_SEND_TO:          Token = "OPTION_SEND_TO"; break;
        case RuleParserBase::Tokens__::OPTION_SWITCH_TO:        Token = "OPTION_SWITCH_TO"; break;
        case RuleParserBase::Tokens__::OPTION_USING:            Token = "OPTION_USING"; break;
        case RuleParserBase::Tokens__::OPTION_VIA:              Token = "OPTION_VIA"; break;
        case RuleParserBase::Tokens__::OUT:                     Token = "OUT"; break;
        case RuleParserBase::Tokens__::PRIORITY:                Token = "PRIORITY"; break;
        case RuleParserBase::Tokens__::RANDOM:                  Token = "RANDOM"; break;
        case RuleParserBase::Tokens__::RATE:                    Token = "RATE"; break;
        case RuleParserBase::Tokens__::RELATIONAL_AT_LEAST:     Token = "RELATIONAL_AT_LEAST"; break;
        case RuleParserBase::Tokens__::RELATIONAL_AT_MOST:      Token = "RELATIONAL_AT_MOST"; break;
        case RuleParserBase::Tokens__::RELATIONAL_IS:           Token = "RELATIONAL_IS"; break;
        case RuleParserBase::Tokens__::RULE_END:                Token = "RULE_END"; break;
        case RuleParserBase::Tokens__::RULE_START_GLOBAL:       Token = "RULE_START_GLOBAL"; break;
        case RuleParserBase::Tokens__::RULE_START_MAP:          Token = "RULE_START_MAP"; break;
        case RuleParserBase::Tokens__::RULE_START_UNIT:         Token = "RULE_START_UNIT"; break;
        case RuleParserBase::Tokens__::RULE_START_ZONE:         Token = "RULE_START_ZONE"; break;
        case RuleParserBase::Tokens__::SAMPLE:                  Token = "SAMPLE"; break;
        case RuleParserBase::Tokens__::SCOPE_AGENT:             Token = "SCOPE_AGENT "; break;
        case RuleParserBase::Tokens__::SCOPE_CONNECTED:         Token = "SCOPE_CONNECTED"; break;
        case RuleParserBase::Tokens__::SCOPE_GLOBAL:            Token = "SCOPE_GLOBAL"; break;
        case RuleParserBase::Tokens__::SCOPE_LOCAL:             Token = "SCOPE_LOCAL"; break;
        case RuleParserBase::Tokens__::SCOPE_MAP:               Token = "SCOPE_MAP"; break;
        case RuleParserBase::Tokens__::TIME_TRIGGER:            Token = "TIME_TRIGGER"; break;
        case RuleParserBase::Tokens__::UNARY:                   Token = "UNARY"; break;
        default:                                                        Token = "?"; break;
    }

    // Show the token identifier with the matching text...
    std::cout << lineNr() << ": " << Token << " \'" << Value << "\'" << std::endl;

    // Show the token numeric identifier and the matched text...
//    print__();
}

}

#endif // RuleLexer_H_INCLUDED_

