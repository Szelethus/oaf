#ifndef SET_H
#define SET_H

#include "vector.h"
#include "headedlinkedlist.h"
#include "headedcircularforwardlinkedlist.h"
#include "headedcircularlinkedlist.h"

/**
 * Halmaz. Látható, hogy a Vector átírása mondjuk HeadedLinkedList-é teljes mértékig lehetséges, és ugyanazt az eredményt adja.
 */

class Set
{
    typedef HeadedCircularForwardLinkedList Container;
    typedef Container::iterator ContIterator;

    Container cont;
public:
    void insert(const int data)
    {
        for(auto i = cont.begin(); i != cont.end(); i++)
        {
            if ((data < *i) == false)
            {
                if((*i < data) == false) //ekvivalensek
                {
                    return;
                }
            }
            else if((*i < data) == false)
            {
                cont.insert(i, data);
                return;
            }
        }
        cont.push_back(data);
    }

    class iterator
    {
        friend class Set;
        ContIterator parent;
    public:
        iterator(ContIterator _parent) : parent(_parent) {}

        bool operator==(const iterator &other)
        {
            return parent == other.parent;
        }
        bool operator!=(const iterator &other)
        {
            return !(*this == other);
        }
        const int& operator*() //halmaznál nem szokás engedni, hogy a felhasználó tudja módosítani az elemeket.
        {
            return *parent;
        }
        iterator operator++() // ++it
        {
            parent++;
            return *this;
        }
        iterator operator++(int) //it++
        {
            return operator++();
        }
        /**
         * Ez következő két függvény nyilván csak akkor írjuk meg, ha kétirányú listánk/sorunk/vektorunk van.
         */
        /*iterator operator--() //--it
        {
            parent--;
            return *this;
        }
        iterator operator--(int)
        {
            return operator--();
        }*/
    };

    iterator begin()
    {
        return iterator(cont.begin());
    }
    iterator end()
    {
        return iterator(cont.end());
    }

    void erase(iterator pos)
    {
        cont.erase(pos.parent);
    }

    unsigned size() const
    {
        return cont.size();
    }
};

#endif // SET_H
