#include <iostream>

using namespace std;

class Node
{
    public:
        unsigned data : 7;
        unsigned tag : 1;
        Node *left, *right;
        Node(int dt)
        {
            data = dt;
            left = right = NULL;
            tag = false;
        }
};

class BST
{
    private:
        Node* root;
        int flag;
        void deleteTree(Node *nd);
        void leftDescend(Node** prev, Node**pres);
        void rightDescend(Node** prev, Node**pres);
        void leftAscend(Node** prev, Node**pres);
        void rightAscend(Node** prev, Node**pres);
    public:
        BST(int data)
        {
            root = new Node(data);
            flag = 0;
        }
        ~BST();
        void inOrder();
        void preOrder();
        void postOrder();
        void insertion(int data);

};
void BST :: leftDescend(Node** prev, Node** pres)
{
    (*pres) -> tag = false;
    Node* temp = (*pres) -> left;
    (*pres) -> left = *prev;
    *prev = *pres;
    *pres = temp;
}

void BST :: rightDescend(Node** prev, Node** pres)
{
    (*pres) -> tag = true;
    Node* temp = (*pres) -> right;
    (*pres) -> right = *prev;
    *prev = *pres;
    *pres = temp;
}

void BST :: leftAscend(Node** prev, Node** pres)
{
    if((*prev) != NULL && (*prev) -> tag == false)
    {
        Node* temp = (*prev) -> left;
        (*prev) -> left = (*pres);
        (*pres) = (*prev);
        (*prev) = temp;
    }
}

void BST :: rightAscend(Node** prev, Node** pres)
{
    if((*prev) != NULL && (*prev) -> tag == true)
    {
        (*prev) -> tag = false;
        Node* temp = (*prev) -> right;
        (*prev) -> right = (*pres);
        (*pres) = (*prev);
        (*prev) = temp;
    }
}
void BST :: deleteTree(Node *nd)
{
    if(nd == NULL)
        return;
    deleteTree(nd -> left);
    deleteTree(nd -> right);
    delete nd;
}
BST :: ~BST()
{
    deleteTree(root);
}
void BST :: insertion(int data)
        {
            if(root == NULL)
                {
                    root = new Node(data);
                    return;
                }
            Node *ptr = root;
            while (ptr != NULL)
            {
                if (data < ptr->data)
                {
                    if (ptr->left == NULL)
                    {
                        ptr->left = new Node(data);
                        return;
                    }
                    ptr = ptr->left;
                }
                else if (data > ptr->data)
                {
                    if (ptr->right == NULL)
                    {
                        ptr->right = new Node(data);
                        return;
                    }
                    ptr = ptr->right;
                }
                else
                {
                    return;
                }
            }
        }

void BST :: inOrder()
{
    flag = 0;
    Node* prev = NULL;
    Node* pres = root;
    while((prev != NULL || flag != 2))
    {
        if(pres -> left != NULL && flag == 0)
        {
            leftDescend(&prev, &pres);
        }
        else
        {
                if(flag != 2)
                    cout << pres -> data << " ";
                if(prev == NULL && pres -> right == NULL)
                {
                    flag = 2;
                }
                else if(pres -> right != NULL &&  flag != 2)
                {
                    rightDescend(&prev, &pres);
                    flag = 0;
                }
                else if(prev != NULL && prev -> tag == true)
                {
                    rightAscend(&prev, &pres);
                    flag = 2;
                }
                else if(prev != NULL && (prev -> tag == false || flag == 2))
                {
                    leftAscend(&prev, &pres);
                    flag = 1;
                }
        }
    }
    cout << endl;
}

void BST :: postOrder()
{
    flag = 0;
    Node* prev = NULL;
    Node* pres = root;
    while(prev != NULL || flag != 2)
    {
        if(pres -> left != NULL && flag == 0)
        {
            leftDescend(&prev, &pres);
            flag = 0;
        }
        else
        {
                if(flag == 2 || (pres -> left == NULL && pres -> right == NULL) || (pres -> right == NULL && flag == 1))
                {
                    cout << pres -> data << " ";
                }
                if(prev == NULL && pres -> right == NULL)
                {
                    flag = 2;
                }
                else if(pres -> right != NULL &&  flag != 2)
                {
                    rightDescend(&prev, &pres);
                    flag = 0;
                }
                else if(prev != NULL && prev -> tag == false)
                {
                    leftAscend(&prev, &pres);
                    flag = 1;
                }
                else if(prev != NULL && prev -> tag == true)
                {
                    rightAscend(&prev, &pres);
                    flag = 2;
                    if(prev == NULL)
                        cout << pres -> data;
                }
        }
    }
    cout << endl;
}


void BST :: preOrder()
{
    flag = 0;
    Node* prev = NULL;
    Node* pres = root;
    while(prev != NULL || flag != 2)
    {
        if(flag == 0)
            cout << pres -> data << " ";
        if(pres -> left != NULL && flag == 0)
        {
            leftDescend(&prev, &pres);
            flag = 0;
        }
        else
        {
            if(prev == NULL && pres -> right == NULL)
                flag = 2;
            else if(pres -> right != NULL &&  flag != 2)
            {
                rightDescend(&prev, &pres);
                flag = 0;
            }
            else if(prev != NULL && prev -> tag == false)
            {
                leftAscend(&prev, &pres);
                flag = 1;
            }
            else if(prev != NULL && prev -> tag == true)
            {
                rightAscend(&prev, &pres);
                flag = 2;
            }
        }
    }
    cout << endl;
}

int main()
{
    int choice, data;
    cout << "Enter data to insert: ";
    cin >> data;
    BST myBST(data);

    do{
        cout << "1. Insertion\n2. In-order Traversal\n3. Pre-Order Traversal\n4. Post-Order Traversal\n5. Exit\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                cout << "Enter data to insert: ";
                cin >> data;
                myBST.insertion(data);
                break;

            case 2:
                cout << "In-order Traversal:\n";
                myBST.inOrder();
                break;

            case 3:
                cout << "Pre-order Traversal:\n";
                myBST.preOrder();
                break;

            case 4:
                cout << "Post-order Traversal:\n";
                myBST.postOrder();
                break;

            case 5:
                cout << "Exiting the program!" << endl;
                break;

            default:
                cout << "Invalid choice. Please enter a valid option.\n";
        }

    } while (choice != 5);
    return 0;
}