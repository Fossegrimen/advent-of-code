
#include <iostream>
#include <numeric>
#include <sstream>
#include <vector>

#define MAX_WIDTH 60

#define MAX_R MAX_WIDTH
#define MAX_Q MAX_R

#define ORIGO_R (MAX_WIDTH / 2)
#define ORIGO_Q ORIGO_R

typedef std::vector<std::vector<size_t>> HexagonGrid;

int main()
{
    HexagonGrid hexagonGrid;
    hexagonGrid.resize(MAX_R);

    for (auto& vector : hexagonGrid)
    {
        vector.resize(MAX_Q, 0);
    }

    std::string line;

    while (std::getline(std::cin, line))
    {
        size_t r = ORIGO_R;
        size_t q = ORIGO_Q;

        size_t pos    = 0;
        size_t offset = 0;

        while ((pos = line.substr(offset, line.size()).find('w')) != std::string::npos)
        {
            offset += pos + 1;
            line.insert(offset, " ");
        }

        pos    = 0;
        offset = 0;

        while ((pos = line.substr(offset, line.size()).find('e')) != std::string::npos)
        {
            offset += pos + 1;
            line.insert(offset, " ");
        }

        std::stringstream _line(line);
        std::string       direction;

        while (_line >> direction)
        {
            if (direction == "nw")
            {
                r--;
            }
            else if (direction == "ne")
            {
                r--;
                q++;
            }
            else if (direction == "w")
            {
                q--;
            }
            else if (direction == "e")
            {
                q++;
            }
            else if (direction == "sw")
            {
                r++;
                q--;
            }
            else if (direction == "se")
            {
                r++;
            }
        }

        hexagonGrid[r][q] = !hexagonGrid[r][q];
    }

    size_t sum = 0;

    for (const auto& vector : hexagonGrid)
    {
        sum += std::accumulate(vector.begin(), vector.end(), 0);
    }

    std::cout << sum << std::endl;

    return 0;
}
