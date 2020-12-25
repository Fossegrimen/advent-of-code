
#include <iostream>

int main()
{
    uint64_t pKey1;
    uint64_t pKey2;

    std::cin >> pKey1;
    std::cin >> pKey2;

    uint64_t sKey1 = 7;
    uint64_t sKey2 = pKey2;

    uint64_t tmp1 = 1;
    uint64_t tmp2 = 1;

    for (size_t i = 1; i < 10000000; i++)
    {
        tmp1 *= sKey1;
        tmp2 *= sKey2;

        tmp1 %= 20201227;
        tmp2 %= 20201227;

        if (tmp1 == pKey1)
        {
            std::cout << tmp2 << std::endl;
            return 0;
        }
    }

    return 1;
}
