
template<class T>
Conjunto<T>::Conjunto() {
    T t;
    _raiz = new Nodo(t);
    _raiz_iteradora = new Nodo(t);
    _raiz_iteradora_aux = new Nodo(t);
    _cardinal = 0;

}

template<class T>
Conjunto<T>::~Conjunto() {

    destruir(_raiz->izq);
    delete _raiz;
    delete _raiz_iteradora_aux;
    delete _raiz_iteradora;

}

template<class T>
void Conjunto<T>::destruir(Nodo *n) {
    if (n != NULL) {
        destruir(n->izq);
        destruir(n->der);
        delete n; // 68 i
    }
}


template<class T>
bool Conjunto<T>::pertenece(const T &clave) const {
    if (_raiz_iteradora->der ==
        _raiz->der) { // quiere decir que es la primera vez que entro a la funcion, reseteo todas las raices
        _raiz_iteradora_aux->izq = _raiz->izq;
        _raiz_iteradora_aux->der = _raiz->der; // no me reseteo
        _raiz_iteradora_aux->valor = _raiz->valor;
    }

    if (_cardinal == 0) {

        //reset_raiz_iteradora();
        _raiz_iteradora_aux->izq = _raiz->izq; // esta de mas resetear esta ahora, pero bueno
        _raiz_iteradora_aux->der = _raiz->der; // esta de mas resetear esta ahora, pero bueno
        _raiz_iteradora_aux->valor = _raiz->valor; // esta de mas resetear esta ahora, pero bueno

        _raiz_iteradora->izq = _raiz->izq;
        _raiz_iteradora->der = _raiz->der;
        _raiz_iteradora->valor = _raiz->valor;


        return false;
    }
    if (_raiz_iteradora_aux->der->valor == clave) {

        //reset_raiz_iteradora();   // no se porque me tira error al compilar

        _raiz_iteradora_aux->izq = _raiz->izq; // esta de mas resetear esta ahora, pero bueno
        _raiz_iteradora_aux->der = _raiz->der; // esta de mas resetear esta ahora, pero bueno
        _raiz_iteradora_aux->valor = _raiz->valor; // esta de mas resetear esta ahora, pero bueno

        _raiz_iteradora->izq = _raiz->izq;
        _raiz_iteradora->der = _raiz->der;
        _raiz_iteradora->valor = _raiz->valor;
        return true;
    } else if (clave > _raiz_iteradora_aux->der->valor &&
               _raiz_iteradora_aux->der->der != NULL) { //clave es mayor y NO estoy en hoja
        // ver si pertenece a la derecha
        //_raiz_iteradora = _raiz_iteradora->der;

        _raiz_iteradora_aux->der = _raiz_iteradora_aux->der->der;
        _raiz_iteradora->der = _raiz_iteradora->der->der;

        pertenece(clave);

    } else if (clave < _raiz_iteradora_aux->der->valor &&
               _raiz_iteradora_aux->der->izq != NULL) { //clave es menor y NO estoy en hoja
        //ver si pertenece a la izq
        //_raiz_iteradora = _raiz_iteradora->izq;

        _raiz_iteradora_aux->der = _raiz_iteradora_aux->der->izq;
        _raiz_iteradora->der = _raiz_iteradora->der->izq;
        pertenece(clave);
    } else {
        _raiz_iteradora->izq = _raiz->izq;
        _raiz_iteradora->der = _raiz->der;
        _raiz_iteradora->valor = _raiz->valor;

        return false;

    }
}

