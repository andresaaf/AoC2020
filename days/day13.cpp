#include "days.hpp"

using namespace std;

namespace
{
    struct Bus
    {
        int id;
        int pos;

        bool operator<(const Bus& rhs)
        {
            return id < rhs.id;
        }
    };
}

void day13(istream& in, int part)
{
    uint32_t earliest;
    in >> earliest;
    string line;
    in >> line;

    vector<Bus> buses;
    size_t pos = 0;
    int bus_pos = 0;
    while ((pos = line.find(',')) != string::npos)
    {
        auto entry = line.substr(0, pos);
        if (entry != "x"s)
            buses.push_back({ stoi(entry), bus_pos });
        line.erase(0, pos + 1);
        ++bus_pos;
    }
    if (line != "x"s)
        buses.push_back({ stoi(line), bus_pos });

    if (part == 1)
    {
        int next_bus = 0;
        int next_bus_wait = INT_MAX;
        for (auto bus : buses)
        {
            if (bus.id == -1)
                continue;
            int prev_arrival = earliest - (earliest % bus.id);
            int next_arrival = prev_arrival + bus.id;
            int diff = next_arrival - earliest;

            if (next_bus_wait > diff)
            {
                next_bus_wait = diff;
                next_bus = bus.id;
            }
        }
        cout << (next_bus * next_bus_wait);
    }
    else
    {
        auto it = begin(buses);
        uint64_t step = it->id;
        uint64_t id = 0;
        ++it;
        while (it != end(buses))
        {
            id += step;
            if ((id + it->pos) % it->id == 0)
            {
                step *= it->id;
                ++it;
            }
        }
        cout << id;
    }
}
