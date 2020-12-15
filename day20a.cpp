
#include <algorithm>
#include <cmath>
#include <iostream>
#include <string>
#include <vector>

enum Side
{
    Left = 0,
    Right = 1,
    Upper = 2,
    Lower = 3
};

class Tile;
class TileHandler;

typedef std::vector<Tile*>              TileTranslations;
typedef std::vector<std::vector<Tile*>> Tiles;
typedef std::vector<std::vector<char>>  TileData;

class Tile
{
private:
    size_t    tileId;
    TileData* tileData;
    Tile*     neighborTiles[4];

    TileData* getTranslatedTileData(TileData* originalTileData, const size_t translation) const
    {
        if (translation == 0)
        {
            return originalTileData;
        }

        TileData* newTileData = nullptr;
        TileData* tempTileData = nullptr;

        switch (translation)
        {
            case 1:
                newTileData = rotateTileData(originalTileData, 90);
                break;
            case 2:
                newTileData = rotateTileData(originalTileData, 180);
                break;
            case 3:
                newTileData = rotateTileData(originalTileData, 270);
                break;
            case 4:
                newTileData = flipTileDataHorizontally(originalTileData);
                break;
            case 5:
                tempTileData = flipTileDataHorizontally(originalTileData);
                newTileData = rotateTileData(tempTileData, 90);
                break;
            case 6:
                tempTileData = flipTileDataHorizontally(originalTileData);
                newTileData = rotateTileData(tempTileData, 180);
                break;
            case 7:
                tempTileData = flipTileDataHorizontally(originalTileData);
                newTileData = rotateTileData(tempTileData, 270);
                break;
        }

        if (tempTileData != nullptr)
        {
            delete(tempTileData);
        }

        return newTileData;
    }

    TileData* flipTileDataHorizontally(const TileData* originalTileData) const
    {
        const size_t rows = originalTileData->size();

        TileData* newTileData = new TileData();
        newTileData->resize(rows);

        for (size_t i = 0; i < rows; i++)
        {
            for (auto itr = originalTileData->at(i).rbegin(); itr != originalTileData->at(i).rend(); itr++)
            {
                newTileData->at(i).push_back(*itr);
            }
        }

        return newTileData;
    }

    TileData* rotateTileData(const TileData* originalTileData, const size_t degrees) const
    {
        const size_t rows = originalTileData->size();
        const size_t columns = originalTileData->at(0).size();

        TileData* newTileData = new TileData();
        newTileData->resize(rows);

        if (degrees == 90)
        {
            for (size_t i = 0; i < columns; i++)
            {
                for (auto itr = originalTileData->rbegin(); itr != originalTileData->rend(); itr++)
                {
                    newTileData->at(i).push_back((*itr)[i]);
                }
            }
        }
        else if (degrees == 180)
        {
            for (size_t y = 0; y < rows; y++)
            {
                for (size_t x = 0; x < columns; x++)
                {
                    newTileData->at(y).push_back(originalTileData->at(columns - y - 1)[columns - x - 1]);
                }
            }
        }
        else if (degrees == 270)
        {
            for (auto itr = originalTileData->begin(); itr != originalTileData->end(); itr++)
            {
                for (size_t i = 0; i < columns; i++)
                {
                    newTileData->at(rows - i - 1).push_back((*itr)[i]);
                }
            }
        }

        return newTileData;
    }

public:
    Tile(const size_t tileId, TileData* tileData, const size_t translation)
        : tileId{tileId}
        , tileData{getTranslatedTileData(tileData, translation)}
        , neighborTiles{nullptr, nullptr, nullptr, nullptr}
    {}

    ~Tile()
    {
        delete(tileData);
    }

    size_t getId() const
    {
        return tileId;
    }

    void setNeighborTile(const Side side, Tile* tile)
    {
        neighborTiles[side] = tile;
    }

    const Tile* getNeighborTile(const Side side) const
    {
        return neighborTiles[side];
    }

    TileData* getTileData() const
    {
        return tileData;
    }
};

class TileHandler
{
private:
    Tiles tiles;

    void addTile(const size_t tileId, TileData* tileData)
    {
        TileTranslations tileTranslations;

        for (size_t translation = 0; translation < 8; translation++)
        {
            tileTranslations.push_back(new Tile(tileId, tileData, translation));
        }

        tiles.push_back(tileTranslations);
    }

