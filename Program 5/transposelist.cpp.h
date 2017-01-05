
template<class Object>
int TransposeList<Object>::find(const Object &obj) {
	DListNode<Object> *found = DList<Object>::header->next;

	int i = 0;
	for (; found != NULL && found->item != obj; found = found->next, ++i)
		++DList<Object>::cost;

	if (found == NULL)
		return -1; // not found

	if (found == DList<Object>::header->next)
		return 0;  // no need to swap

				   // remove found from the current position
				   // insert found before previous
	found->prev->next = found->next;
	if (found->next != NULL)
	found->next->prev = found->prev;
	found->next = found->prev;
	found->prev = found->prev->prev;
	found->prev->next = found;
	found->next->prev = found;

	return i;
}