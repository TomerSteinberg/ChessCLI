#include "PerftCommand.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::milliseconds;


PerftCommand::PerftCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int PerftCommand::maxArg = 2;

void PerftCommand::execute(Context& ctx)
{
    if (m_args.size() < 1)
    {
        throw InvalidArgumentException();
    }
    if (!std::regex_match(this->m_args[0], std::regex(INTEGER_REGEX)))
    {
        throw InvalidArgumentException();
    }
    if ((std::stoi(m_args[0])) <= 0)
    {
        throw InvalidArgumentException();
    }
    if (m_args.size() > 1 && m_args[1] != "-r")
    {
        throw InvalidArgumentException();
    }

    if (m_args.size() > 1)
    {
        for (int i = 1; i < std::stoi(m_args[0]) + 1; i++)
        {
            auto t1 = high_resolution_clock::now();
            int nodes = ctx.getCurrGame()->perft(i - 1);
            auto t2 = high_resolution_clock::now();
            auto ms_int = duration_cast<milliseconds>(t2 - t1);

            std::cout << "Depth: " << i << "\t";
            std::cout << "Nodes: " << nodes << "\t";
            std::cout << "Time: " << ms_int.count() << "ms" << "\t";
            std::cout << "nps: " << (nodes / ms_int.count()) * 1000 << "\t" << std::endl;
        }
    }
    else
    {
        auto t1 = high_resolution_clock::now();
        int nodes = ctx.getCurrGame()->perft(std::stoi(m_args[0]) - 1);
        auto t2 = high_resolution_clock::now();

        auto ms_int = duration_cast<milliseconds>(t2 - t1);
        std::cout << "Nodes: " << nodes << "\t";
        std::cout << "Time: " << ms_int.count() << "ms" << "\t";
        std::cout << "nps: " << (nodes / ms_int.count()) * 1000 << "\t" << std::endl;
    }
}
