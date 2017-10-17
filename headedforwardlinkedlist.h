#ifndef HEADEDFORWARDLINKEDLIST_H
#define HEADEDFORWARDLINKEDLIST_H

/**
 * Fejelemes egyirányú lista.
 */

class HeadedForwardLinkedList
{
    struct Node //nem publikus!
    {
        int data;
        Node* next;

        explicit Node(const int _data, Node* _next = nullptr) : data(_data), next(_next) {}
    };

    Node* head;
public:
    HeadedForwardLinkedList() : head(nullptr) {}

    ~HeadedForwardLinkedList()
    {
        Node *p = head;
        Node *tmp;
        while (p != nullptr)
        {
            tmp = p->next;
            delete p;
            p = tmp;
        }
    }

    HeadedForwardLinkedList(const HeadedForwardLinkedList &other) : head(nullptr)
    {
        if (other.head != nullptr)
        {
            head = new Node(other.head->data);

            Node *p = head;
            const Node *q = other.head->next;
            while (q != nullptr)
            {
                p->next = new Node(q->data);
                p = p->next;
                q = q->next;
            }
        }
    }

    HeadedForwardLinkedList& operator=(const HeadedForwardLinkedList &other)
    {
        if(this == &other)
        {
            return *this;
        }
        Node *p = head;
        Node *tmp;
        while (p != nullptr)
        {
            tmp = p->next;
            delete p;
            p = tmp;
        }
        head = nullptr; //ha other egy egyelemű lista

        if(other.head != nullptr)
        {
            head = new Node(other.head->data);

            p = head;
            const Node *q = other.head->next;
            while(q != nullptr)
            {
                p->next = new Node(q->data);
                p = p->next;
                q = q->next;
            }

        }
        return *this;
    }

    void push_back(const int data)
    {
        if (head == nullptr)
        {
            head = new Node(data);
        }
        else
        {
            Node *p = head;
            while(p->next != nullptr)
            {
                p = p->next;
            }
            p->next = new Node(data);
        }
    }

    void push_front(const int data)
    {
        if (head == nullptr)
        {
            head = new Node(data);
        }
        else
        {
            head = new Node(data, head);
        }
    }

    unsigned size() const
    {
        unsigned count = 0; //lehet üres!
        Node *p = head;
        while(p != nullptr)
        {
            p = p->next;
            count++;
        }
        return count;
    }

    class iterator
    {
        friend class HeadedForwardLinkedList;
        Node *parent;
    public:
        iterator(Node *_parent) : parent(_parent) {}

        bool operator==(const iterator &other)
        {
            return parent == other.parent;
        }
        bool operator!=(const iterator &other)
        {
            return !(*this == other);
        }
        int& operator*()
        {
            return parent->data;
        }
        iterator operator++()
        {
            parent = parent->next;
            return *this;
        }
        iterator operator++(int)
        {
            return operator++();
        }
    };

    iterator begin()
    {
        return iterator(head);
    }
    iterator end()
    {
        return iterator(nullptr);
    }

    void insert(iterator pos, const int _data)
    {
        if(head == nullptr)
        {
            head = new Node(_data, nullptr);
        }
        else
        {
            pos.parent->next = new Node(*pos, pos.parent->next);
            pos.parent->data = _data;
        }
    }

    void erase(iterator pos)
    {
        if (pos.parent == nullptr) return;
        else if (pos.parent->next == nullptr)
        {
            if (pos.parent == head)
            {
                delete head;
                head = nullptr;
            }
            else
            {
                Node *p = head;
                while(p->next != pos.parent)
                {
                    p = p->next;
                }
                p->next = nullptr;
                delete pos.parent;
            }
        }
        else //itt elegánsabb megoldás is lehetne, ha tudnánk a kitörelndő előtti elemet is, de úgy az első elem törlése nehézkes.
        {
            pos.parent->data = pos.parent->next->data;
            Node *tmp = pos.parent->next->next;
            delete pos.parent->next; //nem kell nullptr-é tenni: Node-nak nincs felüldefiniált destruktora.
            pos.parent->next = tmp;
        }
    }
};

#endif // HEADEDFORWARDLINKEDLIST_H
