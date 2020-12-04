
#include <iostream>
#include <regex>
#include <string>
#include <unordered_map>

typedef std::unordered_map<std::string, std::string> Passport;

bool isValidPassport(Passport& passport);

int main()
{
    Passport passport;
    size_t valid = 0;
    std::string line;

    while (std::getline(std::cin, line))
    {
        if (line.empty())
        {
            valid += isValidPassport(passport);
            passport.clear();
            continue;
        }

        std::stringstream _line(line);
        std::string keyValue;

        while (_line >> keyValue)
        {
            std::size_t pos = keyValue.find(':');

            if (pos == std::string::npos)
            {
                return 1;
            }

            passport[keyValue.substr(0, pos)] = keyValue.substr(pos + 1, keyValue.size());
        }
    }

    if (passport.size() > 0)
    {
        valid += isValidPassport(passport);
    }

    std::cout << valid << std::endl;

    return 0;
}

bool isValidPassport(Passport& passport)
{
    if (!std::regex_match(passport["byr"], std::regex("19[2-9][0-9]|200[0-2]")))
    {
        return false;
    }

    if (!std::regex_match(passport["iyr"], std::regex("20(1[0-9]|20)")))
    {
        return false;
    }

    if (!std::regex_match(passport["eyr"], std::regex("20(2[0-9]|30)")))
    {
        return false;
    }

    if (!std::regex_match(passport["hgt"], std::regex("1([5-8][0-9]|9[0-3])cm|(59|6[0-9]|7[0-6])in")))
    {
        return false;
    }

    if (!std::regex_match(passport["hcl"], std::regex("#[[:alnum:]]{6}")))
    {
        return false;
    }

    if (!std::regex_match(passport["ecl"], std::regex("amb|blu|brn|gry|grn|hzl|oth")))
    {
        return false;
    }

    if (!std::regex_match(passport["pid"], std::regex("[0-9]{9}")))
    {
        return false;
    }

    return true;
}
