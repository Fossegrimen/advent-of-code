
#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

#define COMPARE_NUMBER 22477624

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
        for (size_t j = i - 25; j < i - 2; j++)
        {
            uint64_t sum = 0;
            uint64_t min = std::numeric_limits<uint64_t>::max();
            uint64_t max = 0;

            sum += numbers[j];
            min = std::min(min, numbers[j]);
            max = std::max(max, numbers[j]);

            for (size_t k = j + 1; k < i - 1; k++)
            {
                sum += numbers[k];
                min = std::min(min, numbers[k]);
                max = std::max(max, numbers[k]);

                if (sum == COMPARE_NUMBER)
                {
                    std::cout << min << " " << max << std::endl;
                    return 0;
                }
            }
        }
    }

    return 1;
}
