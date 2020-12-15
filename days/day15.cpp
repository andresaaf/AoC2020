#include "days.hpp"

using namespace std;

void day15(istream& in, int part)
{
    unordered_map<int, int> num_index;
    int numbers = 0;
    int prev = 0;

    int i;
    char c;
    while (in >> i)
    {
        prev = i;
        ++numbers;
        num_index[i] = numbers - 1;
        in >> c;
    }

    // Erase last index from key list
    num_index.erase(i);

    const int target = (part == 1 ? 2020 : 30000000);
    while (numbers < target)
    {
        const auto last = num_index.find(prev);
        if (last == end(num_index))
        {
            num_index[prev] = numbers - 1;
            prev = 0;
            ++numbers;
        }
        else
        {
            auto diff = numbers - 1 - num_index[prev];
            num_index[prev] = numbers - 1;
            prev = diff;
            ++numbers;
        }
    }
    cout << prev;
}
