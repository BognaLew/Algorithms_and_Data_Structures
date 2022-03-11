#include <iostream>
using namespace std;

#define MAX_INPUT_LENGTH 15

struct node {                   //struktura jednego wêz³a listy
    node* XOR = NULL;           //xor adresów poprzednika i nastêpnika
    int n;                      //przechowywana wartoœæ
};

struct queue {                  //struktura kolejki
    node* front = NULL;         //wskaŸnik na pocz¹tek kolejki
    node* back = NULL;          //wskaŸnik na koniec kolejki
    bool isEmpty = true;        //zmienna przechowuj¹ca informacjê o tym czy kolejka jest pusta
    int size = 0;               //zmienna przechowuj¹ca rozmiar kolejki
};

struct list {                       //struktura listy
    node* firstNode = NULL;         //wskaŸnik na pierwszy element (pocz¹tek listy)
    node* lastNode = NULL;          //wskaŸnik na ostatni element (koniec listy)
    int size = 0;                   //zmienna przechowuj¹ca rozmiar listy
    queue kolejka;                  //kolejka
};



//FUKCJA DO OBLICZANIA XOR WÊZ£ÓW
node* XOR(node* first, node* second) {
    return reinterpret_cast<node*>(reinterpret_cast<uintptr_t>(first) ^ reinterpret_cast<uintptr_t>(second));
}


//WYSZUKIWANIE WÊZ£ÓW Z LISTY
void go_over(node** tmp, node** neighbour) {
    node* otherNeighbour = XOR((*tmp)->XOR, *neighbour);
    *neighbour = *tmp;
    *tmp = otherNeighbour;
}


//FUNKCJONALNOŒCI LISTY
//DODAWANIE WÊZ£A (na pocz¹tek, na kniec, w œrodku)
void add_beg(list* lista, int n) {
    node* beg = new node;
    beg->n = n;
    beg->XOR = lista->firstNode;
    if (lista->firstNode == NULL) {
        lista->lastNode = beg;
    }
    else {
        lista->firstNode->XOR = XOR(beg, lista->firstNode->XOR);
    }
    lista->firstNode = beg;
    lista->size++;
    
}

void add_end(list* lista, int n) {
    node* end = new node;
    end->n = n;
    end->XOR = lista->lastNode;
    if (lista->lastNode == NULL) {
        lista->firstNode = end;
    }
    else {
        lista->lastNode->XOR = XOR(lista->lastNode->XOR, end);
    }
    lista->size++;
    lista->lastNode = end;
}

node* add_value(list* lista, int n, node* prev, node* next) {
    node* newNode = new node;

    newNode->n = n;
    prev->XOR = XOR(XOR(prev->XOR, next), newNode);
    next->XOR = XOR(XOR(next->XOR, prev), newNode);
    newNode->XOR = XOR(prev, next);

    lista->size++;
    return newNode;
}


//USUWANIE JEDYNEGO WÊZ£A (gdy lista ma 1 wêze³)
void delete_only_node(list* lista) {
    lista->firstNode = NULL;
    lista->lastNode = NULL;
    if (!lista->kolejka.isEmpty) {
        lista->kolejka.front = NULL;
        lista->kolejka.back = NULL;
        lista->kolejka.isEmpty = true;
    }
}

void checkWhatWithQueue(list* lista, node* nodeToDelete) {
    if (lista->kolejka.size == 1 && nodeToDelete == lista->kolejka.front) {
        lista->kolejka.front = NULL;
        lista->kolejka.back = NULL;
        lista->kolejka.isEmpty = true;
    }
    else if (nodeToDelete == lista->firstNode) {
        if (nodeToDelete == lista->kolejka.front) {
            lista->kolejka.front = lista->lastNode;
        }
        else if (nodeToDelete == lista->kolejka.back) {
            lista->kolejka.back = nodeToDelete->XOR;
        }
    }
    else {
        if (nodeToDelete == lista->kolejka.front) {
            lista->kolejka.front = nodeToDelete->XOR;
        }
        else if (nodeToDelete == lista->kolejka.back) {
            lista->kolejka.back = lista->firstNode;
        }
    }

}

//USUWANIE WÊZ£A (pocz¹tkowego, koñcowego)
void delete_beg(list* lista) {
    if (lista->firstNode != NULL) {
        node* beg = lista->firstNode;
        if (lista->firstNode != lista->lastNode) {
            node* next = beg->XOR;
            if (!(lista->kolejka.isEmpty)) {
                checkWhatWithQueue(lista, lista->firstNode);
            }
            next->XOR = XOR(next->XOR, beg);
            lista->firstNode = next;
        }
        else {
            delete_only_node(lista);
        }
        delete beg;
        lista->size--;
    }
}

