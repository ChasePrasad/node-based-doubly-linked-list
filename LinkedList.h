#pragma once

#include <iostream>
#include <vector>
using namespace std;

template <typename T> class LinkedList
{
    public:
        struct Node
        {
            T data;
            Node *next;
            Node *prev;

            Node(T d)
            {
                data = d;
                next = nullptr;
                prev = nullptr;
            };
        };

        LinkedList()
        {
            size = 0;
            head = nullptr;
            tail = nullptr;
        }

        LinkedList(const LinkedList &c)
        {
            size = 0;
            head = nullptr;
            tail = nullptr;

            const Node* temp = c.Head();

            while (temp != nullptr)
            {
                AddTail(temp->data);
                temp = temp->next;
            }
        }

        LinkedList &operator=(const LinkedList &a)
        {
            if (this != &a)
            {
                const Node *temp = head;

                while (temp != nullptr)
                {
                    Node *next = temp->next;
                    delete temp;
                    temp = next;
                }

                size = 0;
                head = nullptr;
                tail = nullptr;

                temp = a.Head();

                while (temp != nullptr)
                {
                    AddTail(temp->data);
                    temp = temp->next;
                }
            }

            return *this;
        }

        ~LinkedList()
        {
            Node *temp = head;

            while (temp != nullptr)
            {
                Node *next = temp->next;
                delete temp;
                temp = next;
            }
        }

        void PrintForward()
        {
            Node *temp = head;

            while (temp != nullptr)
            {
                cout << temp->data << endl;
                temp = temp->next;
            }
        }

        void PrintReverse()
        {
            Node *temp = tail;

            while (temp != nullptr)
            {
                cout << temp->data << endl;
                temp = temp->prev;
            }
        }

        void PrintForwardRecursive(Node *n)
        {
            if (n != nullptr)
            {
                cout << n->data << endl;
                PrintForwardRecursive(n->next);
            }
        }

        void PrintReverseRecursive(Node *n)
        {
            if (n != nullptr)
            {
                cout << n->data << endl;
                PrintReverseRecursive(n->prev);
            }
        }

        const int NodeCount() const
        {
            return size;
        }

        int NodeCount()
        {
            return size;
        }

        void FindAll(vector<Node*>& v, T d)
        {
            Node *temp = head;

            while (temp != nullptr)
            {
                if (temp->data == d)
                {
                    v.push_back(temp);
                }

                temp = temp->next;
            }
        }

        const Node* Find(T d) const
        {
            Node *temp = head;

            while (temp != nullptr)
            {
                if (temp->data == d)
                {
                    return temp;
                }

                temp = temp->next;
            }

            return nullptr;
        }

        Node* Find(T d)
        {
            Node *temp = head;

            while (temp != nullptr)
            {
                if (temp->data == d)
                {
                    return temp;
                }

                temp = temp->next;
            }

            return nullptr;
        }

        const Node* GetNode(int i) const
        {
            if (i < 0 || i > size - 1)
            {
                throw out_of_range("Error: Specified index out of range.");
            }
            else
            {
                Node *temp = head;

                for (int j = 0; j < i; j++)
                {
                    temp = temp->next;
                }

                return temp;
            }
        }

        Node* GetNode(int i)
        {
            if (i < 0 || i > size - 1)
            {
                throw out_of_range("Error: Specified index out of range.");
            }
            else
            {
                Node *temp = head;

                for (int j = 0; j < i; j++)
                {
                    temp = temp->next;
                }

                return temp;
            }
        }

        const Node* Head() const
        {
            return head;
        }

        Node* Head()
        {
            return head;
        }

        const Node* Tail() const
        {
            return tail;
        }

        Node* Tail()
        {
            return tail;
        }

        void AddHead(T d)
        {
            Node *temp = new Node(d);

            if (head == nullptr)
            {
                head = temp;
                tail = temp;
            }
            else
            {
                temp->next = head;
                head->prev = temp;
                head = temp;
            }

            size++;
        }

        void AddTail(T d)
        {
            Node *temp = new Node(d);

            if (tail == nullptr)
            {
                head = temp;
                tail = temp;
            }
            else
            {
                temp->prev = tail;
                tail->next = temp;
                tail = temp;
            }

            size++;
        }

        void AddNodesHead(T d[], int length)
        {
            for (int i = length - 1; i > -1; i--)
            {
                AddHead(d[i]);
            }
        }

        void AddNodesTail(T d[], int length)
        {
            for (int i = 0; i < length; i++)
            {
                AddTail(d[i]);
            }
        }

        void InsertAfter(Node *n, T d)
        {
            Node *temp = new Node(d);

            if (n == tail)
            {
                AddTail(d);
            }
            else
            {
                temp->prev = n;
                temp->next = n->next;
                n->next->prev = temp;
                n->next = temp;

                size++;
            }
        }

        void InsertBefore(Node *n, T d)
        {
            Node *temp = new Node(d);

            if (n == head)
            {
                AddHead(d);
            }
            else
            {
                temp->next = n;
                temp->prev = n->prev;
                n->prev->next = temp;
                n->prev = temp;

                size++;
            }
        }

        void InsertAt(T d, int i)
        {
            if (i < 0 || i > size)
            {
                throw out_of_range("Error: Specified index out of range.");
            }
            else if (i == 0)
            {
                AddHead(d);
            }
            else if (i == size)
            {
                AddTail(d);
            }
            else
            {
                Node *temp = new Node(d);
                Node *n = GetNode(i);

                temp->prev = n->prev;
                temp->next = n;
                n->prev->next = temp;
                n->prev = temp;

                size++;
            }
        }

        bool RemoveHead()
        {
            if (size == 0)
            {
                return false;
            }
            else
            {
                Node *temp = head;

                if (size == 1)
                {
                    head = nullptr;
                    tail = nullptr;
                }
                else
                {
                    head = head->next;
                    head->prev = nullptr;
                }

                delete temp;
                size--;

                return true;
            }
        }

        bool RemoveTail()
        {
            if (size == 0)
            {
                return false;
            }
            else
            {
                Node *temp = tail;

                if (size == 1)
                {
                    head = nullptr;
                    tail = nullptr;
                }
                else
                {
                    tail = tail->prev;
                    tail->next = nullptr;
                }

                delete temp;
                size--;

                return true;
            }
        }

        int Remove(T d)
        {
            Node *temp = head;
            int count = 0;

            while (temp != nullptr)
            {
                if (temp->data == d)
                {
                    if (temp == head)
                    {
                        RemoveHead();
                        temp = head;
                    }
                    else if (temp == tail)
                    {
                        RemoveTail();
                        temp = nullptr;
                    }
                    else
                    {
                        temp->prev->next = temp->next;
                        temp->next->prev = temp->prev;

                        Node *next = temp->next;
                        delete temp;
                        temp = next;
                        size--;
                    }

                    count++;
                }
                else
                {
                    temp = temp->next;
                }
            }

            return count;
        }

        bool RemoveAt(int i)
        {
            if (i < 0 || i > size - 1)
            {
                return false;
            }
            else if (i == 0)
            {
                return RemoveHead();
            }
            else if (i == size - 1)
            {
                return RemoveTail();
            }
            else
            {
                Node *temp = GetNode(i);

                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;

                delete temp;
                size--;

                return true;
            }
        }

        void Clear()
        {
            Node *temp = head;

            while (temp != nullptr)
            {
                Node *next = temp->next;
                delete temp;
                temp = next;
            }

            size = 0;
            head = nullptr;
            tail = nullptr;
        }

        const T& operator[](int i) const
        {
            return GetNode(i)->data;
        }

        T& operator[](int i)
        {
            return GetNode(i)->data;
        }

        bool operator==(const LinkedList &o) const
        {
            if (size != o.NodeCount())
            {
                return false;
            }

            Node *temp1 = head;
            const Node *temp2 = o.Head();

            while (temp1 != nullptr)
            {
                if (temp1->data != temp2->data)
                {
                    return false;
                }

                temp1 = temp1->next;
                temp2 = temp2->next;
            }

            return true;
        }
    
    private:
        Node *head;
        Node *tail;
        int size;
};