
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

typedef std::map<std::string, std::string> AllergenFoodMap;
typedef std::unordered_map<std::string, size_t> IndexMap;
typedef std::vector<std::unordered_set<size_t>> AllergenFoodIndexVector;
typedef std::vector<std::vector<size_t>> Matrix;
typedef std::vector<size_t> Vector;

void                    readRecipes(IndexMap& foodIndexMap, IndexMap& allergenIndexMap, Matrix& foodMatrix, Matrix& allergenMatrix);
size_t                  getIndex(IndexMap& indexMap, const std::string name);
void                    increaseIndex(Vector& vector, const size_t index);
AllergenFoodIndexVector getAllergenFoodVector(const IndexMap& allergenIndexMap, const Matrix& foodMatrix, const Matrix& allergenMatrix);
AllergenFoodMap         getAllergenFoodMap(IndexMap& foodIndexMap, IndexMap& allergenIndexMap, AllergenFoodIndexVector allAllergenFoodVector);
const std::string       getName(const IndexMap& indexMap, const size_t index);

int main()
{
    IndexMap foodIndexMap;
    IndexMap allergenIndexMap;
    Matrix   foodMatrix;
    Matrix   allergenMatrix;

    readRecipes(foodIndexMap, allergenIndexMap, foodMatrix, allergenMatrix);
    AllergenFoodIndexVector allAllergenFoodVector = getAllergenFoodVector(allergenIndexMap, foodMatrix, allergenMatrix);
    AllergenFoodMap allAllergenFoodMap = getAllergenFoodMap(foodIndexMap, allergenIndexMap, allAllergenFoodVector);

    std::string result;

    for (const auto& pair : allAllergenFoodMap)
    {
        result.append(pair.second);
        result.append(",");
    }

    std::cout << result.substr(0, result.size() - 1) << std::endl;

    return 0;
}


void readRecipes(IndexMap& foodIndexMap, IndexMap& allergenIndexMap, Matrix& foodMatrix, Matrix& allergenMatrix)
{
    std::string line;

    while (std::getline(std::cin, line))
    {
        const size_t leftParamIndex = line.find('(');

        const std::string foodLine = line.substr(0, leftParamIndex - 1);
        std::string allergenLine   = line.substr(leftParamIndex + 10, line.size());
        allergenLine               = allergenLine.substr(0, allergenLine.size() - 1);

        Vector foodVector;

        std::stringstream _line(foodLine);
        std::string food;

        while (_line >> food)
        {
            const size_t index = getIndex(foodIndexMap, food);
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
        size_t count   = indexMap.size();
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

AllergenFoodIndexVector getAllergenFoodVector(const IndexMap& allergenIndexMap, const Matrix& foodMatrix, const Matrix& allergenMatrix)
{
    AllergenFoodIndexVector allAllergenFoodVector;

    for (size_t i = 0; i < allergenIndexMap.size(); i++)
    {
        std::unordered_set<size_t> allergenFoodSet;
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

        allAllergenFoodVector.push_back(allergenFoodSet);
    }

    return allAllergenFoodVector;
}

AllergenFoodMap getAllergenFoodMap(IndexMap& foodIndexMap, IndexMap& allergenIndexMap, AllergenFoodIndexVector allAllergenFoodVector)
{
    AllergenFoodMap allAllergenFoodMap;

    for (size_t i = 0; i < allAllergenFoodVector.size(); i++)
    {
        for (size_t j = 0; j < allAllergenFoodVector.size(); j++)
        {
            if (allAllergenFoodVector[j].size() != 1)
            {
                continue;
            }

            const size_t index = *allAllergenFoodVector[j].begin();

            allAllergenFoodMap[getName(allergenIndexMap, j)] = getName(foodIndexMap, index);

            for (size_t k = 0; k < allAllergenFoodVector.size(); k++)
            {
                if (j == k)
                {
                    continue;
                }

                allAllergenFoodVector[k].erase(index);
            }
        }
    }

    return allAllergenFoodMap;
}

const std::string getName(const IndexMap& indexMap, const size_t index)
{
    for (const auto& pair : indexMap)
    {
        if (pair.second == index)
        {
            return pair.first;
        }
    }

    return nullptr;
}
