#include <iostream>
#include <time.h>

template<class T>
struct Nodo {
    T value;
    Nodo* next;
    Nodo* prev;
    Nodo(T x) {
        value = x;
        next = prev = 0;
    }
};

template<class T>
class List {
private:
    Nodo<T>* head;
    Nodo<T>* tail;
    int nelem;
public:
    List() {
        head = tail = 0;
        nelem = 0;
    }

    void push_back(T x) {
        Nodo<T>* nuevo = new Nodo<T>(x);
        if (!nelem)
            head = tail = nuevo;
        else
        {
            nuevo->prev = tail;
            tail->next = nuevo;
            tail = nuevo;
        }
        nelem++;
    }
    void push_front(T x) {
        Nodo<T>* nuevo = new Nodo<T>(x);
        if (!nelem)
            head = tail = nuevo;
        else
        {
            nuevo->next = head;
            head->prev = nuevo;
            head = nuevo;
        }
        nelem++;
    }
    T pop_back()
    {
        T valor;
        Nodo<T>* nuevo = new Nodo<T>('a');
        if (nelem == 1)
        {
            valor = tail->value;
            delete tail;
        }
        else
        {
            valor = tail->value;
            nuevo = tail->prev;
            delete tail;
            tail = nuevo;
        }
        nelem--;
        return valor;
    }
    T pop_front()
    {
        Nodo<T>* nuevo = new Nodo<T>('a');
        T valor = head->value;
        nuevo = head->next;
        delete head;
        head = nuevo;
        nelem--;
        return valor;
    }

    T& operator[](int i)
    {
        Nodo<T>* nuevo = head;
        for (int i = 0; i != 1; i++)
            nuevo = nuevo->next;
        return nuevo->value;
    }
    void print()
    {
        std::cout << "\n";
        for (Nodo<T>* nuevo = head; nuevo != 0; nuevo = nuevo->next)
        {
            std::cout << nuevo->value << " -> ";
        }
    }
};

//-----------------------------------------------------//

template<class T, class S>
class Cola
{
private:
    S seq;
public:
    void print()
    {
        seq.print();
    }
    void push(T x)
    {
        seq.push_back(x);
    }
    T pop()
    {
        return seq.pop_front();
    }
};

//----------------------------------------------------------//

class Juego_bomba
{
private:
    int N_elementos = 10, turnos = 20,turno=0;
    int turno_bomba[20]; //array donde voy a almacenar numeros pseudoaleatorios
    char perdedor;
    std::string jugadores_nombres = "abcdefghijklmnopqrstuvwxyz0123456789";
    Cola<char, List<char>> jugadores;

public:
    Juego_bomba() {
        /*std::cout << "INGRESAR NUMERO DE JUGADORES\n";
        std::cin >> N_elementos;*/
        for (int i = 0; i < N_elementos; i++)
        {
            jugadores.push(jugadores_nombres[i]);
        }
        std::cout << "Lista de jugadores iniciales\n";
        jugadores.print();
        std::cout << "\n";
        pseudoaleatorio_basico(); //creando un array de numeros aleatorios
        while (N_elementos != 1)
        {
            for (int i = 0; i < turno_bomba[turno]; i++) //recorriendo el array de numeros aleatorios, uno por uno
            {
                jugadores.push(jugadores.pop());
            }
            perdedor = jugadores.pop(); //eliminando al jugador con la bomba
            std::cout << "\n";
            jugadores.print();
            std::cout << "\n Musica turno: " << turno_bomba[turno] << "\n Jugador perdido: " << perdedor << "\n";
            turno++, N_elementos--;
        }
        std::cout << "\n EL SOBREVIVIENTE ES: " << jugadores.pop();
    }

    void pseudoaleatorio_basico()
    {
        srand(time(NULL));
        for (int i = 0; i < turnos; i++)
        {
            turno_bomba[i]=rand()%20;
        }
    }
};

int main()
{
    Juego_bomba juego1;
}