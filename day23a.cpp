
#include <iostream>
#include <vector>

int main()
{
    std::vector<size_t> cupVector(9);

    char tempChar;

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
    }

    cupVector[previousCup] = startCup;

    size_t currentCup = startCup;
    size_t round = 0;

    while (round < 100)
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
            destCup = (destCup + 8) % 9;
        }
        while (destCup == pValue1 || destCup == pValue2 || destCup == pValue3);

        cupVector[pValue3] = cupVector[destCup];
        cupVector[destCup] = pValue1;

        round++;
    }

    currentCup = cupVector.front();

    while (currentCup != 0)
    {
        std::cout << (currentCup + 1);
        currentCup = cupVector[currentCup];
    }

    std::cout << std::endl;

    return 0;
}
