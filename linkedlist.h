#ifndef LINKEDLIST_H
#define LINKEDLIST_H

/**
 * Kétirányű lista.
 */

class LinkedList
{
    int data;
    LinkedList *prev;
    LinkedList *next;
public:
    explicit LinkedList(const int _data, LinkedList *_prev = nullptr, LinkedList *_next = nullptr) : data(_data), prev(_prev), next(_next) {}
    ~LinkedList()
    {
        delete next;
    }

    LinkedList(const LinkedList &other) : data(other.data), prev(nullptr), next(nullptr)
    {
        LinkedList *p = this;
        LinkedList *q = other.next;
        while (q != nullptr)
        {
            p->next = new LinkedList(q->data, p);
            p = p->next;
            q = q->next;
        }
    }

    LinkedList& operator=(const LinkedList &other)
    {
        if(this == &other)
        {
            return *this;
        }
        delete next;
        data = other.data;
        next = nullptr; //ha other egy egyelemű lista
        LinkedList *p = this;
        LinkedList *q = other.next;
        while(q != nullptr)
        {
            p->next = new LinkedList(q->data, p);
            p = p->next;
            q = q->next;
        }
        return *this;
    }

    void push_back(const int _data)
    {
        LinkedList *p = this;
        while (p->next != nullptr)
        {
            p = p->next;
        }
        p->next = new LinkedList(_data, p);
    }

    void push_front(const int _data)
    {
        //Nem kell félni, a new operátor paraméterei előbb értékelődnek ki, így nem kell segédváltozó.

        next = new LinkedList(data, this, next);
        if(next->next != nullptr)
        {
            next->next->prev = next;
        }
        data = _data;
    }

    unsigned size() const
    {
        unsigned count = 1; //nem lehet üres!
        LinkedList *p = next;
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
        friend class LinkedList;
        LinkedList *parent;
    public:
        iterator(LinkedList *_parent) : parent(_parent) {}

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
        return iterator(this);
    }
    iterator end()
    {
        return iterator(nullptr);
    }

    void insert(iterator pos, const int _data)
    {
        pos.parent->next = new LinkedList(*pos, pos.parent, pos.parent->next);
        if(pos.parent->next->next != nullptr)
        {
            pos.parent->next->next->prev = pos.parent->next;
        }
        pos.parent->data = _data;
    }

    void erase(iterator pos)
    {
        //std::cout << *pos << std::endl;
        if (pos.parent->next == nullptr)
        {
            pos.parent->prev->next = nullptr;
            delete pos.parent;
        }
        else if(pos.parent->prev == nullptr) //ekkor tudhatjuk hogy a legelső elemről van szó.
        {
            data = next->data;
            LinkedList *tmp = next->next;
            next->next = nullptr; //különben a destruktor törölné a lista hátralevő részét
            delete next;
            next = tmp;
        }
        else //itt magát a listaelemet, nema rákövetkezőt töröljük! ojje!
        {
            pos--;
            LinkedList *tmp = pos.parent->next->next;
            pos.parent->next->next = nullptr;
            delete pos.parent->next;
            pos.parent->next = tmp;
            pos.parent->next->prev = pos.parent;
        }
    }
};
#endif // LINKEDLIST_H
