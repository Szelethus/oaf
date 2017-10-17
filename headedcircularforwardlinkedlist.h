#ifndef HEADEDCIRCULARFORWARDLINKEDLIST_H
#define HEADEDCIRCULARFORWARDLINKEDLIST_H

/**
 * Fejelemes ciklikus egyirányű lista. A head utáni listaelem tartalmazhat adatot, de alapértelmezetten nem használatos.
 * Az end() iterátor pont arra az elemre mutat. (de általában [begin , end) szokott lenni egy ciklus, így azt az elemet
 * ritkán érintjük)
 *
 * Erősen javallott typedef használata, pl.: typedef HeadedCircilarForwardLinkedList::iterator HCFLiterator;
 */
#include <iterator>

class HeadedCircularForwardLinkedList
{
    struct Node //nem publikus!
    {
        int data;
        Node* next;
        explicit Node(const int _data, Node* _next = nullptr) : data(_data), next(_next){}
    };

    Node* head;
public:
    HeadedCircularForwardLinkedList() : head(new Node(666))
    {
        head->next = head;
    }

    ~HeadedCircularForwardLinkedList()
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

    HeadedCircularForwardLinkedList(const HeadedCircularForwardLinkedList &other) : head(new Node(other.head->data))
    {
        if(other.head->next != other.head)
        {
            Node *p = head;
            Node *q = other.head->next;
            while (q != other.head)
            {
                p->next = new Node(q->data);
                p = p->next;
                q = q->next;
            }
            p->next = head;
        }
    }

    HeadedCircularForwardLinkedList& operator=(const HeadedCircularForwardLinkedList &other)
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
                p->next = new Node(q->data);
                p = p->next;
                q = q->next;
            }
            p->next = head;
        }
        return *this;
    }

    void push_back(const int data)
    {
        Node *p = head;
        while (p->next != head)
        {
            p = p->next;
        }
        p->next = new Node(data, head);
    }

    void push_front(const int data)
    {
        head->next = new Node(data, head->next);
    }

    unsigned size() const
    {
        unsigned count = 0; //lehet üres!
        Node *p = head;
        while(p->next != head)
        {
            p = p->next;
            count++;
        }
        return count;
    }

    class iterator : std::iterator<std::bidirectional_iterator_tag, int>
    {
        friend class HeadedCircularForwardLinkedList;
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
        return iterator(head->next);
    }
    iterator end()
    {
        return iterator(head);
    }
    //nincs end függvény!

    void insert(iterator pos, const int _data)
    {
        if(pos == end())
        {
            head->next = new Node(_data, head->next);
        }
        else
        {
            pos.parent->next = new Node(*pos, pos.parent->next);
            pos.parent->data = _data;
        }
    }

    void erase(iterator pos)
    {
        if(pos.parent == head) return;
        if(pos.parent->next == head)
        {
            Node *p = head;
            while(p->next != pos.parent)
            {
                p = p->next;
            }
            p->next = head;
            delete pos.parent;
        }
        else
        {
            pos.parent->data = pos.parent->next->data;
            Node *tmp = pos.parent->next->next;
            delete pos.parent->next; //nem kell nullptr-é tenni: Node-nak nincs felüldefiniált destruktora.
            pos.parent->next = tmp;
        }
    }
};

#endif // HEADEDCIRCULARFORWARDLINKEDLIST_H
