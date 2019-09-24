#include<iostream>
using namespace std;

class LinkedList;

class Node {
private:
	int data;
	Node* next;

public:
	Node(int d = 0)
	{
		data = d;
		next = NULL;
	}

	bool atEnd(){ return (next == NULL);}

	friend class LinkedList;
};

class LinkedList {
private:
    int length;
    Node *head;
public:
    LinkedList() {
        head = NULL;
        length = 0;
    }
    ~LinkedList() {
		while(head != NULL)
		{
			deleteFront();
		}
    }
    void insertFront(int data)
	{
		// int data; cout << "Enter data: "; cin >> data;
		Node* newNode = new Node(data);

		newNode->next = head;
		head = newNode;

		length++;
	}

    void insertEnd(int data)
	{
		// int data; cout << "Enter data: "; cin >> data;
		Node* newNode = new Node(data);

		if(head == NULL) {
			head = newNode;
			length++;
			return;
		}

		Node* cur = head;

		while(!cur->atEnd())
			cur = cur->next;

		cur->next = newNode;
		length++;
	}

    void deleteNode(int d)
	{
		if(length == 0)
		{
			cout << "List is empty!!\n";
			return;
		}

		if(length == 1)
		{
			if(head->data = d)
			{
				delete head;
				head = NULL;
				length--;
				return;
			}

			else
			{
				cout << "Element not present in list!!\n";
				return;
			}
			
		}

		Node* prev = NULL;
		Node* cur = head;

		while(cur->data != d && !cur->atEnd())
		{
			prev = cur;
			cur = cur->next;
		}

		if(cur->data != d)
		{
			cout << "Element not present in list!!\n";
			return;
		}

		prev->next = cur->next;

		delete cur;
		length--;
	}

	void deleteFront()
	{
		if(length == 0)
		{
			cout << "List is empty!!\n";
			return;
		}

		Node* temp = head;

		head = temp->next;

		delete temp;
		length--;
	}

    void printList()
	{
		if(length == 0)
		{
			cout << "List is empty!!";
			return;
		}

		cout << "{";

		Node* cur = head;

		while(!cur->atEnd())
		{
			cout << cur->data << ", ";
			cur = cur->next;
		}

		cout << cur->data << "}\n";
	}

    int len() { return length;}
};

int main() {
    LinkedList list;

	for(int i = 0; i < 10; i++)
		list.insertEnd(i);

	list.printList();

    return 0;
}