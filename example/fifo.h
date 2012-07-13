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
     * Implementiert einen Ringpuffer (FiFo) konstanter Größe für double-Zahlen.
     *
     * Laufzeitgarantien: Alle Methoden werden in O(1) (konstanter Zeit)
     *                    ausgeführt. Ausgenommen davon ist getDataCopy()
     *                    mit einer Laufzeit die in O(n) liegt.
     *
     * Exceptions: Wenn eine Methode dieser Klasse eine Exception wirft,
     *             verbleibt die Fifo-Instanz in einem unveränderten Zustand
     *             und kann normal weiter verwendet werden.
     *
     * @author Markus Jung
     */
    class Fifo {
    
		public:
            /**
             * Erzeugt eine neue Fifo-Instanz mit der gegebenen Kapazität.
             *
             * @param size die Größe des Fifos
             * @throw std::bad_alloc wenn die (interne) Speicherallokation
			 *                       fehlschlägt
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
		     * Kopiert die im Fifo gespeicherten Daten in das übergebene Array.
		     * Es werden so viele Elemente kopiert, bis entweder alle momentan
			 * im Fifo vorhandenen kopiert wurden oder das Array voll ist.
		     *
		     * @param buffer die Adresse des Arrays, in das der Inhalt des Fifos
		     *               kopiert werden soll
		     * @param count die Speicherkapazität des buffer-Arrays, angegeben
		     *              in double-Elementen
		     * @return die Anzahl der in das übergebene Array geschriebenen
		     *         Elemente, die std::min(count, getCount()) entspricht
		     */
		    size_t getDataCopy(double *buffer, const size_t count);

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
		    class Impl; // forward-declaration of nested implementation class
		    Impl *impl; // pointer-to-implementation
    };

}

#endif /* FIFO_H_ */
