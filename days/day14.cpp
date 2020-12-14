#include "days.hpp"

using namespace std;

void day14(istream& in, int part)
{
    string mask_str;
    uint64_t val_and_mask = 0;
    uint64_t or_mask = 0;
    uint64_t addr_and_mask = 0;
    map<uint64_t, uint64_t> mem;

    string line;
    while (getline(in, line))
    {
        if (line.substr(0, 4) == "mask"s)
        {
            mask_str = line.substr(7, 36);
            val_and_mask = 0;
            or_mask = 0;
            addr_and_mask = 0;

            for (uint64_t i = 0; i < 36; ++i)
            {
                uint64_t and_bit = mask_str[i] == 'X' ? 1 : 0;
                uint64_t or_bit = mask_str[i] == '1' ? 1 : 0;
                val_and_mask |= and_bit << (35ull - i);
                or_mask |= or_bit << (35ull - i);

                uint64_t addr_and_bit = mask_str[i] == '0' ? 1 : 0;
                addr_and_mask |= addr_and_bit << (35ull - i);
            }
        }
        else // mem
        {
            uint64_t addr = stoi(line.substr(4, line.find(']') - 4));
            uint64_t val = stoi(line.substr(line.find('=') + 2));

            if (part == 1)
            {
                mem[addr] |= (val & val_and_mask) | or_mask;
            }
            else
            {
                static constexpr uint64_t MAX = (1ull << 35ull);

                const auto base_addr = (addr & addr_and_mask) | or_mask;
                const auto wildcards = count(begin(mask_str), end(mask_str), 'X');
                const uint64_t combinations = 1ull << wildcards;

                for (uint64_t combination = 0; combination < combinations; ++combination)
                {
                    size_t pos = mask_str.length();
                    uint64_t this_addr = base_addr;
                    for (int i = 0; i < wildcards; ++i)
                    {
                        pos = mask_str.rfind('X', pos-1);
                        if (((1ull << i) & combination))
                        {
                            uint64_t float_bit = 1ull << (35ull - pos);
                            this_addr |= float_bit;
                        }
                    }

                    mem[this_addr] = val;
                }
            }
        }
    }

    cout << accumulate(begin(mem), end(mem), 0ull, [](uint64_t acc, auto next) { return acc + next.second; });
}
