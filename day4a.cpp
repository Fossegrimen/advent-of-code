
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

        std::stringstream _line (line);
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
    if (passport.find("byr") == passport.end())
    {
        return false;
    }

    if (passport.find("iyr") == passport.end())
    {
        return false;
    }

    if (passport.find("eyr") == passport.end())
    {
        return false;
    }

    if (passport.find("hgt") == passport.end())
    {
        return false;
    }

    if (passport.find("hcl") == passport.end())
    {
        return false;
    }

    if (passport.find("ecl") == passport.end())
    {
        return false;
    }

    if (passport.find("pid") == passport.end())
    {
        return false;
    }

    return true;
}
