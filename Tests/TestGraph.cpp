/*
    Narayan Designer, a modelling tool for the Narayan simulation engine.
    Copyright (C) 2017-2018 Cartesian Theatre. All rights reserved.
*/

// Includes...

    // Provided by Autoconf...
    #include <config.h>

    // Our headers...
    #include "Graph.h"
    
    // CppUnit...
    #include <cppunit/extensions/HelperMacros.h>
    #include <cppunit/CompilerOutputter.h>
    #include <cppunit/extensions/TestFactoryRegistry.h>
    #include <cppunit/ui/text/TestRunner.h>

    // i18n...
    #include "gettext.h"
    #define _(str) gettext (str)
    #define N_(str) gettext_noop (str)

// Namespaces...

    // Using the standard namespace...
    using namespace std;
    
    // CppUnit...
    using namespace CppUnit;

// Provide a common environment for a set of test cases...
class GraphTestFixture : public TestFixture
{
    // Declare test suite and a factory function...
    CPPUNIT_TEST_SUITE(GraphTestFixture);
    
    // Add each unit test to the test suite...
    CPPUNIT_TEST(TestSomething);
    
    // Finished declaring test suite...
    CPPUNIT_TEST_SUITE_END();

    // Public methods...
    public:

        // Setup context before running a test...
        void setUp() override
        {
        
        }
        
        // Cleanup after running a test...
        void tearDown() override
        {
        
        }

        // Test something...
        void TestSomething()
        {
            CPPUNIT_ASSERT(true);
        }

    // Private data...
    private:
    
        /* Sample graphs here */
};

// Automatically register the test suite in the TestFactoryRegistry...
CPPUNIT_TEST_SUITE_REGISTRATION(GraphTestFixture);

// Entry point...
int main()
{
    // Initialize i18n if configured with native language support...

        // Select user's preferred locale according to environment variable and
        //  check for error...
        if(!::setlocale(LC_ALL, ""))
        {
            // Alert and abort...
            cerr << "error: failed to set user locale" << endl;
            return EXIT_FAILURE;
        }

    #if ENABLE_NLS

        // Set the current message domain and check for error...
        if(!::textdomain(PACKAGE))
        {
            // Alert and abort...
            cerr << "error: failed to set text domain ("
                 << ::strerror(errno) << ")" << endl;
            return EXIT_FAILURE;
        }

    #endif

    // Get global test factory registry...
    TestFactoryRegistry &Registry = TestFactoryRegistry::getRegistry();

    // Create test runner and add test suite created by the test factory
    //  registry to the list of tests to run...
    TextUi::TestRunner Runner;
    Runner.addTest(Registry.makeTest());
    
    // Change the default outputter to a compiler error format outputter...
    Runner.setOutputter(new CompilerOutputter(&Runner.result(), cerr));

    // Perform all unit tests in all suites...
    const bool Status = Runner.run();
    
    // Exit with appropriate status...
    if(Status == true)
        return EXIT_SUCCESS;
    else
        return EXIT_FAILURE;
}

