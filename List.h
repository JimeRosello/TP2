#ifndef LIST_H_
#define LIST_H_

#ifndef NULL
#define NULL 0
#endif

#include "Node.h"
#include <string>

template<class L> class List {

private:
	unsigned int amountOfElements;
	Node<L>* firstNode;
	Node<L>* cursor;

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
	 * Post: Devuelve el elemento del puntero "cursor".
	 */
	L getCursor();

	/*
	 * Pre: ---
	 * Post: Devuelve el elemento del puntero "firstNode".
	 */
	L getFirst();

	/*
	 * Pre: "newElement" es un elemento valido.
	 * Post: Inserta el elemento "newElement" al principio de la lista y aumenta la
	 *       cantidad de elementos de la lista ("amountOfElements") en 1.
	 */
	void addNewElement(L newElement);

	/*
	 * Pre: La lista "List" no esta vacia.
	 * Post: Borra el nodo siguiente al apuntado por el puntero "cursor" de la lista "List"
	 *       y reduce la cantidad de elementos de la lista ("amountOfElements") en 1. En
	 *       caso de que el cursor se encuentre en NULL, borrara el primer elemento de la lista.
	 *       Devuelve el elemento borrado.
	 */
	L removeNextElement();

	/*
	 * Pre: La lista "List" no esta vacia y el cursor apunta a algun nodo.
	 * Post: Devuelve el elemento dentro del nodo al que esta apuntando el cursor.
	 */
	L getElement();

	/*
	 * Pre: La lista "List" no esta vacia y hay un elemento despues del apuntado por el cursor.
	 * Post: Devuelve el elemento dentro del nodo siguiente del que esta apuntando por el cursor,
	 *       en caso de ser NULL devolvera el primer elemento de la lista.
	 */
	L getNextElement();

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
	 * Pre: La posicion pasada como parametro es valida.
	 * Post: Devuelve un puntero al nodo que se encuentra en la posicion pos.
	 */
	Node<L>* getNode(unsigned int pos);

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

template<class L> L List<L>::getCursor() {
	return this->cursor->getElement();
}

template<class L> L List<L>::getFirst() {
	return this->firstNode->getElement();
}

template<class L> void List<L>::addNewElement(L newElement) {
	Node<L>* newNode = new Node<L>(newElement);
	newNode->changeNextNode(firstNode);
	firstNode = newNode;
	initiateCursor();
	this->amountOfElements++;
}

template<class L> L List<L>::removeNextElement() {
	Node<L>* deletedNode = NULL;
	if (this->cursor == NULL) {
		deletedNode = this->firstNode;
		this->firstNode = deletedNode->getNextNode();
	} else if (this->cursor->getNextNode() != NULL){
		//if (this->cursor->getNextNode() == NULL) {
			//throw std::string("No hay mas elementos despues del cursor.");
		//}
		deletedNode = this->cursor->getNextNode();
		this->cursor->changeNextNode(deletedNode->getNextNode());
	}
	this->amountOfElements--;
	L element = deletedNode->getElement();
	delete deletedNode;
	initiateCursor();
	return element;
}

template<class L> L List<L>::getElement() {
	if (this->cursor == NULL) {
		throw std::string("El cursor no apunta a ningun elemento.");
	}
	return this->cursor->getElement();
}

template<class L> L List<L>::getNextElement() {
	L returningElement;
	if (this->cursor == NULL) {
		returningElement = this->firstNode->getElement();
	} else {
		if (this->cursor->getNextNode() == NULL) {
			throw std::string("No hay mas elementos despues del cursor.");
		}
		returningElement = this->cursor->getNextNode()->getElement();
	}
	return returningElement;
}

template<class L> unsigned int List<L>::getAmountOfElements() {
	return this->amountOfElements;
}

template<class L> bool List<L>::isEmpty() {
	return (amountOfElements == 0);
}

template<class L> List<L>::~List() {
	initiateCursor();
	while (!isEmpty()) {
		removeNextElement();
	}
}

#endif /* LIST_H_ */

