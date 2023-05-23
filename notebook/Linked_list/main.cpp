#include <iostream>
using namespace std;
  
class node {
public:
    int data;
    node* next;
  
    // A constructor is called here
    node() {};
    node(int value)
    {
        data = value;
        next = NULL;
    }

};

template <typename T> class linkedlist{
public:

    T* head = NULL;

    // Function to insert an element at head position
    void insertathead(T*& head, int val)
    {
        T* n = new T(val);
        n->next = head;
        head = n;
    }

    // Function to insert a element at a specified position
    void insertafter(T* prev_node, int new_data) 
    { 

        if (prev_node == NULL)              // 1. check if the given prev_node is NULL
            return; 
        T* new_node = new T();        // 2. allocate new node
        new_node->data = new_data;          // 3. put in the data
        
        new_node->next = prev_node->next;   // 4. Make next of new node as next of prev_node
    
        prev_node->next = new_node;         // 5. move the next of prev_node as new_node
    } 
    // Function to insert an element at the end
    void insertatend(T*& head, int val)
    {
        T* n = new T(val);
        if (head == NULL) {
            head = n;
            return;
        }
    
        T* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = n;
    }
        
    // Function to print the singly linked list
    void print(T*& head)
    {
        T* temp = head;
    
        while (temp != NULL) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    int size()
    {
        T* tmp= head;
        int count =1;
        while (tmp->next != NULL)
        {
            count++;
            tmp=tmp->next;
        }
        return count;
    }
};

  
int main()
{
    linkedlist<node> l;
    l.insertathead(l.head,1);
    l.insertatend(l.head,3);
    l.insertafter(l.head,4);
    l.print(l.head);
    cout<<l.size();
    
}
// contributed by divyanshmishra101010