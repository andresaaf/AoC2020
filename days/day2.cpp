#include "days.hpp"

using namespace std;

void day2(istream& in, int part)
{
    int valid = 0;
    string in_range, in_letter, pass;
    while (in >> in_range >> in_letter >> pass)
    {
        auto range_delimiter = in_range.find("-"s);
        auto range_start = stoi(in_range.substr(0, range_delimiter));
        auto range_end = stoi(in_range.substr(range_delimiter + 1, in_range.length() - range_delimiter));
        char letter = in_letter[0];

        if (part == 1)
        {
            auto num = count(begin(pass), end(pass), letter);
            if (num >= range_start && num <= range_end)
            {
                ++valid;
            }
        }
        else
        {

            int correct_letters = 0;
            if (pass[range_start - 1] == letter)
                ++correct_letters;
            if (pass[range_end - 1] == letter)
                ++correct_letters;

            if (correct_letters == 1)
            {
                ++valid;
            }
        }
    }

    cout << valid;
}
