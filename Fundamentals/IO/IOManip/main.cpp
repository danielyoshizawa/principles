#include <iostream>
#include <iomanip>

int main()
{
    std::cout << "Iomanip" << std::endl;
    std::cout << "Hexadecimal" << std::endl;
    std::cout << std::hex;
    std::cout << "Set IOS Flags : showbase" << std::endl;
    std::cout <<  std::setiosflags(std::ios::showbase);
    std::cout << 100 << std::endl;
    std::cout << "Reset IOS Flags : showbase" << std::endl;
    std::cout << std::resetiosflags(std::ios::showbase);
    std::cout << 100 << std::endl;
    std::cout << "Decimal" << std::endl;
    std::cout << std::dec;
    std::cout << 100 << std::endl;
    std::cout << "Octadecimal" << std::endl;
    std::cout << std::oct;
    std::cout << 100 << std::endl;
    std::cout << "Hexadecimal using std::setbase" << std::endl;
    std::cout << std::setbase(16);
    std::cout << 100 << std::endl;
    std::cout << "Filling the begin with x, using std::setfill" << std::endl;
    std::cout << std::setfill('x') << std::setw(32);
    std::cout << "This is complicated" << std::endl;
    std::cout << "Adding padding with std::setw" << std::endl;
    std::cout << std::setfill(' ') << std::setw(24) << std::dec << 9 << std::endl;
    std::cout << "Setting double precision using std::setprecision" << std::endl;
    double d = 3.14151617181920;
    std::cout << std::setprecision(5) << d << std::endl;
    std::cout << std::setprecision(9) << d << std::endl;
    std::cout.precision(4);
    std::cout << "Using fixed" << std::endl;
    std::cout << std::fixed << d << std::endl;
    std::cout << "Using scientific" << std::endl;
    std::cout << std::scientific << d << std::endl;
    std::cout << "Making boolean readable using boolalpha" << std::endl;
    std::cout << std::boolalpha << true << std::endl;
    std::cout << std::boolalpha << false << std::endl;
    std::cout << std::noboolalpha << false << std::endl;

    return 0;
}