#include <iostream>
using namespace std;

struct ListNode {
	int value;
	ListNode *next;
};

ListNode* createNode();
int getLocation(ListNode*);
void insert(ListNode*[], ListNode*, int);
void print(ListNode *[]);
int getHashKey(int);
bool searchNode(ListNode *[], int);
void destroyHashTable(ListNode *[]);
void deleteNode(ListNode*[], int);

int main() {

	char ch = 'a';

	ListNode* x[10];

	for (int i = 0; i < 10; i++)
		x[i] = nullptr;

	int modVal;
	int val;
	ListNode * ptr;

	do {

		cout << "a--Add" << endl;
		cout << "d--delete" << endl;
		cout << "x--destroy table" << endl;
		cout << "s--search record" << endl;
		cout << "p--Print" << endl;
		cout << "q--Quit" << endl;
		cin >> ch;

		switch (ch)
		{
		case 'a':
			ptr = createNode();
			modVal = getLocation(ptr);
			insert(x, ptr, modVal);
			break;
		case 'd':
			cout << "deleting ... \n";
			cout << "enter a value to delete ";
			cin >> val;
			deleteNode(x, val);
			break;
		case 'x':
			destroyHashTable(x);
			break;
		case 's':
			cout << "What are you searching for?";
			cin >> val;
			if (searchNode(x, val))
				cout << "Your Value is in the list" << endl;
			else
				cout << "Your value is not in the list" << endl;
			break;
		case 'p':
			print(x);
			break;
		case 'q':
			break;
		default:
			break;
		}
	} while (ch != 'q');

}

ListNode* createNode() {
	ListNode *newNode = new ListNode;
	newNode->value = rand();
	newNode->next = nullptr;
	return newNode;
}

int getLocation(ListNode*nodePtr) {

	int modVal = getHashKey(nodePtr->value);
	return modVal;
}

void insert(ListNode* x[], ListNode* newNode, int modVal) {
	if (x[modVal] == nullptr)
		x[modVal] = newNode;
	else {
		ListNode*nodePtr = x[modVal];
		ListNode*prevPtr = nullptr;

		while (nodePtr->next != nullptr && nodePtr->value < newNode->value) {
			prevPtr = nodePtr;
			nodePtr = nodePtr->next;
		}
		if (prevPtr == nullptr) {
			x[modVal] = newNode;
			newNode->next = nodePtr;
		}
		else {
			prevPtr->next = newNode;
			newNode->next = nodePtr;
		}
	}
}

void print(ListNode* x[]) {
	for (int i = 0; i < 10; i++) {
		cout << "Index:" << i << endl;
		ListNode* nodePtr = x[i];
		while (nodePtr != nullptr) {
			cout << "value:" << nodePtr->value << ',';
			nodePtr = nodePtr->next;
		}
		cout << endl;
	}
}

int getHashKey(int value) {
	return (value % 10);
}

void destroyHashTable(ListNode * x[]) {
	ListNode * nodePtr;
	ListNode * nextNode;
	for (int i = 0; i < 10; i++) {
		nodePtr = x[i];
		while (nodePtr != nullptr) {
			nextNode = nodePtr->next;
			cout << "deleting ... " << nodePtr->value << endl;
			delete nodePtr;
			nodePtr = nextNode;
		}
	}
	for (int i = 0; i < 10; i++)
		x[i] = nullptr;
}

bool searchNode(ListNode *x[], int val) {
	int hashKey = getHashKey(val);

	ListNode *head = x[hashKey];

	if (head == nullptr)
		return false;
	else {
		ListNode *nodePtr = head;
		while (nodePtr != nullptr) {
			if (nodePtr->value = val)
				return true;
		}
	}
	return false;
}

void deleteNode(ListNode*x[], int val) {
	int hashKey = getHashKey(val);
	ListNode* nodePtr;
	ListNode* head = x[hashKey];
	ListNode* prevPtr = nullptr;
	

	if (head != nullptr) {
		if (head->value == val) {
			nodePtr = head->next;
			delete head;
			head = nodePtr;
		}
		else {
			nodePtr = head;
			while (nodePtr != nullptr && nodePtr->value != val) {
				prevPtr = nodePtr;
				nodePtr = nodePtr->next;
			}
			if (nodePtr != nullptr) {
				prevPtr->next = nodePtr->next;
				delete nodePtr;
			}
			else if (nodePtr->next != nullptr) {
				delete nodePtr;
				prevPtr->next = nullptr;
			}
		}
	}
	else {
		cout << "list is empty" << endl;
	}
}