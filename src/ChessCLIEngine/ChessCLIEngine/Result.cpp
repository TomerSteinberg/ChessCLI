#include "Result.h"

Result::Result(bool isError, bool isMessage, std::string message) :
	isError(isError), isMessage(isMessage), message(message)
{
}

Result::Result(const Result& otherResult) :
	isError(otherResult.isError), isMessage(otherResult.isMessage), message(otherResult.message)
{
}

Result& Result::operator=(const Result& otherResult)
{
	this->isError = otherResult.isError;
	this->isMessage = otherResult.isMessage;
	this->message = otherResult.message;

	return *this;
}

void Result::toJson(json& json, const Result& result)
{
	json["isError"] = result.isError;
	json["isMessage"] = result.isMessage;
	json["message"] = result.message;
}
