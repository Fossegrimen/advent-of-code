
#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

typedef std::unordered_map<size_t, uint64_t> AdapterMap;
typedef std::vector<size_t> joltageRatingList;

uint64_t findPossibilities(AdapterMap& adapterMap, const joltageRatingList& joltageRatings, const size_t n);
bool     validJoltageDiff(const size_t a, const size_t b);

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

    AdapterMap adapterMap;
    adapterMap[joltageRatings.size() - 1] = 1;

    const uint64_t possibilities = findPossibilities(adapterMap, joltageRatings, 0);
    std::cout << possibilities << std::endl;

    return 0;
}

uint64_t findPossibilities(AdapterMap& adapterMap, const joltageRatingList& joltageRatings, const size_t n)
{
    if (n >= joltageRatings.size())
    {
        return 0;
    }

    if (adapterMap.find(n) != adapterMap.end())
    {
        return adapterMap[n];
    }

    uint64_t possibilities = 0;

    for (size_t i = 1; i < 4; i++)
    {
        const bool validBound = ((n + i) < joltageRatings.size());

        if (!validBound)
        {
            continue;
        }

        if (validJoltageDiff(joltageRatings[n], joltageRatings[n + i]))
        {
            possibilities += findPossibilities(adapterMap, joltageRatings, n + i);
        }
    }

    return (adapterMap[n] = possibilities);
}

bool validJoltageDiff(const size_t a, const size_t b)
{
    const size_t c = (b - a);
    return (c >= 1 && c <=3);
}
