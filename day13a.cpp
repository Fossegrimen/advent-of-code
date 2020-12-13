
#include <cmath>
#include <iostream>
#include <limits>
#include <regex>
#include <string>
#include <vector>

int main()
{
    std::vector<size_t> busIds;

    std::string line;
    std::getline(std::cin, line);

    size_t timeToLeave(stol(line));

    std::getline(std::cin, line);
    line = std::regex_replace(line, std::regex("[^[:digit:]]+"), " ");

    std::stringstream _line(line);
    size_t busId;

    while (_line >> busId)
    {
        busIds.push_back(busId);
    }

    size_t value = 0;
    size_t minDepartment = std::numeric_limits<size_t>::max();

    for (size_t busId : busIds)
    {
        size_t department = ceil((double)timeToLeave / busId) * busId;

        if (department < minDepartment )
        {
            minDepartment = department;
            value = (department - timeToLeave) * busId;
        }
    }

    std::cout << value << std::endl;

    return 0;
}