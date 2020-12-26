
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <vector>

typedef std::vector<std::vector<size_t>> Rules;

void readRules(Rules& rules);
bool isValid(const Rules& rules, const size_t value);

int main()
{
    Rules rules;
    readRules(rules);

    std::string line;

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
            if (!isValid(rules, value))
            {
                errorRate += value;
            }
        }
    }

    std::cout << errorRate << std::endl;

    return 0;
}

void readRules(Rules& rules)
{
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

        std::vector<size_t> _rules;
        size_t rule;

        while (_line >> rule)
        {
            _rules.push_back(rule);
        }

        rules.push_back(_rules);
    }
}

bool isValid(const Rules& rules, const size_t value)
{
    for (const auto& vect : rules)
    {
        if ((value >= vect[0] && value <= vect[1]) ||
            (value >= vect[2] && value <= vect[3]))
            {
                return true;
            }
    }

    return false;
}
