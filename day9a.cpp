
#include <iostream>
#include <vector>

typedef std::vector<uint64_t> PreambleList;

uint64_t getBadPreamble(const PreambleList& preambleList);

int main()
{
    PreambleList preambleList;
    uint64_t preamble;

    while (std::cin >> preamble)
    {
        preambleList.push_back(preamble);
    }

    const uint64_t badPreamble = getBadPreamble(preambleList);
    std::cout << badPreamble << std::endl;

    return 0;
}

uint64_t getBadPreamble(const PreambleList& preambleList)
{
    for (size_t i = 25; i < preambleList.size(); i++)
    {
        bool foundNumber = false;

        for (size_t j = i - 25; j < i; j++)
        {
            for (size_t k = j + 1; k < i; k++)
            {
                const uint64_t sum = preambleList[j] + preambleList[k];

                if (sum == preambleList[i])
                {
                    foundNumber = true;
                }
            }
        }

        if (!foundNumber)
        {
            return preambleList[i];
        }
    }

    return 0;
}
