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

	void delete_pos(int pos) {

		if (!head) {

			cout << "List is empty." << endl;
			return;

		}

		if (pos == 1) {

			pop_front();
			return;

		}

		Node* temp = head;

		for (int i = 1; i < pos; i++) {

			if (!temp) {

				cout << "Position doesn't exist." << endl;
				return;

			} else {

				temp = temp->next;

			}
		}

		if (!temp) {

			cout << "Position doesn't exist." << endl;
			return;

		}

		if (!temp->next) {

			pop_back();
			return;

		}

		Node* tempPrev = temp->prev;
		tempPrev->next = temp->next;
		temp->next->prev = tempPrev;

		delete temp;

	}

	void push_back(int v) {

		Node* newNode = new Node(v);

		if (!tail) {

			head = tail = newNode;

		} else {

			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;

		}
	}

	void push_front(int v) {

		Node* newNode = new Node(v);

		if (!head) {

			head = tail = newNode;

		} else {

			newNode->next = head;
			head->prev = newNode;
			head = newNode;

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