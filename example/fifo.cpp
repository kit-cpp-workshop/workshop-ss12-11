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

    class Fifo::Impl {
        public:
            Impl(const size_t size) :
                size(size),
                count(0),
                readPos(0),
                data(new double[size]) {
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
                assert(getRemaining() > 0);
                assert(count < size);

                data[(readPos + count++) % size] = d;

                assert(count <= size);
            }

            double pop() {
                assert(count <= size);
                assert(count > 0);

                double result = data[readPos++];

                readPos %= size;
                count--;

                return result;
            }

            void clear() {
                readPos = 0;
                count = 0;
            }

            size_t getDataCopy(double *(&buffer), const size_t count) {
                size_t read = readPos;

                for (size_t i = 0; i < std::min(count, this->count); i++) {
                    buffer[i] = data[read++];
                    read %= size;
                }

                return std::min(count, this->count);
            }

        protected:
            const size_t size;
            size_t count;
            size_t readPos;

            double * const data;
    };

    Fifo::Fifo(const size_t size) :
        impl(new Impl(size)) {
    }

    Fifo::~Fifo() {
        delete impl;
    }

    void Fifo::push(const double &d) {
        if (impl->getRemaining() == 0) {
            throw std::logic_error("Fifo is already full");
        }

        impl->push(d);
    }

    double Fifo::pop() {
        if (impl->getCount() == 0) {
            throw std::logic_error("Fifo is already empty");
        }

        return impl->pop();
    }

    void Fifo::clear() {
        impl->clear();
    }

    size_t Fifo::getDataCopy(double *(&buffer), const size_t count) {
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
