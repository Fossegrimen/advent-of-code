
#include <iostream>

int main()
{
    uint64_t sKey1 = 7;
    uint64_t sKey2 = 7;

    uint64_t pKey1;
    uint64_t pKey2;

    std::cin >> pKey1;
    std::cin >> pKey2;

    uint64_t pKey1Tmp = 1;
    uint64_t pKey2Tmp = 1;

    size_t pKey1LoopSize = 0;
    size_t pKey2LoopSize = 0;

    for (size_t i = 1; i < 10000000; i++)
    {
        pKey1Tmp *= sKey1;
        pKey1Tmp %= 20201227;

        if (pKey1Tmp == pKey1)
        {
            pKey1LoopSize = i;
            break;
        }
    }

    for (size_t i = 1; i < 10000000; i++)
    {
        pKey2Tmp *= sKey2;
        pKey2Tmp %= 20201227;

        if (pKey2Tmp == pKey2)
        {
            pKey2LoopSize = i;
            break;
        }
    }

    sKey1 = pKey1;
    sKey2 = pKey2;

    pKey1Tmp = 1;
    pKey2Tmp = 1;

    for (size_t i = 0; i < pKey2LoopSize; i++)
    {
        pKey1Tmp *= sKey1;
        pKey1Tmp %= 20201227;
    }

    for (size_t i = 0; i < pKey1LoopSize; i++)
    {
        pKey2Tmp *= sKey2;
        pKey2Tmp %= 20201227;
    }

    if (pKey1Tmp == pKey2Tmp)
    {
        std::cout << pKey1Tmp << std::endl;
        return 0;
    }

    return 1;
}
