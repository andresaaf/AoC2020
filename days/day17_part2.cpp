#include "days.hpp"

using namespace std;

namespace
{
    constexpr char ACTIVE = '#';
    constexpr char INACTIVE = '.';

    using Vec1d = vector<bool>;
    using Vec2d = vector<Vec1d>;
    using Vec3d = vector<Vec2d>;
    using Vec4d = vector<Vec3d>;

    class GameOfLife
    {
    public:
        GameOfLife(Vec2d initial, size_t size)
            : size(size)
            , size_z(1)
            , grid()
        {
            grid.emplace_back() // w=0
                .push_back(initial); // z=0

            extend_grid();
        }

        void step()
        {
            extend_grid();
            Vec4d new_grid = grid;

            auto slice_neighbors = [](Vec3d& slice, int x, int y, int z, bool ignore_same = false) {
                int neighbors = 0;

                for (int zz = 0; zz < 3; ++zz)
                {
                    for (int yy = 0; yy < 3; ++yy)
                    {
                        for (int xx = 0; xx < 3; ++xx)
                        {
                            if (ignore_same && (zz == 1 && yy == 1 && xx == 1))
                                continue;
                            if (slice[zz + z][yy + y][xx + x] == true)
                                ++neighbors;
                        }
                    }
                }
                return neighbors;
            };

            auto d4 = ++begin(grid);
            const auto stop = --end(grid);
            for (; d4 != stop; ++d4)
            {
                auto prev = d4 - 1;
                auto next = d4 + 1;

                for (int z = 1; z < size_z - 1; ++z)
                {
                    for (int y = 1; y < size - 1; ++y)
                    {
                        for (int x = 1; x < size - 1; ++x)
                        {
                            bool cube = (*d4)[z][y][x];
                            int neighbors =
                                slice_neighbors(*prev, x - 1, y - 1, z - 1) +
                                slice_neighbors(*d4, x - 1, y - 1, z - 1, true) +
                                slice_neighbors(*next, x - 1, y - 1, z - 1);

                            if (cube)
                            {
                                if (neighbors < 2 || neighbors > 3)
                                {
                                    new_grid[distance(begin(grid), d4)][z][y][x] = false;
                                }
                            }
                            else
                            {
                                if (neighbors == 3)
                                {
                                    new_grid[distance(begin(grid), d4)][z][y][x] = true;
                                }
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
            for (auto& w : grid)
                for (auto& z : w)
                    for (auto& y : z)
                        for (auto x : y)
                            if (x)
                                ++active;
            return active;
        }

        friend ostream& operator<<(ostream& os, const GameOfLife& game)
        {
            int w = -static_cast<int>(game.grid.size() / 2);

            for (auto& d4 : game.grid)
            {
                ++w;
                int z = -static_cast<int>(game.grid[0].size() / 2);

                for (auto& d3 : d4)
                {
                    ++z;
                    int y = -static_cast<int>(game.grid[0][0].size() / 2);

                    os << "w=" << w << " z=" << z << '\n';

                    for (auto& d2 : d3)
                    {
                        for (auto d1 : d2)
                        {
                            os << (d1 ? ACTIVE : INACTIVE);
                        }
                        os << '\n';
                    }

                    os << '\n';
                }
            }
            return os;
        }

    private:
        void extend_grid()
        {
            size += 2;
            size_z += 2;

            // Extend existing grid
            for (auto& w : grid)
            {
                for (auto& z : w)
                {
                    for (auto& y : z)
                    {
                        y.emplace(begin(y), false);
                        y.emplace_back(false);
                    }
                    Vec1d new_1d = Vec1d(size, false);
                    z.emplace(begin(z), new_1d);
                    z.emplace_back(new_1d);
                }

                Vec2d new_2d = Vec2d(size, Vec1d(size, false));
                w.emplace(begin(w), new_2d);
                w.emplace_back(new_2d);
            }

            // Create two new empty w dimensions
            Vec3d new_3d(size_z, Vec2d(size, Vec1d(size, false)));
            grid.emplace(begin(grid), new_3d);
            grid.emplace_back(new_3d);
        }

    private:
        size_t size;
        size_t size_z;
        Vec4d grid; // grid[w][z][y][x]
    };
}

void day17_part2(istream& in, int part)
{
    Vec2d start;

    string line;
    while (in >> line)
    {
        auto& slice = start.emplace_back();
        for (auto c : line)
        {
            slice.push_back(c == ACTIVE);
        }
    }

    if (part == 2)
    {
        GameOfLife game(start, start[0].size());

        cout << "Before any cycles:\n\n";
        cout << game;

        for (int i = 0; i < 6; ++i)
        {
            //cout << "After " << i << " cycles:\n\n";
            game.step();
            //cout << game;
        }
        cout << game.active_cubes();
    }
}
