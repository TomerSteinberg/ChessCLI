#include "ExceededMaxArgumentsException.h"

ExceededMaxArgumentsException::ExceededMaxArgumentsException(int recieved, int allowed)
{
	this->errMsg = "Max Arguments Exceeded: Command was expecting " +
		std::to_string(allowed) +" Arguments but got "+
		std::to_string(recieved) + "\n";
}

const char* ExceededMaxArgumentsException::what() const noexcept
{
	return this->errMsg.c_str();
}
