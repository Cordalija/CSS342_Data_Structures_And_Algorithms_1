// Jasenko.Cordalija CS.342 Program.5


#include <stdlib.h>
template<class Object>
SList<Object>::SList() {
	init();
}

template<class Object>
SList<Object>::SList(const SList &rhs) {
	init();
	*this = rhs;                                   // then assign rhs to this.
}

template<class Object>
void SList<Object>::init() {
	for (int i = 0; i < LEVEL; i++) {  // for each level
									   // create the left most dummy nodes;
		header[i] = new SListNode<Object>;
		header[i]->prev = NULL;
		header[i]->down = (i > 0) ? header[i - 1] : NULL;
		header[i]->up = NULL;
		if (i > 0) header[i - 1]->up = header[i];

		// create the right most dummy nodes;
		header[i]->next = new SListNode<Object>;
		header[i]->next->next = NULL;
		header[i]->next->prev = header[i];
		header[i]->next->down = (i > 0) ? header[i - 1]->next : NULL;
		header[i]->next->up = NULL;
		if (i > 0) header[i - 1]->next->up = header[i]->next;
	}

	// reset cost.
	cost = 0;
}

template<class Object>
SList<Object>::~SList() {
	clear();                                      // delete items starting 1st
	for (int i = 0; i < LEVEL; i++) {
		delete header[i]->next;                      // delete the right most dummy
		delete header[i];                            // delete the left most dummy
	}
}

template<class Object>
bool SList<Object>::isEmpty() const {
	return (header[0]->next->next == NULL);
}

template<class Object>
int SList<Object>::size() const {
	SListNode<Object> *p = header[0]->next; // at least the right most dummy
	int size = 0;

	for (; p->next != NULL; p = p->next, ++size);
	return size;
}

template<class Object>
void SList<Object>::clear() {
	for (int i = 0; i < LEVEL; i++) {        // for each level
		SListNode<Object> *p = header[i]->next;  // get the 1st item 
		while (p->next != NULL) {              // if this is not the left most
			SListNode<Object> *del = p;
			p = p->next;                           // get the next item
			delete del;                            // delete the current item
		}

		header[i]->next = p;                     // p now points to the left most 
	}                                          // let the right most point to it
}

template<class Object>
void SList<Object>::insert(const Object &obj) {
	// right points to the level-0 item before which a new object is inserted.
	SListNode<Object> *right = searchPointer(obj);
	SListNode<Object> *up = NULL;

	if (right->next != NULL && right->item == obj) 
		// there is an identical object
		return;
	
	// Implement the rest by yourself /////////////////////////////////////////
		// new node newN created and inserted at level 0
		SListNode<Object> *newN = new SListNode<Object>;
		newN->item = obj; // new Node item is obj
		newN->up = NULL;
		newN->down = NULL; // at level 0 up and down null
		newN->next = right;
		newN->prev = right->prev; // newN's right and left connected
		newN->prev->next = newN; // newN's prev points to newN, connected
		right->prev = newN; // newN's next is right which point its prev to newN

		int lv = 1; // once done with level 0 goes up to level 1, the next level
		while(rand() % 2){
			if( lv < LEVEL) { // 50 % of newN going to next level only until before FINAL level 6

			up = right->prev; // rights previous is the newN that was inserted which if choosen goes up to next level

			while(!up->up) { // continues to move left until one left goes up
				up = up->prev;
			}

			up = up->up; // goes up
			up = up->next; // once it goes up moves next (right) to add new node

			newN = new SListNode<Object>;
			newN->item = obj; // again newN's item is obj like before and inserts it before up

			newN->next = up;
			newN->prev = up->prev; // inserted newN's prev is up's previous
			newN->prev->next = newN; // connects newN's previous to newN
			up->prev = newN; // connects ups prev to newN
			up->prev->down = right->prev;
			up->prev->down->up = up->prev; // below ups previous point up is ups previous
			right = up; // now the right is up

			lv++; // increments to move one level up, after 1 to 2, after 2 to 3, 
			      // and on but only until 5 due to second while loop lv < LEVEL
		}
	}
}

template<class Object>
bool SList<Object>::find(const Object &obj) {
	// p oints to the level-0 item close to a given object
	SListNode<Object> *p = searchPointer(obj);

	return (p->next != NULL && p->item == obj);     // true if obj was found
}

template<class Object>
SListNode<Object> *SList<Object>::searchPointer(const Object &obj) {
	SListNode<Object> *p = header[LEVEL - 1];     // start from the top left
	while (p->down != NULL) {                   // toward level 0
		p = p->down;                                // shift down once
		cost++;

		if (p->prev == NULL) {                    // at the left most item
			if (p->next->next == NULL)              // no intermediate items
				continue;
			else {                                    // some intermadiate items
				if (p->next->item <= obj)             // if 1st item <= obj
					p = p->next;                          // shift right to item 1
				cost++;
			}
		}

		while (p->next->next != NULL && p->next->item <= obj) {
			// shift right through intermediate items as far as the item value <= obj
			p = p->next;
			cost++;
		}
	}

	// now reached the bottom. shift right once if the current item < obj
	if (p->prev == NULL || p->item < obj) {
		p = p->next;
		cost++;
	}
	return p; // return the pointer to an item >= a given object.
}

template<class Object>
void SList<Object>::remove(const Object &obj) {
	// p points to the level-0 item to delete
	SListNode<Object> *p = searchPointer(obj);

	// validate if p is not the left most or right most and exactly contains the
	// item to delete
	if (p->prev == NULL || p->next == NULL || p->item != obj)
		return;

	// Implement the rest by yourself /////////////////////////////////////////

		p->next->prev = p->prev; // connects p's next to point to p's previous
		p->prev->next = p->next; // connect p's previous to point to p's next

		if (p->up) { //  moves up, but only if there is also a node above it 
			p = p->up; // now the above p is p
			delete p->down; // now deletes the p below when climbing
		}

		else {
			delete p; // if there is not above p, just go straight to deleting p
		}
		while (p->up) { //  while there is a p, for further levels 1+, and it is going up, this moves through levels
			p->next->prev = p->prev; // repeats connecting p's previous and next with eachother
			p->prev->next = p->next;

			if (p->up) { // again if p can go up like earlier
				p = p->up; // above p is now the p
				delete p->down; // deletes the before p after climbing up
			}

			else {
				delete p; // as before if it cant go up, then just delete current p
			}
		}
}

template<class Object>
const SList<Object> &SList<Object>::operator=(const SList &rhs) {
	if (this != &rhs) { // avoid self-assignment
		clear();           // deallocate old items

		int index;
		SListNode<Object> *rnode;
		for (index = 0, rnode = rhs.header[0]->next; rnode->next != NULL;
		rnode = rnode->next, ++index)
			insert(rnode->item);

		cost = rhs.cost;
	}
	return *this;
}

template<class Object>
int SList<Object>::getCost() const {
	return cost;
}

template<class Object>
void SList<Object>::show() const {
	cout << "contents:" << endl;
	for (SListNode<Object> *col = header[0]; col != NULL; col = col->next) {
		SListNode<Object> *row = col;
		for (int level = 0; row != NULL && level < LEVEL; level++) {
			if (row->prev == NULL)
				cout << "-inf\t";
			else if (row->next == NULL)
				cout << "+inf\t";
			else
				cout << row->item << "\t";
			row = row->up;
		}
		cout << endl;
	}
}
