
#include <iostream>
#include <vector>

int main()
{
    std::vector<size_t> cupVector(1000000);

    for (size_t i = 0; i < 1000000; i++)
    {
        cupVector[i] = i + 1;
    }

    char   tempChar;
    size_t amountOfChars = 0;

    ssize_t previousCup =  0;
    ssize_t startCup    = -1;

    while (std::cin >> tempChar)
    {
        size_t value = tempChar - '0' - 1;

        if (startCup == -1)
        {
            startCup = value;
        }
        else
        {
            cupVector[previousCup] = value;
        }

        previousCup = value;
        amountOfChars++;
    }

    cupVector[previousCup] = amountOfChars;
    cupVector.back() = startCup;

    size_t currentCup = startCup;
    size_t round = 0;

    while (round < 10000000)
    {
        const size_t pValue1 = cupVector[currentCup];
        const size_t pValue2 = cupVector[pValue1];
        const size_t pValue3 = cupVector[pValue2];
        const size_t aValue  = cupVector[pValue3];

        size_t destCup = currentCup;

        cupVector[currentCup] = aValue;
        currentCup = aValue;

        do
        {
            destCup = (destCup + 999999) % 1000000;
        }
        while (destCup == pValue1 || destCup == pValue2 || destCup == pValue3);

        cupVector[pValue3] = cupVector[destCup];
        cupVector[destCup] = pValue1;

        round++;
    }

    std::cout << (cupVector.front() + 1) * (cupVector[cupVector.front()] + 1) << std::endl;

    return 0;
}
