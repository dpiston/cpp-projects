#include <iostream>

int add(int x, int y)
{
    return x + y;
}

int main()
{
    std::cout << "Enter two numbers seperated by a space: ";
    int num1 {};
    int num2 {};
    std::cin >> num1 >> num2;
    std::cout << add(num1, num2);
    return 0;
}
