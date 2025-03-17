#pragma once

#include "game.h"
#include <iostream>
#include <thread>
#include <future>
#include <fstream>
#include <string.h>
#include <filesystem>


namespace kudzem_games {

	void game::configure() {
//                keypad(win, TRUE);
		std::cout << "configure game" << std::endl;
		cfg = init_cfg();
		cfg->apply_user_settings();
		read_record();
	}

	void game::launch() {
		std::cout << "Launch game" << std::endl;
		configure();
		std::thread timer_thread(&game::timer, this, 1000);
		timer_thread.detach();

		std::thread logic_thread(&game::logic, this);
		logic_thread.detach();

		std::thread visual_thread(&game::visualize, this);
		visual_thread.detach();

		interaction();
	}

	void game::upgrade_level()
	{
		std::unique_lock lk(_game_mtx);
		if (level_to_be_upgraded() && _timer_interval_ms > 100)
		{
			_timer_interval_ms -= 100;
			++_level;
		}

		change_speed();
	}

	void game::change_speed()
	{
        if (level2tmo.find(_level) != level2tmo.end())
		{
            _timer_interval_ms = level2tmo.at(_level);
			return;
		}

		if (_level >= 30) _timer_interval_ms = level2tmo.at(30);
		else if (_level >= 20) _timer_interval_ms = level2tmo.at(20);
		else if (_level >= 15) _timer_interval_ms = level2tmo.at(15);
		else _timer_interval_ms = level2tmo.at(10);
	}

	void game::read_record()
	{
		std::filesystem::path record_file_path = std::filesystem::current_path() / "record.txt";
		std::cout << record_file_path.string() << std::endl;
		std::ifstream record_file(record_file_path.string());

		if (!record_file.is_open())
		{
			std::cout << "File not opened: " << strerror(errno) << std::endl;
			return;
		}

		record_file >> _record;
		record_file.close();
	}

	void game::save_record()
	{
		if (_score <= _record) return;

		std::filesystem::path record_file_path = std::filesystem::current_path() / "record.txt";
		std::cout << record_file_path.string() << std::endl;
		std::fstream record_file(record_file_path.string(), std::ios::out);

		if (!record_file.is_open())
		{
			std::cout << "File not opened: " << strerror(errno) << std::endl;
			return;
		}
		
		record_file << _score;
		record_file.close();
	}
}
