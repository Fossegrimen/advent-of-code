
#include <iostream>
#include <numeric>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef std::unordered_map<std::string, size_t> IndexMap;
typedef std::unordered_set<size_t> IndexSet;
typedef std::vector<std::vector<size_t>> Matrix;
typedef std::vector<size_t> Vector;

void     readRecipes(IndexMap& foodIndexMap, IndexMap& allergenIndexMap, Matrix& foodMatrix, Matrix& allergenMatrix);
size_t   getIndex(IndexMap& indexMap, const std::string name);
void     increaseIndex(Vector& vector, const size_t index);
IndexSet getAllergenFoodSet(const IndexMap& allergenIndexMap, const Matrix& foodMatrix, const Matrix& allergenMatrix);
size_t   countFoodIndex(const Matrix& foodMatrix, const ssize_t index);

int main()
{
    IndexMap foodIndexMap;
    IndexMap allergenIndexMap;
    Matrix   foodMatrix;
    Matrix   allergenMatrix;

    readRecipes(foodIndexMap, allergenIndexMap, foodMatrix, allergenMatrix);
    IndexSet allAllergenFoodSet = getAllergenFoodSet(allergenIndexMap, foodMatrix, allergenMatrix);

    const size_t allFoodCount         = countFoodIndex(foodMatrix, -1);
    size_t       allAllergenFoodCount = 0;

    for (size_t index : allAllergenFoodSet)
    {
        allAllergenFoodCount += countFoodIndex(foodMatrix, index);
    }

    std::cout << (allFoodCount - allAllergenFoodCount) << std::endl;

    return 0;
}

void readRecipes(IndexMap& foodIndexMap, IndexMap& allergenIndexMap, Matrix& foodMatrix, Matrix& allergenMatrix)
{
    std::string line;

    while (std::getline(std::cin, line))
    {
        const size_t leftParamIndex = line.find('(');

        const std::string foodLine  = line.substr(0, leftParamIndex - 1);
        std::string allergenLine    = line.substr(leftParamIndex + 10, line.size());
        allergenLine = allergenLine.substr(0, allergenLine.size() - 1);

        Vector foodVector;

        std::stringstream _line(foodLine);
        std::string food;

        while (_line >> food)
        {
            size_t index = getIndex(foodIndexMap, food);
            increaseIndex(foodVector, index);
        }

        foodMatrix.push_back(foodVector);

        Vector allergenVector;

        std::stringstream __line(allergenLine);
        std::string allergen;

        while (__line >> allergen)
        {
            if (allergen[allergen.size() - 1] == ',')
            {
                allergen = allergen.substr(0, allergen.size() - 1);
            }

            const size_t index = getIndex(allergenIndexMap, allergen);
            increaseIndex(allergenVector, index);
        }

        allergenMatrix.push_back(allergenVector);
    }
}

size_t getIndex(IndexMap& indexMap, const std::string name)
{
    if (indexMap.find(name) != indexMap.end())
    {
        return indexMap[name];
    }
    else
    {
        size_t count = indexMap.size();
        indexMap[name] = count;
        return count;
    }
}

void increaseIndex(Vector& vector, const size_t index)
{
    if (index >= vector.size())
    {
        vector.resize(index + 1, 0);
    }

    vector[index] =  1;
}

IndexSet getAllergenFoodSet(const IndexMap& allergenIndexMap, const Matrix& foodMatrix, const Matrix& allergenMatrix)
{
    IndexSet allAllergenFoodSet;

    for (size_t i = 0; i < allergenIndexMap.size(); i++)
    {
        IndexSet allergenFoodSet;
        ssize_t firstAllergenIndex = -1;

        for (size_t j = 0; j < foodMatrix.size(); j++)
        {
            if (i >= allergenMatrix[j].size())
            {
                continue;
            }
            else if (allergenMatrix[j][i] == 1)
            {
                for (size_t k = 0; k < foodMatrix[j].size(); k++)
                {
                    if (foodMatrix[j][k] == 1)
                    {
                        if ((ssize_t)j == firstAllergenIndex || firstAllergenIndex == -1)
                        {
                            allergenFoodSet.insert(k);
                            firstAllergenIndex = j;
                        }
                    }
                    else
                    {
                        allergenFoodSet.erase(k);
                    }
                }
            }
        }

        for (size_t index : allergenFoodSet)
        {
            allAllergenFoodSet.insert(index);
        }
    }

    return allAllergenFoodSet;
}

size_t countFoodIndex(const Matrix& foodMatrix, const ssize_t index)
{
    size_t sum = 0;

    for (const auto& vector: foodMatrix)
    {
        if (index == -1)
        {
            sum += std::accumulate(vector.begin(), vector.end(), 0);
        }
        else if (index < (ssize_t)vector.size())
        {
            sum += vector[index];
        }
    }

    return sum;
}
