#ifndef FORWARDLINKEDLIST_H
#define FORWARDLINKEDLIST_H

/**
 * Egyirányú lista.
 */

class ForwardLinkedList
{
    int data;
    ForwardLinkedList *next;
public:
    explicit ForwardLinkedList(const int _data, ForwardLinkedList *_next = nullptr) : data(_data), next(_next) {}
    ~ForwardLinkedList()
    {
        delete next;
    }

    ForwardLinkedList(const ForwardLinkedList &other) : data(other.data), next(nullptr)
    {
        ForwardLinkedList *p = this;
        const ForwardLinkedList *q = other.next;
        while (q != nullptr)
        {
            p->next = new ForwardLinkedList(q->data);
            p = p->next;
            q = q->next;
        }
    }

    ForwardLinkedList& operator=(const ForwardLinkedList &other)
    {
        if(this == &other)
        {
            return *this;
        }
        delete next;
        data = other.data;
        next = nullptr; //ha other egy egyelemű lista
        ForwardLinkedList *p = this;
        ForwardLinkedList *q = other.next;
        while(q != nullptr)
        {
            p->next = new ForwardLinkedList(q->data);
            p = p->next;
            q = q->next;
        }
        return *this;
    }

    void push_back(const int _data)
    {
        ForwardLinkedList *p = this;
        while (p->next != nullptr)
        {
            p = p->next;
        }
        p->next = new ForwardLinkedList(_data);
    }

    void push_front(const int _data)
    {
        //Nem kell félni, a new operátor paraméterei előbb értékelődnek ki, így nem kell segédváltozó.
        next = new ForwardLinkedList(data, next);
        data = _data;
    }

    unsigned size() const
    {
        unsigned count = 1; //nem lehet üres!
        ForwardLinkedList *p = next;
        while(p != nullptr)
        {
            count++;
            p = p->next;
        }
        return count;
    }
    /**
     * Gyakorlatilag egy felsoroló, csak nem egy rakás szar megvalósítással mitn EA-n.
     * Ha cpp vizsgán lennénk, örökölnénk továbbá az std::iterator<std::forward_iterator_tag, int> osztályból publikusan.
     */
    class iterator
    {
        friend class ForwardLinkedList;
        ForwardLinkedList *parent;
    public:
        iterator(ForwardLinkedList *_parent) : parent(_parent) {}

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
        return iterator(this);
    }
    iterator end()
    {
        return iterator(nullptr);
    }

    void insert(iterator pos, const int _data)
    {
        pos.parent->next = new ForwardLinkedList(*pos, pos.parent->next);
        pos.parent->data = _data;
    }
    void erase(iterator pos)
    {
        if (next == nullptr) return;
        else if (pos.parent->next == nullptr)
        {
            ForwardLinkedList *p = this;
            while(p->next != pos.parent)
            {
                p = p->next;
            }
            p->next = nullptr;
            delete pos.parent;
        }
        else //itt elegánsabb megoldás is lehetne, ha tudnánk a kitörelndő előtti elemet is, de úgy az első elem törlése nehézkes.
        {
            pos.parent->data = pos.parent->next->data;
            ForwardLinkedList *tmp = pos.parent->next->next;
            pos.parent->next->next = nullptr; //különben a destruktor törölné a lista hátralevő részét
            delete pos.parent->next;
            pos.parent->next = tmp;
        }
    }
};

#endif // FORWARDLINKEDLIST_H
