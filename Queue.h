#ifndef QUEUE_H_
#define QUEUE_H_

#ifndef NULL
#define NULL 0
#endif

#include "Node.h"

template<class Q> class Queue {

private:
	unsigned int amountOfElements;
	Node<Q>* entryNode;
	Node<Q>* outputNode;

public:
	/*
	 * Pre: ---
	 * Post: Crea una cola vacia.
	 */
	Queue();

	/*
	 * Pre: ---
	 * Post: Devuelve el puntero "entryNode".
	 */
	Node<Q>* getEntry();

	/*
	 * Pre: ---
	 * Post: Devuelve el puntero "outputNode".
	 */
	Node<Q>* getOutput();

	/*
	 * Pre: "newElement" es un elemento valido.
	 * Post: Inserta el elemento "newElement" al final de la cola y queda apuntado por "entryNode"
	 *       y aumenta la cantidad de elementos de la cola ("amounOfElements") en 1.
	 */
	void addNewElement(Q* newElement);

	/*
	 * Pre: La cola "Queue" no esta vacia.
	 * Post: Borra el nodo apuntado por el puntero "outputNode" de la cola
	 *       y reduce la cantidad de elementos de la cola ("amountOfElements") en 1.
	 *       Devuelve un puntero hacia el elemento eliminado.
	 */
	Q* removeElement();

	/*
	 * Pre: ---
	 * Post: Devuelve la cantidad de elementos en la cola ("amountOfElements").
	 */
	unsigned int getAmountOfElements();

	/*
	 * Pre: ---
	 * Post: Devuelve TRUE si la cola se encuentra vacia o FALSE en el caso contrario.
	 */
	bool isEmpty();

	/*
	 * Pre: ---
	 * Post: Libera la memoria.
	 */
	~Queue();
};

template<class Q> Queue<Q>::Queue() {
	this->amountOfElements = 0;
	this->entryNode = NULL;
	this->outputNode = NULL;
}

template<class Q> Node<Q>* Queue<Q>::getEntry() {
	return this->entryNode;
}

template<class Q> Node<Q>* Queue<Q>::getOutput() {
	return this->outputNode;
}

template<class Q> void Queue<Q>::addNewElement(Q* newElement) {
	Node<Q>* newNode = new Node<Q>(newElement);
	if (isEmpty()) {
		this->outputNode = newNode;
	} else {
		this->entryNode->changeNextNode(newNode);
	}
	this->entryNode = newNode;
	this->amountOfElements++;
}

template<class Q> Q* Queue<Q>::removeElement() {
	Node<Q>* deletedNode = this->outputNode;
	this->outputNode = deletedNode->getNextNode();
	this->amountOfElements--;
	return deletedNode;
}

template<class Q> unsigned int Queue<Q>::getAmountOfElements() {
	return this->amountOfElements;
}

template<class Q> bool Queue<Q>::isEmpty() {
	return (amountOfElements == 0);
}

template<class Q> Queue<Q>::~Queue() {
	while (this->outputNode != NULL) {
		removeElement();
	}
}

#endif /* QUEUE_H_ */
