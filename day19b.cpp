
#include <iostream>
#include <regex>
#include <sstream>
#include <string>
#include <unordered_map>

typedef std::vector<char> RegexVector;
typedef std::unordered_map<size_t, std::vector<ssize_t>> RuleMap;
typedef std::unordered_map<size_t, char> LetterMap;

const RegexVector getRegex(RuleMap& ruleMap, LetterMap& letterMap, const size_t index);

int main()
{
    RuleMap   ruleMap;
    LetterMap letterMap;

    std::string line;

    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            break;
        }

        line = line.erase(line.find(':'), 1);

        if (line.find('\"') != std::string::npos)
        {
            size_t pos = std::string::npos;

            while ((pos = line.find("\"")) != std::string::npos)
            {
                line.erase(pos, 1);
            }

            std::stringstream _line(line);

            size_t index;
            _line >> index;

            char letter;
            _line >> letter;

            letterMap[index] = letter;
        }
        else
        {
            const size_t pos = line.find('|');

            if (pos != std::string::npos)
            {
                line = line.erase(pos, 1);
                line = line.insert(pos, "-1");
            }

            std::stringstream _line(line);

            size_t index;
            _line >> index;

            std::vector<ssize_t> rules;
            ssize_t rule;

            while (_line >> rule)
            {
                rules.push_back(rule);
            }

            ruleMap[index] = rules;
        }
    }

    ruleMap[8]  = std::vector<ssize_t>(
        {
            42, -2
        });
    ruleMap[11] = std::vector<ssize_t>(
        {
            42, 31, -1,
            42, 42, 31, 31, -1,
            42, 42, 42, 31, 31, 31, -1,
            42, 42, 42, 42, 31, 31, 31, 31, -1,
            42, 42, 42, 42, 42, 31, 31, 31, 31, 31
        });

    RegexVector regexVector = getRegex(ruleMap, letterMap, 0);
    std::string regexString(regexVector.begin(), regexVector.end());

    size_t matches = 0;

    while (std::getline(std::cin, line))
    {
        matches += std::regex_match(line, std::regex(regexString));
    }

    std::cout << matches << std::endl;

    return 0;
}

const RegexVector getRegex(RuleMap& ruleMap, LetterMap& letterMap, const size_t index)
{
    RegexVector regexVector;

    if (letterMap.find(index) != letterMap.end())
    {
        regexVector.push_back(letterMap[index]);
    }
    else if (ruleMap.find(index) != ruleMap.end())
    {
        regexVector.push_back('(');

        for (ssize_t _index : ruleMap[index])
        {
            if (_index == -1)
            {
                regexVector.push_back('|');
                continue;
            }
            else if (_index == -2)
            {
                regexVector.push_back('+');
                continue;
            }

            for (char letter : getRegex(ruleMap, letterMap, _index))
            {
                regexVector.push_back(letter);
            }
        }

        regexVector.push_back(')');
    }

    return regexVector;
}
