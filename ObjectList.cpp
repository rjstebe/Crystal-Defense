#include "LogManager.h"
#include "ObjectList.h"

// Default constructor.
df::ObjectList::ObjectList() {
	m_p_obj = (Object**)malloc(sizeof(Object*));
}

// Free array if memory is allocated to it.
df::ObjectList::~ObjectList() {
	if (m_p_obj != NULL) {
		free(m_p_obj);
	}
}

// Deep copy the list when copying.
df::ObjectList::ObjectList(const ObjectList& other) {
	m_p_obj = (Object**)malloc(sizeof(Object*) * other.max_count);
	if (m_p_obj == NULL) {
		LM.writeLog("ObjectList::ObjectList(const ObjectList& other): out of memory (could not allocate memory for copy)");
	}
	else {
		memcpy(m_p_obj, other.m_p_obj, sizeof(Object*) * other.max_count);
		max_count = other.max_count;
		m_count = other.m_count;
	}
}

// Deep copy the list when assigning.
df::ObjectList& df::ObjectList::operator=(const ObjectList& rhs) {
	// If both ObjectList's are the same, return it
	if (&rhs == this) {
		return *this;
	}

	// If this was already initialized, free its memory
	if (m_p_obj != NULL) {
		free(m_p_obj);
	}

	// Copy data from rhs to *this or return null list
	m_p_obj = (Object**)malloc(sizeof(Object*) * rhs.max_count);
	if (m_p_obj == NULL) {
		LM.writeLog("ObjectList::ObjectList(const ObjectList& other): out of memory (could not allocate memory for copy)");
		ObjectList nullList = ObjectList();
		return nullList;
	}
	else {
		memcpy(m_p_obj, rhs.m_p_obj, sizeof(Object*) * rhs.max_count);
		max_count = rhs.max_count;
		m_count = rhs.m_count;
	}

	return *this;
}

// Insert object pointer in list.
// Return 0 if ok, else -1.
int df::ObjectList::insert(Object* p_o) {
	LM.writeLog(-20, "df::ObjectList::insert(): Adding Object with id: %d to ObjectList", p_o->getId());
	// If there is no space for another object, double the allocated space.
	if (isFull()) {
		LM.writeLog(-20, "df::ObjectList::insert(): ObjectList is full, allocating more memory");
		Object** p_temp_obj;
		p_temp_obj = (Object**)realloc(m_p_obj, 2 * sizeof(Object*) * max_count);
		// If space cannot be doubled, return -1.
		if (p_temp_obj == NULL) {
			LM.writeLog("df::ObjectList::insert(): Could not allocate more memory");
			return -1;
		}
		m_p_obj = p_temp_obj;
		max_count *= 2;
	}
	// Since there is space for another object,
	// Add it to the end of the list, and increment count.
	m_p_obj[m_count] = p_o;
	m_count++;
	return 0;
}

// Remove object pointer from list.
// Return 0 if found, else -1.
int df::ObjectList::remove(Object* p_o) {
	LM.writeLog(-20, "df::ObjectList::insert(): Removing Object with id: %d from ObjectList", p_o->getId());
	// Iterate over objects.
	for (int i = 0; i < m_count; i++) {
		// If object is found, free it, decrement count,
		// and fill space with last element.
		if (m_p_obj[i]->getId() == p_o->getId()) {
			m_count--;
			m_p_obj[i] = m_p_obj[m_count];
			return 0;
		}
	}
	LM.writeLog(100, "df::ObjectList::insert(): Given Object does not exist in this ObjectList");
	return -1;
}

// Clear list (setting count to 0).
void df::ObjectList::clear() {
	m_count = 0;
}

// Return count of number of objects in list.
int df::ObjectList::getCount() const {
	return m_count;
}

// Return true if list is empty, else false.
bool df::ObjectList::isEmpty() const {
	return m_count == 0;
}

// Return true if list is full, else false.
bool df::ObjectList::isFull() const {
	return m_count >= max_count;
}

// Add two lists, second appended to first.
df::ObjectList df::ObjectList::operator+(df::ObjectList list) {
	// Start with first list.
	ObjectList big_list = *this;

	// Iterate through second list, adding each element.
	ObjectListIterator li(&list);
	for (li.first(); !li.isDone(); li.next()) {
		// Add element from second, to first list.
		big_list.insert(li.currentObject());
	}

	// Return combined list.
	return big_list;
}
