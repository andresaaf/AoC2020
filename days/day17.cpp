#include "days.hpp"

using namespace std;

namespace
{
    constexpr char ACTIVE = '#';
    constexpr char INACTIVE = '.';

    struct Slice
    {
        Slice() = default;
        Slice(size_t size)
        {
            for (size_t i = 0; i < size; ++i)
            {
                rows.emplace_back(size, INACTIVE);
            }
        }

        friend ostream& operator<<(ostream& os, const Slice& slice)
        {
            for (auto& row : slice.rows)
            {
                for (auto c : row)
                {
                    os << c;
                }
                os << '\n';
            }
            return os;
        }

        vector<vector<char>> rows;
    };

    class GameOfLife3D
    {
    public:
        GameOfLife3D(Slice initial, size_t size)
            : size(size)
            , grid()
        {
            grid.push_back(initial);
            extend_grid();
        }

        void step()
        {
            extend_grid();
            vector<Slice> new_grid = grid;

            auto slice_neighbors = [](Slice& slice, int x, int y, bool ignore_same = false) {
                int neighbors = 0;
                for (int j = 0; j < 3; ++j)
                {
                    for (int i = 0; i < 3; ++i)
                    {
                        if (ignore_same && (j == 1 && i == 1))
                            continue;
                        if (slice.rows[y+j][x+i] == ACTIVE)
                            ++neighbors;
                    }
                }
                return neighbors;
            };

            auto slice = ++begin(grid);
            const auto stop = --end(grid);
            for (; slice != stop; ++slice)
            {
                auto prev = slice - 1;
                auto next = slice + 1;

                for (int y = 1; y < size - 1; ++y)
                {
                    for (int x = 1; x < size - 1; ++x)
                    {
                        char cube = slice->rows[y][x];
                        int neighbors =
                            slice_neighbors(*prev, x - 1, y - 1) +
                            slice_neighbors(*slice, x - 1, y - 1, true) +
                            slice_neighbors(*next, x - 1, y - 1);

                        if (cube == ACTIVE)
                        {
                            if (neighbors < 2 || neighbors > 3)
                            {
                                new_grid[distance(begin(grid), slice)].rows[y][x] = INACTIVE;
                            }
                        }
                        else
                        {
                            if (neighbors == 3)
                            {
                                new_grid[distance(begin(grid), slice)].rows[y][x] = ACTIVE;
                            }
                        }
                    }
                }
            }

            grid.swap(new_grid);
        }

        int active_cubes() const
        {
            int active = 0;
            for (auto& slice : grid)
            {
                for (auto& row : slice.rows)
                {
                    for (auto& cube : row)
                    {
                        if (cube == ACTIVE)
                            ++active;
                    }
                }
            }
            return active;
        }

        friend ostream& operator<<(ostream& os, const GameOfLife3D& game)
        {
            int i = -static_cast<int>(game.grid.size() / 2);

            for (auto& slice : game.grid)
            {
                os << "z=" << (i++) << '\n' << slice << "\n\n";
            }
            return os;
        }

    private:
        void extend_grid()
        {
            size += 2;

            // Extend current grids
            for (auto& slice : grid)
            {
                for (auto& row : slice.rows)
                {
                    row.emplace(begin(row), INACTIVE);
                    row.emplace_back(INACTIVE);
                }
                slice.rows.emplace(begin(slice.rows), vector<char>(size, INACTIVE));
                slice.rows.emplace_back(vector<char>(size, INACTIVE));
            }

            // Create two new layers
            grid.emplace(begin(grid), size);
            grid.emplace_back(size);
        }

        void neighbors(size_t slice)
        {

        }

    private:
        size_t size;
        vector<Slice> grid;
    };
}

void day17(istream& in, int part)
{
    Slice start;

    string line;
    while (in >> line)
    {
        auto& slice = start.rows.emplace_back();
        for (auto c : line)
        {
            slice.push_back(c);
        }
    }

    if (part == 1)
    {
        GameOfLife3D game(start, start.rows[0].size());

        cout << "Before any cycles:\n\n";
        cout << game;

        for (int i = 0; i < 6; ++i)
        {
            cout << "After " << i << " cycles:\n\n";
            game.step();
            cout << game;
        }
        cout << game.active_cubes();
    }
    else
    {

    }
}
