#include <iostream>
#include <sstream>

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
        if (nelem==1)
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
            std::cout << nuevo->value << " ";
        }
    }
};

//-----------------------------------------------------//

template<class T, class S>
class Pila {
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
        return seq.pop_back();
    }

};

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

class RPN
{
private:
    char* start, * x;
    int nelempila, nelemcola, nelem_parentesis, value1, value2, result;
    char pop_value;
    Pila<char, List<char>> A1;
    Cola<char, List<char>> B1;

public:

    RPN() {
        nelempila = nelemcola = nelem_parentesis = value1 = value2 = result = 0;
        std::cout << "\n Ingrese una ecuacion\nEjemplos: (7*4)+(2-8*4), (2^3)+(3^2), (8+2)/2\n";
        start = new char[100];
        std::cin >> start;
        x = start;
    }
    ~RPN() {
        delete start;
    }

    //CONVIERTIENDO A INFIJA//

    void conv_infija() {
        while (*x != 0)
        {
            if (*x == '*' || *x == '-' || *x == '+' || *x == '/' || *x == '^')
            {
                A1.push(*x); //ingresa los operadores en la pila
                nelempila++;
                x++;
            }
            else if (*x == '(')
            {
                x++;
                case_parentesis_infija(); //avanza hasta encontrar ')'
            }
            else if (*x == ')')
            {
                x++;
            }
            else
            {
                B1.push(*x); //despliega enteros
                nelemcola++;
                x++;
            }
        }
        for (; nelempila != 0 ; nelempila--, nelemcola++) //quita lo de la pila y lo pone en la cola, "despliega los elementos restantes"
        {
            pop_value = A1.pop();
            B1.push(pop_value);
        }

    }
    void case_parentesis_infija() {
        while (*(x - 1) != ')') //recorre elementos del parentesis
        {
            if (*x == '*' || *x == '-' || *x == '+' || *x == '/' || *x == '^')
            {
                A1.push(*x);
                nelem_parentesis++;
                x++;
            }
            else if (*x == ')')
            {
                for (; nelem_parentesis; nelem_parentesis--,nelemcola++) //despliega elementos antes ingresados en la pila
                {
                    pop_value = A1.pop();
                    B1.push(pop_value);
                }
                nelem_parentesis = 0;
                x++;
            }
            else if (*x == '(')
            {
                case_parentesis_infija(); //si hay otro parentesis por dentro
            }
            else
            {
                B1.push(*x);
                nelemcola++;
                x++;
            }
        }
    }
    void print_inf()
    {
        B1.print();
    }

    //CONVIRTIENDO A POSTFIJA//

    void conv_post()
    {
        while (nelemcola != 0)
        {
            pop_value = B1.pop();
            if (pop_value == '*' || pop_value == '-' || pop_value == '+' || pop_value == '/' || pop_value == '^')
            {
                value1 = int(A1.pop()-'0'); //convertir ASCII a entero '0'=48, '1'=49, '2'=50 , ...
                value2 = int(A1.pop()-'0');
                switch (pop_value)
                {
                case '*':
                    result = (value2 * value1);
                    break;
                case'-':
                    result = (value2 - value1);
                    break;
                case'+':
                    result = (value2 + value1);
                    break;
                case '/':
                    result = (value2 / value1);
                    break;
                case '^':
                    result=potenciacion(value2, value1);                  
                    break;
                }
                if (result >= 80) //despues del ASCII 80 al convertir me salia negativo
                    A1.push(-(result)+'0');
                else
                    A1.push(result + '0'); //convertimos a ASCII ya que puede que volvamos a usar este elemento luego
                nelemcola--;
            }
            else
            {
                A1.push(pop_value);
                nelemcola--;
            }
        }
    }
    void print_post()
    {
        pop_value = A1.pop();
        if (result >= 80)
            std::cout << "\n Resultado: " << -(int(pop_value))+'0';
        else
            std::cout << "\n Resultado: " << int(pop_value - '0');
    }

    //MATEMATICA
    int potenciacion(int x, int y)
    {
        int xresult=x;
        if (y == 0)
            return 1;
        else if (y == 1)
            return x;
        else
        {
            for (; y != 1; y--)
                xresult = xresult * x;

            return xresult;
        }
    }
};

int main()
{
    RPN A;
    std::cout << "\n Convirtiendo la expresion a infija ";
    A.conv_infija();
    A.print_inf();
    std::cout << "\n\n Usando la cola donde desplegamos elementos, obtenemos\n";
    A.conv_post();
    A.print_post();

}

