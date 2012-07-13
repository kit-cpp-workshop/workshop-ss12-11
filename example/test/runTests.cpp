/*
 * runTests.cpp
 *
 *  Created on: 13.07.2012
 *      Author: markus
 */

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>

int main(int argc, char **argv) {
    // Verantwortlich dafür, die Tests auszuführen
    CppUnit::TextUi::TestRunner runner;

    // Sammelt alle (registrierten) Testsuites
    CppUnit::TestFactoryRegistry &registry =
            CppUnit::TestFactoryRegistry::getRegistry();

    // Führt die Testsuites aus
    runner.addTest(registry.makeTest());
    runner.run();

    return 0;
}