    void setNeighbors(Tile* tileA, Tile* tileB)
    {
        const TileData* tileDataA = tileA->getTileData();
        const TileData* tileDataB = tileB->getTileData();

        if (testLeftToRightSides(tileDataA, tileDataB))
        {
            tileA->setNeighborTile(Side::Right, tileB);
            tileB->setNeighborTile(Side::Left, tileA);
        }

        if (testLeftToRightSides(tileDataB, tileDataA))
        {
            tileB->setNeighborTile(Side::Right, tileA);
            tileA->setNeighborTile(Side::Left, tileB);
        }

        if (testUpperToLowerSides(tileDataA, tileDataB))
        {
            tileA->setNeighborTile(Side::Lower, tileB);
            tileB->setNeighborTile(Side::Upper, tileA);
        }

        if (testUpperToLowerSides(tileDataB, tileDataA))
        {
            tileB->setNeighborTile(Side::Lower, tileA);
            tileA->setNeighborTile(Side::Upper, tileB);
        }
    }

    bool testLeftToRightSides(const TileData* leftTileData, const TileData* rightTileData) const
    {
        for (size_t i = 0; i < leftTileData->size(); i++)
        {
            if (leftTileData->at(i).back() != rightTileData->at(i).front())
            {
                return false;
            }
        }

        return true;
    }

    bool testUpperToLowerSides(const TileData* upperTileData, const TileData* lowerTileData) const
    {
        for (size_t i = 0; i < upperTileData->at(0).size(); i++)
        {
            if (upperTileData->back()[i] != lowerTileData->front()[i])
            {
                return false;
            }
        }

        return true;
    }

public:
    TileHandler()
        : tiles{}
    {}

    ~TileHandler()
    {
        for (const TileTranslations& tileTranslations : tiles)
        {
            for (Tile* tile : tileTranslations)
            {
                delete(tile);
            }
        }
    }

    void readTiles()
    {
        std::string line;

        while (std::getline(std::cin, line))
        {
            if (line.empty())
            {
                continue;
            }

            const size_t tileId = std::stoi(line.substr(5, line.size()));
            TileData* tileData = new TileData();

            while (std::getline(std::cin, line))
            {
                if (line.empty())
                {
                    break;
                }

                tileData->push_back(std::vector<char>(line.begin(), line.end()));
            }

            addTile(tileId, tileData);
        }
    }

    void setAllNeighbors()
    {
        for (size_t a = 0; a < tiles.size(); a++)
        {
            for (size_t b = a + 1; b < tiles.size(); b++)
            {
                const TileTranslations& tileTranslationsA = tiles[a];
                const TileTranslations& tileTranslationsB = tiles[b];

                for (Tile* tileA : tileTranslationsA)
                {
                    for (Tile* tileB : tileTranslationsB)
                    {
                        setNeighbors(tileA, tileB);
                    }
                }
            }
        }
    }

    const std::vector<Tile*> getCornerTiles() const
    {
        std::vector<Tile*> cornerTiles;

        for (const auto& tileTranslations : tiles)
        {
            if (tileTranslations[0]->getNeighborTile(Side::Left) == nullptr &&
                tileTranslations[0]->getNeighborTile(Side::Upper) == nullptr)
            {
                cornerTiles.push_back(tileTranslations[0]);
            }
            else if (tileTranslations[0]->getNeighborTile(Side::Right) == nullptr &&
                     tileTranslations[0]->getNeighborTile(Side::Upper) == nullptr)
            {
                cornerTiles.push_back(tileTranslations[0]);
            }
            else if (tileTranslations[0]->getNeighborTile(Side::Left) == nullptr &&
                     tileTranslations[0]->getNeighborTile(Side::Lower) == nullptr)
            {
                cornerTiles.push_back(tileTranslations[0]);
            }
            else if (tileTranslations[0]->getNeighborTile(Side::Right) == nullptr &&
                     tileTranslations[0]->getNeighborTile(Side::Lower) == nullptr)
            {
                cornerTiles.push_back(tileTranslations[0]);
            }
        }

        return cornerTiles;
    }
};

int main()
{
    TileHandler tileHandler;
    tileHandler.readTiles();
    tileHandler.setAllNeighbors();

    uint64_t product = 1;

    for (const Tile* tile : tileHandler.getCornerTiles())
    {
        product *= tile->getId();
    }

    std::cout << product << std::endl;

    return 0;
}
