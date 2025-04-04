#pragma once

#include "game.h"
#include "board.h"
#include <memory>
#include <mutex>
#include <queue>
#include <condition_variable>

namespace kudzem_games {

	enum class tetris_event {
		MOVE_DOWN,
		MOVE_LEFT,
		MOVE_RIGHT,
		ROTATE,
		TOUCH_DOWN,
		BOARD_FULL,
		PAUSE,
		UNKNOWN_KEY_PRESSED
	};

	class tetris_cfg : public game_config {
		size_t board_width, board_height;
		int _difficulty;

	private:
		void set_default();

	public:
		size_t get_board_width() const { return board_width; }
		size_t get_board_height() const { return board_height; }
		virtual void apply_user_settings() override;
		tetris_cfg() { 
			set_default();
		}
	};

	class tetris : public game {

	private:
		shared_ptr<board> board_ptr;
		std::queue<tetris_event> _event_queue;
		std::mutex _event_queue_mx;
		std::condition_variable _event_queue_cv;

		std::mutex _render_done_mx;
		std::condition_variable _render_done_cv;

		std::shared_ptr<figure> _current_figure;
		std::shared_ptr<figure> _next_figure;
		std::mutex _current_figure_mx;
		std::condition_variable _current_figure_cv;
		bool _current_figure_changed = false;

		size_t n_of_clear = 0;
		size_t n_of_clear_in_level = 0;
		size_t n_of_tetris_clear = 0;

	public:
		virtual std::shared_ptr<game_config> init_cfg() override { return std::make_shared<tetris_cfg>(); }
		virtual void visualize() override;
		virtual void interaction() override;
		virtual void logic() override;
		virtual void timer(int start_value) override;
		std::shared_ptr<figure> generate_figure();
		size_t generate_figure_idx_randomly();
		size_t generate_figure_idx_seqly();
		void increase_score(size_t n_of_exploided_lines);
		void print_stats() const;
		void update_info_panel();

		bool level_to_be_upgraded() override;
	};

}
