#include "days.hpp"

using namespace std;

namespace
{
    enum class Op {
        Add,
        Mul
    };

    uint64_t reduce_expr(Op op, uint64_t lhs, uint64_t rhs)
    {
        switch (op)
        {
        case Op::Add:
            return lhs + rhs;
        case Op::Mul:
            return lhs * rhs;
        }
        throw runtime_error("err");
    }

    uint64_t reduce_string(string str, size_t& pos, bool plus_prio, uint64_t stack_val = 0)
    {
        Op op = Op::Add;
        bool has_lhs = stack_val > 0 ? true : false;
        uint64_t lhs = stack_val > 0 ? stack_val : 0;
        while (pos < str.length())
        {
            char token = str[pos++];
            switch (token)
            {
            case ' ':
                break;
            case '(':
            {
                uint64_t val = reduce_string(str, pos, plus_prio);
                if (!has_lhs)
                {
                    has_lhs = true;
                    lhs = val;
                }
                else
                {
                    if (plus_prio && op == Op::Mul)
                    {
                        return reduce_expr(op, lhs, reduce_string(str, pos, plus_prio, val));
                    }
                    else
                    {
                        lhs = reduce_expr(op, lhs, val);
                    }
                }
                break;
            }
            case ')':
                return lhs;
            case '+':
                op = Op::Add;
                break;
            case '*':
                op = Op::Mul;
                break;
            default:
                if (!has_lhs)
                {
                    has_lhs = true;
                    lhs = token - '0';
                }
                else
                {
                    if (plus_prio && op == Op::Mul)
                    {
                        return reduce_expr(op, lhs, reduce_string(str, --pos, plus_prio));
                    }
                    int64_t rhs = token - '0';
                    lhs = reduce_expr(op, lhs, rhs);
                }
                break;
            }
        }
        return lhs;
    }
}

void day18(istream& in, int part)
{
    string line;
    uint64_t sum = 0;
    while (getline(in, line))
    {
        size_t pos = 0;
        sum += reduce_string(line, pos, part == 2);
    }
    cout << sum;
}
