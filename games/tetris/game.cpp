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
		std::thread vt(&game::visualize, this);
		vt.detach();
		interaction();
		logic();

	}

}