
#include <algorithm>
#include <iostream>
#include <string>

int main()
{
    size_t valid = 0;
    char tempChar;

    size_t posA;
    size_t posB;
    char character;
    std::string password;

    while (std::cin >> posA &&
           std::cin >> tempChar &&
           std::cin >> posB &&
           std::cin >> character &&
           std::cin >> tempChar &&
           std::cin >> password)
    {
        if ((password[posA - 1] == character && password[posB - 1] != character) ||
            (password[posA - 1] != character && password[posB - 1] == character))
        {
            valid++;
        }
    }

    std::cout << valid << std::endl;

    return 0;
}
