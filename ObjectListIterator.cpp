#include "ObjectListIterator.h"

// Create iterator, over indicated list.
df::ObjectListIterator::ObjectListIterator(const ObjectList* p_l) {
	m_p_list = p_l;
}

// Set iterator to first item in list.
void df::ObjectListIterator::first() {
	m_index = 0;
}

// Set iterator to next item in list.
void df::ObjectListIterator::next() {
	if (m_index < m_p_list->getCount()) {
		m_index++;
	}
}

// Return true if at end of list.
bool df::ObjectListIterator::isDone() const {
	return m_index >= m_p_list->getCount();
}

// Return pointer to current object, NULL if done/empty.
df::Object* df::ObjectListIterator::currentObject() const {
	if (isDone()) {
		return NULL;
	}
	return m_p_list->m_p_obj[m_index];
}
