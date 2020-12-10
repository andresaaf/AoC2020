#include "days.hpp"

using namespace std;

namespace
{
    pair<bool, uint64_t> count_chains(vector<int64_t>& mem, const set<int>& jolts, int target, int curr)
    {
        if (mem[curr] != -1)
            return { true, mem[curr] };

        if (jolts.find(curr) == end(jolts))
            return { false, 0 };

        if (curr == target - 3)
            return { true, 1 };

        uint64_t cnt = 0;
        auto [ends1, cnt1] = count_chains(mem, jolts, target, curr + 1);
        if (ends1)
            cnt += cnt1;
        auto [ends2, cnt2] = count_chains(mem, jolts, target, curr + 2);
        if (ends2)
            cnt += cnt2;
        auto [ends3, cnt3] = count_chains(mem, jolts, target, curr + 3);
        if (ends3)
            cnt += cnt3;

        bool ends = ends1 || ends2 || ends3;
        mem[curr] = ends ? cnt : -1;
        return { ends, cnt };
    }

    tuple<bool, int, int> find_chain(const set<int>& jolts, int target, int curr)
    {
        if (jolts.find(curr) == end(jolts))
            return { false, 0, 0 };

        if (curr == target || curr == target - 2)
            return { true, 0, 0 };
        else if (curr == target - 1)
            return { true, 1, 0 };
        else if (curr == target - 3)
            return { true, 0, 1 };

        auto [ends1, d1_1, d3_1] = find_chain(jolts, target, curr + 1);
        if (ends1)
            return { true, d1_1 + 1, d3_1 };

        auto [ends2, d1_2, d3_2] = find_chain(jolts, target, curr + 2);
        if (ends1)
            return { true, d1_2, d3_2 };

        auto [ends3, d1_3, d3_3] = find_chain(jolts, target, curr + 3);
        if (ends3)
            return { true, d1_3, d3_3 + 1 };

        return { false, 0, 0 };
    }
}

void day10(istream& in, int part)
{
    set<int> jolts;
    int temp;
    while (in >> temp)
    {
        jolts.insert(temp);
    }

    int dev_jolt = *jolts.rbegin() + 3;

    if (part == 1)
    {
        auto [ends1, d1_1, d3_1] = find_chain(jolts, dev_jolt, 1);
        ++d1_1;
        auto [ends2, d1_2, d3_2] = find_chain(jolts, dev_jolt, 2);
        auto [ends3, d1_3, d3_3] = find_chain(jolts, dev_jolt, 3);
        ++d3_3;

        if (ends1)
            cout << "0->1->... = " << (d1_1 * d3_1) << '\n';
        if (ends2)
            cout << "0->2->... = " << (d1_2 * d3_2) << '\n';
        if (ends3)
            cout << "0->3->... = " << (d1_3 * d3_3) << '\n';
    }
    else
    {
        vector<int64_t> mem(dev_jolt, -1);
        uint64_t cnt = 0;
        auto [ends1, cnt1] = count_chains(mem, jolts, dev_jolt, 1);
        if (ends1) cnt += cnt1;
        auto [ends2, cnt2] = count_chains(mem, jolts, dev_jolt, 2);
        if (ends2) cnt += cnt2;
        auto [ends3, cnt3] = count_chains(mem, jolts, dev_jolt, 3);
        if (ends3) cnt += cnt3;

        cout << cnt;
    }
}
