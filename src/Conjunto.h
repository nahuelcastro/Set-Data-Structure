#ifndef CONJUNTO_H_
#define CONJUNTO_H_

#include <assert.h>
#include <string>
#include <iostream>

using namespace std;

template <class T>
class Conjunto
{
    public:

        // Constructor. Genera un conjunto vacío.
        Conjunto();

        // Destructor. Debe dejar limpia la memoria.
        ~Conjunto();

        // Inserta un elemento en el conjunto. Si este ya existe,
        // el conjunto no se modifica.
        void insertar(const T&);

        // Decide si un elemento pertenece al conjunto o no.
        bool pertenece(const T&) const;

        // Borra un elemento del conjunto. Si este no existe,
        // el conjunto no se modifica.
        void remover(const T&);

        // Siguiente elemento al recibido por párametro, en orden.
        const T& siguiente(const T& elem);

        // Devuelve el mínimo elemento del conjunto según <.
        const T& minimo() const;

        // Devuelve el máximo elemento del conjunto según <.
        const T& maximo() const;

        // Devuelve la cantidad de elementos que tiene el conjunto.
        unsigned int cardinal() const;

        // Muestra el conjunto.
        void mostrar(std::ostream&) const;

    private:

        /**
         * Completar con lo que sea necesario...
         **/



         void reset_raiz_iteradora(); //

         void reset_raiz_iteradora_aux(); //

         //bool omitir_reinicio = false;

         //void actualizar_cantHijos_padres();

        int _cardinal;

        struct Nodo
        {
            // El constructor, toma el elemento al que representa el nodo.
            //Nodo(const T& v);
            //int cant;
            Nodo(const T& v) :
                valor(v), izq(NULL), der(NULL), padre(NULL){}

//            ~Nodo();

            // El elemento al que representa el nodo.
            T valor;
            // Puntero al padre
            Nodo* padre;
            // Puntero a la raíz del subárbol izquierdo.
            Nodo* izq;
            // Puntero a la raíz del subárbol derecho.
            Nodo* der;

        };

        // Puntero a la raíz de nuestro árbol.
        Nodo* _raiz;
        Nodo* _raiz_iteradora; // parte del invariante es que raiz iteradora apunte a la raiz, por ende me aseguro que
                                // simepre al salir de una funcion o entrar, que esto se cumpla

        Nodo* _raiz_iteradora_aux; // la voy a ir moviendo con la raiz iteradora, pero al finalizar cada funcion, la reseteo

        void destruir(Nodo * n);

        void eliminar (Nodo* padre, string dir, Nodo* nodo,const T& valor);

        bool esHoja(Nodo& nodo);

    //bool omitir_reinicio = false;

};

template<class T>
std::ostream& operator<<(std::ostream& os, const Conjunto<T>& c) {
	 c.mostrar(os);
	 return os;
}

#include "Conjunto.hpp"

#endif // CONJUNTO_H_
