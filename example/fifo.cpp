/*
 * fifo.c
 *
 *  Created on: 03.04.2012
 *      Author: markus
 */

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include "fifo.h"

namespace task02 {

    /*
     * Die verborgene Implementierung von Fifo, realisiert als "nested class".
     * Außerhalb von Fifo ist diese Klasse nie sichtbar.
     */
    class Fifo::Impl {
        public:
            Impl(const size_t size) :
                size(size),
                count(0),
                readPos(0),
                data(new double[size]) {  // Kann std::bad_alloc werfen -> Doku!
            }

            ~Impl() {
                delete[] data;
            }

            size_t getSize() {
                return size;
            }

            size_t getCount() {
                return count;
            }

            size_t getRemaining() {
                return size - count;
            }

            void push(const double &d) {
                /*
                 * Fifo::Impl gehört zu Fifo. Damit haben die Methoden von
                 * Fifo::Impl logisch den Rang einer privaten Methode und werden
                 * entsprechend behandelt.
                 * Sprich: Invarianten und Vorbedingungen werden nur über
                 *         Assertions geprüft, da bei korrekter Implementierung
                 *         nur "vertrauenswürdige" Daten innerhalb der Komponente
                 *         verwendet werden.
                 */
                assert(count < size); // Freier Speicherplatz vorhanden

                data[(readPos + count++) % size] = d;

                assert(count <= size); // Maximal size Elemente gespeichert
            }

            double pop() {
                assert(count > 0); // Fifo ist nicht leer

                double result = data[readPos++];

                readPos %= size;
                count--;

                // assert(readPos < size) // Nicht wirklich erforderlich, da modulo ...

                return result;
            }

            void clear() {
                readPos = 0;
                count = 0;
            }

            size_t getDataCopy(double *buffer, const size_t count) {
                // Hier sind mir keine sinnvollen/nichttrivialen Invarianten eingefallen ...

                size_t read = readPos;

                for (size_t i = 0; i < std::min(count, this->count); i++) {
                    buffer[i] = data[read++];
                    read %= size;
                }

                return std::min(count, this->count);
            }

        protected:
            const size_t size;
            size_t count; // Invariante: count <= size
            size_t readPos; // Invariante: readPos <= size

            double * const data; // Invariante: Zeigt auf double[size]
    };

    Fifo::Fifo(const size_t size) :
        impl(new Impl(size)) {
    }

    Fifo::~Fifo() {
        delete impl;
    }

    void Fifo::push(const double &d) {
        /*
         * Dieser Teil der Klasse gehört zur öffentlichen Schnittstelle. Alle
         * übergebenen Daten müssen auf ihre Korrektheit geprüft werden.
         * Verletzungen der Schnittstellenspezifikation werden entsprechend
         * dieser behandelt, hier über eine Exception.
         * Bei komplexeren Klassen kann außerdem der Aufruf von Methoden an
         * innere Zustande gekoppelt sein, auch diese Vorbedingungen sollten
         * dann entsprechend überprüft werden. Grundsätzlich sollten an der
         * "Grenze" zwischen Innen und Außen alle versehentlich oder absichtlich
         * von außen verletzbaren Vorbedingungen überprüft werden, sofern dieser
         * Aufwand vertretbar ist.
         */
        if (impl->getRemaining() == 0) { // Fifo voll
            throw std::logic_error("Fifo is already full");
        }

        impl->push(d);
    }

    double Fifo::pop() {
        if (impl->getCount() == 0) { // Fifo leer
            throw std::logic_error("Fifo is already empty");
        }

        return impl->pop();
    }

    void Fifo::clear() {
        impl->clear();
    }

    size_t Fifo::getDataCopy(double *buffer, const size_t count) {
        return impl->getDataCopy(buffer, count);
    }

    size_t Fifo::getSize() {
        return impl->getSize();
    }

    size_t Fifo::getCount() {
        return impl->getCount();
    }

    size_t Fifo::getRemaining() {
        return impl->getRemaining();
    }

}
