#include "days/days.hpp"

using namespace std;

int main()
{
    ifstream file{ "input/day4.txt" };

    istream& input = file;
    //istream& input = cin;

    int part = 2;

    day4(input, part);
}
