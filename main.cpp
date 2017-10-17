#include <iostream>

void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

#include "vector.h"
#include "queue.h"
#include "forwardlinkedlist.h"
#include "headedforwardlinkedlist.h"
#include "headedcircularforwardlinkedlist.h"
#include "linkedlist.h"
#include "headedlinkedlist.h"
#include "headedcircularlinkedlist.h"
#include "set.h"
#include "multiset.h"
#include <stdexcept>

//TODO : Possible dead code in HCL erase. (first if) (NOT IMPORTANT)
//TODO : push_front in HL and HCL, possibly LL. (CRUCIAL)

typedef HeadedLinkedList HeadedContainer;

void test(HeadedContainer &a)
{
    bool ok = true;
    try
    {
        /**
         * push_back check.
         */
        for (int i = 0; i<10; i++)
        {
            a.push_back(i);
        }
        //for(auto &i : a) std::cout << i << std::endl;
        auto j1 = a.begin();
        for (int i = 0; i<10; i++)
        {
            ok = (ok &&(*j1 == i));
            j1++;
        }
        std::cout << "push_back? " << (ok? "ok." : "not ok.") << std::endl;

        /**
         * bidirectional iterator check.
         */
        ok = true;
        auto j12 = a.begin();
        for (int i = 0; i<9; i++)
        {
            //std::cout << *j12 << std::endl;
            ok = (ok &&(*j12 == i));
            j12++;
        }
        //for (auto &i : a) std::cout << i << std::endl;
        for (int i = 9; i>0; i--)
        {
            //std::cout << *j12 << std::endl;
            ok = (ok &&(*j12 == i));
            j12--;
        }
        std::cout << "bidirectional iterator? " << (ok? "ok." : "not ok.") << std::endl;
        /**
         * size check.
         */
        ok = true;
        ok = (a.size() == 10);
        std::cout << "size of non-empty container? " << (ok? "ok." : "not ok.") << std::endl;

        /**
         * operator= check.
         */
        {
            HeadedContainer b;
            b = a;
            b.push_front(666);
            b.erase(b.begin()++);
        }
        ok = true;
        auto j2 = a.begin();
        for (int i = 0; i<10; i++)
        {
            ok = (ok &&(*j2 == i));
            j2++;
        }
        std::cout << "op=? " <<(ok? "ok." : "not ok.") << std::endl;


        /**
         * copy ctor check.
         */
        ok = true;
        {
            HeadedContainer b = a;
            b.push_front(666);
            b.erase(b.begin()++);
        }
        ok = true;
        auto j3 = a.begin();
        for (int i = 0; i<10; i++)
        {
            ok = (ok &&(*j3 == i));
            j3++;
        }
        std::cout << "copy ctor? " << (ok? "ok." : "not ok.") << std::endl;

        /**
         * push_front check.
         */
        ok = true;
        a.push_front(420);
        auto j4 = a.begin();
        ok = (ok &&(*j4 == 420));
        std::cout << "push_front? " << (ok? "ok." : "not ok.") << std::endl;

        /**
         * push_front rest of the elements check.
         */
        ok = true;
        j4++;
        for (int i = 0; i<10; i++)
        {
            ok = (ok &&(*j4 == i));
            j4++;
        }
        std::cout << "rest of the elements after push_front? " << (ok? "ok." : "not ok.") << std::endl;

        /**
         * erasing first element check.
         */
        ok = true;
        a.erase(a.begin());
        auto j5 = a.begin();
        for (int i = 0; i<10; i++)
        {
            ok = (ok &&(*j5 == i));
            j5++;
        }
        std::cout << "erasing first element? " << (ok? "ok." : "not ok.") << std::endl;

        /**
         * Erasing all elements.
         */
        ok = true;
        for (int i = 0; i<10; i++)
        {
            a.erase(a.begin());
        }
        ok = (a.begin() == a.end());
        std::cout << "erasing all elements? " << (ok? "ok." : "not ok.") << std::endl;

        /**
         * size check.
         */
        ok = true;
        ok = (a.size() == 0);
        std::cout << "size of empty container? " << (ok? "ok." : "not ok.") << std::endl;

        /**
         * push_front2 check.
         */
        ok = true;
        for (int i = 0; i<10; i++)
        {
            a.push_front(i);
        }
        auto j6 = a.begin();
        for (int i = 9; i>=0; i--)
        {
            ok = (ok &&(*j6 == i));
            j6++;
        }
        std::cout << "push_front2? " << (ok? "ok." : "not ok.") << std::endl;

        /**
         * bidirectional iterator check.
         */
        ok = true;
        auto j13 = a.begin();
        for (int i = 9; i>1; i--)
        {
            ok = (ok &&(*j13 == i));
            j13++;
        }
        //for (auto &i : a) std::cout << i << std::endl;
        for (int i = 1; i<10; i++)
        {
            //std::cout << *j13 << " " << i << std::endl;
            ok = (ok &&(*j13 == i));
            j13--;
        }
        std::cout << "bidirectional iterator2? " << (ok? "ok." : "not ok.") << std::endl;

        /**
         * random element erase check.
         */
        ok = true;
        a.erase(a.begin()++);
        //for (auto &i : a) std::cout << i << std::endl;
        auto j7 = a.begin();
        ok = (*j7 == 9);
        j7++;
        for (int i = 7; i>=0; i--)
        {
            ok = (ok &&(*j7 == i));
            j7++;
        }
        std::cout << "random element erase? " << (ok? "ok." : "not ok.") << std::endl;
        /**
         * Insert at random place.
         */
        ok = true;
        a.insert(a.begin()++, 8);
        //for (auto &i : a) std::cout << i << std::endl;
        auto j8 = a.begin();
        for (int i = 9; i>=0; i--)
        {
            ok = (ok &&(*j8 == i));
            j8++;
        }
        std::cout << "random element insert? " << (ok? "ok." : "not ok.") << std::endl;
        /**
         * erase at end check.
         */
        ok = true;
        a.erase(a.begin()++++++++++++++++++);
        auto j9 = a.begin();
        for (int i = 9; i>0; i--)
        {
            ok = (ok &&(*j9 == i));
            j9++;
        }
        std::cout << "erase at end? " << (ok? "ok." : "not ok.") << std::endl;
        /**
         * insert at begin check.
         */
        ok = true;
        a.insert(a.begin(), 10);
        auto j10 = a.begin();
        for (int i = 10; i>0; i--)
        {
            ok = (ok &&(*j10 == i));
            j10++;
        }
        std::cout << "insert at begin? " << (ok? "ok." : "not ok.") << std::endl;
        /**
         * bidirectional iterator check.
         */
        ok = true;
        auto j11 = a.begin();
        for (int i = 10; i>1; i--)
        {
            ok = (ok &&(*j11 == i));
            j11++;
        }
        //for (auto &i : a) std::cout << i << std::endl;
        for (int i = 1; i<9; i++)
        {
            //std::cout << *j11 << std::endl;
            ok = (ok &&(*j11 == i));
            j11--;
        }
        std::cout << "bidirectional iterator3? " << (ok? "ok." : "not ok.") << std::endl;
    }
    catch(std::exception &exc)
    {
        std::cout << exc.what();
    }
    catch(...)
    {
        std::cout << "Some uncaught exception!" << std::endl;
    }
}

int main()
{
    HeadedContainer a;
    test(a);
    return 0;
}
