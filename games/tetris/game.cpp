#pragma once

#include "game.h"
#include <iostream>
#include <thread>
#include <future>

namespace kudzem_games {

	void game::configure() {
		std::cout << "configure game" << std::endl;
		cfg = init_cfg();
		cfg->apply_user_settings();
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
}