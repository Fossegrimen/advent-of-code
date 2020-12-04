
#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> map;
    std::string line;

    while (std::cin >> line)
    {
        map.push_back(line);
    }

    const size_t width = map[0].size();
    const size_t height = map.size();

    const std::vector<size_t> offsetX = { 1, 3, 5, 7, 1 };
    const std::vector<size_t> offsetY = { 1, 1, 1, 1, 2 };

    size_t multiplier = 1;

    for (size_t i = 0; i < offsetX.size(); i++)
    {
        size_t x = 0;
        size_t y = 0;
        size_t trees = 0;

        do
        {
            if (map[y][x] == '#')
            {
                trees++;
            }

            x = (x + offsetX[i]) % width;
            y = (y + offsetY[i]);
        } while (y < height);

        multiplier *= trees;
    }

    std::cout << multiplier << std::endl;

    return 0;
}
