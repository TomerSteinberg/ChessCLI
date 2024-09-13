#ifndef INVOKER_H
#define INVOKER_H

#include "ICommand.h"
#include "Context.h"
#include <memory>

class Invoker
{
public:
	static Result invoke(Context& ctx, std::vector<std::unique_ptr<ICommand>>& cmds, const bool logResult=true);

};

#endif