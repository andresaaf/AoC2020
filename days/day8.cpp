#include "days.hpp"

using namespace std;

namespace {
    class Operation
    {
    public:
        enum class Code
        {
            acc,
            jmp,
            nop
        };

        Operation(Code code, uint32_t arg) : code(code), arg(arg) {};

        Code code;
        uint32_t arg;
    };

    class GameConsole
    {
    public:
        void add_op(string op, string arg)
        {
            Operation::Code code = Operation::Code::nop;

            if (op == "acc"s)
                code = Operation::Code::acc;
            else if (op == "jmp"s)
                code = Operation::Code::jmp;

            code_.emplace_back(code, stoi(arg));
        }

        void execute()
        {
            Operation op = code_[pc_];
            switch (op.code)
            {
            case Operation::Code::acc:
                acc_ += op.arg;
                ++pc_;
                break;
            case Operation::Code::jmp:
                pc_ += op.arg;
                break;
            case Operation::Code::nop:
                ++pc_;
                break;
            }
        }

        void run()
        {
            vector<bool> visited(size(), false);
            while (true)
            {
                if (pc_ == size() || visited[pc_])
                    break;

                visited[pc_] = true;
                execute();
            }
        }

        void find_broken_instruction()
        {
            for (auto it = begin(code_); it != end(code_); ++it)
            {
                reset();

                Operation temp = *it;

                if (it->code == Operation::Code::jmp)
                    it->code = Operation::Code::nop;
                else if (it->code == Operation::Code::nop)
                    it->code = Operation::Code::jmp;
                else
                    continue;

                run();

                *it = temp;

                if (pc_ == size())
                    return;
            }
        }

        void reset()
        {
            pc_ = 0;
            acc_ = 0;
        }

        uint32_t pc() const { return pc_; }
        uint32_t accumulator() const { return acc_; }
        size_t size() const { return code_.size(); }

    private:
        vector<Operation> code_;
        uint32_t pc_ = 0;
        uint32_t acc_ = 0;
    };
};

void day8(istream& in, int part)
{
    GameConsole game;
    string op;
    string arg;

    while (in >> op >> arg)
    {
        game.add_op(op, arg);
    }

    if (part == 1)
    {
        game.run();
        cout << game.accumulator();
    }
    else
    {
        game.find_broken_instruction();
        cout << game.accumulator();
    }
}
