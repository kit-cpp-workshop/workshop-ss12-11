/*
 * BasicTests.cpp
 *
 *  Created on: 13.07.2012
 *      Author: markus
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <stdexcept>
#include "../src/fifo.h"

using namespace task02;

// forward-declaration und Registration der Testsuite
class BasicTests;
CPPUNIT_TEST_SUITE_REGISTRATION(BasicTests);

// Die Testsuite, erbt von TestFixture wo setUp() und tearDown() deklariert werden
class BasicTests : public CppUnit::TestFixture {

        // Start der Initialisierung der Testsuite.
        // Im Rahmen dieser Initialisierung werden die einzelnen Testcases bei
        // der Testsuite registriert. Eigenlich möchte man ein Test-Framework,
        // bei dem das automatisch geschieht ... CppUnit kann das leider nicht
        CPPUNIT_TEST_SUITE(BasicTests);

        // Registration der Tests in die Testsuite
        CPPUNIT_TEST(testPush); // Normaler Test, soll nicht fehlschlagen
        CPPUNIT_TEST(testPushPop);
        CPPUNIT_TEST(testClear);
        // Zwei Tests die eine Exception auslösen sollen
        CPPUNIT_TEST_EXCEPTION(testPushExcept, std::logic_error);
        CPPUNIT_TEST_EXCEPTION(testPopExcept, std::logic_error);

        CPPUNIT_TEST(testGetDataCopy);

        CPPUNIT_TEST(testGetSize);
        CPPUNIT_TEST(testGetCount);
        CPPUNIT_TEST(testGetRemaining);

        // Ende der Initialisierung der Testsuite
        CPPUNIT_TEST_SUITE_END();

    public:
        // Dummy-Konstruktor um fifoSize zu initialisieren
        BasicTests() :
            fifoSize(5) {
        }

        // Wird vor jedem Test aufgerufen, dient der Vorbereitung der Tests
        void setUp() {
            fifo = new Fifo(fifoSize);
        }

        // Wird nach jedem Test zur Trümmerbeseitigung (Speicher!) aufgerufen
        void tearDown() {
            delete fifo;
        }

        /*
         * Ab hier beginnen die Testcases.
         *
         * Man könnte den Fifo auch noch deutlich gründlicher testen. Man kann
         * es aber auch lassen. Gerade bei so trivialen Klassen wie dem Fifo
         * fällt es oft schwer, sinnvolle Tests zu formulieren.
         * In solchen fällen bietet es sich manchmal an, einfach nur ein kleines
         * Testprogramm zu schreiben, dass den Prüfling auf verschiedene Arten
         * nutzt.
         * Was hier zum Beispiel fehlt: Tests mit größeren Datenmengen,
         *                              die speziell auf das Verhalten im
         *                              Grenzbereich bzw. beim Umlauf um die
         *                              Puffergrenze hin abzielen.
         */

        // Ein primitiver Test der einfach nur versucht, einige Elemente einzufügen
        void testPush() {
            fifo->push(-1.0);
            fifo->push(0.0);
            fifo->push(1.0);

            // Keine assertion, hier sollte einfach nur alles gut gehen
        }

        // Ein komplexerer Test der zuerst Elemente einfügt um sie dann wieder
        // zu entfernen.
        // Dabei werden Eingefügte und zurückgegebene Elemente verglichen.
        void testPushPop() {
            const double first = -1.0;
            const double second = 0.0;
            const double third = 1.0;

            fifo->push(first);
            fifo->push(second);
            fifo->push(third);

            CPPUNIT_ASSERT_EQUAL(first, fifo->pop());
            CPPUNIT_ASSERT_EQUAL(second, fifo->pop());
            CPPUNIT_ASSERT_EQUAL(third, fifo->pop());
        }

        // Provoziert eine Exception durch überfüllen des Fifos
        void testPushExcept() {
            for (int i = 0; i <= fifoSize; i++) {
                fifo->push(42.0);
            }
        }

        // Provoziert eine Exception indem auf ein nicht vorhandenes Element
        // zugegriffen wird.
        void testPopExcept() {
            fifo->pop();
        }

        // Fügt einige Elemente ein, leert dann den Fifo und prüft ob er danach
        // auch wirklich leer ist.
        void testClear() {
            testPush(); // Fügt einige Elemente ein

            fifo->clear();

            CPPUNIT_ASSERT_EQUAL((size_t) 0, fifo->getCount());

            bool gotException = false;

            try {
                fifo->pop();
            } catch (std::logic_error &e) {
                gotException = true;
            }

            CPPUNIT_ASSERT(gotException);
        }

        // Testet ob die Kopierfunktion alle enthaltenen Daten zurückgibt
        void testGetDataCopy() {
            const double input[] = { -23.0, 0, 42.0 };
            double output[3];

            for (int i = 0; i < 3; i++) {
                fifo->push(input[i]);
            }

            fifo->getDataCopy(output, 3);

            for (int i = 0; i < 3; i++) {
                CPPUNIT_ASSERT_EQUAL(input[i], output[i]);
            }
        }

        // Prüft ob die im Konstruktor angegebene Größe wirklich übernommen wurde
        void testGetSize() {
            CPPUNIT_ASSERT_EQUAL((size_t) fifoSize, fifo->getSize());
        }

        // Prüft ob die Anzahl enthaltener Elemente korrekt ermittelt wird
        void testGetCount() {
            CPPUNIT_ASSERT_EQUAL((size_t) 0, fifo->getCount());

            fifo->push(1.0);

            CPPUNIT_ASSERT_EQUAL((size_t) 1, fifo->getCount());

            fifo->pop();

            CPPUNIT_ASSERT_EQUAL((size_t) 0, fifo->getCount());
        }

        // Prüft ob der freie Speicherplatz korrekt ermittelt wird
        void testGetRemaining() {
            CPPUNIT_ASSERT_EQUAL((size_t) fifoSize, fifo->getRemaining());

            fifo->push(1.0);

            CPPUNIT_ASSERT_EQUAL((size_t) fifoSize - 1, fifo->getRemaining());

            fifo->pop();

            CPPUNIT_ASSERT_EQUAL((size_t) fifoSize, fifo->getRemaining());
        }

    private:
        int fifoSize;
        Fifo *fifo;
};
