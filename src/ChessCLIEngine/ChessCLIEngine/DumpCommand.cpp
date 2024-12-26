#include "DumpCommand.h"

DumpCommand::DumpCommand(std::vector<std::string> args) : ICommand(args)
{
}

unsigned int DumpCommand::maxArg = 2;


Result DumpCommand::execute(Context& ctx)
{
	if(!ctx.getCurrGame())
	{	throw InvalidCommandException(COMMAND_NAME); }
	if(!this->matchRegexVector())
	{	throw InvalidArgumentException(); }

	std::string resultString = "";
	bool bin = std::find(this->m_args.begin(), this->m_args.end(), "-b") != this->m_args.end();
	bool hex = std::find(this->m_args.begin(), this->m_args.end(), "-h") != this->m_args.end();
	bool label = std::find(this->m_args.begin(), this->m_args.end(), "-l") != this->m_args.end();
	std::vector<std::string> labels = {
		"black pawn", "black knight", "black bishop", "black rook", "black queen", "black king",
		"white pawn", "white knight", "white bishop", "white rook", "white queen", "white king"
	};
	std::pair<std::string, std::string> metadataLabel = { "flags", "enpassant" };

	if(bin && hex)
	{
		throw InvalidArgumentException("Conflicting arguments: -b and -h");
	}
	if(hex)
	{	std::cout << std::hex; }

	u64 pieces[SIDES][NUMBER_OF_PIECES] = { 0 };
	std::pair<uint8_t, uint8_t> positionMetadata = ctx.getCurrGame()->dump(pieces);
	for (int i = 0; i < SIDES; i++)
	{
		for (int j = 0; j < NUMBER_OF_PIECES; j++)
		{
			if (label) { std::cout << labels[(i * 6) + j] << ": "; }
			if(bin)
			{
				std::cout << std::bitset<64>(pieces[i][j])<<std::endl;
				continue;
			}
			std::cout << pieces[i][j] << std::endl;
		}
	}
	if (label) { std::cout << metadataLabel.first << ": "; }
	if (bin)
	{
		std::cout << std::bitset<8>(positionMetadata.first) << std::endl;
		if (label) { std::cout << metadataLabel.second << ": "; }
		std::cout << std::bitset<8>(positionMetadata.second) << std::endl;
	}
	else
	{
		std::cout << (int)positionMetadata.first << std::endl;
		if (label) { std::cout << metadataLabel.second << ": "; }
		std::cout << (int)positionMetadata.second << std::endl;
	}

	std::cout << std::dec;
	return Result(false);
}


bool DumpCommand::matchRegexVector()
{
	for (auto it = this->m_args.begin(); it != this->m_args.end(); it++)
	{
		if (!std::regex_match(*it, std::regex(FLAGS_REGEX)))
		{
			return false;
		}
	}
	return true;
}
