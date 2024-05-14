#include <bits/stdc++.h>

using namespace std;

class Stack
{
    private:
        int size, top;
        int *arr;
    public:
        Stack(int lim);
        int pop();
        bool push(int elem);        
        bool isFull();
        bool isEmpty();
        void multiPop(int k);
        ~Stack();
};
int Stack ::  pop()
            {
                if(!isEmpty())
                    return arr[top--];
                else
                    return 0;
            }
bool Stack ::  push(int elem)
            {
                if(!isFull())
                    arr[++top] = elem;
                else
                    return false;
                return true;
            }
bool Stack :: isFull()
            {
                return top == size - 1;
            }     
bool Stack :: isEmpty()
            {
                return top == -1;
            }
void Stack :: multiPop(int k)
            {
                if(isEmpty()) {
                    cout << "Stack is empty!" << endl;
                    return;
                }
                while(!isEmpty() && k > 0 )
                {
                    cout << pop() << " has been popped" << endl;
                    --k;
                }
            }     
Stack :: Stack(int lim)
{
    size = lim;
    top = -1;
    arr = new int[lim];
}
Stack :: ~Stack()
            {
                delete arr;
            }
int main()
{
    int size;
    cout << "Enter the stack size: ";
    cin >> size;
    Stack S(size);
    while(true)
    {
        cout << "To push enter 1 and to multipop enter 2: ";
        int num;
        cin >> num;
        switch (num)
        {
        case 1 : 
            int elem;
            cout << "Enter the element to push: ";
            cin >> elem;
            if(S.push(elem))
            {
                cout << "Element has been pushed" << endl;
            }
            else
                cout << "Stack is full" << endl;
        break;
        case 2 : 
            int num;
            cout << "Enter number of elements to be popped: ";
            cin >> num;
            S.multiPop(num);
        break;
        default:
            cout << "Give a valid input!" << endl;
            break;
        }
    }
    return 0;
}