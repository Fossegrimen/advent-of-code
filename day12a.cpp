
#include <cmath>
#include <iostream>

int main()
{
    char action;
    size_t value;

    ssize_t x   = 0;
    ssize_t y   = 0;
    size_t  deg = 0;

    while (std::cin >> action && std::cin >> value)
    {
        switch (action)
        {
            case 'N':
            {
                y += value;
                break;
            }
            case 'S':
            {
                y -= value;
                break;
            }
            case 'E':
            {
                x += value;
                break;
            }
            case 'W':
            {
                x -= value;
                break;
            }
            case 'L':
            {
                deg = (deg + value + 360) % 360;
                break;
            }
            case 'R':
            {
                deg = (deg - value + 360) % 360;
                break;
            }
            case 'F':
            {
                if (deg == 0)
                {
                    x += value;
                }
                else if (deg == 90)
                {
                    y += value;
                }
                else if (deg == 180)
                {
                    x -= value;
                }
                else if (deg == 270)
                {
                    y -= value;
                }

                break;
            }
        }
    }

    std::cout << (abs(x) + abs(y)) << std::endl;

    return 0;
}
