#pragma once

#include <string>

class Player
{
private:
	std::string m_name;
	std::string m_consolePref;  //add player class member variable for storing the players console preference.

public:
	Player()
	{
	}

	void SetName(const std::string& name)
	{
		m_name = name;
	}
	//add setter function for Player class member variable m_consolePref
	void SetConsolePref(const std::string& console)
	{
		m_consolePref = console;
	}

	const std::string& GetName() const
	{
		return m_name;
	}
	//add getter function to return the value of the Player class member variable m_consolePref
	const std::string& GetConsolePref() const
	{
		return m_consolePref;
	}
};