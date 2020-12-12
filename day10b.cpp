
#include <algorithm>
#include <cmath>
#include <iostream>
#include <unordered_map>
#include <vector>

uint64_t findPossibilities(std::unordered_map<size_t, uint64_t>& adapterArrangementsMap, std::vector<size_t>& joltageRatings, size_t n);
bool validJoltageDiff(size_t a, size_t b);

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

    std::unordered_map<size_t, uint64_t> adapterArrangementsMap;
    adapterArrangementsMap[joltageRatings.size() - 1] = 1;

    std::cout << findPossibilities(adapterArrangementsMap, joltageRatings, 0) << std::endl;

    return 0;
}

uint64_t findPossibilities(std::unordered_map<size_t, uint64_t>& adapterArrangementsMap, std::vector<size_t>& joltageRatings, size_t n)
{
    if (n >= joltageRatings.size())
    {
        return 0;
    }

    if (adapterArrangementsMap.find(n) != adapterArrangementsMap.end())
    {
        return adapterArrangementsMap[n];
    }

    uint64_t possibilities = 0;

    for (size_t i = 1; i < 4; i++)
    {
        if ((n + i) < joltageRatings.size() && validJoltageDiff(joltageRatings[n], joltageRatings[n + i]))
        {
            possibilities += findPossibilities(adapterArrangementsMap, joltageRatings, n + i);
        }
    }

    adapterArrangementsMap[n] = possibilities;

    return possibilities;
}

bool validJoltageDiff(size_t a, size_t b)
{
    size_t c = abs(b - a);
    return (c >= 1 && c <=3);
}
