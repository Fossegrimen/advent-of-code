
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string, std::size_t> BagRuleMap;
typedef std::unordered_map<std::string, BagRuleMap> BagRulesMap;

void fillBagRulesMap(BagRulesMap& bagRulesMap);
size_t countBags(BagRulesMap& bagRulesMap, std::string bagName);

int main()
{
    BagRulesMap bagRulesMap;
    fillBagRulesMap(bagRulesMap);

    std::cout << countBags(bagRulesMap, "shiny gold") << std::endl;

    return 0;
}

void fillBagRulesMap(BagRulesMap& bagRulesMap)
{
    std::string line;

    while (std::getline(std::cin, line))
    {
        if (line.find("no other") != std::string::npos)
        {
            continue;
        }

        line = std::regex_replace(line, std::regex("bags?"), "");
        line = std::regex_replace(line, std::regex(" , "), ":");
        line = std::regex_replace(line, std::regex(" +"), " ");
        line = std::regex_replace(line, std::regex(" [.]?$"), "");

        std::size_t pos = line.find("contain");

        if (pos == std::string::npos)
        {
            return;
        }

        std::string bagName = line.substr(0, pos - 1);
        std::string bagRule = line.substr(pos + 8, line.size());

        do
        {
            std::size_t pos = bagRule.find(":");

            if (pos == std::string::npos)
            {
                pos = bagRule.size();
            }

            bagRulesMap[bagName][bagRule.substr(2, pos - 2)] = std::stoi(bagRule.substr(0, 1));

            if (pos == bagRule.size())
            {
                bagRule.clear();
            }
            else
            {
                bagRule = bagRule.substr(pos + 1, bagRule.size());
            }

        } while (!bagRule.empty());
    }
}

size_t countBags(BagRulesMap& bagRulesMap, std::string bagName)
{
    if (bagRulesMap.find(bagName) == bagRulesMap.end())
    {
        return 0;
    }

    size_t bagsAmount = 0;

    for (auto& itr : bagRulesMap[bagName])
    {
        bagsAmount += itr.second + itr.second * countBags(bagRulesMap, itr.first);
    }

    return bagsAmount;
}
