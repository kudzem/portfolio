#pragma once

#include "game.h"

namespace kudzem_games {

	class tetris_cfg : public game_config {
		size_t board_width, board_height;
		int _difficulty;

	private:
		void set_default();

	public:
		virtual void apply_user_settings() override;
		tetris_cfg() { set_default(); }
	};

	class tetris : public game {

	public:
		virtual std::shared_ptr<game_config> init_cfg() override { return std::make_shared<tetris_cfg>(); }
		virtual void visualize() override;
		virtual void interaction() override;
		virtual void logic() override;
	};

}