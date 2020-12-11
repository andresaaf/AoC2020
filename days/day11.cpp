#include "days.hpp"

using namespace std;

namespace
{
    constexpr char FLOOR = '.';
    constexpr char EMPTY_SEAT = 'L';
    constexpr char OCCUPIED_SEAT = '#';

    template<typename... checks>
    bool has_far_neighbor(const vector<char>& grid, size_t row_len, size_t cell_index, int x, int y, checks&&... check)
    {
        while ((check(cell_index) && ...))
        {
            cell_index += y * row_len + x;

            if (grid[cell_index] == OCCUPIED_SEAT)
                return true;
            else if (grid[cell_index] == EMPTY_SEAT)
                return false;
        }
        return false;
    }

    int count_far_neighbors(const vector<char>& grid, size_t row_len, size_t cell_index)
    {
        int neighbors = 0;

        auto has_left = [row_len](int cell) { return cell % row_len > 0; };
        auto has_up = [row_len](int cell) { return cell >= row_len; };
        auto has_right = [row_len](int cell) { return cell % row_len != (row_len - 1); };
        auto has_down = [row_len, size = grid.size()](int cell) { return cell < (size - row_len); };

        // Up-left
        if (has_far_neighbor(grid, row_len, cell_index, -1, -1, has_up, has_left))
            ++neighbors;

        // Up
        if (has_far_neighbor(grid, row_len, cell_index, 0, -1, has_up))
            ++neighbors;

        // Up-right
        if (has_far_neighbor(grid, row_len, cell_index, 1, -1, has_up, has_right))
            ++neighbors;

        // Left
        if (has_far_neighbor(grid, row_len, cell_index, -1, 0, has_left))
            ++neighbors;

        // Right
        if (has_far_neighbor(grid, row_len, cell_index, 1, 0, has_right))
            ++neighbors;

        // Down-left
        if (has_far_neighbor(grid, row_len, cell_index, -1, 1, has_down, has_left))
            ++neighbors;

        // Down
        if (has_far_neighbor(grid, row_len, cell_index, 0, 1, has_down))
            ++neighbors;

        // Down-right
        if (has_far_neighbor(grid, row_len, cell_index, 1, 1, has_down, has_right))
            ++neighbors;

        return neighbors;
    }

    int count_neighbors(const vector<char>& grid, size_t row_len, size_t cell_index)
    {
        int neighbors = 0;

        bool has_left = cell_index % row_len > 0;
        bool has_up = cell_index >= row_len;
        bool has_right = cell_index % row_len != (row_len - 1);
        bool has_down = cell_index < (grid.size() - row_len);

        // Up-left
        if (has_up && has_left
            && grid[cell_index - row_len - 1] == OCCUPIED_SEAT)
            ++neighbors;

        // Up
        if (has_up
            && grid[cell_index - row_len] == OCCUPIED_SEAT)
            ++neighbors;

        // Up-right
        if (has_up && has_right
            && grid[cell_index - row_len + 1] == OCCUPIED_SEAT)
            ++neighbors;

        // Left
        if (has_left
            && grid[cell_index - 1] == OCCUPIED_SEAT)
            ++neighbors;

        // Right
        if (has_right
            && grid[cell_index + 1] == OCCUPIED_SEAT)
            ++neighbors;

        // Down-left
        if (has_down && has_left
            && grid[cell_index + row_len - 1] == OCCUPIED_SEAT)
            ++neighbors;

        // Down
        if (has_down
            && grid[cell_index + row_len] == OCCUPIED_SEAT)
            ++neighbors;

        // Down-right
        if (has_down && has_right
            && grid[cell_index + row_len + 1] == OCCUPIED_SEAT)
            ++neighbors;

        return neighbors;
    }

    vector<char> run_simulation_1(const vector<char>& grid, size_t row_len)
    {
        vector<char> cpy(grid);

        for (size_t i = 0; i < grid.size(); ++i)
        {
            int neighbors = count_neighbors(grid, row_len, i);
            if (neighbors == 0 && grid[i] == EMPTY_SEAT)
                cpy[i] = OCCUPIED_SEAT;
            else if (neighbors >= 4 && grid[i] == OCCUPIED_SEAT)
                cpy[i] = EMPTY_SEAT;
        }

        return cpy;
    }

    vector<char> run_simulation_2(const vector<char>& grid, size_t row_len)
    {
        vector<char> cpy(grid);

        for (size_t i = 0; i < grid.size(); ++i)
        {
            int neighbors = count_far_neighbors(grid, row_len, i);
            if (neighbors == 0 && grid[i] == EMPTY_SEAT)
                cpy[i] = OCCUPIED_SEAT;
            else if (neighbors >= 5 && grid[i] == OCCUPIED_SEAT)
                cpy[i] = EMPTY_SEAT;
        }

        return cpy;
    }
}

void day11(istream& in, int part)
{
    vector<char> grid{};
    string line;
    size_t row_len = 0;
    while (in >> line)
    {
        row_len = line.length();
        for (char c : line)
        {
            grid.push_back(c);
        }
    }

    vector<char> sim(grid);
    vector<char> prev(grid);

    while (true)
    {
        if (part == 1)
            sim = run_simulation_1(sim, row_len);
        else
            sim = run_simulation_2(sim, row_len);

        if (sim == prev)
            break;

        prev = sim;
    };

    auto occupied = count(begin(sim), end(sim), OCCUPIED_SEAT);
    cout << occupied;
}
