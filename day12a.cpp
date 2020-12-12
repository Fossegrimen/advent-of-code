
#include <cmath>
#include <iostream>

int main()
{
    char action;
    size_t value;

    ssize_t x = 0;
    ssize_t y = 0;
    size_t degrees = 0;

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
                degrees = (degrees + value + 360) % 360;
                break;
            }
            case 'R':
            {
                degrees = (degrees - value + 360) % 360;
                break;
            }
            case 'F':
            {
                if (degrees == 0)
                {
                    x += value;
                }
                else if (degrees == 90)
                {
                    y += value;
                }
                else if (degrees == 180)
                {
                    x -= value;
                }
                else if (degrees == 270)
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
