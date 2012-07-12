/*
 * fifo.h
 *
 *  Created on: 03.04.2012
 *      Author: markus
 */

#ifndef FIFO_H_
#define FIFO_H_

#include <cstddef>

namespace task02 {

    /**
     * Implementiert einen Ringpuffer (FiFo) für double-Zahlen.
     *
     * @author Markus Jung
     */
    class Fifo {
    
		public:
            /**
             * Erzeugt eine neue Fifo-Instanz mit der gegebenen Kapazität.
             *
             * @param size die Größe des Fifos
             * @throw std::bad_alloc wenn bei der (internen) Speicherallokation
			 *        etwas schiefgeht
             */
		    Fifo(const size_t size);
		    /**
		     * Zerstört die Fifo-Instanz und gibt den zusätzlich alloziierten
		     * Speicher frei.
		     */
		    virtual ~Fifo();

		    /**
		     * Fügt ein neues Element am Ende des Fifos ein, sofern der Fifo
		     * noch über freien Speicherplatz verfügt.
		     *
		     * Laufzeit: O(1)
		     *
		     * @param d das am Ende einzufügende Element
		     * @throw std::logic_error wenn (getRemaining == 0)
		     */
		    void push(const double &d);
		    /**
		     * Entfernt das erste Element aus dem Fifo und gibt es zurück.
		     *
		     * @return das (ehemalige) erste Element des Fifos
		     * @throw std::logic_error wenn (getCount == 0)
		     */
		    double pop();
		    /**
		     * Leert den Fifo, nach einem Aufruf dieser Methode gilt:
		     * (getCount() == 0).
		     */
		    void clear();

		    /**
		     * Kopiert alle im Fifo gespeicherten Daten in das übergebene Array,
		     * sofern dessen Kapazität dafür ausreichend ist.
		     *
		     * @param buffer die Adresse des Arrays, in das der Inhalt des Fifos
		     *               kopiert werden soll
		     * @param count die Speicherkapazität des buffer-Arrays, angegeben
		     *              in double-Elementen
		     * @return die Anzahl der in das übergebene Array geschriebenen
		     *         Elemente, die std::min(count, getCount()) entspricht
		     */
		    size_t getDataCopy(double *(&buffer), const size_t count);

		    /**
		     * Gibt die Speicherkapazität des Fifo in double-Elementen zurück.
		     *
		     * @return die maximal speicherbare Elementanzahl
		     */
		    size_t getSize();
		    /**
		     * Gibt die Anzahl der momentan gespeicherten Elemente zurück.
		     *
		     * @return die Anzahl der gespeicherten Elemente
		     */
		    size_t getCount();
		    /**
		     * Gibt die verbleibende freien Speicherkapazität in
		     * double-Elementen zurück.
		     *
		     * Ist der Fifo voll, ist das Ergebnis 0, ist er leer entspricht das
		     * Ergebnis dem Rückgabewert von getSize().
		     *
		     * @return die Anzahl der noch nicht belegten Plätze im Fifo
		     */
		    size_t getRemaining();
		    
		private:
		    class Impl;
		    Impl *impl;
    };

}

#endif /* FIFO_H_ */
