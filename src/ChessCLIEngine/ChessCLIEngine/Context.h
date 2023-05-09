#pragma once
class Context
{
public:
	Context();

	bool getInGame() const;
	void setInGame(const bool val);

private:
	bool m_inGame;

};

