#include <iostream>
using namespace std;

#define MAX_INPUT_LENGTH 15

struct node {			//struktura jednego węzła listy
	node* XOR = NULL;	//xor adresów poprzednika i następnika
	int n;				//przechowywana wartość
};

struct list {					//struktura listy
	node* firstNode = NULL;		//wskaźnik na pierwszy element (początek listy)
	node* lastNode = NULL;		//wskaźnik na ostatni element (koniec listy)
	node* actual = NULL;		//wskaźnik na aktualny element
	node* prev = NULL;			//wskaźnik na poprzednika aktualnego
	node* next = NULL;			//wskażnik na natępnika aktualnego
};

//FUKCJA DO OBLICZANIA XOR WĘZŁÓW
node* XOR(node* first, node* second) {
	return reinterpret_cast<node*>(reinterpret_cast<uintptr_t>(first) ^ reinterpret_cast<uintptr_t>(second));
}


//WYSZUKIWANIE WĘZŁÓW Z LISTY
void go_over(node** tmp, node** neighbour) {
	node* otherNeighbour = XOR((*tmp)->XOR, *neighbour);
	*neighbour = *tmp;
	*tmp = otherNeighbour;
}


//DODAWANIE WĘZŁA (na początek, na kniec, jako poprzednik actual)
void add_beg(list *lista, int n) {
	node* beg = new node;
	beg->n = n;
	beg->XOR = lista->firstNode;
	if (lista->firstNode == NULL) {
		lista->lastNode = beg;
		lista->actual = beg;
	}else {
		lista->firstNode->XOR = XOR(beg, lista->firstNode->XOR);

		if (lista->actual == lista->firstNode) {
			lista->prev = beg;
		}
	}
	lista->firstNode = beg;
}

void add_end(list* lista, int n) {
	node* end = new node;
	end->n = n;
	end->XOR = lista->lastNode;
	if (lista->lastNode == NULL) {
		lista->firstNode = end;
		lista->actual = end;
	}else {
		lista->lastNode->XOR = XOR(lista->lastNode->XOR, end);
		
		if (lista->actual == lista->lastNode) {
			lista->next = end;
		}		
	}
	lista->lastNode = end;
}

void add_act(list* lista, int n) {
	if (lista->actual == lista->firstNode) {
		add_beg(lista, n);
	}else {
		node* newNode = new node;
		node* prev = lista->prev;
		node* tmp = lista->actual;

		newNode->n = n;
		prev->XOR = XOR(XOR(prev->XOR, tmp), newNode);
		tmp->XOR = XOR(XOR(tmp->XOR, prev), newNode);
		newNode->XOR = XOR(prev, tmp);
		lista->prev = newNode;
	}
}


//USUWANIE JEDYNEGO WĘZŁA (gdy lista ma 1 węzeł)
void delete_only_node(list* lista) {
	lista->firstNode = NULL;
	lista->lastNode = NULL;
	lista->actual = NULL;
}

//USUWANIE WĘZŁA (początkowego, końcowego, aktualnego, wszystkie z daną wartością)
void delete_beg(list* lista) {
	if(lista->firstNode != NULL){
		node* beg = lista->firstNode;
		if (lista->firstNode != lista->lastNode) {
			node* next = beg->XOR;
			if (lista->firstNode == lista->actual) {
				lista->actual = lista->lastNode;
			}
			next->XOR = XOR(next->XOR, beg);
			lista->firstNode = next;
		}else {
			delete_only_node(lista);
		}
		delete beg;
	}
}

void delete_end(list* lista) {
	if (lista->lastNode != NULL) {
		node* end = lista->lastNode;
		if (lista->firstNode != lista->lastNode) {
			node* prev = end->XOR;
			if (lista->lastNode == lista->actual) {
				lista->actual = prev;
			}
			prev->XOR = XOR(prev->XOR, end);
			lista->lastNode = prev;
		}else {
			delete_only_node(lista);
		}
		delete end;
	}
}

void delete_act(list* lista) {
	if(lista->firstNode != NULL){
		if (lista->actual == lista->firstNode) {
			delete_beg(lista);
		}else if (lista->actual == lista->lastNode){
			delete_end(lista);
		}else {
			node* prev = lista->prev;
			node* tmp = lista->actual;
			node* next = lista->next;
			prev->XOR = XOR(XOR(prev->XOR, tmp), next);
			next->XOR = XOR(XOR(next->XOR, tmp), prev);
			lista->actual = prev;
			lista->prev = XOR(prev->XOR, next);
			delete tmp;
		}
	}
}

