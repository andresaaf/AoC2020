#include "days.hpp"

using namespace std;

void day1(istream& in, int part)
{
    if (part == 1)
    {
        // ..
    }
    else
    {
        vector<uint64_t> vec;
        for (int in; cin >> in;)
        {
            vec.push_back(in);
        }

        auto product = [&vec]() {
            for (size_t x = 0; x < vec.size(); ++x)
                for (size_t y = x + 1; y < vec.size(); ++y)
                    for (size_t z = y + 1; z < vec.size(); ++z)
                        if (vec[x] + vec[y] + vec[z] == 2020u)
                            return vec[x] * vec[y] * vec[z];

            return 0ull;
        }();

        cout << product;
    }
}
