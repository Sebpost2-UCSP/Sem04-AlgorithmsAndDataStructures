#include <iostream>
#include <sstream>
#include <list>
#include <vector>
#include <stdlib.h>

struct CFd1
{
    inline int string_to_char(char a)
    {
        int b;
        std::stringstream s2;
        s2 << a;
        s2 >> b;
        return b;
    }

    inline std::vector<int> operator()(int x)
    {
        int mat[8] = { 3,2,7,6,5,4,3,2 };
        int mat2[11] = { 6,7,8,9,0,1,1,2,3,4,5 };
        int result = 0, count = 0;
        // 1-Convirtiendo el int a str para separar los digitos
        std::string dig_str;
        std::vector<int> dig_vec;
        std::stringstream s1;
        s1 << x;
        s1 >> dig_str;
        std::string::iterator i;
        for (i = dig_str.begin(); i < dig_str.end(); i++)
            dig_vec.push_back(string_to_char(*i));

        // 2-multiplicar los numeros y sumarlos
        for (std::vector<int>::iterator i = dig_vec.begin(); i != dig_vec.end(); i++)
        {
            result += *i * mat[count];
            count++;
        }
        // 3-usamos modulo 11 y restamos 11
        result = result % 11;
        result = 11 - result;
        switch (result)
        {
        case 11:
            result = 0;
            break;
        }
        // 4-Le damos el valor numerico dependiendo de su posicion
        result = mat2[result];
        /* 5-por ultimo, llenamos el vector con el dni y su numero que luego
        le sacaremos modulo en la funcion insertar.*/
        dig_vec.clear();
        dig_vec.push_back(x);
        dig_vec.push_back(result);
        return dig_vec;
    }
};


template<class T, class S, class Fd, unsigned int Sz>
class CHashTable
{
public:
    CHashTable();
    ~CHashTable();
    bool find(T v);
    bool ins(T v);
    bool rem(T v);
    void print();

    S* table;
    Fd fd;
};

template<class T, class S, class Fd, unsigned int Sz>
CHashTable<T, S, Fd, Sz>::CHashTable()
{
    table = new S[Sz];
}

template<class T, class S, class Fd, unsigned int Sz>
CHashTable<T, S, Fd, Sz>::~CHashTable()
{
    delete[] table;
}

template<class T, class S, class Fd, unsigned int Sz>
bool CHashTable<T, S, Fd, Sz>::find(T v)
{
    //sirve para encontrar si algun dni se repite
    typename S::iterator i;

    for (i = table[fd(v)[1]].begin(); i != table[fd(v)[1]].end(); ++i)
        if (v == *i)
            return 1;
    return 0;
}

template<class T, class S, class Fd, unsigned int Sz>
bool CHashTable<T, S, Fd, Sz>::ins(T v)
{
    //revisando que los dnis no se repitan
    if (find(v) == 1)
    {
        std::cout << "\n\n\t\t Ese numero ya esta en la tabla";
        return 0;
    }
    std::vector<int> result = fd(v);
    std::vector<int> sort_vec;
    bool sort = 0;
    typename S::iterator i;
    std::vector<int>::iterator j;
    table[result[1]].push_back(result[0]);
    //revisando que los numeros esten en orden.
    for (i = table[result[1]].begin(); i != table[result[1]].end(); ++i)
    {
        if (*i > result[0]) {
            sort = 1;
            break;
        }
    }
    //si los numeros no estan ordenados, los ordenamos
    switch (sort)
    {
    case 1:
        while (!table[result[1]].empty())
        {
            T temp = table[result[1]].front();
            for (i = table[result[1]].begin(); i != table[result[1]].end(); ++i)
            {
                if (temp > *i)
                    temp = *i;
            }
            sort_vec.push_back(temp);
            table[result[1]].remove(temp);
        }
        for (j = sort_vec.begin(); j != sort_vec.end(); ++j)
            table[result[1]].push_back(*j);
        break;
    }
    return 1;
}

template<class T, class S, class Fd, unsigned int Sz>
bool CHashTable<T, S, Fd, Sz>::rem(T v)
{
    table[fd(v)[1] % Sz].remove(v);
    return 0;
}

template<class T, class S, class Fd, unsigned int Sz>
void CHashTable<T, S, Fd, Sz>::print()
{
    // usando la subclase iterador para recorrer las listas
    typename S::iterator j;
    for (int i = 0; i != Sz; i++)
    {
        std::cout << "\n\t\t" << i << " -> ";
        for (j = table[i].begin(); j != table[i].end(); ++j)
            std::cout << *j << " -> ";
    }
}

int main()
{
    CHashTable<int, std::list<int>, CFd1, 11> ht;
    int choice = 0, val=0;
    char windows = 'n', anything ='0';
    //Poniendo valores como ejemplo
    ht.ins(72215345);
    ht.ins(17801146);
    ht.ins(72039840);
    ht.ins(30960533);
    ht.ins(72414960);

    /*SI SE USA REPLIT, pueden aparecer problemas con el CLS pero 
    aun asi corre normal, solo muestra un mensaje de no encontrar CLS*/

    /*SI SE ESCRIBE UN DNI QUE YA ESTA EN LA TABLA, NO SE INGRESARA
    PORQUE LOS DNIS NO SE PUEDEN REPETIR*/

    while (true)
    {
        if (windows == 's')
            break;

        while (windows == 'n')
        {
            std::cout << "\n\n\t\t1 - Insertar Dni \n\t\t2 - Remove";
            std::cout << "\n\t\t3 - Salir \n\n\t\t";
            std::cout << "Por ejemplo escribir '1' para insertar\n";
            ht.print();
            std::cout << "\n\n";
            std::cin >> choice;
            switch (choice)
            {
            case 1:
                windows = 'a';
                break;
            case 2:
                windows = 'b';
                break;
            case 3:
                windows = 'c';
                break;
            }
            system("CLS");
        }
        while (windows == 'a')
        {
            std::cout << "\n\n\t\tEscribir el Dni que quiere insertar\n";
            std::cout << "\n\t\tpor ejemplo '72215345'\n\t\t";
            std::cin >> val;
            ht.ins(val);
            ht.print();
            std::cout << "\n\n\t\tEscribir cualquier cosa (1 char) para continuar\n\t\t";
            std::cin >> anything;
            windows = 'n';
            system("CLS");
        }
        while (windows == 'b')
        {
            std::cout << "\n\n\t\tEscribir el Dni que quiere borrar\n\t\t";
            ht.print();
            std::cout << "\n\n\t\t";
            std::cin >> val;
            ht.rem(val);
            ht.print();
            std::cout << "\n\n\t\tEscribir cualquier cosa (1 char) para continuar\n\t\t";
            std::cin >> anything;
            windows = 'n';
            system("CLS");
        }
        while (windows == 'c')
        {
            windows = 's';
        }
    }
}


