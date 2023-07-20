// Here is where move shines, we will test
// the differences between copy and move
// using a vector, a container that does
// a lot of allocations. Vectors double
// its memory size everytime it reaches its limits
// and to do so, it copies all the elements
// from the previous container to the next.
#include <iostream>
#include <vector>
#include <string>

class Data
{
    std::string id;

public:
    Data(std::string id) : id{id}
    {
        std::cout << "ID : " << id << " | Data constructor" << std::endl;
    }
    ~Data()
    {
        std::cout << "ID : " << id << " | Data destructor" << std::endl;
    }
};

class Copyable
{
private:
    std::string id;
    Data *data;

public:
    Copyable(std::string id) : id{id}, data{new Data{id}}
    {
        std::cout << "ID : " << id << " | Copyable Constructor" << std::endl;
    }
    ~Copyable()
    {
        std::cout << "ID : " << id << " | Copyable Destructor" << std::endl;
    }
    Copyable(const Copyable &copyable)
    {
        id = copyable.id;
        std::cout << "ID : " << id << " | Copy Constructor" << std::endl;
        data = new Data{copyable.id};
    }
    Copyable &operator=(const Copyable &copyable)
    {
        id = copyable.id;
        std::cout << "ID : " << id << " | Copy Assignment" << std::endl;
        data = new Data{copyable.id};

        return *this;
    }
};

class Movable
{
private:
    std::string id;
    Data *data;

public:
    Movable(std::string id) : id{id}, data{new Data{id}}
    {
        std::cout << "ID : " << id << " | Movable Constructor" << std::endl;
    }
    ~Movable()
    {
        std::cout << "ID : " << id << " | Movable Destructor" << std::endl;
    }
    Movable(Movable &&movable)
    {
        id = movable.id;
        std::cout << "ID : " << id << " | Move Constructor" << std::endl;
        data = movable.data;
        movable.data = nullptr;
    }
    Movable &operator=(Movable &&movable)
    {
        if (&movable == this)
        {
            return *this;
        }
        id = movable.id;
        std::cout << "ID : " << id << " | Move Assignment" << std::endl;
        delete data;
        data = movable.data;
        movable.data = nullptr;

        return *this;
    }
};

int main()
{
    // Lets create 3 of each type and store in 2 separate vector
    // to test how allocation happens when the vector reaches its limits
    std::vector<Copyable> copyVector;
    std::cout << "Pushing First Copyable" << std::endl;
    copyVector.push_back(Copyable{"COPY-01"});
    std::cout << "Pushing Second Copyable" << std::endl;
    copyVector.push_back(Copyable{"COPY-02"});
    std::cout << "Pushing Third Copyable" << std::endl;
    copyVector.push_back(Copyable{"COPY-03"});

    std::vector<Movable> moveVector;
    std::cout << "Pushing First Movable" << std::endl;
    moveVector.push_back(Movable{"MOVE-01"});
    std::cout << "Pushing Second Movable" << std::endl;
    moveVector.push_back(Movable{"MOVE-02"});
    std::cout << "Pushing Third Movable" << std::endl;
    moveVector.push_back(Movable{"MOVE-03"});

    std::cout << "Deallocating vectors" << std::endl;
    return 0;
}
// Output : 
// Pushing First Copyable
// ID : COPY-01 | Data constructor
// ID : COPY-01 | Copyable Constructor
// ID : COPY-01 | Copy Constructor
// ID : COPY-01 | Data constructor
// ID : COPY-01 | Copyable Destructor
// Pushing Second Copyable
// ID : COPY-02 | Data constructor
// ID : COPY-02 | Copyable Constructor
// ID : COPY-02 | Copy Constructor
// ID : COPY-02 | Data constructor
// ID : COPY-01 | Copy Constructor
// ID : COPY-01 | Data constructor
// ID : COPY-01 | Copyable Destructor
// ID : COPY-02 | Copyable Destructor
// Pushing Third Copyable
// ID : COPY-03 | Data constructor
// ID : COPY-03 | Copyable Constructor
// ID : COPY-03 | Copy Constructor
// ID : COPY-03 | Data constructor
// ID : COPY-01 | Copy Constructor
// ID : COPY-01 | Data constructor
// ID : COPY-02 | Copy Constructor
// ID : COPY-02 | Data constructor
// ID : COPY-01 | Copyable Destructor
// ID : COPY-02 | Copyable Destructor
// ID : COPY-03 | Copyable Destructor
// Pushing First Movable
// ID : MOVE-01 | Data constructor
// ID : MOVE-01 | Movable Constructor
// ID : MOVE-01 | Move Constructor
// ID : MOVE-01 | Movable Destructor
// Pushing Second Movable
// ID : MOVE-02 | Data constructor
// ID : MOVE-02 | Movable Constructor
// ID : MOVE-02 | Move Constructor
// ID : MOVE-01 | Move Constructor
// ID : MOVE-01 | Movable Destructor
// ID : MOVE-02 | Movable Destructor
// Pushing Third Movable
// ID : MOVE-03 | Data constructor
// ID : MOVE-03 | Movable Constructor
// ID : MOVE-03 | Move Constructor
// ID : MOVE-01 | Move Constructor
// ID : MOVE-02 | Move Constructor
// ID : MOVE-01 | Movable Destructor
// ID : MOVE-02 | Movable Destructor
// ID : MOVE-03 | Movable Destructor
// Deallocating vectors
// ID : MOVE-01 | Movable Destructor
// ID : MOVE-02 | Movable Destructor
// ID : MOVE-03 | Movable Destructor
// ID : COPY-01 | Copyable Destructor
// ID : COPY-02 | Copyable Destructor
// ID : COPY-03 | Copyable Destructor

// The main difference here is that when the objects
// are passed around inside the vector structure,
// while on copy it will allocate memory for a
// new data object, and on move, it won't.
// Saving resources and being more efficient,
// consider that Data is a high cost object to create,
// or the number of elements pushed to the vector
// is very high and you don't know before hand
// how many will be, and you can see the problem.