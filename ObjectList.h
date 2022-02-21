#pragma once

#include "Object.h"
#include "ObjectListIterator.h"

namespace df {

const int MAX_COUNT_INIT = 1;

class ObjectListIterator;

class ObjectList {
private:
	int m_count = 0;                // Count of objects in list.
	int max_count = MAX_COUNT_INIT; // Initial list size(e.g. 1).
	Object** m_p_obj;               // Array of pointers to objects.
	
public:
	friend class ObjectListIterator;
	
	// Default constructor.
	ObjectList();

	// Free array if memory is allocated to it.
	~ObjectList();

	// Deep copy the list when copying.
	ObjectList(const ObjectList& other);

	// Deep copy the list when assigning.
	ObjectList& operator=(const ObjectList& rhs);
	
	// Insert object pointer in list.
	// Return 0 if ok, else -1.
	int insert(Object* p_o);
	
	// Remove object pointer from list.
	// Return 0 if found, else -1.
	int remove(Object* p_o);
	
	// Clear list (setting count to 0).
	void clear();
	
	// Return count of number of objects in list.
	int getCount() const;
	
	// Return true if list is empty, else false.
	bool isEmpty() const;
	
	// Return true if list is full, else false.
	bool isFull() const;

	// Add two lists, second appended to first.
	ObjectList operator+(df::ObjectList list);
};
	
}
