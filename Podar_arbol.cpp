#include <iostream>
#include <queue>
#include <stack>
#include <math.h>

template <class T>
struct CBinTreeNode
{
    CBinTreeNode(T v)
    {
        value = v;
        nodes[0] = nodes[1] = 0;
    }
    T value;
    CBinTreeNode<T>* nodes[2]; //0 left, 1 right
};

template <class T>
class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    CBinTreeNode<T>* Root();
    bool Find(T x, CBinTreeNode<T>**& p);
    bool Ins(T x);
    bool Rem(T x);
    CBinTreeNode<T>** Rep(CBinTreeNode<T>** p);
    void printspace(int a);
    int MaxDepth(CBinTreeNode<T>* n);
    void Print(CBinTreeNode<T>* n);
    void podar(CBinTreeNode<T>* n);

private:
    CBinTreeNode<T>* root;
    bool brep;
};

template <class T>
CBinTree<T>::CBinTree()
{
    root = 0;
    brep = 0;
}

template <class T>
CBinTree<T>::~CBinTree()
{
    
}

template <class T>
CBinTreeNode<T>* CBinTree<T>::Root()
{
    return root;
}

template <class T>
bool CBinTree<T>::Find(T x, CBinTreeNode<T>**& p)
{
    for (p = &root;
        *p && (*p)->value != x;
        p = &((*p)->nodes[(*p)->value < x])
        );
    return *p != 0;
}

template <class T>
bool CBinTree<T>::Ins(T x)
{
    CBinTreeNode<T>** p;
    if (Find(x, p)) return 0;
    *p = new CBinTreeNode<T>(x);
    return 1;
}

template <class T>
bool CBinTree<T>::Rem(T x)
{
    CBinTreeNode<T>** p;
    if (!Find(x, p)) return 0;
    if ((*p)->nodes[0] && (*p)->nodes[1])
    {
        CBinTreeNode<T>** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CBinTreeNode<T>* t = *p;
    *p = (*p)->nodes[(*p)->nodes[1] != 0];
    delete t;
    return 1;
}

template <class T>
CBinTreeNode<T>** CBinTree<T>::Rep(CBinTreeNode<T>** p)
{
    CBinTreeNode<T>** q;
    for (q = &(*p)->nodes[!brep];
        (*q)->nodes[brep];
        q = &(*q)->nodes[brep]);
    brep = !brep;
    return q;
}

template<class T>
void  CBinTree<T>::printspace(int a)
{
    for (int i = 0; i < a; i++)
        std::cout << " ";
}

template <class T>
int CBinTree<T>::MaxDepth(CBinTreeNode<T>* n)
{
    if (!n) return 0;
    return std::max(MaxDepth(n->nodes[0]), MaxDepth(n->nodes[1])) + 1;
}

template <class T>
void CBinTree<T>::Print(CBinTreeNode<T>* n)
{
    if (!root) return;
    std::queue< CBinTreeNode<T>* > q;
    // usa una cola para recorrer el arbol y luego imprimirlo de arriba hacia abajo
    T valor=0;
    int altura = MaxDepth(root);
    int espacios = pow(2, altura-1)*10;
    int nivel = 0, elementos = 0;
    q.push(root);
    printspace(espacios/2);
    while (!q.empty())
    {
        //Esto es para darle espacio a los hijos nulo del arbol.
        if (q.front() == NULL) {
            //asume que tiene dos nodos, sino se hace esto se pierden espacios
            q.push(NULL); q.push(NULL);
            printspace(espacios);
            elementos++;
            q.pop();
            if (elementos >= pow(2, nivel+1))
                break;
            continue;
        }
        //agrega un valor y si no, agrega un null que representa un hijo nulo del arbol
        if (q.front()->nodes[0])
            q.push(q.front()->nodes[0]);
        else if (nivel<=altura)
            q.push(NULL);
        if (q.front()->nodes[1])
            q.push(q.front()->nodes[1]);
        else  if (nivel<=altura)
            q.push(NULL);

        //checkea cuando un valor es mayor que el anterior para saber si paso a otro nivel
        if (valor > q.front()->value) 
        {
            std::cout << "\n\n";
            espacios = espacios / 2;
            printspace(espacios / 2);
            nivel++;
        }

        valor = q.front()->value;
        std::cout << valor;
        q.pop();
        elementos++;
        printspace(espacios);
    }
}

template <class T>
void CBinTree<T>::podar(CBinTreeNode<T>* n)
{
    if (!root) return;
    //cola para recorrer la matriz por niveles
    std::queue< CBinTreeNode<T>* > q;
    //pila para eliminar nodos que deben ser eliminados
    std::stack< CBinTreeNode<T>* > p;
    int power=1;
    char check = 'a';
    T valor=0;
    q.push(root);
    while (!q.empty())
    {
        if (valor > q.front()->value and check=='a')
            check = 'o';

        if (check=='o')
        {
            if (q.size() != pow(2, power))
            {
                //cuando check sea 'r', todos los elementos de aqui en adelante se agregaran a la pila
                check='r';
            }
            else
            {
                check = 'a';
            }
            power++;
        }

        if (q.front()->nodes[0])
            q.push(q.front()->nodes[0]);
        if (q.front()->nodes[1])
            q.push(q.front()->nodes[1]);
        valor = q.front()->value;
        if (check == 'r')
            p.push(q.front());
        q.pop();
    }
    while (!p.empty())
    {// eliminando todo lo de la pila
        Rem(p.top()->value);
        p.pop();
    }
}

int main()
{
    /*El print se ve mal si la consola no esta en pantalla completa,
    despues de eso no hay ningun problema.*/
    CBinTree<int> arbol1;
    arbol1.Ins(50);
    arbol1.Ins(40); 
    arbol1.Ins(80); 
    arbol1.Ins(30); 
    arbol1.Ins(43); 
    arbol1.Ins(60); 
    arbol1.Ins(95); 
    arbol1.Ins(20);
    arbol1.Ins(35);
    arbol1.Ins(73);
    arbol1.Ins(90);
    arbol1.Ins(99);
    arbol1.Ins(10);
    arbol1.Ins(28);
    arbol1.Ins(70);

    arbol1.Print(arbol1.Root());     std::cout << "\n";
    arbol1.podar(arbol1.Root());     std::cout << "\nPODAR: \n";
    arbol1.Print(arbol1.Root());     std::cout << "\n";
}
