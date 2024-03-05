#include "ContinueCommand.h"

ContinueCommand::ContinueCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int ContinueCommand::maxArg = 0;

void ContinueCommand::execute(Context& ctx)
{
	if (!ctx.getCurrGame())
	{
		throw InvalidCommandException(COMMAND_NAME);
	}
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now();
	ctx.getCurrGame()->playBest();
    auto t2 = high_resolution_clock::now();

    /* Getting number of milliseconds as an integer. */
    auto ms_int = duration_cast<milliseconds>(t2 - t1);

    /* Getting number of milliseconds as a double. */
    duration<double, std::milli> ms_double = t2 - t1;

    std::cout << "Execution time: " << ms_int.count() << "ms\n";
}
