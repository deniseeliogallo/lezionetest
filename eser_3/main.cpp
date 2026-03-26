
#include <iostream>
#include "classe.hpp"

int main(void)
{
rational<int> c(3,6);
std::cout << c << "\n";

rational<int> d(3,6);
rational<int> b(1,0);
std::cout << d.operator/(b) << "\n";
std::cout << b << "\n";

rational<int> r(-2,5);
rational<int> s(3,15);

std::cout << r.operator*(s) << "\n";
std::cout << r.operator+(s) << "\n";
std::cout << r.operator-(s) << "\n";

return 0;
}

