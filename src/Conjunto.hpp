template <class T>
Conjunto<T>::Nodo::Nodo(const T& v): valor(v), izq(nullptr), der(nullptr), anterior(nullptr)  {
}

template <class T>
Conjunto<T>::Conjunto(): _raiz(nullptr), cardinal_(0) {
}


template <class T>
Conjunto<T>::~Conjunto() {
    while (cardinal() > 0){
        remover(minimo());
    }
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    Nodo* nodo_i = _raiz;
    bool res = false;
    while (nodo_i != nullptr && not res){
        if (nodo_i->valor > clave){
            nodo_i = nodo_i->izq;
        }
        else{
            if (nodo_i->valor < clave){
                nodo_i = nodo_i->der;
            }
            else{
                res = true;
            }
        }
    }
    return res;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if (not this->pertenece(clave)){
        Nodo *nodo_iesimo = _raiz;
        Nodo *nodoNuevo = new Nodo(clave);
        if (_raiz == nullptr)
        {
            _raiz = nodoNuevo;
            cardinal_++;
        }
        else
        {
            while(not pertenece(clave))
            {
                if (clave > nodo_iesimo->valor){
                    if (nodo_iesimo->der != nullptr){
                        nodo_iesimo = nodo_iesimo->der;
                    }
                    else{
                        nodo_iesimo->der = nodoNuevo;
                        nodo_iesimo->der->anterior = nodo_iesimo;
                        cardinal_++;
                    }
                }
                else{
                    if (nodo_iesimo->izq != nullptr){
                        nodo_iesimo = nodo_iesimo-> izq;
                    }
                    else{
                        nodo_iesimo->izq = nodoNuevo;
                        nodo_iesimo->izq->anterior = nodo_iesimo;
                        cardinal_++;
                    }
                }
            }
        }
    }
}

template <class T>
void Conjunto<T>::remover(const T& clave) {
    if (this->pertenece(clave))
    {
        Nodo *nodo_i = _raiz;
        while (nodo_i->valor != clave)
        {
            if (clave > nodo_i->valor){
                nodo_i = nodo_i->der;
            }
            else{
                nodo_i = nodo_i->izq;
            }
        }

        if (nodo_i->izq == nullptr && nodo_i->der == nullptr) //Sin hijos
        {
            if (nodo_i->anterior != nullptr){
                if (nodo_i->anterior->der == nodo_i){
                    nodo_i->anterior->der = nullptr;
                }
                else{
                    nodo_i->anterior->izq = nullptr;
                }
            }
            else{
                _raiz = nullptr;
            }
        }
        else{
            if (nodo_i->der != nullptr && nodo_i->izq != nullptr){
                Nodo* minimoDerecha = nodo_i->der;
                while (minimoDerecha->izq != nullptr){
                    minimoDerecha = minimoDerecha->izq;
                }
                nodo_i->valor = minimoDerecha->valor;
                if (minimoDerecha->der != nullptr){
                    minimoDerecha->der->anterior = minimoDerecha->anterior;
                    if (minimoDerecha->anterior == nodo_i){
                        minimoDerecha->anterior->der = minimoDerecha->der;
                    }
                    else{
                        minimoDerecha->anterior->izq = minimoDerecha->der;
                    }
                }
                else{
                    if (minimoDerecha->anterior == nodo_i){
                        minimoDerecha->anterior->der = nullptr;
                    }
                    else{
                        minimoDerecha->anterior->izq = nullptr;
                    }
                }
                nodo_i = minimoDerecha;
            }
            else{
                if (nodo_i->anterior != nullptr){
                    if (nodo_i->der != nullptr){
                        if (nodo_i->valor < nodo_i->anterior->valor){
                            nodo_i->anterior->izq = nodo_i->der;
                        }
                        else{
                            nodo_i->anterior->der = nodo_i->der;
                        }
                        nodo_i->der->anterior = nodo_i->anterior;
                    }
                    else{
                        if(nodo_i->valor < nodo_i->anterior->valor){
                            nodo_i->anterior->izq = nodo_i->izq;
                        }
                        else{
                            nodo_i->anterior->der = nodo_i->izq;
                        }
                        nodo_i->izq->anterior = nodo_i->anterior;
                    }
                }
                else{
                    if (nodo_i->der != nullptr){
                        nodo_i->der->anterior = nullptr;
                        _raiz = nodo_i->der;
                    }
                    else{
                        nodo_i->izq->anterior = nullptr;
                        _raiz = nodo_i->izq;
                    }
                }
            }
        }
        delete nodo_i;
        cardinal_--;
    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    Nodo* nodo_iesimo = _raiz;
    while (nodo_iesimo->valor != clave){
        if (clave > nodo_iesimo->valor){
            nodo_iesimo = nodo_iesimo->der;
        }
        else{
            nodo_iesimo = nodo_iesimo->izq;
        }
    }
    if (nodo_iesimo->der != nullptr){
        nodo_iesimo = nodo_iesimo->der;
        while (nodo_iesimo->izq != nullptr){
            nodo_iesimo = nodo_iesimo->izq;
        }
    }
    else{
        nodo_iesimo = nodo_iesimo->anterior;
    }
    return nodo_iesimo->valor;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo *min = _raiz;
    while (min->izq != nullptr){
        min = min->izq;
    }
    return min->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo *max = _raiz;
    while (max->der != nullptr){
        max = max->der;
    }
    return max->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return cardinal_;
}


template <class T>
const T& Conjunto<T>::buscarMinimo(const T& nodo) {
    if (pertenece(nodo))
    {
        Nodo *nodoi = _raiz;
        while(nodoi->valor == nodo)
        {
            if (nodo > nodoi->valor)
            {
                nodoi = nodoi->der;
            }
            else
            {
                nodoi = nodoi->izq;
            }
        }

        while(nodoi->der != nullptr && nodoi->izq != nullptr)
        {
            if (nodoi->izq != nullptr)
            {
                nodoi = nodoi->izq;
            }
            else
            {
                nodoi = nodoi->der;
            }
        }
        return nodoi->valor;
    }
    return 0;
}

template <class T>
void Conjunto<T>::mostrar(std::ostream&) const {
    assert(false);
}
