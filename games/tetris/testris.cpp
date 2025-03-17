#include "tetris.h"
#include <iostream>
#include <thread>
#if defined _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <cmath>
bool kbhit() {
    struct termios oldt, newt;
    int oldf;
    char ch;
    bool oldf2;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    oldf2 = false;
    try {
        if (read(STDIN_FILENO, &ch, 1) == 1) {
            oldf2 = true;
        }
    } catch (...) {
        oldf2 = false; // In case of any exceptions
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    return oldf2;
}

char getch(void)
{
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    printf("%c\n", buf);
    return buf;
 }

#endif
#include <cstdlib>

using namespace std::chrono_literals;

namespace kudzem_games {

	const size_t number_of_tetris_figures = 7;
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
//                        std::cout << "Key press detected" << std::endl;
			key = getch();
//                        std::cout << "Key = " << int(key) << std::endl;
#if defined _WIN32
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
			else if (key == 27) {
				return tetris_event::PAUSE;
			}

#elif defined (__LINUX__) || defined(__gnu_linux__) || defined(__linux__)

                                switch (key) {
                                case 32:
                                        return tetris_event::PAUSE;
                                case 65:
                                        return tetris_event::ROTATE;
                                case 68:
                                        return tetris_event::MOVE_LEFT;
                                case 67:
                                        return tetris_event::MOVE_RIGHT;
                                case 66:
                                        return tetris_event::MOVE_DOWN;
                                }
#endif
                }
                return tetris_event::UNKNOWN_KEY_PRESSED;
	}

	void tetris::interaction() {
		std::cout << "interaction" << std::endl;
		while (!_stop) {

			if (kbhit() != 0) {
				//char c = getch();
				auto key_event = CheckKey();

				if (key_event != tetris_event::UNKNOWN_KEY_PRESSED &&
					(_paused && key_event == tetris_event::PAUSE ||
				     !_paused)) {
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

		while (!_stop) {

			if (!_paused) 
			{
				std::unique_lock lk(_event_queue_mx);
				_event_queue.push(tetris_event::MOVE_DOWN);
				_event_queue_cv.notify_one();
				lk.unlock();
			}

			std::this_thread::sleep_for(std::chrono::milliseconds(_timer_interval_ms));
		};
		return;
	}

	void tetris::logic() {
		std::cout << "logic" << std::endl;
		_current_figure = generate_figure();
		while (!_stop) {
			std::unique_lock lk(_event_queue_mx);
			_event_queue_cv.wait(lk, [this] { return _event_queue.empty() == false; });
			//std::cout << "New event" << std::endl;
			auto event = _event_queue.front();
			_event_queue.pop();

			std::unique_lock lk2(_current_figure_mx);

			if (event == tetris_event::PAUSE)
			{
				//std::cout << "PAUSE" << std::endl;
				pause();
			}
			else if (event == tetris_event::ROTATE)
			{
				//std::cout << "ROTATE" << std::endl;
				if (_current_figure)
				_current_figure->rotate();

				std::unique_lock lk(_render_done_mx);
					_render_done_cv.wait(lk, [] { return true; });
			}
			else if (event == tetris_event::MOVE_LEFT)
			{
				if (_current_figure)
				_current_figure->shift_left();
			}
			else if (event == tetris_event::MOVE_RIGHT)
			{
				if (_current_figure)
				_current_figure->shift_right();
			}
			else if (event == tetris_event::MOVE_DOWN && _current_figure)
			{
				if (_current_figure)
				_current_figure->shift_down();

				std::unique_lock lk(_render_done_mx);
				_render_done_cv.wait(lk, [this] { return true; });
			}
			else if (event == tetris_event::TOUCH_DOWN)
			{
				//std::cout << "Touch down" << std::endl;
				_current_figure = generate_figure();
				upgrade_level();
			}
			else if (event == tetris_event::BOARD_FULL)
			{
                print_stats();
				std::cout << "Game over" << std::endl;
				save_record();
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

	size_t 
	tetris::generate_figure_idx_seqly() {

		auto idx = _number_of_generated_obj % number_of_tetris_figures;
		return idx;

	}

	size_t
	tetris::generate_figure_idx_randomly() {

		auto idx = rand() % number_of_tetris_figures;
		return idx;
	}

	std::shared_ptr<figure>
	tetris::generate_figure() {

		auto idx = generate_figure_idx_randomly();

		++_number_of_generated_obj;
		switch (idx) {
		case 0:
			return make_shared<figure_i>();
		case 1:
			return make_shared<figure_t>();
		case 2:
			return make_shared<figure_o>();
		case 3:
			return make_shared<figure_s>();
		case 4:
			return make_shared<figure_z>();
		case 5:
			return make_shared<figure_j>();
		case 6:
			return make_shared<figure_l>();
		};
	}

	void tetris::visualize() {
		board = std::make_shared<kudzem_games::board>(std::dynamic_pointer_cast<tetris_cfg>(cfg)->get_board_width(),
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
			board->field->draw_figure(_current_figure);
			board->render();
			board->show();

			if (board->field->check_if_figure_touched(_current_figure)) {

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
				board->field->freeze(_current_figure);

				increase_score(board->field->exploid());

				// this is probably unsafe
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
			else lk.unlock();

			std::unique_lock lk3(_game_mtx);
			_current_figure_changed = false;
			print_stats();
			update_info_panel();

			_render_done_cv.notify_one();
		};

		return;
	}

	void tetris::print_stats() const {

		std::cout << "Record: " << _record << std::endl;
		std::cout << "Efficiency: " << _score / _number_of_generated_obj << std::endl;
		if (_paused) {
			std::cout << "Pause" << std::endl;
		}
	}

	void tetris::update_info_panel() {

		board->update_level(_level);
		board->update_score(_score);
		// board->update_lines(1);
		board->update_figures(_number_of_generated_obj);
	}


	void tetris::increase_score(size_t n_of_exploided_lines) {
		_score += 100 * (pow(2, n_of_exploided_lines) - 1);
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
