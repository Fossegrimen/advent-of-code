
#include <algorithm>
#include <iostream>
#include <string>

int main()
{
    size_t valid = 0;
    char tempChar;

    size_t min;
    size_t max;
    char character;
    std::string password;

    while (std::cin >> min &&
           std::cin >> tempChar &&
           std::cin >> max &&
           std::cin >> character &&
           std::cin >> tempChar &&
           std::cin >> password)
    {
        size_t count = std::count(password.begin(), password.end(), character);

        if (count >= min && count <= max)
        {
            valid++;
        }
    }

    std::cout << valid << std::endl;

    return 0;
}