void delete_end(list* lista) {
    if (lista->lastNode != NULL) {
        node* end = lista->lastNode;
        if (lista->firstNode != lista->lastNode) {
            node* prev = end->XOR;
            if (!lista->kolejka.isEmpty) {
                checkWhatWithQueue(lista, lista->lastNode);
            }
            prev->XOR = XOR(prev->XOR, end);
            lista->lastNode = prev;
        }
        else {
            delete_only_node(lista);
        }
        lista->size--;
        delete end;
    }
}

//WYPISYWANIE LISTY
void print_list(node* firstNodeToPrint) {        //w zale¿noœci od tego czy jako parametr funkcja uzyska pierwszy lub
    if (firstNodeToPrint != NULL) {                  //ostatni wêze³, lista zostanie wypisana od przodu b¹dŸ od ty³u
        node* neighbour = NULL;
        node* tmp = firstNodeToPrint;

        while (tmp != NULL) {
            cout << tmp->n << " ";
            go_over(&tmp, &neighbour);
        }
    }
    else {
        cout << "NULL";
    }

    cout << endl;
}

//WYPISYWANIE ROZMIARU LISTY
void size(list* lista) {
    cout << lista->size << endl;
}


//FUNKCJONALNOŒCI KOLEJKI
//WYPISYWANIE ROZMIARU KOLEJKI
void count(list* lista) {
    int n = 0;
    if (!lista->kolejka.isEmpty) {
        
        node* tmp = lista->lastNode;
        node* next = NULL;
        while (tmp != lista->kolejka.front) {   //znajdowanie pocz¹tku listy
            go_over(&tmp, &next);
        }
        if (next == lista->kolejka.back) {      //zabezpieczenie jeœli back jest nastêpnikiem front
            n++;
            go_over(&tmp, &next);
        }
        while (next != lista->kolejka.back) {   //liczenie elementów kolejki
            if (next == lista->firstNode) {
                tmp = lista->lastNode;
                next = NULL;
            }
            n++;
            go_over(&tmp, &next);
        }
    }
    lista->kolejka.size = n;
}

//WPYCHANIE ELEMENTÓW DO KOLEJKI
void push(list* lista, int n) {
    count(lista);       //aktualizacja zmiennej size w kolejce
    if (lista->kolejka.isEmpty) {
        if (lista->firstNode == NULL) {
            add_beg(lista, n);
        }else {
            lista->lastNode->n = n;
        }
        lista->kolejka.front = lista->lastNode;
        lista->kolejka.back = lista->kolejka.front;
        lista->kolejka.isEmpty = false;
    }else if (!lista->kolejka.isEmpty && lista->kolejka.size == lista->size) {
        if (lista->kolejka.front != lista->lastNode) {
            lista->kolejka.back = add_value(lista, n, lista->kolejka.front, lista->kolejka.back);
        }else {
            add_beg(lista, n);
            lista->kolejka.back = lista->firstNode;
        }
    }else {
        if (lista->kolejka.back == lista->firstNode) {
            lista->lastNode->n = n;
            lista->kolejka.back = lista->lastNode;
        }else {
            node* next = NULL;
            node* tmp = lista->lastNode;
            while (next != lista->kolejka.back) {
                go_over(&tmp, &next);
            }
            tmp->n = n;
            lista->kolejka.back = tmp;
        }
    }
}

//WYCI¥GANIE ELEMENTÓW Z KOLEJKI
void pop(list* lista) {
    count(lista);       //aktualizacja zmiennej size w kolejce
    if (lista->kolejka.size > 1) {
        node* next = NULL;
        node* tmp = lista->lastNode;
        while (next != lista->kolejka.front) {
            go_over(&tmp, &next);
        }
        if (tmp == NULL) {
            tmp = lista->lastNode;
        }
        cout << lista->kolejka.front->n << endl;
        lista->kolejka.front = tmp;
    }
    else if (lista->kolejka.size == 1) {
        cout << lista->kolejka.front->n << endl;;
        lista->kolejka.front = NULL;
        lista->kolejka.back = NULL;
        lista->kolejka.isEmpty = true;
    }
    else {
        cout << "NULL\n";
    }

}

