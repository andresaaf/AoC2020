#include "days/days.hpp"

using namespace std;

int main()
{
    ifstream file{ "input/day6.txt" };

    istream& input = file;
    //istream& input = cin;

    int part = 2;

    day6(input, part);
}
