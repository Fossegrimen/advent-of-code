
#include <iostream>
#include <vector>

typedef std::vector<size_t> Vector;

int main()
{
    Vector expenses;
    size_t expense = 0;

    while (std::cin >> expense)
    {
        expenses.push_back(expense);
    }

    for (size_t i = 0; i < expenses.size(); i++)
    {
        for (size_t j = i + 1; j < expenses.size(); j++)
        {
            for (size_t k = j + 1; k < expenses.size(); k++)
            {
                const size_t sum = expenses[i] + expenses[j] + expenses[k];

                if (sum == 2020)
                {
                    const size_t product = expenses[i] * expenses[j] * expenses[k];
                    std::cout << product << std::endl;

                    return 0;
                }
            }
        }
    }

    return 1;
}
