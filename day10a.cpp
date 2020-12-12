
#include <algorithm>
#include <iostream>
#include <vector>

int main()
{
    std::vector<size_t> joltageRatings;
    joltageRatings.push_back(0);

    size_t joltageRating = 0;

    while (std::cin >> joltageRating)
    {
        joltageRatings.push_back(joltageRating);
    }

    std::sort(joltageRatings.begin(), joltageRatings.end());
    joltageRatings.push_back(joltageRatings[joltageRatings.size() - 1] + 3);

    size_t difference_1 = 0;
    size_t difference_3 = 0;

    for (size_t i = 1; i < joltageRatings.size(); i++)
    {
        if ((joltageRatings[i] - joltageRatings[i - 1]) == 1)
        {
            difference_1++;
        }

        if ((joltageRatings[i] - joltageRatings[i - 1]) == 3)
        {
            difference_3++;
        }
    }

    std::cout << (difference_1 * difference_3) << std::endl;

    return 0;
}
