#include <iostream>
#include <string>

// Open Closed Principle (OCP)

// Definition: Software entities (classes, modules, functions, etc.) should be open for extension 
// but closed for modification.

// Explanation: You should be able to extend the behavior of a class without modifying its 
// source code. This can be achieved through inheritance, interfaces, and polymorphism. 
// This principle helps in making the system more flexible and easier to maintain.


// Before OCP: Modifying existing code to add new behavior
class Rectangle {
public:
    virtual double area() const {
        return width * height;
    }

protected:
    double width;
    double height;
};

// After OCP: Extending behavior without modifying existing code
class Shape {
public:
    virtual double area() const = 0;
};

class Rectangle : public Shape {
public:
    double area() const override {
        return width * height;
    }

private:
    double width;
    double height;
};

class Circle : public Shape {
public:
    double area() const override {
        return 3.14 * radius * radius;
    }

private:
    double radius;
};