#ifndef INVOKER_H
#define INVOKER_H

#include "ICommand.h"
#include "Context.h"
#include <memory>

class Invoker
{
public:
	static void invoke(Context& ctx, std::unique_ptr<ICommand>& cmd);

};

#endif