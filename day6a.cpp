
#include <iostream>
#include <string>
#include <unordered_set>

int main()
{
    std::unordered_set<char> charSet;
    size_t      sum = 0;
    std::string line;

    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            sum += charSet.size();
            charSet.clear();
        }
        else
        {
            for (size_t i = 0; i < line.size(); i++)
            {
                charSet.insert(line[i]);
            }
        }
    }

    sum += charSet.size();
    std::cout << sum << std::endl;

    return 0;
}
