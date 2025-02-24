#include "ClassTemplate.h"

int main()
{
    Box<int> intBox(123);
    std::cout << "Int Box: " << intBox.getContent() << std::endl;

    Box<std::string> strBox("Hello, World!");
    std::cout << "String Box: " << strBox.getContent() << std::endl;
}