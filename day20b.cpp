
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
    Tile(TileData* tileData, const size_t translation)
        : tileData{getTranslatedTileData(tileData, translation)}
        , neighborTiles{nullptr, nullptr, nullptr, nullptr}
    {}

    ~Tile()
    {
        delete(tileData);
    }

    void setNeighborTile(const Side side, Tile* tile)
    {
        neighborTiles[side] = tile;
    }

    Tile* getNeighborTile(const Side side) const
    {
        return neighborTiles[side];
    }

    TileData* getTileData() const
    {
        return tileData;
    }

    TileData* getTrimmedTileData()
    {
        tileData->erase(tileData->begin());
        tileData->pop_back();

        for (size_t i = 0; i < tileData->size(); i++)
        {
            tileData->at(i).erase(tileData->at(i).begin());
            tileData->at(i).pop_back();
        }

        return tileData;
    }
};

class TileHandler
{
private:
    Tiles tiles;
    TileTranslations fullTiles;

    void addTile(TileData* tileData)
    {
        TileTranslations tileTranslations;

        for (size_t translation = 0; translation < 8; translation++)
        {
            tileTranslations.push_back(new Tile(tileData, translation));
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

    Tile* getStartTile() const
    {
        for (const auto& tileTranslations : tiles)
        {
            for (Tile* tile : tileTranslations)
            {
                if (tile->getNeighborTile(Side::Left)  == nullptr &&
                    tile->getNeighborTile(Side::Upper) == nullptr)
                {
                    return tile;
                }
            }
        }

        return nullptr;
    }

    const std::vector<Tile*> getFullTileParts(Tile* startTile)
    {
        std::vector<Tile*> fullTileParts;

        Tile* rowTile = startTile;
        Tile* columnTile = rowTile;

        while (true)
        {
            fullTileParts.push_back(columnTile);
            columnTile = columnTile->getNeighborTile(Side::Right);

            if (columnTile == nullptr)
            {
                rowTile = rowTile->getNeighborTile(Side::Lower);

                if (rowTile == nullptr)
                {
                    return fullTileParts;
                }
                else
                {
                    columnTile = rowTile;
                }
            }
        }

        return std::vector<Tile*>();
    }

public:
    TileHandler()
        : tiles{}
        , fullTiles{}
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

        for (Tile* tile : fullTiles)
        {
            delete(tile);
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

            TileData* tileData = new TileData();

            while (std::getline(std::cin, line))
            {
                if (line.empty())
                {
                    break;
                }

                tileData->push_back(std::vector<char>(line.begin(), line.end()));
            }

            addTile(tileData);
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

    void assembleFullTile()
    {
        Tile* startTile = getStartTile();

        if (startTile == nullptr)
        {
            exit(1);
        }

        const std::vector<Tile*> fullTileParts = getFullTileParts(startTile);

        if (fullTileParts.empty())
        {
            exit(1);
        }

        const size_t newHeight = sqrt(fullTileParts.size()) * (fullTileParts[0]->getTileData()->size() - 2);

        TileData* fullTileData = new TileData();
        fullTileData->resize(newHeight);

        size_t yOffset = 0;

        for (Tile* tile : fullTileParts)
        {
            const TileData* tileData = tile->getTrimmedTileData();

            for (size_t y = 0; y < tileData->size(); y++)
            {
                fullTileData->at(y + yOffset).insert(fullTileData->at(y + yOffset).end(), tileData->at(y).begin(), tileData->at(y).end());
            }

            if (tile->getNeighborTile(Side::Right) == nullptr)
            {
                yOffset += tileData->size();
            }
        }

        for (size_t translation = 0; translation < 8; translation++)
        {
            fullTiles.push_back(new Tile(fullTileData, translation));
        }
    }

    const TileTranslations& getFullTileTranslations() const
    {
        return fullTiles;
    }
};

int main()
{
    TileHandler tileHandler;
    tileHandler.readTiles();
    tileHandler.setAllNeighbors();
    tileHandler.assembleFullTile();

    for (const Tile* tile : tileHandler.getFullTileTranslations())
    {
        const TileData* tileData = tile->getTileData();
        std::vector<size_t> posVector[2];
        size_t monsters = 0;

        for (size_t y = 0; y < tileData->size(); y++)
        {
            for (size_t pos : posVector[1])
            {
                if (tileData->at(y)[pos + 1]  != '#' ||
                    tileData->at(y)[pos + 4]  != '#' ||
                    tileData->at(y)[pos + 7]  != '#' ||
                    tileData->at(y)[pos + 10] != '#' ||
                    tileData->at(y)[pos + 13] != '#' ||
                    tileData->at(y)[pos + 16] != '#')
                {
                    continue;
                }

                monsters++;
            }

            posVector[1].clear();

            for (size_t pos : posVector[0])
            {
                if (tileData->at(y)[pos + 0]  != '#' ||
                    tileData->at(y)[pos + 5]  != '#' ||
                    tileData->at(y)[pos + 6]  != '#' ||
                    tileData->at(y)[pos + 11] != '#' ||
                    tileData->at(y)[pos + 12] != '#' ||
                    tileData->at(y)[pos + 17] != '#' ||
                    tileData->at(y)[pos + 18] != '#' ||
                    tileData->at(y)[pos + 19] != '#')
                {
                    continue;
                }

                posVector[1].push_back(pos);
            }

            posVector[0].clear();
            size_t pos = 0;

            while (pos + 19 < tileData->at(y).size())
            {
                if (tileData->at(y)[pos + 18] == '#')
                {
                    posVector[0].push_back(pos);
                }

                pos++;
            }
        }

        if (monsters > 0)
        {
            size_t sum = 0;

            for (size_t y = 0; y < tileData->size(); y++)
            {
                sum += std::count(tileData->at(y).begin(), tileData->at(y).end(), '#');
            }

            std::cout << sum - (15 * monsters) << std::endl;

            return 0;
        }
    }

    return 1;
}
