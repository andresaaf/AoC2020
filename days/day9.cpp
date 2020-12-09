#include "days.hpp"

using namespace std;

namespace
{
    static constexpr uint32_t PREAMBLE_SIZE = 25U;
    bool is_valid(const array<uint64_t, PREAMBLE_SIZE>& preamble, uint64_t value)
    {
        for (int n1 = 0; n1 < PREAMBLE_SIZE - 1; ++n1)
        {
            for (int n2 = n1 + 1; n2 < PREAMBLE_SIZE; ++n2)
            {
                if ((preamble[n1] + preamble[n2]) == value)
                    return true;
            }
        }
        return false;
    }
}

void day9(istream& in, int part)
{
    if (part == 1)
    {
        array<uint64_t, PREAMBLE_SIZE> preamble;
        for (int i = 0; i < PREAMBLE_SIZE; ++i)
        {
            in >> preamble[i];
        }

        uint32_t index = 0;
        uint64_t num;
        while (in >> num)
        {
            if (!is_valid(preamble, num))
                cout << num << '\n';

            preamble[(index++) % PREAMBLE_SIZE] = num;
        }
    }
    else
    {
        static constexpr uint64_t target = 90433990; // from part 1

        vector<uint64_t> numbers;
        uint64_t num;
        while (in >> num)
        {
            numbers.push_back(num);
        }

        for (int x = 0; x < numbers.size() - 1; ++x)
        {
            int y = x + 1;
            uint64_t sum = numbers[x];
            uint64_t smallest = sum, largest = sum;
            while (sum < target && y < numbers.size())
            {
                uint64_t num = numbers[y++];
                sum += num;
                smallest = min(smallest, num);
                largest = max(largest, num);
            }

            if (sum == target)
            {
                cout << "FOUND: min=" << smallest << " max=" << largest << " sum:" << (smallest + largest) << '\n';
            }
        }
    }
}
