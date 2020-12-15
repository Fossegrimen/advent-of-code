
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

typedef std::unordered_map<uint64_t, uint64_t> MemoryMap;
typedef std::vector<uint64_t> Addresses;

const Addresses getAddresses(const std::string mask, uint64_t address);
const Addresses getAddressPossibilities(std::string mask, const uint64_t address);

int main()
{
    MemoryMap memory;

    std::string mask;
    std::string line;

    while (std::getline(std::cin, line))
    {
        size_t pos = line.find("=");

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
            const uint64_t value   = stol(second);

            for (uint64_t _address : getAddresses(mask, address))
            {
                memory[_address] = value;
            }
        }
    }

    uint64_t sum = 0;

    for (const auto &pair : memory)
    {
        sum += pair.second;
    }

    std::cout << sum << std::endl;

    return 0;
}

const Addresses getAddresses(const std::string mask, uint64_t address)
{
    for (size_t i = 0; i < mask.size(); i++)
    {
        if (mask[i] == '1')
        {
            address |= (1UL << (mask.size() - 1 - i));
        }
    }

    return getAddressPossibilities(mask, address);
}

const Addresses getAddressPossibilities(std::string mask, const uint64_t address)
{
    Addresses    addresses;
    const size_t pos = mask.find("X");

    if (pos == std::string::npos)
    {
        addresses.push_back(address);
        return addresses;
    }

    mask[pos] = '0';

    for (uint64_t addr : getAddressPossibilities(mask, address & (~(1UL << (mask.size() - 1 - pos)))))
    {
        addresses.push_back(addr);
    }

    mask[pos] = '1';

    for (uint64_t addr : getAddressPossibilities(mask, address | (1UL << (mask.size() - 1 - pos))))
    {
        addresses.push_back(addr);
    }

    return addresses;
}
