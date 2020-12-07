#include "days.hpp"

using namespace std;

namespace
{
    struct Bag
    {
        string type;
        list<pair<Bag*, int>> holds;

        Bag(string type) : type(type) {}
    };

    bool bag_holds_shiny_gold(Bag& bag)
    {
        if (bag.type == "shiny gold"s)
        {
            return false;
        }

        for (auto& b : bag.holds)
        {
            if (b.first->type == "shiny gold"s)
                return true;

            if (bag_holds_shiny_gold(*b.first))
                return true;
        }
        return false;
    }

    uint32_t bags_in_bag(Bag& bag)
    {
        return accumulate(begin(bag.holds), end(bag.holds), 0,
            [](uint32_t acc, const pair<Bag*, int>& bag) { return acc + bag.second + bag.second * bags_in_bag(*bag.first); });
    }

    Bag& get_bag(list<Bag>& bags, const string& bag_name)
    {
        auto f = find_if(begin(bags), end(bags), [bag_name](const auto& bag) { return bag.type == bag_name; });
        if (f == end(bags))
            return bags.emplace_back(bag_name);
        return *f;
    }
}

void day7(istream& in, int part)
{
    list<Bag> bags;

    string line;
    string temp;
    while (getline(in, line))
    {
        stringstream ss(line);

        string bag_type;
        string bag_color;
        ss >> bag_type >> bag_color >> temp >> temp;

        auto& bag = get_bag(bags, bag_type + " "s + bag_color);

        string bag_count;
        while (ss >> bag_count)
        {
            if (bag_count == "no"s)
            {
                break;
            }
            ss >> bag_type >> bag_color >> temp;
            auto& hold_bag = get_bag(bags, bag_type + " "s + bag_color);
            bag.holds.emplace_back(&hold_bag, stoi(bag_count));
        }
    }

    if (part == 1)
    {
        int total_shiny = 0;
        for (auto& bag : bags)
        {
            if (bag_holds_shiny_gold(bag))
                ++total_shiny;
        }

        cout << total_shiny;
    }
    else
    {
        cout << bags_in_bag(*find_if(begin(bags), end(bags), [](Bag& bag) { return bag.type == "shiny gold"s; }));
    }
}