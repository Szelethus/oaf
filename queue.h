#ifndef QUEUE_H
#define QUEUE_H

/**
 * Sor. Figyeljük meg a turpisságot: ez egy az egyben a vektor, csak fordított sorrendben ad vissza, töröl és szúr be.
 * (meg picit hatékonyabb az insert, de azt ilyen típusú konténereknél ne használjuk)
 *
 * Bizonyára létezik elegánsabb megoldás, de sokkal egyszerűbb a vektor ismeretében alig :D
 *
 * swap függvény hiányzik!! (én csúnya módon preprocesszor parancsokal értem el hogy benne legyen)
 */

class Queue
{
    unsigned current_size;
    unsigned max_size;
    int *ptr;
public:
    //sok szenvedést megspórolhatunk, ha nem engedjük meg a felhasználónak hogy üres sort hozzon létre :3
    Queue() : current_size(0), max_size(5), ptr(new int[max_size]) {}
    ~Queue()
    {
        delete [] ptr;
    }
    Queue(const Queue &other) : current_size(other.current_size), max_size(other.max_size), ptr(new int[max_size])
    {
        for (unsigned i = 0; i<other.size(); i++)
        {
            ptr[i] = other.ptr[i];
        }
    }
    Queue& operator=(const Queue &other)
    {
        if(this == &other) return *this;
        delete [] ptr;
        current_size = other.current_size;
        max_size = other.max_size;
        ptr = new int[max_size];
        for (unsigned i = 0; i<other.size(); i++)
        {
            ptr[i] = other.ptr[i];
        }
        return *this;
    }

    void push_front(int data)
    {
        if (current_size == max_size)
        {
            int *tmp = ptr;
            max_size *= 2;
            ptr = new int[max_size];
            for (unsigned i = 0; i<current_size; i++)
            {
                ptr[i] = tmp[i];
            }
            delete [] tmp;
        }
        ptr[current_size] = data;
        current_size++;
    }

    void pop_front()
    {
        current_size--;
    }

    /**
     * Gyakorlatilag egy felsoroló, csak nem egy rakás szar megvalósítással mitn EA-n.
     * Ha cpp vizsgán lennénk, örökölnénk továbbá az std::iterator<std::random_access_iterator_tag, int> osztályból publikusan.
     */
    class iterator
    {
        friend class Queue;
        Queue *parent;
        unsigned position;
    public:
        iterator(Queue *_parent, const unsigned _position) : parent(_parent), position(_position) {}
        bool operator==(const iterator &other)
        {
            return position == other.position;
        }
        bool operator!=(const iterator &other)
        {
            return !(*this == other);
        }
        int& operator*()
        {
            return (*parent)[position];
        }
        iterator operator++() // ++it
        {
            position++;
            return *this;
        }
        iterator operator++(int) //it++
        {
            return operator++();
        }
        iterator operator--() //--it
        {
            position--;
            return *this;
        }
        iterator operator--(int)
        {
            return operator--();
        }
        iterator operator+(const int a)
        {
            return iterator(parent, position + a);
        }
        iterator operator-(const int a)
        {
            return iterator(parent, position - a);
        }
        int operator-(const iterator &other)
        {
            return position - other.position;
        }
    };

    iterator begin()
    {
        return iterator(this, 0);
    }
    iterator end()
    {
        return iterator(this, current_size);
    }

    class const_iterator
    {
        friend class Vector;
        const Queue *parent;
        unsigned position;
    public:
        const_iterator(const Queue *_parent, const unsigned _position) : parent(_parent), position(_position) {}
        bool operator==(const const_iterator &other)
        {
            return position == other.position;
        }
        bool operator!=(const const_iterator &other)
        {
            return !(*this == other);
        }
        const int& operator*() const
        {
            return (*parent)[position];
        }
        const_iterator operator++() // ++it
        {
            position++;
            return *this;
        }
        const_iterator operator++(int) //it++
        {
            return operator++();
        }
        const_iterator operator--() //--it
        {
            position--;
            return *this;
        }
        const_iterator operator--(int)
        {
            return operator--();
        }
        const_iterator operator+(const int a)
        {
            return const_iterator(parent, position + a);
        }
        const_iterator operator-(const int a)
        {
            return const_iterator(parent, position - a);
        }
        int operator-(const const_iterator &other)
        {
            return position - other.position;
        }
    };

    const_iterator begin() const
    {
        return const_iterator(this, 0);
    }
    const_iterator end() const
    {
        return const_iterator(this, current_size);
    }

    void insert(iterator _pos, const int data)
    {
        if(_pos.position == 0)
        {
            push_front(data);
            return;
        }
        unsigned pos = current_size - _pos.position;
        if(current_size == max_size)
        {
            max_size *= 2;
            int *tmp = ptr;
            ptr = new int[max_size];
            for (unsigned i = 0; i<pos; i++)
            {
                ptr[i] = tmp[i];
            }
            ptr[pos] = data;
            for (unsigned i = pos + 1; i<current_size + 1; i++)
            {
                ptr[i] = tmp[i - 1];
            }
            delete [] tmp;
        }
        else
        {
            int tmp = ptr[pos];
            ptr[pos] = data;
            for(unsigned i = pos + 1; i<current_size; i++)
            {
                swap(ptr[i], tmp);
            }
            if (current_size != 0)
            {
                ptr[current_size] = tmp;
            }
        }
        current_size++;
    }

    void erase(iterator pos)
    {
        if (current_size == 0) return;
        for (unsigned i  = current_size - pos.position - 1; i < current_size - 1; i++)
        {
            swap(ptr[i], ptr[i+1]);
        }
        current_size--;
    }

    void push_back(const int data) //csak azt akartam hogy működjön a tesztelés... nem épp elegáns megoldás, insertből copyztam O:) sorban úgy se illik push_back-et írni O:)
    {
        if(current_size == max_size)
        {
            max_size *= 2;
            int *tmp = ptr;
            ptr = new int[max_size];
            ptr[0] = data;
            for (unsigned i = 0; i<current_size; i++)
            {
                ptr[i + 1] = tmp[i];
            }
            delete [] tmp;
        }
        else
        {
            int tmp = ptr[0];
            ptr[0] = data;
            for(unsigned i = 1; i<current_size; i++)
            {
                swap(ptr[i], tmp);
            }
            if (current_size != 0)
            {
                ptr[current_size] = tmp;
            }
        }
        current_size++;
    }

    int& operator[](const int i)
    {
        return ptr[current_size - i - 1];
    }
    const int& operator[](const int i) const
    {
        return ptr[current_size - i - 1];
    }

    unsigned size() const
    {
        return current_size;
    }
};

#endif // QUEUE_H
