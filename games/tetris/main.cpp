#include "tetris.h"
#include <memory>
using namespace kudzem_games;

int main() {

	auto game = std::make_unique<tetris>();
	game->launch();
}