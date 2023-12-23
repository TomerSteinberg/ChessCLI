#include "IllegalMoveException.h"

IllegalMoveException::IllegalMoveException(std::string reason)
{
	this->errMsg = "Illegal move:" + reason + "\n";
}

IllegalMoveException::IllegalMoveException()
{
	this->errMsg = "Illegal move: Try reading the rules here -> https://en.wikipedia.org/wiki/Rules_of_chess \n";
}

const char* IllegalMoveException::what() const noexcept
{
	return this->errMsg.c_str();
}
