#include <iostream>
#include <fstream>
#include <sstream>

int main()
{
    std::fstream fs{"test.txt", std::fstream::in | std::fstream::out | std::fstream::trunc};
    if (fs.is_open())
    {
        fs << "Testing fstream" << std::endl;
        fs << "Adding a second" << std::endl;
        fs << "and a third line" << std::endl;

        // Read the whole file
        std::cout << "Using fstream::read" << std::endl;
        // Getting the length
        fs.seekg(0, fs.beg);
        fs.seekg(0, fs.end);
        int length = fs.tellg();
        fs.seekg(0, fs.beg);
        // Creating a char* to hold all data
        char *data = new char[length];
        fs.read(data, length);

        // printing content
        std::cout.write(data, length);
        delete[] data;

        std::cout << "Using fstream::getline" << std::endl;

        std::string line;
        fs.seekg(0, fs.beg); // Returns carrier to file begin
        // Read line by line
        while (getline(fs, line)) // Destructive reading process
        {
            std::cout << line << std::endl;
        }

        fs.close();
    }
    else
    {
        std::cout << "Unable to open the file" << std::endl;
    }
    return 0;
}