template<class T>
void Conjunto<T>::insertar(const T &clave) {
    //assert(false);

    if (_raiz_iteradora->der ==
        _raiz->der) { // quiere decir que es la primera vez que entro a la funcion, reseteo todas las raices
        reset_raiz_iteradora_aux();
    }


    // antes tengo que chequear que no aparece
    if (not(pertenece(clave))) {
        Nodo *nodo = new Nodo(clave); // defino el nodo a agregar

        if (_cardinal == 0) { //agrego el primer elemento al conj
            _raiz->der = nodo;
            _raiz->izq = nodo;
            _raiz->valor = nodo->valor;
            nodo->padre = NULL;

            reset_raiz_iteradora();
            _cardinal++;

        } else { // lo coloco donde corresponda
            if (clave < _raiz_iteradora_aux->der->valor &&
                _raiz_iteradora_aux->der->izq == NULL) { // clave es menor y estoy en hoja

                _raiz_iteradora_aux->der->izq = nodo;
                nodo->padre = _raiz_iteradora_aux->der;
                reset_raiz_iteradora();

                _cardinal++;
            } else if (clave > _raiz_iteradora_aux->der->valor &&
                       _raiz_iteradora_aux->der->der == NULL) { // clave es mayor y estoy en hoja

                _raiz_iteradora_aux->der->der = nodo;
                nodo->padre = _raiz_iteradora_aux->der;
                reset_raiz_iteradora();

                _cardinal++;
            } else if (clave < _raiz_iteradora_aux->der->valor &&
                       _raiz_iteradora_aux->der->izq != NULL) { //clave es menor y NO estoy en hoja
                _raiz_iteradora_aux->der = _raiz_iteradora_aux->der->izq;
                _raiz_iteradora->der = _raiz_iteradora->der->izq;
                insertar(clave);
                delete nodo;
            } else if (clave > _raiz_iteradora_aux->der->valor &&
                       _raiz_iteradora_aux->der->der != NULL) { // clave es mayor y NO estoy en hoja
                _raiz_iteradora_aux->der = _raiz_iteradora_aux->der->der;
                _raiz_iteradora->der = _raiz_iteradora->der->der;
                insertar(clave);
                delete nodo;
            }
        }
    }

}


template<class T>
void Conjunto<T>::remover(const T &clave) {

    if (_raiz_iteradora->der ==
        _raiz->der) { // quiere decir que es la primera vez que entro a la funcion, reseteo todas las raices
        _raiz_iteradora_aux->izq = _raiz->izq;
        _raiz_iteradora_aux->der = _raiz->der;
        _raiz_iteradora_aux->valor = _raiz->valor;
    }

    if (pertenece(clave)) {

        if (_cardinal == 1) {
            delete _raiz->der;
            _raiz->der = NULL;
            _raiz->izq = NULL;
            _cardinal--;
        } else {
            eliminar(NULL, "", _raiz->der, clave);
        }

    }

}



template<class T>
void Conjunto<T>::eliminar(Nodo *padre, string dir, Nodo *nodo, const T &valor) {
    if (nodo->valor == valor) {

        if (nodo->der == NULL && nodo->izq == NULL) { // es hoja
            delete nodo;
            if (dir == "IZQ") {
                padre->izq = NULL;
            } else {
                padre->der = NULL;
            }
            _cardinal--;
        } else {
            if (nodo->der != NULL) {

                _raiz_iteradora_aux->der = nodo->der;   // nodo.der
                _raiz->padre = _raiz->der;              //
                nodo->valor = minimo(); //nodo->der
                _raiz_iteradora_aux->der = _raiz->der;  //
                _raiz->padre = NULL;                    //

                eliminar(nodo, "DER", nodo->der, nodo->valor);
            } else {
                _raiz_iteradora_aux->der = nodo->izq;
                _raiz->padre = _raiz->der;
                nodo->valor = maximo(); //nodo->izq
                _raiz_iteradora_aux->der = _raiz->der;
                _raiz->padre = NULL;
                eliminar(nodo, "IZQ", nodo->izq, nodo->valor);
            }
        }


    } else {
        if (nodo->valor > valor) {
            eliminar(nodo, "IZQ", nodo->izq, valor);
        } else {
            eliminar(nodo, "DER", nodo->der, valor);
        }
    }
}












//
//template<class T>
//bool Conjunto<T>::esHoja (Nodo& nodo){
//    return (nodo->der == NULL && nodo->izq == NULL);
//}





