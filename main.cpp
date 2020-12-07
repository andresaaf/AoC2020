#include "days/days.hpp"

using namespace std;

int main()
{
    ifstream file{ "input/day7.txt" };

    istream& input = file;
    //istream& input = cin;

    int part = 2;

    day7(input, part);
}
