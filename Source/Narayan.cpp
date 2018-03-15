/*
    Narayan™, a library for simulating artificial life in big cities.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Standard C++ / POSIX system headers...
    #include <cstdlib>
    #include <iostream>
    #include <stdexcept>
    
    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Using the standard namespace...
using namespace std;

// Library initializing...
NARAYAN_DEFINE_FUNCTION_CONSTRUCTOR(Narayan_Initialize)
static void Narayan_Initialize(void)
{
    // Initialize i18n if configured with native language support...

        // Select user's preferred locale according to environment variable and
        //  check for error...
        if(!::setlocale(LC_ALL, ""))
        {
            // Alert and abort...
            cerr << "error: failed to set user locale" << endl;
            exit(EXIT_FAILURE);
        }

    #if ENABLE_NLS

        // Set the current message domain and check for error...
        if(!::textdomain(PACKAGE))
        {
            // Alert and abort...
            cerr << "error: failed to set text domain ("
                 << ::strerror(errno) << ")" << endl;
            exit(EXIT_FAILURE);
        }

    #endif

    // Initialize C++ streams in case the standard C++ library hasn't had a
    //  chance to do so yet...
    ios_base::Init StreamInitializer;

    // Stubbed...
    cout << __PRETTY_FUNCTION__ << endl;

}

// Library cleaning up...
NARAYAN_DEFINE_FUNCTION_DESTRUCTOR(Narayan_Cleanup)
static void Narayan_Cleanup(void)
{
    // Stubbed...
    cout << __PRETTY_FUNCTION__ << endl;
}

