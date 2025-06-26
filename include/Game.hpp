// include/Game.hpp
#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <algorithm>
#include <thread>
#include <chrono>
#include <random>
#include <fstream>

#include "Drawings.hpp"

class Game
{
public:
	Game();
	void run();

private:
	void draw(int miss);
	void processGuess(char guess);
	void resetGame();

	std::string rndWord();
	void loadFromFile(const std::string& filename);

	std::string m_str;		// Word to guess
	std::string m_eStr;		// Empty string, replace all characters from m_str with a hyphen 

	int m_mistakes;
	std::vector<char> m_guessedChars;

	std::vector<std::string> m_wordList;
	std::mt19937 m_rndGen;
};

#endif // GAME_HPP