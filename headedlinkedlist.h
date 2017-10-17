#ifndef HEADEDLINKEDLIST_H
#define HEADEDLINKEDLIST_H

/**
 * Fejelemes kétirányú lista.
 */

class HeadedLinkedList
{
    struct Node
    {
        int data;
        Node *prev;
        Node *next;
        explicit Node(const int _data, Node *_prev = nullptr, Node *_next = nullptr) : data(_data), prev(_prev), next(_next) {}

    };

    Node *head;
public:
    HeadedLinkedList() : head(nullptr) {}
    ~HeadedLinkedList()
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

    HeadedLinkedList(const HeadedLinkedList &other) : head(nullptr)
    {
        if(other.head != nullptr)
        {
            head = new Node(other.head->data);
            Node *p = head;
            Node *q = other.head->next;
            while (q != nullptr)
            {
                p->next = new Node(q->data, p);
                p = p->next;
                q = q->next;
            }
        }
    }

    HeadedLinkedList& operator=(const HeadedLinkedList &other)
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
        if (other.head != nullptr)
        {
            head = new Node(other.head->data);
            Node *p = head;
            Node *q = other.head->next;
            while(q != nullptr)
            {
                p->next = new Node(q->data, p);
                p = p->next;
                q = q->next;
            }
        }
        return *this;
    }

    void push_back(const int _data)
    {
        if (head != nullptr)
        {
            Node *p = head;
            while (p->next != nullptr)
            {
                p = p->next;
            }
            p->next = new Node(_data, p);
        }
        else
        {
            head = new Node(_data);
        }
    }

    void push_front(const int _data)
    {
        if (head != nullptr)
        {
            head = new Node(_data, nullptr, head);
            if (head->next != nullptr)
            {
                head->next->prev = head;
            }
        }
        else
        {
            head = new Node(_data);
        }
    }

    unsigned size() const
    {
        unsigned count = 0;
        Node *p = head;
        while(p != nullptr)
        {
            count++;
            p = p->next;
        }
        return count;
    }
    /**
     * Gyakorlatilag egy felsoroló, csak nem egy rakás szar megvalósítással mitn EA-n.
     * Ha cpp vizsgán lennénk, örökölnénk továbbá az std::iterator<std::bidirectional_iterator_tag, int> osztályból publikusan.
     */
    class iterator
    {
        friend class HeadedLinkedList;
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
        iterator operator++() // ++it
        {
            parent = parent->next;
            return *this;
        }
        iterator operator++(int) //it++
        {
            return operator++();
        }
        iterator operator--() //--it
        {
            parent = parent->prev;
            return *this;
        }
        iterator operator--(int)
        {
            return operator--();
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

    class const_iterator
    {
        friend class HeadedLinkedList;
        const Node *parent;
    public:
        const_iterator(const Node *_parent) : parent(_parent) {}

        bool operator==(const const_iterator &other)
        {
            return parent == other.parent;
        }
        bool operator!=(const const_iterator &other)
        {
            return !(*this == other);
        }
        const int& operator*() const
        {
            return parent->data;
        }
        const_iterator operator++() // ++it
        {
            parent = parent->next;
            return *this;
        }
        const_iterator operator++(int) //it++
        {
            return operator++();
        }
        const_iterator operator--() //--it
        {
            parent = parent->prev;
            return *this;
        }
        const_iterator operator--(int)
        {
            return operator--();
        }
    };

    const_iterator begin() const
    {
        return const_iterator(head);
    }
    const_iterator end() const
    {
        return const_iterator(nullptr);
    }

    void insert(iterator pos, const int _data)
    {
        if(head == nullptr)
        {
            head = new Node(_data, nullptr, nullptr);
        }
        else
        {
            pos.parent->next = new Node(*pos, pos.parent, pos.parent->next);
            if(pos.parent->next->next != nullptr)
            {
                pos.parent->next->next->prev = pos.parent->next;
            }
            pos.parent->data = _data;
        }
    }

    void erase(iterator pos)
    {
        if (pos.parent == nullptr) return;
        if (pos.parent->next == nullptr) //utolsó elem
        {
            if(pos.parent == head) //egyelemű lista
            {
                delete head;
                head = nullptr;
            }
            else
            {
                pos.parent->prev->next = nullptr;
                delete pos.parent;
            }
        }
        else if(pos.parent == head) //legelső elem
        {
            if(pos.parent->next != nullptr)
            {
                Node *tmp = head;
                head = head->next;
                delete tmp;
            }
            else
            {
                delete head;
                head = nullptr;
            }
        }
        else //itt magát a listaelemet, nem a rákövetkezőt töröljük! ojje!
        {
            pos--;
            Node *tmp = pos.parent->next->next;
            delete pos.parent->next;
            pos.parent->next = tmp;
            pos.parent->next->prev = pos.parent;
        }
    }
};
#endif // HEADEDLINKEDLIST_H
