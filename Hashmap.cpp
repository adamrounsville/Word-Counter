#include "Hashmap.h"

Hashmap::Hashmap() {
	mapSize = 0;
	
	for (int i = 0; i < BUCKETS; i++) {
		buckets[i] = NULL;
	}
};

Hashmap::~Hashmap() {
	clear();
};

void Hashmap::insert(string key, int value) {
	int& valptr = at(key);
	valptr = value;
};

bool Hashmap::contains(string key) const {
	return true;
};

int Hashmap::get(string key) const {
	 return 0;
};

int& Hashmap::operator [](string key) {
	return at(key);
};

int& Hashmap::at(string name) {
	int hashval = hash(name); // Compute the hash value for this name, for now assume it is 0
	Node *ptr = buckets[hashval];
	
	while (ptr != NULL) {
		if (name == ptr->key) { // We found it
			break;
		} else {
			ptr = ptr->next;
		}
	}
	
	if (ptr == NULL) { // We need to create a new node, put it on the front of the list
		ptr = new Node;
		ptr->next = buckets[hashval];
		buckets[hashval] = ptr;
		ptr->key = name;

		if (ptr->next) {
			ptr->next->prev = ptr; // Connect the previous node
		}
	}
	
	return(ptr->value);
};

bool Hashmap::remove(string key) {
	unsigned int bucket = hash(key);
	Node* current = buckets[bucket];

	while ((current != NULL) && (current->key != key)) {
		current = current->next;
	}

	if (current == NULL) {
		return false;
	} else {
		if (current->next != NULL) {
			current->next->prev = current->prev;
		}
		
		if (current->prev == NULL) {
			buckets[bucket] = current->next;
		} else {
			current->prev->next = current->next;
		}
				
		delete current;
		
		return true;
	}
};

void Hashmap::clear() {
	
};

string Hashmap::toString() const {
	stringstream ss;

	for (int i = 0; i < BUCKETS; i++) {
		Node* head = buckets[i];

		if (head == NULL) { // There is nothing in the hash bucket
			ss << "[" << i << "]" << endl;
		} else { // There is something in the hash bucket
			Node* current = head;
			ss << "[" << i << "]";

			while (current != NULL) {
				ss << current->key << " => " << current->value;

				if (current->next != NULL) {
					ss << ", ";
				}

				current = current->next;
			}

			ss << endl;
		}
	}

	return ss.str();
};

int Hashmap::size() const {
	return mapSize;
};

string Hashmap::toSortedString() const {
	stringstream ss;
  priority_queue<Node*, vector<Node*>, NodeCompare> nodeHeap;

  for (int i = 0; i < BUCKETS; i++) {
		Node* current = buckets[i];

		while (current != NULL) {
			nodeHeap.push(current);
			current = current->next;
		}
  }
  
	while (!nodeHeap.empty()) {
    Node* top = nodeHeap.top(); // Get top node (next node in sorted order)
    ss << top->key << " => " << top->value << endl; // Add node data to stringstream
    nodeHeap.pop(); // Pop it off
  }
	
  return ss.str();
};

unsigned int Hashmap::hash(string key) const {
	unsigned int hashCode = 0;

	for (int i = 0; i < key.length(); i++) {
		hashCode = (hashCode * 31) + key.at(i);
	}

	return hashCode % BUCKETS;
}
