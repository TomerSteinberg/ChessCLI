#pragma once
#include <string>
#include <fstream>
#include "json.hpp"

using nlohmann::json;


struct Result {
	
	Result(bool isError, bool isMessage=false, std::string message="");
	Result(const Result &otherResult);
	Result& operator=(const Result& otherResult);
	static void toJson(json& json, const Result& result);

	bool isError;
	bool isMessage;
	std::string message;
};