template <class T>
Conjunto<T>::Nodo::Nodo(const T& v): valor(v), izq(nullptr), der(nullptr)  {
}

template <class T>
Conjunto<T>::Conjunto(): _raiz(nullptr), valor_de_nodos() {
}

template <class T>
Conjunto<T>::~Conjunto() {
    delete _raiz;
}

template <class T>
bool Conjunto<T>::pertenece(const T& clave) const {
    for (int i = 0; i < valor_de_nodos.size(); i++) {
        if (valor_de_nodos[i] == clave)
        {
            return true;
        }
    }
    return false;
}

template <class T>
void Conjunto<T>::insertar(const T& clave) {
    if (not this->pertenece(clave))
    {
        Nodo *nodo_i = _raiz;
        Nodo *nodoNuevo = new Nodo(clave);
        if (nodo_i == nullptr)
        {
            _raiz = nodoNuevo;
            valor_de_nodos.push_back(clave);
        }
        else
        {
            while(not this->pertenece(clave))
            {
                if (nodo_i->der == nullptr && nodo_i->izq == nullptr )
                {
                    if (clave > nodo_i->valor)
                    {
                        nodo_i->der = nodoNuevo;
                    }
                    else
                    {
                        nodo_i->izq = nodoNuevo;
                    }
                    valor_de_nodos.push_back(clave);
                }
                else
                {
                    if (nodo_i->der == nullptr)
                    {
                        if (clave > nodo_i->valor)
                        {
                            nodo_i->der = nodoNuevo;
                            valor_de_nodos.push_back(clave);
                        }
                        else
                        {
                            nodo_i = nodo_i->izq;
                        }
                    }
                    else
                    {
                        if (nodo_i->izq == nullptr)
                        {
                            if (clave < nodo_i->valor)
                            {
                                nodo_i->izq = nodoNuevo;
                                valor_de_nodos.push_back(clave);
                            }
                            else
                            {
                                nodo_i = nodo_i->der;
                            }
                        }
                        else
                        {
                            if (clave > nodo_i->valor)
                            {
                                nodo_i = nodo_i->der;
                            }
                            else
                            {
                                nodo_i = nodo_i->izq;
                            }
                        }
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
            if (clave > nodo_i->valor)
            {
                nodo_i = nodo_i->der;
            }
            else
            {
                nodo_i = nodo_i->izq;
            }
        }

        if (nodo_i->izq == nullptr && nodo_i->der == nullptr) //Sin hijos
        {
            delete nodo_i;
//            remover(nodo_i->valor);
        }
        else
        {
            if (nodo_i->izq == nullptr) //Con 1 hijos
            {
                Nodo *nodoAnterior = nodo_i;
                nodo_i = nodo_i->der;
                delete nodoAnterior;
//                remover(nodoAnterior->valor);
            }
            else
            {
                if (nodo_i->der == nullptr)
                {
                    Nodo *nodoAnterior = nodo_i;
                    nodo_i = nodo_i->izq;
                    delete nodoAnterior;
//                    remover(nodoAnterior->valor);
                }
                else //Con 2 hijos
                {
                    Nodo *nodoMinimo = new Nodo(buscarMinimo(nodo_i->valor)); //falta buscar
                    nodo_i = nodoMinimo;
                    delete nodo_i->der;
//                    remover(nodo_i->der->valor);
                }
            }
        }

        for (int i = 0; i < valor_de_nodos.size(); ++i)
        {
            if (clave == valor_de_nodos[i])
            {
                valor_de_nodos[i] = valor_de_nodos[valor_de_nodos.size()-1];
                valor_de_nodos.pop_back();
            }
        }

    }
}

template <class T>
const T& Conjunto<T>::siguiente(const T& clave) {
    T diff = this->maximo(); T candidato;
    for (int i = 0; i < valor_de_nodos.size(); ++i) {
        if (valor_de_nodos[i] != clave && abs(valor_de_nodos[i]-clave) < diff)
        {
            diff = abs(valor_de_nodos[i]-clave);
            candidato = valor_de_nodos[i];
        }
    }
    Nodo *res = new Nodo(candidato);
    return res->valor;
}

template <class T>
const T& Conjunto<T>::minimo() const {
    Nodo *min = _raiz;
    while (min->der != nullptr && min->izq != nullptr)
    {
        if (min->izq != nullptr)
        {
            min = min->izq;
        }
        else
        {
            min = min->der;
        }
    }
    return min->valor;
}

template <class T>
const T& Conjunto<T>::maximo() const {
    Nodo *max = _raiz;
    while (max->der != nullptr && max->izq != nullptr)
    {
        if (max->der != nullptr)
        {
            max = max->der;
        }
        else
        {
            max = max->izq;
        }
    }
    return max->valor;
}

template <class T>
unsigned int Conjunto<T>::cardinal() const {
    return valor_de_nodos.size();
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

