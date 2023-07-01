#include "tetris.h"
#include <iostream>
#include <thread>
#include <conio.h>

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
	;

	tetris_event CheckKey(void) {
		int key;
		if (kbhit()) {
			key = getch();
			if (key == 224) {
				do {
					key = getch();
				} while (key == 224);

				switch (key) {
				case 72:
					return tetris_event::ROTATE;
				case 75:
					return tetris_event::MOVE_LEFT;
				case 77:
					return tetris_event::MOVE_RIGHT;
				case 80:
					return tetris_event::MOVE_DOWN;
				}
			}
		}
		return tetris_event::UNKNOWN_KEY_PRESSED;
	}

	void tetris::interaction() {
		std::cout << "interaction" << std::endl;
		while (!_stop) {

			if (kbhit() != 0) {
				//char c = getch();
				auto key_event = CheckKey();

				if (key_event != tetris_event::UNKNOWN_KEY_PRESSED) {
					std::unique_lock lk(_event_queue_mx);
					_event_queue.push(key_event);
					//std::cout << "Send event=" << c << std::endl;
					_event_queue_cv.notify_one();
				}
				//std::this_thread::sleep_for(10ms);
				//std::cout << "Check keyboard" << std::endl;
			}
		}
	}

	void tetris::timer(int start_value) {
		std::cout << "Timer" << std::endl;
		size_t counter = 0;
		const size_t level_upgrade_counter = 10;
		while (!_stop) {
			std::unique_lock lk(_event_queue_mx);
			_event_queue.push(tetris_event::MOVE_DOWN);
			_event_queue_cv.notify_one();
			lk.unlock();
			std::this_thread::sleep_for(1000ms);
		};
		return;
	}

	void tetris::logic() {
		std::cout << "logic" << std::endl;
		_current_figure = make_shared<figure_t>();
		_current_figure->set_pos(5, 0);
		while (!_stop) {
			std::unique_lock lk(_event_queue_mx);
			_event_queue_cv.wait(lk, [this] { return _event_queue.empty() == false; });
			//std::cout << "New event" << std::endl;
			auto event = _event_queue.front();
			_event_queue.pop();

			std::unique_lock lk2(_current_figure_mx);

			if (event == tetris_event::ROTATE)
			{
				std::cout << "ROTATE" << std::endl;
				_current_figure->rotate();
			}
			else if (event == tetris_event::MOVE_LEFT)
			{
				_current_figure->shift_left();
			}
			else if (event == tetris_event::MOVE_RIGHT)
			{
				_current_figure->shift_right();
			}
			else if (event == tetris_event::MOVE_DOWN && _current_figure)
			{
				//std::cout << "Shift figure down" <<std::endl;
				_current_figure->shift_down();
			}
			else if (event == tetris_event::TOUCH_DOWN)
			{
				//std::cout << "Shift figure down" << std::endl;
				_current_figure = make_shared<figure_t>();
				_current_figure->set_pos(5, 0);
			}
			else if (event == tetris_event::BOARD_FULL)
			{
				std::cout << "Game over" << std::endl;
				stop();
				continue;
			}
			//std::cout << "Notify update" << std::endl;
			this->_current_figure_changed = true;
			_current_figure_cv.notify_one();
			lk2.unlock();
		};

		return;
	}

	void tetris::visualize() {
		board = std::make_shared<field>(std::dynamic_pointer_cast<tetris_cfg>(cfg)->get_board_width(),
			std::dynamic_pointer_cast<tetris_cfg>(cfg)->get_board_height());
		std::cout << "visualize" << std::endl;

		while (!_stop) {
			std::unique_lock lk(_current_figure_mx);
			_current_figure_cv.wait(lk, [this] { return _current_figure_changed == true; });
			kudzem_games::Clear();
			if (_current_figure == nullptr) {
				//std::cout << "Figure is empty" << std::endl;
				lk.unlock();
				continue;
			}
			board->draw_figure(_current_figure);
			board->render_sceen();

			if (board->check_if_figure_touched(_current_figure)) {

				if (_current_figure->is_not_moved()) {
					lk.unlock();
					std::unique_lock lk2(_event_queue_mx);
					//std::cout << "Touch happened lock" << std::endl;
					_event_queue.push(tetris_event::BOARD_FULL);
					_event_queue_cv.notify_one();
					lk2.unlock();
					this->_current_figure_changed = false;
					return;
				}
				//std::cout << "Touch happened" << std::endl;
				board->freeze(_current_figure);
				board->exploid();
				_current_figure = nullptr;
				lk.unlock();
				std::unique_lock lk2(_event_queue_mx);
				//std::cout << "Touch happened lock" << std::endl;
				while (!_event_queue.empty()) {
					_event_queue.pop();
				}
				_event_queue.push(tetris_event::TOUCH_DOWN);
				_event_queue_cv.notify_one();
				lk2.unlock();
				//std::cout << "Touch happened unlock" << std::endl;
			}
			this->_current_figure_changed = false;
		};

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
		//std::cin >> _difficulty;
		return;
	}


}