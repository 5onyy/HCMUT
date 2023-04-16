#include <iostream>
using namespace std;
struct node
{
  int data;
  node *next;
};
void push(node **head,int data)
{
    node *new_node=new node;
    new_node->data=data;
    new_node->next=*head;
    *head=new_node;
}
node *createLinkedList(int n)
{
    node* head= NULL;
    for (int i=0;i<n;i++)
    {
        int x;    
        cin>>x;
        push(&head,x);
    }
    return head;
}
void print(node *head)
{
  while (head != nullptr)
  {
    cout << head->data << endl;
    head = head->next;
  }
}
int main()
{
  int n = 0;
  cin >> n;
  if (n > 0)
  {
    node *head = createLinkedList(n);
    print(head);
  }
  else
  {
    cout << "Invalid n" << endl;
  }
  return 0;
}