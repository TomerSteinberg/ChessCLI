#include "ICommand.h"
#include "InvalidCommandException.h"
#include "InvalidArgumentException.h"

#include <regex>
#include <unordered_map>

#define MOVE_REGEX "([abcdefgh][1-8]){2}([rbnq])?$"
#define PROMOTION_LENGTH 5

class MoveCommand : public ICommand
{
public:
	MoveCommand(std::vector<std::string> args);

	void execute(Context& ctx);
	static unsigned int maxArg;

};