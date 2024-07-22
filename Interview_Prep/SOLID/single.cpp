#include <iostream>
#include <string>

// Single Responsibility Principle (SRP)

// Definition : A class should have only one reason to change, meaning it should have only one responsibility.

// Explanation: Each class should focus on a single task or responsibility. 
// This makes the class easier to understand, test, and maintain. 
// If a class has multiple responsibilities, changes to one responsibility might affect the other, 
// leading to a fragile design.

// Before SRP: A class with multiple responsibilities
class User {
public:
    void save() {
        // Save user to database
    }

    void sendEmail() {
        // Send email to user
    }
};

// After SRP: Separate classes for each responsibility
class User {
public:
    void save() {
        // Save user to database
    }
};

class EmailService {
public:
    void sendEmail(const User& user) {
        // Send email to user
    }
};