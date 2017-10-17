#ifndef HEADEDCIRCULARLINKEDLIST_H
#define HEADEDCIRCULARLINKEDLIST_H

/**
 * Fejelemes ciklikus kétirányű lista. A head utáni listaelem tartalmazhat adatot, de alapértelmezetten nem használatos.
 * Az end() iterátor pont arra az elemre mutat. (de általában [begin , end) szokott lenni egy ciklus, így azt az elemet
 * ritkán érintjük)
 *
 * Erősen javallott typedef használata, pl.: typedef HeadedCircilarLinkedList::iterator HCLiterator;
 */

class HeadedCircularLinkedList
{
    struct Node
    {
        int data;
        Node *prev;
        Node *next;
        explicit Node(const int _data, Node *_prev = nullptr, Node *_next = nullptr) : data(_data), prev(_prev), next(_next){}
    };

    Node *head;
public:
    HeadedCircularLinkedList() : head(new Node(666))
    {
        head->next = head->prev = head;
    }
    ~HeadedCircularLinkedList()
    {
        Node *p = head;
        Node *tmp;
        while (p->next != head)
        {
            tmp = p->next;
            delete p;
            p = tmp;
        }
        delete head;
    }

    HeadedCircularLinkedList(const HeadedCircularLinkedList &other) : head(new Node(other.head->data))
    {
        if(other.head->next != other.head)
        {
            Node *p = head;
            Node *q = other.head->next;
            while (q != other.head)
            {
                p->next = new Node(q->data, p);
                p = p->next;
                q = q->next;
            }
            p->next = head;
            head->prev = p;
        }
        else
        {
            head->next = head;
        }
    }

    HeadedCircularLinkedList& operator=(const HeadedCircularLinkedList &other)
    {
        if(this == &other)
        {
            return *this;
        }
        Node *p = head;
        Node *tmp;
        while (p->next != head)
        {
            tmp = p->next;
            delete p;
            p = tmp;
        }
        head->data = other.head->data;
        if(other.head->next != other.head)
        {
            Node *p = head;
            Node *q = other.head->next;
            while (q != other.head)
            {
                p->next = new Node(q->data, p);
                p = p->next;
                q = q->next;
            }
            p->next = head;
            head->prev = p;
        }
        else
        {
            head->next = head;
        }
        return *this;
    }

    void push_back(const int _data)
    {
        Node *p = head;
        while (p->next != head)
        {
            p = p->next;
        }
        p->next = new Node(_data, p, head);
        head->prev = p->next;
    }

    void push_front(const int _data)
    {
        head->next = new Node(_data, head, head->next);
        head->next->next->prev = head->next;
    }

    unsigned size() const
    {
        unsigned count = 0;
        Node *p = head;
        while(p->next != head)
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
        friend class HeadedCircularLinkedList;
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
        return iterator(head->next);
    }
    iterator end()
    {
        return head;
    }
    /**
     * Itt a kétirányúság és a fejelem miatt célszerű definiálni a másik irányú bejáráshoz is kezdő/végpontot.
     * Namost ezekhez illene írni egy reverse_iterator-t is, ahol felüldefiniáljuk a ++ és -- operátort, hogy
     * másik irányba menjenek. Ezt meghagyom házi feladatnak ;) (olyankor értelemszerűen a visszatéréis érték
     * is reverse_iterator iterator helyett)
     */
    iterator rbegin()
    {
        return iterator(head->prev);
    }
    iterator rend()
    {
        return iterator(head);
    }

    void insert(iterator pos, const int _data)
    {
        if(pos == end())
        {
            head->next = new Node(_data, head, head->next);
        }
        else
        {
            pos.parent->next = new Node(*pos, pos.parent, pos.parent->next);
            if(pos.parent->next->next != head)
            {
                pos.parent->next->next->prev = pos.parent->next;
            }
            pos.parent->data = _data;
        }
    }

    void erase(iterator pos)
    {
        if(pos.parent == head)
        {
            Node *tmp = head->next;
            head->prev->next = head->next;
            head->next->prev = head->prev;
            delete head;
            head = tmp;
        }
        else
        {
            pos--;
            Node *tmp = pos.parent->next->next;
            delete pos.parent->next;
            pos.parent->next = tmp;
            pos.parent->next->prev = pos.parent;

        }
    }
};

#endif // HEADEDCIRCULARLINKEDLIST_H
