#ifndef LIST_H_
#define LIST_H_

#ifndef NULL
#define NULL 0
#endif

#include "Node.h"

template<class L> class List {

private:
	unsigned int amountOfElements;
	Node<L>* firstNode;
	Node<L>* cursor;

	/*
	 * Pre: La lista "List" no esta vacia.
	 * Post: Quita el nodo siguiente al apuntado por el puntero "previousNode" de la lista "List"
	 *       (o el primero en caso de que "previousNode" sea NULL).
	 *       Devuelve un puntero nodo removido, sin liberar la memoria de este.
	 */
	Node<L>* getNextNode(Node<L>* previousNode);

public:
	/*
	 * Pre: ---
	 * Post: Crea una lista vacia.
	 */
	List();

	/*
	 * Pre: ---
	 * Post: Deja el cursor de la lista "List" preparado para hacer un nuevo recorrido sobre sus elementos.
	 */
	void initiateCursor();

	/*
	 * Pre: El cursor fue inicializado.
	 * Post: Devuelve TRUE si hay un nodo siguiente y deja al cursor sobre
	 *       dicho nodo, de otra forma devuelve FALSE.
	 */
	bool advanceCursor();

	/*
	 * Pre: ---
	 * Post: Devuelve el puntero "cursor".
	 */
	Node<L>* getCursor();

	/*
	 * Pre: ---
	 * Post: Devuelve el puntero "firstNode".
	 */
	Node<L>* getFirst();

	/*
	 * Pre: "newElement" es un elemento valido.
	 * Post: Inserta el elemento "newElement" al principio de la lista y aumenta la
	 *       cantidad de elementos de la lista ("amounOfElements") en 1.
	 */
	void addNewElement(L* newElement);

	/*
	 * Pre: La lista "List" no esta vacia.
	 * Post: Borra el nodo siguiente al apuntado por el puntero "previousNode" de la lista "List"
	 *       (o el primero en caso de que "previousNode" sea NULL) y reduce la cantidad de
	 *       elementos de la lista ("amountOfElements") en 1.
	 */
	void deleteNextNode(Node<L>* previousNode);

	/*
	 * Pre: La lista "List" no esta vacia.
	 * Post: Quita el nodo siguiente al apuntado por el puntero "previousNode" de la lista "List"
	 *       (o el primero en caso de que "previousNode" sea NULL) y reduce la cantidad de
	 *       elementos de la lista ("amountOfElements") en 1.
	 *       Devuelve un puntero al elemento del nodo eliminado, sin liberar la memoria de este.
	 */
	L* getPointerNextElement(Node<L>* previousNode);

	/*
	 * Pre: "readingNode" es un puntero a un nodo Node que se encuentra en la lista "List", en caso
	 *      de no indicarse ninguno se tomara la ubicacion del cursor.
	 * Post: Devuelve el elemento dentro del nodo al que se esta apuntando, en caso de no mandar un
	 *       puntero por parametro se tomara al puntero "cursor".
	 */
	L getElement(Node<L>* readingNode = NULL);

	/*
	 * Pre: ---
	 * Post: Devuelve la cantidad de elementos en la lista ("amountOfElements").
	 */
	unsigned int getAmountOfElements();

	/*
	 * Pre: ---
	 * Post: Devuelve TRUE si la lista se encuentra vacia o FALSE en el caso contrario.
	 */
	bool isEmpty();

	/*
	 * Pre: ---
	 * Post: Libera la memoria.
	 */
	~List();
};

template<class L> List<L>::List() {
	this->amountOfElements = 0;
	this->firstNode = NULL;
	this->cursor = NULL;
}

template<class L> void List<L>::initiateCursor() {
	this->cursor = NULL;
}

template<class L> bool List<L>::advanceCursor() {
	if (this->cursor == NULL) {
		this->cursor = this->firstNode;
	} else {
		this->cursor = this->cursor->getNextNode();
	}
	return (this->cursor != NULL);
}

template<class L> Node<L>* List<L>::getCursor() {
	return this->cursor;
}

template<class L> Node<L>* List<L>::getFirst() {
	return this->firstNode;
}

template<class L> void List<L>::addNewElement(L* newElement) {
	Node<L>* newNode = new Node<L>(newElement);
	newNode->changeNextNode(firstNode);
	firstNode = newNode;
	this->initiateCursor();							//Para reiniciar el cursor.
	this->amountOfElements++;
}

template<class L> Node<L>* List<L>::getNextNode(Node<L>* previousNode) {
	Node<L>* deletedNode;
	if (previousNode == NULL) {
		deletedNode = this->firstNode;
		this->firstNode = deletedNode->getNextNode();
	} else {
		deletedNode = previousNode->getNextNode();
		previousNode->changeNextNode(deletedNode->getNextNode());
	}
	this->initiateCursor();							//Para reiniciar el cursor.
	this->amountOfElements--;
	return deletedNode;
}

template<class L> void List<L>::deleteNextNode(Node<L>* previousNode) {
	delete (this->getNextNode(previousNode));
}

template<class L> L* List<L>::getPointerNextElement(Node<L>* previousNode) {
	Node<L>* removedNode = this->getNextNode(previousNode);
	L cellphone = removedNode->getElement();
	return &cellphone;
}

template<class L> L List<L>::getElement(Node<L>* readingNode) {
	if (readingNode == NULL) {
		readingNode = this->cursor;
	}
	return (readingNode->getElement());
}

template<class L> unsigned int List<L>::getAmountOfElements() {
	return this->amountOfElements;
}

template<class L> bool List<L>::isEmpty() {
	return (amountOfElements == 0);
}

template<class L> List<L>::~List() {
	while (this->firstNode != NULL) {
		deleteNextNode(NULL);
	}
}

#endif /* LIST_H_ */
