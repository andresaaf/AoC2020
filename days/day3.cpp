#include "days.hpp"

using namespace std;

void day3(istream& in, int part)
{
    if (part == 1)
    {
        int trees = 0;
        uint64_t x = 4;
        string line;
        in >> line; // Skip first
        while (in >> line)
        {
            if (line[(x - 1) % line.length()] == '#')
            {
                ++trees;
            }

            x += 3;
        }

        cout << trees;
    }
    else
    {
        struct move {
            const int right;
            const int down;
            int x;
            int skipped;
            int trees;
        };

        array<move, 5> moves = { {
            {1, 1, 2, 0, 0},
            {3, 1, 4, 0, 0},
            {5, 1, 6, 0, 0},
            {7, 1, 8, 0, 0},
            {1, 2, 2, 0, 0}
        } };

        string line;
        in >> line; // Skip first
        while (in >> line)
        {
            for (auto& move : moves)
            {
                if (move.down > 1)
                {
                    if ((move.skipped + 1) == move.down)
                    {
                        move.skipped = 0;
                    }
                    else
                    {
                        ++move.skipped;
                        continue;
                    }
                }

                if (line[(move.x - 1) % line.length()] == '#')
                {
                    ++move.trees;
                }

                move.x += move.right;
            }
        }

        auto total_trees = accumulate(begin(moves), end(moves), 1ull, [](uint64_t acc, move next) { return acc * next.trees; });

        cout << total_trees;
    }
}
