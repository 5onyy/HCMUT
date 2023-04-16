#include <iostream>
using namespace std;
struct node
{
  int data;
  node *next;
};

node *createLinkedList(int n); // The implementation is provided implicitly

bool isEqual(node *head1, node *head2)
{
    node *h1=head1;
    node *h2=head2;
    if (h1==NULL || h2==NULL)   return 0;
    while (h1->next !=NULL)
    {
        if (h2->next == NULL)
            return 0;
        if (h1->data != h2->data)
            return 0;
        h1=h1->next;
        h2=h2->next;
    }
    if (h2->next==NULL)
    {
        if (h1->data == h2->data)
            return 1;
        else return 0;
    }
    return 0;
}

int main()
{
  int n = 0;
  cin>> n;
  node *head1 = createLinkedList(n);
  int m = 0;
  cin>> m;
  node *head2 = createLinkedList(m);
  cout << isEqual(head1, head2) << endl;
  return 0;
}
