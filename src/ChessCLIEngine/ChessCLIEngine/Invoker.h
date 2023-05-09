#include "ICommand.h"
#include "Context.h"

#pragma once
class Invoker
{
public:
	static void invoke(Context& ctx, ICommand* cmd);

};

