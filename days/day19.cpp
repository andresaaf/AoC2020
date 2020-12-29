#include "days.hpp"

using namespace std;

namespace
{
    struct Rule {
        virtual ~Rule() = default;
    };

    struct Match : Rule
    {
        char letter;
        Match(char c) : letter(c) {}
    };

    struct Link : Rule
    {
        vector<vector<size_t>> rules;
    };

    vector<int> count_len(unordered_map<size_t, unique_ptr<Rule>>& rules, size_t rule_id, string_view line)
    {
        if (auto match = dynamic_cast<Match*>(rules[rule_id].get()))
        {
            if (line.length() > 0 && line[0] == match->letter)
                return { 1 };
            return {};
        }
        else if (auto link = dynamic_cast<Link*>(rules[rule_id].get()))
        {
            vector<int> paths;
            for_each(link->rules.begin(), link->rules.end(), [&](const auto& subrule) {
                vector<int> subpaths = { 0 };
                for_each(subrule.begin(), subrule.end(), [&](const auto subid) {
                    vector<int> temp;
                    for_each(subpaths.begin(), subpaths.end(), [&](auto subpath) {
                        for (auto c : count_len(rules, subid, line.substr(subpath)))
                            temp.push_back(c + subpath);
                    });
                    subpaths = move(temp);
                });
                paths.insert(paths.begin(), subpaths.begin(), subpaths.end());
            });
            return paths;
        }
        throw runtime_error("err");
    }
}

void day19(istream& in, int part)
{
    unordered_map<size_t, unique_ptr<Rule>> rules;
    string line;
    while (getline(in, line))
    {
        if (line == ""s)
            break;

        auto id = stoi(line.substr(0, line.find(':')));

        if (auto char_match = line.find('"');
            char_match != string::npos)
        {
            rules[id] = make_unique<Match>(line[char_match + 1]);
        }
        else
        {
            vector<string> words;
            size_t pos = 0;
            while ((pos = line.find(' ')) != std::string::npos) {
                words.push_back(line.substr(0, pos));
                line.erase(0, pos + 1);
            }
            words.push_back(line);


            auto link = make_unique<Link>();
            vector<size_t> rule;
            for (auto it = ++words.begin(); it != words.end(); ++it)
            {
                if (*it == "|"s)
                {
                    link->rules.push_back(rule);
                    rule.clear();
                }
                else
                {
                    rule.emplace_back(stoi(*it));
                }
            }
            link->rules.push_back(rule);
            rules[id] = move(link);
        }
    }

    if (part == 2)
    {
        auto link = make_unique<Link>();

        vector<size_t> rule = { 42 };
        link->rules.push_back(rule);
        rule = { 42, 8 };
        link->rules.push_back(rule);
        rules[8] = move(link);

        link = make_unique<Link>();
        rule = { 42, 31 };
        link->rules.push_back(rule);
        rule = { 42, 11, 31 };
        link->rules.push_back(rule);
        rules[11] = move(link);
    }

    int num_valid = 0;
    while (getline(in, line))
    {
        auto match_len = count_len(rules, 0, line);
        if (any_of(match_len.begin(), match_len.end(), [line_len = line.length()](auto len) { return len == line_len; }))
            ++num_valid;
    }
    cout << num_valid;
}
