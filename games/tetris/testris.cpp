#include "tetris.h"
#include <iostream>
#include <thread>

using namespace std::chrono_literals;

namespace kudzem_games {

	void Clear()
	{
#if defined _WIN32
		system("cls");
		//clrscr(); // including header file : conio.h
#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
		system("clear");
		//std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences 
#elif defined (__APPLE__)
		system("clear");
#endif
	}

	void tetris::visualize() {
		std::cout << "visualize" << std::endl;
		while (true) {
			kudzem_games::Clear();
			std::cout << "game goes on" << std::endl;
			std::this_thread::sleep_for(100ms);
		};

		return;
	}

	void tetris::interaction() {
		std::cout << "interaction" << std::endl;
		return;
	}

	void tetris::logic() {
		std::cout << "logic" << std::endl;
		return;
	}

	void tetris_cfg::set_default() {
		std::cout << "Set default game settings" << std::endl;
		_difficulty = 1;
		board_width = 10;
		board_height = 20;
		return;
	}

	void tetris_cfg::apply_user_settings() {
		std::cout << "Communication with user" << std::endl;
		std::cout << "Set game complexity(1..3): ";
		std::cin >> _difficulty;
		return;
	}


}