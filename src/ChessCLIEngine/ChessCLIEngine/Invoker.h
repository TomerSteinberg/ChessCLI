#include "ICommand.h"
#include "Context.h"
#include <memory>

#pragma once
class Invoker
{
public:
	static void invoke(Context& ctx, std::unique_ptr<ICommand>& cmd);

};

