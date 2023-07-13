#include <iostream>

class A
{
private:
    int i;
public:
    // The default constructor must exists so instances of class B and C
    // can call it. In our example, when creating an instance of Class D
    // this won't be called from B or C constructor.
    A()
    {
        std::cout << "Constructor A" << std::endl;
    }
    A(int i) : i{i}
    {
        std::cout << "Constructor A parameterized : " << i << std::endl;
    }
    void print()
    {
        std::cout << "Calling print from Class A" << std::endl;
    }
};
class B : virtual public A
{
public:
    B()
    {
        std::cout << "Constructor B" << std::endl;
    }
};
class C : virtual public A
{
public:
    C()
    {
        std::cout << "Constructor C" << std::endl;
    }
};
class D : public B, public C
{
public:
    D() : A{1}
    {
        std::cout << "Constructor D" << std::endl;
    }
};

int main()
{
    // To fix the diamond problem, we can use virtual inheritance
    // making Class B and Class C inherit virtually, will create a
    // virtual base class, which means there is only one base object.
    // The base object is shared between all objects in the inheritance tree
    // and it is only constructed once.
    D d;
    // Now that we fixed the ambiguity we can call functions from Class A.
    d.print();
    // However, this leads to one more problem, if B and C share a A base class,
    // who is responsible for creating it? The answer, as it turns out, is class D.
    // The class D constructor is responsible for creating A. Consequently, this
    // is one time when D is allowed to call a non-immediate-parent constructor directly.
    // If we create an instance of Class B or Class C, then it will respect
    // what is defined on their hierarchies.
    B b;
    // There are a few details to remember
    // 1. For the constructor of the most derived class, virtual base classes
    // are always created before non-virtual base classes, which ensures all bases
    // get created before their derived classes.
    // 2. Class B and Class C still have calls to Class A constructor. When creating
    // an instance of Class D, these constructors calls are ignored because Class D
    // is responsible for creating the Class A.
    // However, if we were to create an instance of Class B or Class C, those constructor
    // calls would be used, and normal inheritance rules applyed.
    // 3. If a class inherits one or more classes that have virtual parents, the most derived
    // class is responsible for constructing the virtual base class. In this case Class D
    // inherits Class B and Class C, both of which have Class A virtual base classes. Class D
    //, the most derived class, is responsible for creation of Class A. Note that this is true
    // even in a single inheritance case: If class D singly inherited from Class B, and Class B
    // was virtually inherited from Class A, Class D is still responsible for creating Class A.
    // 4. All classes inheriting a virtual base class will have a virtual table, even if they
    // would normally not have one otherwise, and thus instances of the class will be larger by a
    // pointer. Because Class B and CLass C derive virtually from Class A, Class D will only be
    // one Class A sub-object. Class B and Class C both need to know how to find that single
    // Class A sub-object, so they can access its members (because after all, they are derived from it).
    // This is typically done through some virtual table magic (which essentially stores the offset
    // from each subclass to the Class A sub-object).
}