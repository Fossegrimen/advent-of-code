
#include <iostream>
#include <string>
#include <unordered_map>

typedef std::unordered_map<char, size_t> CharMap;

size_t countAnswers(CharMap& charMap, size_t people);

int main()
{
    CharMap     charMap;
    size_t      sum    = 0;
    size_t      people = 0;
    std::string line;

    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            sum   += countAnswers(charMap, people);
            people =  0;
            charMap.clear();
        }
        else
        {
            people++;

            for (size_t i = 0; i < line.size(); i++)
            {
                charMap[line[i]]++;
            }
        }
    }

    sum += countAnswers(charMap, people);
    std::cout << sum << std::endl;

    return 0;
}

size_t countAnswers(CharMap& charMap, const size_t people)
{
    size_t sum = 0;
    
    for (const auto& pair : charMap)
    {
        sum += (pair.second == people);        
    }

    return sum;
}
