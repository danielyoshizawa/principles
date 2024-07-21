#include <memory>
#include <iostream>

// Weak Pointer
// The weak pointer is used to solve the circular reference problem of shared pointers.
// When two objects reference each other, they create a circular reference, which prevents the garbage collector from deleting them.
// The weak pointer is a non-owning reference to a shared pointer. So, deleting the shared pointer does not affect the weak pointer.

// Characteristics:
// 1. Non-owning reference to a shared_ptr
// 2. Does not contribute to the reference count
// 3. Does not prevent the managed object from being deleted
// 4. Can be converted to a shared_ptr
// 5. Can be used to check if the managed object is still available
// 6. Can be used to break the circular reference

// Use case:
// 1. When you want to reference an object that is managed by a shared_ptr but do not want to contribute to the reference count.
// 2. When you want to break the circular reference between two objects.

#include <iostream>
#include <memory>

class Node {
public:
    std::string name;
    std::shared_ptr<Node> next;
    std::weak_ptr<Node> prev; // Use weak_ptr to break the circular reference
    // std::shared_ptr<Node> prev; // This will create a circular reference

    Node(const std::string& name) : name(name) {
        std::cout << "Node " << name << " created\n";
    }

    ~Node() {
        std::cout << "Node " << name << " destroyed\n";
    }
};

int main() {
    {
        // Create two nodes
        std::shared_ptr<Node> node1 = std::make_shared<Node>("Node1");
        std::shared_ptr<Node> node2 = std::make_shared<Node>("Node2");

        // Create a circular reference
        node1->next = node2;
        node2->prev = node1;

        // At this point, node1 and node2 reference each other
        std::cout << "node1 use count: " << node1.use_count() << std::endl; // Output: 1
        std::cout << "node2 use count: " << node2.use_count() << std::endl; // Output: 2 (node1->next and node2->prev.lock())

        // Breaking the circular reference
        if (auto prevNode = node2->prev.lock()) { // Use lock to safely access the managed object, if the object is destroyed, lock will return an empty shared_ptr
            std::cout << "node2's previous node is: " << prevNode->name << std::endl;
        }
    }

    // Both nodes should be destroyed here
    std::cout << "End of scope\n";

    return 0;
}