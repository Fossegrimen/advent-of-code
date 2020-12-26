
#include <algorithm>
#include <cmath>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <vector>

typedef std::vector<size_t> Vector;

int main()
{
    Vector busIds;

    std::string line;
    std::getline(std::cin, line);

    const size_t timeToLeave(stol(line));

    std::getline(std::cin, line);
    std::replace(line.begin(), line.end(), ',', ' ');
    std::replace(line.begin(), line.end(), 'x', ' ');

    std::stringstream _line(line);
    size_t busId;

    while (_line >> busId)
    {
        busIds.push_back(busId);
    }

    size_t value         = 0;
    size_t minDepartment = std::numeric_limits<size_t>::max();

    for (size_t busId : busIds)
    {
        const size_t department = ceil((double)timeToLeave / busId) * busId;

        if (department < minDepartment )
        {
            minDepartment = department;
            value         = (department - timeToLeave) * busId;
        }
    }

    std::cout << value << std::endl;

    return 0;
}
