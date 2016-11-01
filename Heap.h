#include "List.h"


template <class H>
class Heap {
	private:
		List<H>* list;
	public:
		void addElement(H element);
		H removeElement();
		bool isEmpty();
		H seeFirstElement();
};

template <class H> void Heap<H>::addElement(H element) {
	list->addNewElement(element);
}

template <class H> H Heap<H>::removeElement() {
	H value = list->getElement(0);
	list->removeElement(0);
	return value;
}

template <class H> bool Heap<H>::isEmpty() {
	return (list->getAmountOfElements() == 0);
}

template <class H> H Heap<H>::seeFirstElement() {
	return (list->getFirst());
}
