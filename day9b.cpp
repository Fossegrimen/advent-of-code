
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

typedef std::vector<uint64_t> PreambleList;

uint64_t getBadPreamble(const PreambleList& preambleList);

int main()
{
    PreambleList preambleList;
    uint64_t     preamble;

    while (std::cin >> preamble)
    {
        preambleList.push_back(preamble);
    }

    const uint64_t badPreamble = getBadPreamble(preambleList);

    for (size_t i = 25; i < preambleList.size(); i++)
    {
        for (size_t j = i - 25; j < i; j++)
        {
            uint64_t sum = 0;
            uint64_t min = std::numeric_limits<uint64_t>::max();
            uint64_t max = 0;

            sum += preambleList[j];
            min  = std::min(min, preambleList[j]);
            max  = std::max(max, preambleList[j]);

            for (size_t k = j + 1; k < i - 1; k++)
            {
                sum += preambleList[k];
                min  = std::min(min, preambleList[k]);
                max  = std::max(max, preambleList[k]);

                if (sum == badPreamble)
                {
                    std::cout << (min + max) << std::endl;
                    return 0;
                }
            }
        }
    }

    return 1;
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
