#include <iostream>
#include <vector>
#include <list>
#include <thread>

template <class G>
struct CNode
{
    typedef typename G::Node Node;
    typedef typename G::Edge Edge;
    typedef typename G::N N;

    N value;
    std::list<Edge*> edges;

    CNode(N val)
    {
        value = val;
    }
    ~CNode()
    {
        value = 0;
    }
};

template<class G>
struct CEdge
{
    typedef typename G::Node Node;
    typedef typename G::E E;

    CEdge(Node* a, Node* b, E e, bool d)
    {
        nodes[0] = a;
        nodes[1] = b;
        value = e;
        dir = d;
    }
    ~CEdge()
    {
        nodes[0] = NULL;
        nodes[1] = NULL;
        value = 0;
    }

    E value;
    Node* nodes[2];
    bool dir;
};

template<class _N, class _E>
class CGraph
{
public:
    typedef CGraph<_N, _E> G;
    typedef CNode<G> Node;
    typedef CEdge<G> Edge;
    typedef _N N;
    typedef _E E;

    void InsNode(N n)
    {
        CNode<G>* n_n = new CNode<G>(n);
        nodes.push_back(n_n);
    }
    void InsEdge(Node* a, Node* b, E e, bool d)
    {
        CEdge<G>* e_n = new CEdge<G>(a, b, e, d);
        a->edges.push_back(e_n);
        b->edges.push_back(e_n);
    }
    void RemEdge(Node* a, Node* b, E e)
    {
        typename std::list<Edge*>::iterator i;
        CEdge<G>* e_n = new CEdge<G>(a, b, e, 0);
        CEdge<G>* e_n2 = new CEdge<G>(a, b, e, 1);
        a->edges.remove(e_n);
        for (i = b->edges.begin(); i != b->edges.end(); ++i)
        {
            if (*i == e_n || *i == e_n2) {
                delete* i;
                b->edges.remove(*i);
                break;
            }
        }
        delete e_n;
        delete e_n2;
    }
    void RemNode(N n)
    {
        typename std::list<Edge*>::iterator j;
        CNode<G>* n_n = new CNode<G>(n);
        for (int i = 0; i != nodes.size(); i++)
        {
            if (nodes[i]->value == n)
            {
                for (j = nodes[i]->edges.begin(); j != nodes[i]->edges.end(); ++j)
                {
                    delete* j;
                }
                nodes[i]->edges.clear();
                delete nodes[i];
                break;
            }
        }
        delete n_n;
    }

    void print() {
        std::cout << "\n\t\t\tEjemplo para entender el print de los nodos";
        std::cout << "\n\t\t\tNodo_i->nodo(distancia)->nodo(distancia)\n";
        for (int i = 0; i != nodes.size(); i++)
        {
            std::cout << "\n\t\t\t\t" << nodes[i]->value;

            for (CEdge<G>* j : nodes[i]->edges)
            {
                if (j->nodes[0] == nodes[i])
                {
                    std::cout << "->" << j->nodes[1]->value << "(" << j->value << ")";
                }
            }
        }
    }

    std::vector<Node*> nodes;
};

struct CGraph_pre : public CGraph<int, int>
{
    int** weights;
    std::list<Node*>** min_paths;

    CGraph_pre()
    {
        
    }

    //este sera como el constructor ya que para poder crear las matrices
    //necesito saber nodes.size() pero eso solo lo puedo saber despues de 
    //crear una instancia de la clase, por lo que es imposible con el constructor
    void create_arrays()
    {
        weights = new int* [nodes.size()];
        for (int it = 0; it != nodes.size(); it++)
        {
            weights[it] = new int[nodes.size()];
        }
        min_paths = new std::list<Node*>*[nodes.size()];
        for (int it = 0; it != nodes.size(); it++)
        {
            min_paths[it] = new std::list<Node*>[nodes.size()];
        }
    }

    ~CGraph_pre()
    {
        for (int it = 0; it != nodes.size(); ++it)
        {
            delete[] weights[it];
        }
        delete[] weights;
    }

