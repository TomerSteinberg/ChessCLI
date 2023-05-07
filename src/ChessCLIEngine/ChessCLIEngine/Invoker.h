#include "Command.h"
#include "Context.h"

#pragma once
class Invoker
{
public:
	static void invoke(Context& ctx, Command* cmd);

};