void delete_val(list* lista, int n) {
	if (lista->firstNode != NULL) {
		if (lista->lastNode == lista->firstNode && lista->firstNode->n == n) {
			delete_only_node(lista);
		}else if(lista->firstNode != lista->lastNode){
			node* prev = NULL;
			node* tmp = lista->firstNode;
			node* next = tmp->XOR;

			while (tmp != NULL) {
				if (tmp->n == n) {
					if (tmp == lista->firstNode) {
						delete_beg(lista);
						tmp = lista->firstNode;
						next = tmp->XOR;
					}else if (tmp == lista->lastNode) {
						delete_end(lista);
						tmp = NULL;
					}else {
						node* t = tmp;
						prev->XOR = XOR(XOR(prev->XOR, t), next);
						next->XOR = XOR(XOR(next->XOR, t), prev);
						tmp = next;
						delete t;
						next = XOR(tmp->XOR, prev);
					}
				}else {
					if (tmp != lista->lastNode) {
						go_over(&tmp, &prev);
						next = XOR(tmp->XOR, prev);
					}else {
						tmp = NULL;
					}
				}
			}
		}
		
	}
}


//WYPISYWANIE WĘZŁA (aktualny, następnik, poprzednik)
void actual(list* lista) {
	if (lista->actual != NULL) {
		cout << lista->actual->n << endl;
	}else {
		cout << "NULL\n";
	}
	
}

void next(list* lista) {
	if (lista->actual != NULL) {
		node* tmp = lista->actual;
		if (lista->actual == lista->lastNode) {
			lista->actual = lista->firstNode;
			lista->next = lista->actual->XOR;
			lista->prev = NULL;
		}else {
			lista->actual = lista->next;
			lista->next = XOR(lista->actual->XOR, tmp);
			lista->prev = tmp;
		}
		cout << lista->actual->n << endl;
	}else {
		cout << "NULL\n";
	}
	
}

void prev(list* lista) {
	if (lista->actual != NULL) {
		node* tmp = lista->actual;
		if (lista->actual == lista->firstNode) {
			lista->actual = lista->lastNode;
			lista->prev = lista->actual->XOR;
			lista->next = NULL;
		}else {
			lista->actual = lista->prev;
			lista->prev = XOR(lista->actual->XOR, tmp);
			lista->next = tmp;
		}
		cout << lista->actual->n << endl;
	}else {
		cout << "NULL\n";
	}
}


//WYPISYWANIE LISTY (od przodu, od końca)
void print_forward(node* firstNode) {
	if (firstNode != NULL) {
		node* prev = NULL;
		node* tmp = firstNode;
	
		while (tmp != NULL) {
			cout << tmp->n << " ";
			go_over(&tmp, &prev);
		}
	}else {
		cout << "NULL\n";
	}
	
	cout << endl;
}

void print_backward(node* lastNode) {
	if (lastNode != NULL) {
		node* tmp = lastNode;
		node* next = NULL;
		while (tmp != NULL) {
			cout << tmp->n << " ";
			go_over(&tmp, &next);
		}
	}else{
		cout << "NULL\n";
	}
	
	cout << endl;
}


//WYBIERANIE ODPOWIEDNIEJ FUNKCJONALNOŚCI
void ster(list* lista, char *komenda) {
	int n;
	if (strcmp(komenda, "ACTUAL") == 0) {
		actual(lista);
	}else if (strcmp(komenda, "NEXT") == 0) {
		next(lista);
	}else if (strcmp(komenda, "PREV") == 0) {
		prev(lista);
	}else if (strcmp(komenda, "ADD_BEG") == 0) {
		cin >> n;
		add_beg(lista, n);
	}else if (strcmp(komenda, "ADD_END") == 0) {
		cin >> n;
		add_end(lista, n);
	}else if (strcmp(komenda, "ADD_ACT") == 0) {
		cin >> n;
		add_act(lista, n);
	}else if (strcmp(komenda, "PRINT_FORWARD") == 0) {
		print_forward(lista->firstNode);
	}else if (strcmp(komenda, "PRINT_BACKWARD") == 0) {
		print_backward(lista->lastNode);
	}else if (strcmp(komenda, "DEL_BEG") == 0) {
		delete_beg(lista);
	}else if (strcmp(komenda, "DEL_END") == 0) {
		delete_end(lista);
	}else if (strcmp(komenda, "DEL_ACT") == 0) {
		delete_act(lista);
	}else if (strcmp(komenda, "DEL_VAL") == 0) {
		cin >> n;
		delete_val(lista, n);
	}
}

int main() {
	char komenda[MAX_INPUT_LENGTH];
	list *lista = new list;
	while (cin >> komenda) {
		ster(lista, komenda);
	}
	return 0;
}
