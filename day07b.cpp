
#include <iostream>
#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string, size_t> BagRuleMap;
typedef std::unordered_map<std::string, BagRuleMap> BagRulesMap;

void   fillBagRulesMap(BagRulesMap& bagRulesMap);
void   trimString(std::string& line);
size_t countBags(BagRulesMap& bagRulesMap, const std::string bagName);

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

        trimString(line);

        size_t pos = line.find(":");

        if (pos == std::string::npos)
        {
            return;
        }

        const std::string bagName = line.substr(0, pos);
        std::string       bagRule = line.substr(pos + 1, line.size());

        do
        {
            pos = bagRule.find(":");

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

void trimString(std::string& line)
{
    size_t pos = std::string::npos;

    while ((pos = line.find(" bags")) != std::string::npos)
    {
        line.erase(pos, 5);
    }

    while ((pos = line.find(" bag")) != std::string::npos)
    {
        line.erase(pos, 4);
    }

    while ((pos = line.find(", ")) != std::string::npos)
    {
        line.erase(pos, 2);
        line.insert(pos, ":");
    }

    while ((pos = line.find(".")) != std::string::npos)
    {
        line.erase(pos, 1);
    }

    while ((pos = line.find(" contain ")) != std::string::npos)
    {
        line.erase(pos, 9);
        line.insert(pos, ":");
    }
}

size_t countBags(BagRulesMap& bagRulesMap, const std::string bagName)
{
    if (bagRulesMap.find(bagName) == bagRulesMap.end())
    {
        return 0;
    }

    size_t bagsAmount = 0;

    for (const auto& itr : bagRulesMap[bagName])
    {
        bagsAmount += itr.second + (itr.second * countBags(bagRulesMap, itr.first));
    }

    return bagsAmount;
}
