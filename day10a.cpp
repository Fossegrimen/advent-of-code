
#include <algorithm>
#include <iostream>
#include <vector>

typedef std::vector<size_t> joltageRatingList;

int main()
{
    joltageRatingList joltageRatings;
    joltageRatings.push_back(0);

    size_t joltageRating;

    while (std::cin >> joltageRating)
    {
        joltageRatings.push_back(joltageRating);
    }

    std::sort(joltageRatings.begin(), joltageRatings.end());
    joltageRatings.push_back(joltageRatings[joltageRatings.size() - 1] + 3);

    size_t diff_1 = 0;
    size_t diff_3 = 0;

    for (size_t i = 1; i < joltageRatings.size(); i++)
    {
        const size_t diff = joltageRatings[i] - joltageRatings[i - 1];

        if (diff == 1)
        {
            diff_1++;
        }
        else if (diff == 3)
        {
            diff_3++;
        }
    }

    std::cout << (diff_1 * diff_3) << std::endl;

    return 0;
}
