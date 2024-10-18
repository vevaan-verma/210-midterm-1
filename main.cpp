// COMSC-210 | Midterm #1 | Vevaan Verma
#include <iostream>
using namespace std;

/* CONSTANTS */
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {

private:
	struct Node {

		int data;
		Node* prev;
		Node* next;

		Node(int val, Node* p = nullptr, Node* n = nullptr) {

			data = val;
			prev = p;
			next = n;

		}
	};
	Node* head;
	Node* tail;

public:
	DoublyLinkedList() { head = nullptr; tail = nullptr; }

	// insert_after() inserts a new node after a specified position
	// arguments: int value - the value to insert, int position - the position to insert the value after
	// returns: void
	void insert_after(int value, int position) {

		// make sure position is actually a valid position (it must be >= 0)
		if (position < 0) {

			cout << "Position must be >= 0." << endl;
			return;

		}

		Node* newNode = new Node(value); // create new node with the passed value

		if (!head) { // if list is empty, set head and tail to the new node and return

			head = tail = newNode;
			return;

		}

		Node* temp = head; // create a temporary node to traverse the list and initialize it to the head

		for (int i = 0; i < position && temp; ++i) // traverse the list until the position is reached or the end of the list is reached
			temp = temp->next;

		if (!temp) { // make sure the position is valid (it is within the list); if not, print an error message, delete the new node, and return

			cout << "Position exceeds list size. Node not inserted.\n";
			delete newNode;
			return;

		}

		newNode->next = temp->next; // set the new node's next pointer to the current node's next pointer
		newNode->prev = temp; // set the new node's previous pointer to the current node

		// the two lines above basically insert the new node between the current node and the current node's next node
		// however, the nodes aren't completely linked yet

		if (temp->next) // if the current node has a next node, set the next node's previous pointer to the new node
			temp->next->prev = newNode;
		else // if the current node is the current tail, set the tail to the new node
			tail = newNode;

		temp->next = newNode; // finally, set the current node's next pointer to the new node

	}

	// delete_val() deletes the first occurrence of a value in the list
	// arguments: int value - the value to delete
	// returns: void
	void delete_val(int value) {

		if (!head) return; // make sure the list isn't empty

		Node* temp = head; // create a temporary node to traverse the list and initialize it to the head

		while (temp && temp->data != value) // traverse the list until the value is found or the end of the list is reached
			temp = temp->next;

		if (!temp) return; // if the value wasn't found, return

		if (temp->prev) // if the current node has a previous node, set the previous node's next pointer to the current node's next pointer
			temp->prev->next = temp->next;
		else // if the current node is the current head, set the head to the current node's next node
			head = temp->next;

		if (temp->next) // if the current node has a next node, set that node's previous pointer to the current node's previous pointer
			temp->next->prev = temp->prev;
		else // if the current node is the current tail, set the tail to the current node's previous node
			tail = temp->prev;

		delete temp; // delete the current node

	}

	// delete_pos() deletes a node at a specified position
	// arguments: int position - the position to delete the node at
	// returns: void
	void delete_pos(int pos) {

		if (!head) { // if the list is empty, print an error message and return

			cout << "List is empty." << endl;
			return;

		}

		if (pos == 1) { // if the position is 1, you can just pop the front of the list and return

			pop_front();
			return;

		}

		Node* temp = head; // create a temporary node to traverse the list and initialize it to the head

		for (int i = 1; i < pos; i++) { // traverse the list until the position is reached

			if (!temp) { // if the end of the list is reached before the position, print an error message and return

				cout << "Position doesn't exist." << endl;
				return;

			} else {

				temp = temp->next; // move to the next node

			}
		}

		if (!temp) { // if the position is invalid, print an error message and return

			cout << "Position doesn't exist." << endl;
			return;

		}

		if (!temp->next) { // if the node to delete is the tail, you can just pop the back of the list and return

			pop_back();
			return;

		}

		Node* tempPrev = temp->prev; // create a temporary node to store the previous node of the node to delete
		tempPrev->next = temp->next; // set the next pointer of the previous node to the next node of the node to delete
		temp->next->prev = tempPrev; // set the previous pointer of the next node of the node to delete to the stored previous node

		// now all pointers have been rerouted correctly, so the current node can be deleted

		delete temp; // delete the node

	}

	void push_back(int v) {

		Node* newNode = new Node(v); // create a new node with the passed value

		if (!tail) { // if the list is empty, set the head and tail to the new node

			head = tail = newNode;

		} else {

			tail->next = newNode; // set the current tail's next pointer to the new node
			newNode->prev = tail; // set the new node's previous pointer to the current tail
			tail = newNode; // set the tail to the new node

			// the code above adds the new node to the end of the list and moves the tail to this node to reflect this addition

		}
	}

	void push_front(int v) {

		Node* newNode = new Node(v); // create a new node with the passed value

		if (!head) { // if the list is empty, set the head and tail to the new node

			head = tail = newNode;

		} else {

			newNode->next = head; // set the new node's next pointer to the current head
			head->prev = newNode; // set the current head's previous pointer to the new node
			head = newNode; // set the head to the new node

			// the code above adds the new node to the front of the list and moves the head to this node to reflect this addition

		}
	}

	void pop_front() {

		if (!head) {

			cout << "List is empty." << endl;
			return;

		}

		Node* temp = head;

		if (head->next) {

			head = head->next;
			head->prev = nullptr;

		} else {

			head = tail = nullptr;

		}

		delete temp;

	}

	void pop_back() {

		if (!tail) {

			cout << "List is empty." << endl;
			return;

		}

		Node* temp = tail;

		if (tail->prev) {

			tail = tail->prev;
			tail->next = nullptr;

		} else {

			head = tail = nullptr;

		}

		delete temp;

	}

	~DoublyLinkedList() {

		while (head) {

			Node* temp = head;
			head = head->next;
			delete temp;

		}
	}

	void print() {

		Node* current = head;

		if (!current) {

			cout << "List is empty." << endl;
			return;

		}

		while (current) {

			cout << current->data << " ";
			current = current->next;

		}

		cout << endl;

	}

	void print_reverse() {

		Node* current = tail;

		if (!current) {

			cout << "List is empty." << endl;
			return;

		}

		while (current) {

			cout << current->data << " ";
			current = current->prev;

		}

		cout << endl;

	}
};

int main() {

	cout << MIN_NR + MIN_LS + MAX_NR + MAX_LS; // dummy statement to avoid compiler warning
	return 0;

}