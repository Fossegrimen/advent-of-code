
#include <cmath>
#include <iostream>

int main()
{
    char action;
    size_t value;

    ssize_t x   = 0;
    ssize_t y   = 0;
    ssize_t w_x = 10;
    ssize_t w_y = 1;

    while (std::cin >> action && std::cin >> value)
    {
        switch (action)
        {
            case 'N':
            {
                w_y += value;
                break;
            }
            case 'S':
            {
                w_y -= value;
                break;
            }
            case 'E':
            {
                w_x += value;
                break;
            }
            case 'W':
            {
                w_x -= value;
                break;
            }
            case 'L':
            {
                if (value == 90)
                {
                    ssize_t tmp = w_x;
                    w_x = -w_y;
                    w_y = tmp;
                }
                else if (value == 180)
                {
                    w_x = -w_x;
                    w_y = -w_y;
                }
                else if (value == 270)
                {
                    ssize_t tmp = w_x;
                    w_x = w_y;
                    w_y = -tmp;
                }

                break;
            }
            case 'R':
            {
                if (value == 90)
                {
                    ssize_t tmp = w_x;
                    w_x = w_y;
                    w_y = -tmp;
                }
                else if (value == 180)
                {
                    w_x = -w_x;
                    w_y = -w_y;
                }
                else if (value == 270)
                {
                    ssize_t tmp = w_x;
                    w_x = -w_y;
                    w_y = tmp;
                }

                break;
            }
            case 'F':
            {
                x += w_x * value;
                y += w_y * value;

                break;
            }
        }
    }

    std::cout << (abs(x) + abs(y)) << std::endl;

    return 0;
}
