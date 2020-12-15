
#include <iostream>
#include <string>
#include <unordered_map>

typedef std::unordered_map<uint64_t, uint64_t> MemoryMap;

int main()
{
    MemoryMap memoryMap;

    std::string mask;
    std::string line;

    while (std::getline(std::cin, line))
    {
        size_t pos = line.find('=');

        if (pos == std::string::npos)
        {
            return 1;
        }

        const std::string first  = line.substr(0, pos - 1);
        const std::string second = line.substr(pos + 2, line.size());

        if (first.find("mask") != std::string::npos)
        {
            mask = second;
        }
        else if (first.find("mem") != std::string::npos)
        {
            const uint64_t address = stol(first.substr(4, line.size() - 5));
            uint64_t       value   = stol(second);

            for (size_t i = 0; i < mask.size(); i++)
            {
                if (mask[i] == '1')
                {
                    value |= (1UL << (mask.size() - 1 - i));
                }
                else if (mask[i] == '0')
                {
                    value &= ~(1UL << (mask.size() - 1 - i));
                }
            }

            memoryMap[address] = value;
        }
    }

    uint64_t sum = 0;

    for (const auto &pair : memoryMap)
    {
        sum += pair.second;
    }

    std::cout << sum << std::endl;

    return 0;
}
