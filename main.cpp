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
	// constructor
	DoublyLinkedList() { head = nullptr; tail = nullptr; }

	// insert_after() inserts a new node after a specified position
	// arguments: int value - the value to insert, int position - the position to insert the value after
	// returns: void
	void insert_after(int value, int position) {

		// make sure position is actually a valid position (it must be >= 0) (because nothing can be inserted at a negative position)
		if (position < 0) {

			cout << "Position must be >= 0." << endl;
			return;

		}

		Node* newNode = new Node(value); // create new node with the passed value

		if (!head) { // if list is empty (meaning there's nothing to insert after)

			head = tail = newNode; // set head and tail to the new node and return
			return;

		}

		Node* temp = head; // create a temporary node to traverse the list and initialize it to the head

		for (int i = 0; i < position && temp; ++i) // traverse the list until the position is reached or the end of the list is reached
			temp = temp->next;

		if (!temp) { // if the position is invalid (it is out of the list's bounds)

			cout << "Position exceeds list size. Node not inserted.\n"; // print an error message
			delete newNode; // delete the new node to free up memory and return
			return;

		}

		newNode->next = temp->next; // set the new node's next pointer to the current node's next pointer
		newNode->prev = temp; // set the new node's previous pointer to the current node

		// the two lines above basically insert the new node between the current node and the current node's next node
		// however, the nodes aren't completely linked yet

		if (temp->next) // if the current node has a next node
			temp->next->prev = newNode; // set the next node's previous pointer to the new node
		else // if the current node is the current tail
			tail = newNode; // set the tail to the new node

		temp->next = newNode; // finally, set the current node's next pointer to the new node

	}

	// delete_val() deletes the first occurrence of a value in the list
	// arguments: int value - the value to delete
	// returns: void
	void delete_val(int value) {

		if (!head) return; // make sure the list isn't empty (because if it is empty, there's nothing to delete)

		Node* temp = head; // create a temporary node to traverse the list and initialize it to the head

		while (temp && temp->data != value) // traverse the list until the value is found or the end of the list is reached
			temp = temp->next;

		if (!temp) return; // if the value wasn't found, return

		if (temp->prev) // if the current node has a previous node
			temp->prev->next = temp->next; // set the previous node's next pointer to the current node's next pointer
		else // if the current node is the current head
			head = temp->next; // set the head to the current node's next node

		if (temp->next) // if the current node has a next node
			temp->next->prev = temp->prev; // set the next node's previous pointer to the current node's previous pointer
		else // if the current node is the current tail
			tail = temp->prev; // set the tail to the current node's previous node

		delete temp; // delete the current node

	}

	// delete_pos() deletes a node at a specified position
	// arguments: int position - the position to delete the node at
	// returns: void
	void delete_pos(int pos) {

		if (!head) { // if the list is empty (meaning there's nothing to delete)

			cout << "List is empty." << endl; // print an error message and return
			return;

		}

		if (pos == 1) { // if the position is 1 (which means the head should be deleted)

			pop_front(); // you can just pop the front of the list and return (as the head will be deleted) and return
			return;

		}

		Node* temp = head; // create a temporary node to traverse the list and initialize it to the head

		for (int i = 1; i < pos; i++) { // traverse the list until the position is reached

			if (!temp) { // if the end of the list is reached before the position

				cout << "Position doesn't exist." << endl; // print an error message and
				return;

			} else {

				temp = temp->next; // move to the next node

			}
		}

		if (!temp) { // if the current node's position is invalid

			cout << "Position doesn't exist." << endl; // print an error message and return
			return;

		}

		if (!temp->next) { // if the node to delete is the tail

			pop_back(); // you can just pop the back of the list and return (as the tail will be deleted)
			return;

		}

		Node* tempPrev = temp->prev; // create a temporary node to store the previous node of the node to delete
		tempPrev->next = temp->next; // set the next pointer of the previous node to the next node of the node to delete
		temp->next->prev = tempPrev; // set the previous pointer of the next node of the node to delete to the stored previous node

		// now all pointers have been rerouted correctly, so the current node can be deleted

		delete temp; // delete the node

	}

	// push_back() adds a new node to the end of the list
	// arguments: int v - the value to add to the list
	// returns: void
	void push_back(int v) {

		Node* newNode = new Node(v); // create a new node with the passed value

		if (!tail) { // if the list is empty

			head = tail = newNode; // set the head and tail to the new node

		} else {

			tail->next = newNode; // set the current tail's next pointer to the new node
			newNode->prev = tail; // set the new node's previous pointer to the current tail
			tail = newNode; // set the tail to the new node

			// the code above adds the new node to the end of the list and moves the tail to this node to reflect this addition

		}
	}

	// push_front() adds a new node to the front of the list
	// arguments: int v - the value to add to the list
	// returns: void
	void push_front(int v) {

		Node* newNode = new Node(v); // create a new node with the passed value

		if (!head) { // if the list is empty

			head = tail = newNode; // set the head and tail to the new node

		} else {

			newNode->next = head; // set the new node's next pointer to the current head
			head->prev = newNode; // set the current head's previous pointer to the new node
			head = newNode; // set the head to the new node

			// the code above adds the new node to the front of the list and moves the head to this node to reflect this addition

		}
	}

	// pop_front() removes the first node in the list
	// arguments: none
	// returns: void
	void pop_front() {

		if (!head) { // if the list is empty, print an error message and return (as nothing can be popped)

			cout << "List is empty." << endl;
			return;

		}

		Node* temp = head; // create a temporary node to store the current head

		if (head->next) { // if the head has a next node (meaning there is more than one element in the list)

			head = head->next; // set the head to the next node
			head->prev = nullptr; // set the new head's previous pointer to null (as it is now the first node in the list)

		} else { // if the head is the only node in the list (meaning the list will be empty after pop)

			head = tail = nullptr; // set the head and tail to null

		}

		delete temp; // delete the old head to free up memory

	}

	// pop_back() removes the last node in the list
	// arguments: none
	// returns: void
	void pop_back() {

		if (!tail) { // if the list is empty (meaning there's nothing to pop)

			cout << "List is empty." << endl; // print an error message and return
			return;

		}

		Node* temp = tail; // create a temporary node to store the current tail

		if (tail->prev) { // if the tail has a previous node (meaning there is more than one element in the list)

			tail = tail->prev; // set the tail to the previous node
			tail->next = nullptr; // set the new tail's next pointer to null (as it is now the last node in the list)

		} else { // if the tail is the only node in the list (meaning the list will be empty after pop)

			head = tail = nullptr; // set the head and tail pointers to null

		}

		delete temp; // delete the old tail to free up memory

	}

	// ~DoublyLinkedList() is the destructor for the DoublyLinkedList class that deletes all nodes in the list
	// arguments: none
	// returns: void
	~DoublyLinkedList() {

		while (head) { // while there are still nodes in the list

			Node* temp = head; // create a temporary node to store the current head
			head = head->next; // set the head to the next node
			delete temp; // delete the old head

			// this process will continue until the head is null (meaning all nodes have been deleted)

		}
	}

	// print() prints the list from head to tail
	// arguments: none
	// returns: void
	void print() {

		Node* current = head; // create a temporary node to traverse the list and initialize it to the head

		if (!current) { // if the list has no elements

			cout << "List is empty." << endl; // print an error message and return
			return;

		}

		while (current) { // loop while there are still nodes in the list

			cout << current->data << " "; // print the current node's data
			current = current->next; // move to the next node

		}

		cout << endl; // print a new line at the end for formatting purposes

	}

	// print_reverse() prints the list from tail to head
	// arguments: none
	// returns: void
	void print_reverse() {

		Node* current = tail; // create a temporary node to traverse the list and initialize it to the tail

		if (!current) { // if the list has no elements

			cout << "List is empty." << endl; // print an error message and return
			return;

		}

		while (current) { // loop while there are still nodes in the list

			cout << current->data << " "; // print the current node's data
			current = current->prev; // move to the previous node

		}

		cout << endl; // print a new line at the end for formatting purposes

	}

	// avoid_every_other_element() prints every other element in the list
	// arguments: none
	// returns: void
	void every_other_element() {

		Node* current = head; // create a temporary node to traverse the list and initialize it to the head

		if (!current) { // if the list has no elements (meaning there's nothing to print)

			cout << "List is empty." << endl; // print an error message and return
			return;

		}

		while (current) { // loop while there are still nodes in the list

			cout << current->data << " "; // print the current node's data

			if (current->next) // if the current node has a next node
				current = current->next->next; // move to the next, next node
			else // if the current node is the tail
				break; // break the loop as there are no more nodes to print

		}

		cout << endl; // print a new line at the end for formatting purposes

	}
};

// main() is the entry point of the program and tests the DoublyLinkedList class
// arguments: none
// returns: int - the exit code of the program
int main() {

	DoublyLinkedList list; // create a new DoublyLinkedList object

	// populate the list with some values for testing
	list.insert_after(10, 0);
	list.insert_after(20, 1);
	list.insert_after(30, 2);
	list.insert_after(40, 3);
	list.insert_after(50, 4);
	list.insert_after(60, 5);
	list.insert_after(70, 6);

	list.every_other_element(); // print every other element in the list

	return 0;

}