#include "days.hpp"

using namespace std;

namespace
{
    auto parse(const std::string& line) -> pair<int, int>
    {
        static constexpr uint32_t ROWS = 128;
        static constexpr uint32_t COLS = 8;

        // Parse row
        int start = 0;
        int end = ROWS - 1;
        for (int i = 0; i < 7; ++i)
        {
            if (line[i] == 'F')
            {
                end = start + ((end - start) / 2);
            }
            else
            {
                start += static_cast<int>(((end - start) / 2.0f) + 0.5f);
            }
        }

        int row = start;

        // Parse col
        start = 0;
        end = COLS - 1;
        for (int i = 7; i < 10; ++i)
        {
            if (line[i] == 'L')
            {
                end = start + ((end - start) / 2);
            }
            else
            {
                start += static_cast<int>(((end - start) / 2.0f) + 0.5f);
            }
        }

        return { row, start };
    }
}

void day5(istream& in, int part)
{
    array<bool, 128 * 8> boarding_list{};

    string line;
    while (in >> line)
    {
        auto [row, col] = parse(line);
        boarding_list[row * 8 + col] = true;
    }

    if (part == 1)
    {
        auto max_pass = find(rbegin(boarding_list), rend(boarding_list), true);
        cout << distance(begin(boarding_list), max_pass.base() - 1);
    }
    else
    {
        // Trim leading and trailing false
        auto start = find(begin(boarding_list), end(boarding_list), true);
        auto tend = find(rbegin(boarding_list), rend(boarding_list), true);

        // Will be in form of row*8 + col
        auto my_seat = distance(begin(boarding_list), find(start, tend.base() - 1, false));
        cout << my_seat;
    }
}
