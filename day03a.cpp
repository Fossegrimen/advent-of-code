
#include <iostream>
#include <string>
#include <vector>

typedef std::vector<std::string> Matrix;

int main()
{
    Matrix map;
    std::string line;

    while (std::cin >> line)
    {
        map.push_back(line);
    }

    const size_t width  = map[0].size();
    const size_t height = map.size();

    size_t x     = 0;
    size_t y     = 0;
    size_t trees = 0;

    do
    {
        if (map[y][x] == '#')
        {
            trees++;
        }

        x = (x + 3) % width;
        y = (y + 1);
    } while (y < height);

    std::cout << trees << std::endl;

    return 0;
}
