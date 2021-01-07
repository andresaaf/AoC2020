#include "days.hpp"

using namespace std;

namespace
{
    struct CircularList
    {
        int64_t value;
        CircularList* next;
    };

    template<int N>
    void step(CircularList* cups, vector<CircularList*>& index)
    {
        array<CircularList*, 3> next_3 = {
            cups->next,
            cups->next->next,
            cups->next->next->next
        };

        auto dest = cups->value;
        while (true)
        {
            dest -= 1;
            if (dest == 0)
                dest = N;
            if (find_if(next_3.begin(), next_3.end(), [dest](CircularList* node) { return node->value == dest; }) == end(next_3))
                break;
        }
        
        CircularList* next_it = index[dest];

        // current -> [3 cups] -> new_current_next
        cups->next = next_3[2]->next;

        // next_it -> [3 cups] -> next_it->next
        auto temp = next_it->next;
        next_it->next = next_3[0];
        next_3[2]->next = temp;
    }
}

void day23(istream& in, int part)
{
    string line;
    in >> line;

    vector<CircularList*> index(part == 1 ? 10 : 10'000'001);

    CircularList* prev = new CircularList{ line[0] - '0', nullptr };
    CircularList* head = prev;
    index[prev->value] = prev;
    for (int i = 1; i < 9; ++i)
    {
        CircularList* node = new CircularList{ line[i] - '0', nullptr };
        prev->next = node;
        prev = node;
        index[prev->value] = prev;
    }

    if (part == 2)
    {
        for (int i = 9; i < 1000000; ++i)
        {
            CircularList* node = new CircularList{ (i + 1), nullptr };
            prev->next = node;
            prev = node;
            index[prev->value] = prev;
        }
    }

    prev->next = head;

    CircularList* cup_it = head;
    if (part == 1)
    {
        for (int steps = 0; steps < 100; ++steps)
        {
            step<9>(cup_it, index);
            cup_it = cup_it->next;
        }
    }
    else
    {
        for (int steps = 0; steps < 10000000; ++steps)
        {
            step<1000000>(cup_it, index);
            cup_it = cup_it->next;
        }
    }

    cout << "\n\nDone: ";

    if (part == 1)
    {
        auto it = index[1]->next;
        for (int i = 0; i < 8; ++i)
        {
            cout << it->value;
            it = it->next;
        }
    }
    else
    {
        cout << index[1]->next->value << " * " << index[1]->next->next->value << " = ";
        cout << (index[1]->next->value * index[1]->next->next->value);
    }
}