template<class T>
const T &Conjunto<T>::siguiente(const T &clave) {
    //assert(false);
    if (_raiz_iteradora->der == _raiz->der && not(_raiz->padre ==
                                                  _raiz_iteradora_aux->der)) { // quiere decir que es la primera vez que entro a la funcion, reseteo todas las raices
        _raiz_iteradora_aux->izq = _raiz->izq;
        _raiz_iteradora_aux->der = _raiz->der;
        _raiz_iteradora_aux->valor = _raiz->valor;
    }

    while (_raiz_iteradora_aux->der->valor != clave) { // me posiciono en la clave
        if (clave > _raiz_iteradora_aux->der->valor) {
            _raiz_iteradora_aux->der = _raiz_iteradora_aux->der->der;
            _raiz_iteradora->der = _raiz_iteradora->der->der; // no se si tal vez la cago
        } else if (clave < _raiz_iteradora_aux->der->valor) {
            _raiz_iteradora_aux->der = _raiz_iteradora_aux->der->izq;
            _raiz_iteradora->der = _raiz_iteradora->der->izq; // no se si tal vez la cago
        }
    }

    if (_raiz_iteradora_aux->der->der == NULL) { // no tiene hijo mayor, → itero hasta encontrar al primer padre mayor
        while (not(_raiz_iteradora_aux->der->valor > clave)) {
            _raiz_iteradora_aux->der = _raiz_iteradora_aux->der->padre;
            _raiz_iteradora->der = _raiz_iteradora->der->padre;
        }

        _raiz_iteradora->izq = _raiz->izq; // reset raiz iteradora
        _raiz_iteradora->der = _raiz->der; //
        _raiz_iteradora->valor = _raiz->valor; //

        return _raiz_iteradora_aux->der->valor;

    } else if (_raiz_iteradora_aux->der->der != NULL) { //tiene hijo a la derehca, busco el min del der
        _raiz_iteradora_aux->der = _raiz_iteradora_aux->der->der;

        _raiz->padre = _raiz->der;

        return minimo(); // al finalizar me resetea _raiz_iteradora
    }

}

template<class T>
const T &Conjunto<T>::minimo() const {

    if (_raiz_iteradora->der == _raiz->der &&
        not(_raiz->padre == _raiz->der)) { // es la primera vez que entro a la funcion, reseteo todas las raices
        // el raiz padre siempre es null, excepto cuando llamo a minimo desde siguiente(t),
        // y lo utilizo solo para saltear este if, y al terminar lo vuelvo a la normalidad (a null)
        _raiz_iteradora_aux->izq = _raiz->izq;
        _raiz_iteradora_aux->der = _raiz->der;
        _raiz_iteradora_aux->valor = _raiz->valor;
    }

    if (_raiz_iteradora_aux->der->izq == NULL) {
        _raiz_iteradora->izq = _raiz->izq;
        _raiz_iteradora->der = _raiz->der;
        _raiz_iteradora->valor = _raiz->valor;

        _raiz->padre = NULL;

        return _raiz_iteradora_aux->der->valor;

    } else {

        if (not(_raiz->padre ==
                _raiz->der)) { // quiere decir que es la primera vez que entro a la funcion, reseteo todas las raices
            _raiz_iteradora->der = _raiz_iteradora->der->izq;
        }

        _raiz_iteradora_aux->der = _raiz_iteradora_aux->der->izq;
        minimo();
    }

}


template<class T>
const T &Conjunto<T>::maximo() const {
    //assert(false);

    if (_raiz_iteradora->der == _raiz->der && not(_raiz->padre ==
                                                  _raiz->der)) { // quiere decir que es la primera vez que entro a la funcion, reseteo todas las raices
        _raiz_iteradora_aux->izq = _raiz->izq;
        _raiz_iteradora_aux->der = _raiz->der;
        _raiz_iteradora_aux->valor = _raiz->valor;
    }

    if (_raiz_iteradora_aux->der->der == NULL) {

        _raiz_iteradora->izq = _raiz->izq;
        _raiz_iteradora->der = _raiz->der;
        _raiz_iteradora->valor = _raiz->valor;

        return _raiz_iteradora_aux->der->valor;

    } else {

        if (not(_raiz->padre ==
                _raiz->der)) { // quiere decir que es la primera vez que entro a la funcion, reseteo todas las raices
            _raiz_iteradora->der = _raiz_iteradora->der->der;
        }
        _raiz_iteradora_aux->der = _raiz_iteradora_aux->der->der;
        maximo();
    }

}

template<class T>
unsigned int Conjunto<T>::cardinal() const {
    //assert(false);
    //return 0;
    return _cardinal;
}

template<class T>
void Conjunto<T>::mostrar(std::ostream &) const {
    assert(false);
}


// funciones auxiliares

template<class T>
void Conjunto<T>::reset_raiz_iteradora() {
    _raiz_iteradora->izq = _raiz->izq;
    _raiz_iteradora->der = _raiz->der;
    _raiz_iteradora->valor = _raiz->valor;
}

template<class T>
void Conjunto<T>::reset_raiz_iteradora_aux() {
    _raiz_iteradora_aux->izq = _raiz->izq;
    _raiz_iteradora_aux->der = _raiz->der;
    _raiz_iteradora_aux->valor = _raiz->valor;
}
