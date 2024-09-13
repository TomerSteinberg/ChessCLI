#ifndef ICOMMAND_H
#define ICOMMAND_H
#pragma once

#include "Context.h"
#include "Result.h"
#include <vector>
#include <string>


class ICommand
{
public:
	ICommand(std::vector<std::string> args);

	virtual Result execute(Context& ctx)=0;
protected:
	std::vector<std::string> m_args;

};

#endif
