#include <iostream>
using namespace std;


class A
{
public:
    A(int x): a(x){}
    int a;
    void func()
    {
        cout << "A::func() a = " << a << endl;
    }

    virtual void func2()
    {
        cout << "A::func2() a = " << a << endl;
    }
};

class B: public A
{
public:
    B(int x, int y): A(x), b(y){}

    int b;
    /* int func()
    {
        A::func();
        cout << "B::func() b = " << b << " a = "<< a << endl;
        return 0;
    } */
    /* void func2() override
    {
        A::func2();
        cout << "B::func2() b = " << b << " a = "<< a << endl;
    } */
};

class C : private A
{
public:
    C(int x, int y): A(x), c(y){}

    int c;
    /* int func()
    {
        A::func();
        cout << "C::func() c = " << c << " a = "<< a << endl;
        return 0;
    } */

    /* void func2() override
    {
        A::func2();
        cout << "C::func2() c = " << c << " a = "<< a << endl;
    } */
};

int main()
{
    A a(1);
    a.func();
    a.func2();

    B b(1,2);
    b.func();
    b.func2();

    C c(3,4);
    c.func();
    c.func2();

    A *pa = &b;
    pa->func();
    pa->func2();

    return 0;

}


