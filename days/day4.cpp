#include "days.hpp"

using namespace std;

void day4(istream& in, int part)
{
    struct passport
    {
        string byr{};
        string iyr{};
        string eyr{};
        string hgt{};
        string hcl{};
        string ecl{};
        string pid{};
        string cid{};

        void set(const string& key, const string& value)
        {
            if (key == "byr"s)
                byr = value;
            else if (key == "iyr"s)
                iyr = value;
            else if (key == "eyr"s)
                eyr = value;
            else if (key == "hgt"s)
                hgt = value;
            else if (key == "hcl"s)
                hcl = value;
            else if (key == "ecl"s)
                ecl = value;
            else if (key == "pid"s)
                pid = value;
            else if (key == "cid"s)
                cid = value;
        }

        bool valid(bool validate_value = false) const
        {
            bool all_keys = (byr != "" && iyr != "" && eyr != "" && hgt != "" && hcl != "" && ecl != "" && pid != "");
            if (!validate_value)
            {
                return all_keys;
            }
            else
            {
                if (!all_keys)
                    return false;

                int t_byr = stoi(byr);
                int t_iyr = stoi(iyr);
                int t_eyr = stoi(eyr);

                if (hgt.length() < 3)
                    return false;
                string hgt_unit = hgt.substr(hgt.length() - 2, 2);
                int hgt_n = stoi(hgt.substr(0, hgt.length() - 2));
                if (hgt_unit == "cm"s)
                {
                    if (hgt_n < 150 || hgt_n > 193)
                        return false;
                }
                else if (hgt_unit == "in"s)
                {
                    if (hgt_n < 59 || hgt_n > 76)
                        return false;
                }
                else
                    return false;

                if (hcl.length() != 7 || hcl[0] != '#')
                    return false;
                for (int i = 1; i < 7; ++i)
                    if (!((hcl[i] >= '0' && hcl[i] <= '9') || (hcl[i] >= 'a' && hcl[i] <= 'f')))
                        return false;

                if (ecl != "amb"s && ecl != "blu"s && ecl != "brn"s && ecl != "gry"s &&
                    ecl != "grn"s && ecl != "hzl"s && ecl != "oth"s)
                    return false;

                if (pid.length() != 9)
                    return false;
                if (!all_of(begin(pid), end(pid), [](char c) { return c >= '0' && c <= '9'; }))
                    return false;

                return (t_byr >= 1920 && t_byr <= 2002)
                    && (t_iyr >= 2010 && t_iyr <= 2020)
                    && (t_eyr >= 2020 && t_eyr <= 2030);
            }
        }
    };

    passport pass{};

    const bool validate = (part == 2);
    int valid = 0;
    string line;
    ostringstream ss;
    while (getline(in, line))
    {
        // New entry
        if (line == ""s)
        {
            if (pass.valid(validate))
                ++valid;
            pass = {};
            continue;
        }

        auto parse_word = [&pass](string word) {
            auto sep = word.find(':');
            auto key = word.substr(0, sep);
            auto value = word.substr(sep + 1, word.length() - sep);
            pass.set(key, value);
        };

        size_t pos = 0;
        while ((pos = line.find(' ')) != string::npos)
        {
            auto word = line.substr(0, pos);
            parse_word(word);
            line.erase(0, pos + 1);
        }
        parse_word(line); // last word
    }
    // ... last one
    if (pass.valid(validate))
        ++valid;

    cout << valid;
}
