#include <iostream>
#include <memory>

// Unique pointer
// std::unique_ptr is a smart pointer that manages a single object and ensures its unique ownership.
// It automatically deletes the managed object when the unique_ptr goes out of scope.

// Characteristics:
// 1. Unique Ownership: Only one unique_ptr can manage an object at a time.
// 2. Automatic Deletion: The managed object is automatically deleted when the unique_ptr is destroyed.
// 3. No Copying: unique_ptr cannot be copied.

// Use case
// 1. When you want to ensure that an object is uniquely owned and automatically deleted when it goes out of scope.
// 2. When you want to transfer ownership of an object from one function to another.
// 3. Suitable for managing resources with strict ownership semantics, such as file handlers or sockets.

class Unique {
    public:
        Unique() {
            std::cout << "Unique" << std::endl;
        }

        ~Unique() {
            std::cout << "Unique destroyed" << std::endl;
        }

        void print() {
            std::cout << "Unique print" << std::endl;
        }
};

int main() {
    std::unique_ptr<Unique> unique = std::make_unique<Unique>();
    unique->print();
    // std::unique_ptr<Unique> unique2 = unique; // This will cause a compilation error
    std::unique_ptr<Unique> unique2 = std::move(unique);
    unique2->print();

    return 0;
}