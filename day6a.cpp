
#include <iostream>
#include <string>
#include <unordered_set>

int main()
{
    std::unordered_set<char> group;
    size_t sum = 0;
    std::string line;

    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            sum += group.size();
            group.clear();
        }
        else
        {
            for (size_t i = 0; i < line.size(); i++)
            {
                group.emplace(line[i]);
            }
        }
    }

    sum += group.size();
    std::cout << sum << std::endl;

    return 0;
}
