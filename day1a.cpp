
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

    for (size_t i = 0; i < expenses.size() - 1; i++)
    {
        for (size_t j = i + 1; j < expenses.size(); j++)
        {
            if (expenses[i] + expenses[j] == 2020)
            {
                std::cout << expenses[i] * expenses[j] << std::endl;
                return 0;
            }
        }
    }

    return 1;
}
