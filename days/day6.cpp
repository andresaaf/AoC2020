#include "days.hpp"

using namespace std;

void day6(istream& in, int part)
{
    if (part == 1)
    {
        size_t total_size = 0;
        unordered_set<char> uset{};
        string line;
        while (getline(in, line))
        {
            if (line == ""s)
            {
                total_size += uset.size();
                uset.clear();
                continue;
            }

            for (auto c : line)
            {
                uset.insert(c);
            }
        }
        total_size += uset.size(); // last group

        cout << total_size;
    }
    else
    {
        size_t total_size = 0;
        int rows = 0;
        map<char, int> mmap{};
        string line;
        while (getline(in, line))
        {
            if (line == ""s)
            {
                total_size += count_if(cbegin(mmap), cend(mmap), [rows](auto it) { return it.second == rows; });
                mmap.clear();
                rows = 0;
                continue;
            }

            ++rows;
            for (auto c : line)
            {
                if (mmap.find(c) == end(mmap))
                    mmap[c] = 1;
                else
                    mmap[c] += 1;
            }
        }
        total_size += count_if(cbegin(mmap), cend(mmap), [rows](auto it) { return it.second == rows; });

        cout << total_size;
    }
}
