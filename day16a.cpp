
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

typedef std::vector<std::vector<size_t>> RulesMatrix;

bool isValid(RulesMatrix rulesMatrix, size_t value);

int main()
{
    RulesMatrix rulesMatrix;
    std::string line;

    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            break;
        }

        line = std::regex_replace(line, std::regex("([[:alpha:]]+)"), "");
        line = std::regex_replace(line, std::regex(".?: "), "");
        line = std::regex_replace(line, std::regex("-"), " ");
        line = std::regex_replace(line, std::regex(" or "), " ");

        std::stringstream _line(line);

        std::vector<size_t> rules;
        size_t rule;

        while (_line >> rule)
        {
            rules.push_back(rule);
        }

        rulesMatrix.push_back(rules);
    }

    std::getline(std::cin, line);
    std::getline(std::cin, line);
    std::getline(std::cin, line);
    std::getline(std::cin, line);

    size_t errorRate = 0;

    while (std::getline(std::cin, line))
    {
        line = std::regex_replace(line, std::regex(","), " ");

        std::stringstream _line(line);
        size_t value = 0;

        while (_line >> value)
        {
            if (!isValid(rulesMatrix, value))
            {
                errorRate += value;
            }
        }
    }

    std::cout << errorRate << std::endl;

    return 0;
}

bool isValid(RulesMatrix rulesMatrix, size_t value)
{
    for (const auto& vect : rulesMatrix)
    {
        if ((value >= vect[0] && value <= vect[1]) ||
            (value >= vect[2] && value <= vect[3]))
            {
                return true;
            }
    }

    return false;
}
