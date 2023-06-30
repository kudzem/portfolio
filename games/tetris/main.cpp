#include "tetris.h"
#include <memory>
#include <iostream>
#include <thread>

using namespace kudzem_games;
using namespace std::chrono_literals;

int main() {

	auto game = std::make_unique<tetris>();
	game->launch();
	std::this_thread::sleep_for(4s);
	game->stop();
}