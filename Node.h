#ifndef NODE_H_
#define NODE_H_

#ifndef NULL
#define NULL 0
#endif

template<class N> class Node {
private:
	N element;
	Node<N>* nextNode;

public:
	/*
	 * Pre: ---
	 * Post: El nodo "Node" resulta inicializado con el elemento "element" dado y sin un nodo siguiente.
	 */
	Node(N element);

	/*
	 * Pre: ---
	 * Post: Devuelve el siguiente nodo "Node".
	 */
	Node<N>* getNextNode();

	/*
	 * Pre: ---
	 * Post: Devuelve el elemento que contiene el nodo.
	 */
	N getElement();

	/*
	 * Pre: ---
	 * Post: Cambia el nodo siguiente por el nodo "newNextNode".
	 */
	void changeNextNode(Node<N>* newNextNode);
};

template<class N> Node<N>::Node(N element) {
	this->element = element;
	this->nextNode = NULL;
}

template<class N> Node<N>* Node<N>::getNextNode() {
	return this->nextNode;
}

template<class N> N Node<N>::getElement() {
	return this->element;
}

template<class N> void Node<N>::changeNextNode(Node<N>* newNextNode) {
	this->nextNode = newNextNode;
}

#endif /* NODE_H_ */