//WYPISYWANIE KOLEJKI
void print_queue(list* lista) {
    if (!lista->kolejka.isEmpty) {
        node* tmp = lista->lastNode;
        node* next = NULL;
        while (tmp != lista->kolejka.front) {
            go_over(&tmp, &next);
        }
        if (next == lista->kolejka.back) {
            cout << tmp->n << " ";
            go_over(&tmp, &next);
        }
        while (next != lista->kolejka.back) {
            if (next == lista->firstNode) {
                tmp = lista->lastNode;
                next = NULL;
            }
            cout << tmp->n << " ";
            go_over(&tmp, &next);
        }
    }else {
        cout << "NULL";
    }
    cout << endl;
}

//WPISYWANIE WARTOŒCI 0 DO ELEMENTÓW Z LISTY NIE BÊD¥CYCH W KOLEJCE
void garbage_soft(list* lista) {
    if (lista->kolejka.isEmpty && lista->lastNode != NULL) {
        node* tmp = lista->lastNode;
        node* next = NULL;
        while (tmp != NULL) {
            tmp->n = 0;
            go_over(&tmp, &next);
        }
    }
    else {
        node* tmp = lista->lastNode;
        node* next = NULL;
        if (lista->firstNode != lista->kolejka.back) {
            while (next != lista->kolejka.back) {
                go_over(&tmp, &next);
            }
        }
        while (tmp != lista->kolejka.front) {
            if (next == lista->firstNode) {
                tmp = lista->lastNode;
                next = NULL;
            }
            tmp->n = 0;
            go_over(&tmp, &next);
        }
    }

}

//USUWANIE ELEMENTÓW Z LISTY NIE BÊD¥CYCH W KOLEJCE
void garbage_hard(list* lista) {
    if (lista->kolejka.isEmpty && lista->lastNode != NULL) {
        while (lista->firstNode != NULL) {
            delete_end(lista);
        }
    }
    else {
        node* tmp = lista->lastNode;
        if (lista->firstNode == lista->kolejka.back) {
            while (tmp != lista->kolejka.front) {
                delete_end(lista);
                tmp = lista->lastNode;
            }
        }
        else {
            node* next = NULL;
            while (next != lista->kolejka.back) {
                go_over(&tmp, &next);
            }
            node* prev = XOR(tmp->XOR, next);
            while (tmp != lista->kolejka.front) {
                if (tmp == lista->firstNode) {
                    delete_beg(lista);
                    tmp = lista->lastNode;
                    prev = tmp->XOR;
                    next = NULL;
                }
                else if (tmp == lista->lastNode) {
                    delete_end(lista);
                    tmp = lista->lastNode;
                    prev = tmp->XOR;
                    next = NULL;
                }
                else {
                    node* t = tmp;
                    prev->XOR = XOR(XOR(prev->XOR, t), next);
                    next->XOR = XOR(XOR(next->XOR, t), prev);
                    delete t;
                    tmp = prev;
                    prev = XOR(tmp->XOR, next);
                    lista->size--;
                }
            }
        }

    }

}


//WYBIERANIE ODPOWIEDNIEJ FUNKCJONALNOŒCI
void ster(list* lista, char* komenda) {
    int n;
    if (strcmp(komenda, "ADD_BEG") == 0) {
        cin >> n;
        add_beg(lista, n);
    }
    else if (strcmp(komenda, "ADD_END") == 0) {
        cin >> n;
        add_end(lista, n);
    }
    else if (strcmp(komenda, "PRINT_FORWARD") == 0) {
        print_list(lista->firstNode);
    }
    else if (strcmp(komenda, "PRINT_BACKWARD") == 0) {
        print_list(lista->lastNode);
    }
    else if (strcmp(komenda, "DEL_BEG") == 0) {
        delete_beg(lista);
    }
    else if (strcmp(komenda, "DEL_END") == 0) {
        delete_end(lista);
    }
    else if (strcmp(komenda, "SIZE") == 0) {
        size(lista);
    }
    else if (strcmp(komenda, "PUSH") == 0) {
        cin >> n;
        push(lista, n);
    }
    else if (strcmp(komenda, "POP") == 0) {
        pop(lista);
    }
    else if (strcmp(komenda, "PRINT_QUEUE") == 0) {
        print_queue(lista);
    }
    else if (strcmp(komenda, "GARBAGE_SOFT") == 0) {
        garbage_soft(lista);
    }
    else if (strcmp(komenda, "GARBAGE_HARD") == 0) {
        garbage_hard(lista);
    }
    else if (strcmp(komenda, "COUNT") == 0) {
        count(lista);
        cout << lista->kolejka.size << endl;
    }
}

int main() {
    char komenda[MAX_INPUT_LENGTH];
    list* lista = new list;
    while (cin >> komenda) {
        ster(lista, komenda);
    }
    return 0;
}