    //Actualiza los pesos para poder saber cual es el valor mas
    //cercano de los nodos visitados a otros nodos
    void up_weights(Node* A, int* &arr ,std::list<Node*> list, std::list<Node*>* &arr2)
    {
        char trasher = 'd';

        for (Node* it_cen : list)
        {
            for (Edge* it_cee : it_cen->edges)
            {
                if ((it_cee->value + arr[it_cen->value - 1]) < arr[(it_cee->nodes[1]->value - 1)])
                {
                    arr[(it_cee->nodes[1]->value - 1)] = it_cee->value + arr[it_cen->value - 1];
                    for (Node* it_cel : arr2[(it_cee->nodes[1]->value - 1)])
                    {
                        if (trasher == 'a')
                        {
                            arr2[(it_cee->nodes[1]->value - 1)].remove(it_cel);
                        }

                        if (it_cel == it_cee->nodes[0])
                        {
                            trasher = 'a';
                        }
                    }
                    arr2[(it_cee->nodes[1]->value - 1)].push_back(it_cen);
                }
            }
        }
    }

    //determina la arista mas corta que sale de una lista de nodos.
    //En este caso, recorre los nodos visitados, y agrega 
    //el nuevo nodo visitado a la lista de nodos visitados
    void short_edge(std::list<Node*> &listnn, std::list<Node*> &listnu, int* &arr, std::list<Node*>* &arr2)
    {
        Node* A=listnn.front();
        Node* B=listnn.front();
        int min = 1000000000;
        char a = 'a';
        for (Node* it_sen : listnn)
        {
            for (Edge* it_sel : it_sen->edges)
            {
                for (Node* itseu : listnu)
                {
                    if (it_sel->nodes[1] == itseu && (it_sel->value+arr[it_sel->nodes[0]->value-1]) < min)
                    {
                        min = it_sel->value;
                        A = it_sel->nodes[1];
                        B = it_sel->nodes[0];
                        a = 'b';
                    }
                }
            }
        }
        if (a == 'b')
        {
            arr[A->value - 1] = arr[B->value - 1] + min;
            arr2[A->value - 1] = arr2[B->value - 1];
            arr2[A->value - 1].push_back(A);

            listnn.push_back(A);
            listnu.remove(A);
        }
    }

    //Halla el menor camino del Nodo A hacia todo los nodos
    void djkistra_all(Node* A)
    {

        int iteration=0;

        std::list<Node*>* mpaths;
        int* wnodes;

        std::vector<Node*>::iterator it_n;
        Node* it_nod;

        //Nodos no visitados
        std::list<Node*> n_nu;
        for (Node* it_nn : nodes)
        {
            n_nu.push_back(it_nn);
        }

        //Nodos visitados
        std::list<Node*> n_nn;

        //inicializando las matrices
        wnodes = new int[nodes.size()];
        for (int i = 0; i != nodes.size(); ++i)
            wnodes[i] = -1;

        mpaths = new std::list<Node*>[nodes.size()];
        for (int i = 0; i != nodes.size(); ++i)
            mpaths[i].push_back(A);

        //el camino de A hacia A siempre sera 0
        wnodes[A->value-1] = 0;
        n_nu.remove(A);
        n_nn.push_back(A);


        for (it_n = nodes.begin(); it_n != nodes.end(); ++it_n)
        {
            if (A == *it_n)
                continue;

            while (iteration != nodes.size() + 1)
            {
                it_nod = *it_n;
                short_edge(n_nn, n_nu, wnodes, mpaths);
                up_weights(A, wnodes, n_nn, mpaths);
                iteration++;
            }

            iteration = 0;
            }

        for (int i = 0; i != nodes.size(); ++i)
        {
            weights[A->value - 1][i] = wnodes[i];
            min_paths[A->value - 1][i] = mpaths[i];
        }

        delete[]wnodes;
        delete[]mpaths;
        
    }
    
    //imprime el camino mas cercano de u nodo a otro nodo
    void print_path(int nodea, int nodeb)
    {
        for (Node* A : min_paths[nodea - 1][nodeb - 1])
        {
            std::cout << A->value << "->";
        }
        std::cout << "NULL";
    }

    //imprime la matriz weights donde podemos hallar las distancias minimas
    void pre_print()
    {
        std::cout << "\n\t\t";
        for (int i = 0; i != nodes.size(); i++)
        {
            std::cout << "\n\t\t";
            for (int j = 0; j != nodes.size(); j++)
            {
                
                    std::cout << "[" << weights[i][j] << "]";
            }
        }
    }
};

