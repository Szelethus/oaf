#ifndef VECTOR_H
#define VECTOR_H

/**
 * Vektor.
 *
 * swap függvény hiányzik!! (én csúnya módon preprocesszor parancsokal értem el hogy benne legyen)
 */

class Vector
{
    unsigned current_size;
    unsigned max_size;
    int *ptr;
public:
    //sok szenvedést megspórolhatunk, ha nem engedjük meg a felhasználónak hogy üres vektort hozzon létre :3
    Vector() : current_size(0), max_size(5), ptr(new int[max_size]) {}
    ~Vector()
    {
        delete [] ptr;
    }
    Vector(const Vector &other) : current_size(other.current_size), max_size(other.max_size), ptr(new int[max_size])
    {
        for (unsigned i = 0; i<other.size(); i++)
        {
            ptr[i] = other.ptr[i];
        }
    }
    Vector& operator=(const Vector &other)
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

    void push_back(int data)
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

    void pop_back()
    {
        current_size--;
    }

    /**
     * Gyakorlatilag egy felsoroló, csak nem egy rakás szar megvalósítással mitn EA-n.
     * Ha cpp vizsgán lennénk, örökölnénk továbbá az std::iterator<std::random_access_iterator_tag, int> osztályból publikusan.
     */
    class iterator
    {
        friend class Vector;
        Vector *parent;
        unsigned position;
    public:
        iterator(Vector *_parent, const unsigned _position) : parent(_parent), position(_position) {}
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
        const Vector *parent;
        unsigned position;
    public:
        const_iterator(const Vector *_parent, const unsigned _position) : parent(_parent), position(_position) {}
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

    void erase(iterator pos)
    {
        if (current_size == 0) return;
        for (unsigned i  = pos.position; i < current_size - 1; i++)
        {
            swap(ptr[i], ptr[i+1]);
        }
        current_size--;
    }

    void insert(const iterator pos, const int data)
    {
        if(current_size == max_size)
        {
            max_size *= 2;
            int *tmp = ptr;
            ptr = new int[max_size];
            for (unsigned i = 0; i<pos.position; i++)
            {
                ptr[i] = tmp[i];
            }
            ptr[pos.position] = data;
            for (unsigned i = pos.position + 1; i<current_size + 1; i++)
            {
                ptr[i] = tmp[i - 1];
            }
            delete [] tmp;
        }
        else
        {
            int tmp = ptr[pos.position];
            ptr[pos.position] = data;
            for(unsigned i = pos.position + 1; i<current_size; i++)
            {
                swap(ptr[i], tmp);
            }
            if (current_size != 0) ptr[current_size] = tmp;
        }
        current_size++;
    }

    void push_front(const int data) //csak azt akartam hogy működjön a tesztelés... nem épp elegáns megoldás
    {
        insert(iterator(this, 0), data);
    }

    int& operator[](const int i)
    {
        return ptr[i];
    }
    const int& operator[](const int i) const
    {
        return ptr[i];
    }

    unsigned size() const
    {
        return current_size;
    }
};

#endif // VECTOR_H
