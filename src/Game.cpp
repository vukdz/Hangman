// src/Game.cpp
#include "Game.hpp"

void clearScreen()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

Game::Game() : 
	m_str(""), 
	m_eStr(""), 
	m_mistakes(0), 
	m_guessedChars(),
	m_rndGen(std::chrono::high_resolution_clock::now().time_since_epoch().count())
{
	loadFromFile("assets/words.txt");
	resetGame();
}

std::string Game::rndWord()
{
	if (m_wordList.empty())
	{
		std::cerr << "Error: Word list is empty, please make sure assets/words.txt exists and is populated.\n";
		return "default";
	}

	std::uniform_int_distribution<> wordDist(0, static_cast<int>(m_wordList.size() - 1));

	return m_wordList[wordDist(m_rndGen)];
}

void Game::loadFromFile(const std::string& filename)
{
	std::ifstream file(filename);

	if (!file.is_open())
	{
		std::cerr << "Error: Could not open word list file: " << filename << std::endl;
		std::cerr << "Please make sure 'words.txt' is in the 'assets' folder." << std::endl;
		m_wordList = { "programming", "hangman", "defaultword" };
		return;
	}

	std::string word;

	while (std::getline(file, word))
	{
		std::transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return std::tolower(c); });
		word.erase(0, word.find_first_not_of(" \t\n\r\f\v"));
		word.erase(word.find_last_not_of(" \t\n\r\f\v") + 1);

		if (!word.empty())
		{
			m_wordList.push_back(word);
		}
	}

	file.close();

	if (m_wordList.empty())
	{
		std::cerr << "Warning: Word list file was empty or contained no valid words. Using default words.\n";
		m_wordList = { "programming", "hangman", "defaultword" };
	}
}

void Game::resetGame()
{
	m_str = rndWord();
	m_eStr.clear();

	for (char c : m_str)
	{
		m_eStr.push_back('-');
	}

	m_mistakes = 0;
	m_guessedChars.clear();
}

void Game::run()
{
	while (m_mistakes < hang.size() - 1 && m_eStr.find('-') != std::string::npos)
	{
		clearScreen();
		draw(m_mistakes);

		std::cout << "\nWord: " << m_eStr << std::endl;
		std::cout << "Guessed characters: ";

		for (char gc : m_guessedChars)
		{
			std::cout << gc << " ";
		}

		std::cout << "\nMistakes: " << m_mistakes << "/" << hang.size() - 1 << std::endl;

		char guess;

		std::cout << "\nEnter your guess (single letter): ";
		std::cin >> guess;

		guess = static_cast<char>(std::tolower(guess));

		if (!std::isalpha(static_cast<unsigned char>(guess)))
		{
			std::cout << "Invalid input! Please enter a letter from the alphabet.\n";
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}			

		if (std::find(m_guessedChars.begin(), m_guessedChars.end(), guess) != m_guessedChars.end())
		{
			std::cout << "You already guessed that letter! Try again.\n";
			std::this_thread::sleep_for(std::chrono::seconds(2));
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}

		m_guessedChars.push_back(guess);
		processGuess(guess);

		if (std::cin.peek() == '\n')
		{
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}		
	}

	clearScreen();
	draw(m_mistakes);

	std::cout << "\nWord: " << m_eStr << std::endl;

	if (m_eStr.find('-') == std::string::npos)
	{
		std::cout << "\n*** CONGRATULATIONS! You guessed the word: " << m_str << " ***" << std::endl;
	}
	else
	{
		std::cout << "\n*** GAME OVER! The word was: " << m_str << " ***" << std::endl;
	}

	std::cout << "\nPress Enter to play again or type 'exit' to quit...";

	std::string playAgain;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	std::getline(std::cin, playAgain);

	std::transform(playAgain.begin(), playAgain.end(), playAgain.begin(), [](unsigned char c) { return std::tolower(c); });
	
	if (playAgain == "exit")
	{
		//Do nothing, main returns program exit
	}
	else
	{
		resetGame();
		run();
	}
}

void Game::processGuess(char guess)
{
	bool found = false;

	for (size_t i = 0; i < m_str.length(); ++i)
	{
		if (std::tolower(m_str[i]) == guess)
		{
			m_eStr[i] = m_str[i];
			found = true;
		}
	}

	if (!found)
	{
		m_mistakes++;
	}
}

void Game::draw(int miss)
{
	std::cout << hang[m_mistakes] << std::endl;
}
