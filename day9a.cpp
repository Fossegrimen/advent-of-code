
#include <iostream>
#include <vector>

int main()
{
    std::vector<uint64_t> numbers;
    uint64_t number = 0;

    while (std::cin >> number)
    {
        numbers.push_back(number);
    }

    for (size_t i = 25; i < numbers.size(); i++)
    {
        bool foundNumber = false;

        for (size_t j = i - 25; j < i - 2; j++)
        {
            for (size_t k = j + 1; k < i - 1; k++)
            {
                if ((numbers[j] + numbers[k]) == numbers[i])
                {
                    foundNumber = true;
                }
            }
        }

        if (!foundNumber)
        {
            std::cout << numbers[i] << std::endl;
            return 0;
        }
    }

    return 1;
}
