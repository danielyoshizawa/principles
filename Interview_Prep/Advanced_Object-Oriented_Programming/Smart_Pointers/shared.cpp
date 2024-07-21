#include <iostream>
#include <memory>

// Shared Pointer
// std::shared_ptr is a smart pointer that manages a single object and ensures its shared ownership.
// It automatically deletes the managed object when the last shared_ptr goes out of scope.

// Characteristics:
// 1. Shared Ownership: Multiple shared_ptr can manage the same object.
// 2. Automatic Deletion: The managed object is automatically deleted when the last shared_ptr is destroyed.
// 3. Reference Counting: shared_ptr keeps track of the number of shared_ptr instances that manage the same object.

// Use cases:
// 1. When you want to ensure that an object is shared among multiple objects and automatically deleted when the last shared_ptr is destroyed.
// 2. When you want to transfer ownership of an object from one function to another.
// 3. Suitable for managing resources that can be shared among multiple objects, such as network connections or file handles.

class Shared {
    public:
        Shared() {
            std::cout << "Shared" << std::endl;
        }
        ~Shared() {
            std::cout << "Shared destroyed" << std::endl;
        }
        void print() {
            std::cout << "Shared print" << std::endl;
        }
};

int main() {
    std::shared_ptr<Shared> shared = std::make_shared<Shared>();
    std::shared_ptr<Shared> shared2 = shared;
    shared->print();
    shared2->print();

    return 0;
}