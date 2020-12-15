
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

int main()
{
    std::unordered_map<size_t, std::vector<size_t>> spokenNumberMap;

    size_t lastSpokenNumber;
    size_t round = 1;

    std::string line;
    std::getline(std::cin, line);
    std::replace(line.begin(), line.end(), ',', ' ');

    std::stringstream _line(line);

    while (_line >> lastSpokenNumber)
    {
        spokenNumberMap[lastSpokenNumber].push_back(round);
        round++;
    }

    while (round < 30000001)
    {
        if (spokenNumberMap.find(lastSpokenNumber) != spokenNumberMap.end())
        {
            if (spokenNumberMap[lastSpokenNumber].size() == 1)
            {
                lastSpokenNumber = 0;
            }
            else
            {
                const auto ptr = spokenNumberMap[lastSpokenNumber].cend();
                lastSpokenNumber = *(ptr-1) - *(ptr-2);
            }
        }

        spokenNumberMap[lastSpokenNumber].push_back(round);
        round++;
    }

    std::cout << lastSpokenNumber << std::endl;

    return 0;
}
