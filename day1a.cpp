
#include <iostream>
#include <vector>

int main()
{
    std::vector<size_t> expenses;
    size_t expense = 0;

    while (std::cin >> expense)
    {
        expenses.push_back(expense);
    }

    for (size_t i = 0; i < expenses.size(); i++)
    {
        for (size_t j = i + 1; j < expenses.size(); j++)
        {
            const size_t sum = expenses[i] + expenses[j];

            if (sum == 2020)
            {
                const size_t product = expenses[i] * expenses[j];
                std::cout << product << std::endl;

                return 0;
            }
        }
    }

    return 1;
}