int main()
{
    //Si no hay camino entre dos nodos, escribira -1 en el peso.
    CGraph_pre g;
    g.InsNode(1);
    g.InsNode(2);
    g.InsNode(3);
    g.InsNode(4);
    g.InsNode(5);
    g.InsEdge(g.nodes[0], g.nodes[1], 2, 0);
    g.InsEdge(g.nodes[0], g.nodes[4], 10, 0);
    g.InsEdge(g.nodes[1], g.nodes[2], 3, 0);
    g.InsEdge(g.nodes[1], g.nodes[4], 7, 0);
    g.InsEdge(g.nodes[2], g.nodes[0], 4, 0);
    g.InsEdge(g.nodes[2], g.nodes[3], 4, 0);
    g.InsEdge(g.nodes[3], g.nodes[4], 5, 0);
    g.InsEdge(g.nodes[4], g.nodes[2], 3, 0);

    //Empezando con los metodos de la clase CGraph_pre()
    g.create_arrays();

    //USANDO THREADS PARA EL PRE_PROCESADO-------------------------------------
    int nthreads = std::thread::hardware_concurrency(), iteration = 0, itn=0;
    std::thread* ths;

    while (iteration != g.nodes.size() / nthreads)
    {
        ths = new std::thread[nthreads];

        for (int it=0; it != nthreads; ++it, itn++)
            ths[it%nthreads] = std::thread(&CGraph_pre::djkistra_all, &g, g.nodes[itn]);

        for (int it=0;it != nthreads; ++it)
            ths[it].join();

        iteration++;
        delete[] ths;
    }
    ths = new std::thread[nthreads];
    for (int it=0; it != g.nodes.size()%nthreads; ++it,itn++)
        ths[it % nthreads] = std::thread(&CGraph_pre::djkistra_all, &g, g.nodes[itn]);

    for (int it = 0; it != g.nodes.size() % nthreads; ++it)
        ths[it % nthreads].join();
    delete[] ths;
    //-------------------------------------------------------------

    char window = 'h', anything='a', input='a';
    int NodeA = 0, NodeB = 0;

    while (true)
    {
        if (window == 'e')
            break;

        while (window == 'h')
        {
            std::cout << "\n\n\t\t(a) ver cual es el minimo camino de un nodo a otro";
            std::cout << "\n\n\t\t(b) imprimir la matriz de todas las distancias";
            std::cout << "\n\n\t\t(c) imprimir todos los caminos";
            std::cout << "\n\n\t\t(d) salir del programa";
            std::cout << "\n\n\n\n\t\tescribir 'a' para seleccionar la opcion (a) por ejemplo\n\t\t";
            std::cin >> input;
            switch (input)
            {
            case 'a':
                window = 'a';
                break;
            case 'b':
                window = 'b';
                break;
            case 'c':
                window = 'c';
                break;
            case 'd':
                window = 'e';
                break;
            }
        }

        while (window == 'a')
        {
            std::cout << "\t\t";
            g.print();
            std::cout << "\n\n\t\tEscribir el primer nodo (por ejemplo '1') \n\t\t\t";
            std::cin >> NodeA;
            std::cout << "\n\t\tEscribir el segundo nodo (por ejemplo '2') \n\t\t\t";
            std::cin >> NodeB;
            std::cout << "\n\t\tLa distancia del camino es:  " << g.weights[NodeA - 1][NodeB-1] << "\n\t\tEl camino es:\t";
            g.print_path(NodeA, NodeB);
            std::cout << "\n\n\t\tEscribir cualquier CHAR (como 'o') para continuar\n\t\t";
            std::cin >> anything;
            window = 'h';
        }

        while (window == 'b')
        {
            g.pre_print();
            std::cout << "\n\n\t\tEscribir cualquier CHAR (como 'o') para continuar\n\t\t\t";
            std::cin >> anything;
            window = 'h';
        }

        while (window == 'c')
        {
            for (int i = 1; i != g.nodes.size()+1; i++)
                for (int j = 1; j != g.nodes.size() + 1; j++)
                {
                    std::cout <<"\n\t\tDe "<<i<<" hacia "<<j<<":" << "\n\t\t";
                    g.print_path(i, j);
                    std::cout << "\n";
                }
            std::cout << "\n\n\t\tEscribir cualquier CHAR (como 'o') para continuar\n\t\t\t";
            std::cin >> anything;
            window = 'h';
        }
    }
}

