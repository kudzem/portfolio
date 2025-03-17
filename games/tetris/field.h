#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "figure.h"

using namespace std;

namespace kudzem_games {

	class field {
		vector<vector<char>> hard_cells;
		vector<vector<char>> moving_cells;
		vector<vector<char>> all_cells;
		static const unsigned border_width = 0;
		size_t _board_width;
		size_t _board_height;

		vector<char> empty_line;

		friend class board;

	public:
		field(size_t width, size_t height) {

			_board_width = width + border_width;
			_board_height = height + border_width;

			empty_line.resize(_board_width);
			std::fill(empty_line.begin(), empty_line.end(), es);

			hard_cells.resize(_board_height);
			moving_cells.resize(_board_height);
			all_cells.resize(_board_height);

			for (auto& column : all_cells) {
				column.resize(_board_width);
				std::fill(column.begin(), column.end(), es);
			}

			for (auto& column : hard_cells) {
				column.resize(_board_width);
				std::fill(column.begin(), column.end(), es);
			}

			for (auto& column : moving_cells) {
				column.resize(_board_width);
				std::fill(column.begin(), column.end(), es);
			}
		}

		void draw_figure(shared_ptr<kudzem_games::figure> f) {

			for (int l = 0; l < _board_height; ++l) {
				for (int c = 0; c < _board_width; ++c) {
					moving_cells[l][c] = es;
				}
			}

			for (int l = 0; l < f->get_height(); ++l) {
				for (int c = 0; c < f->get_width(); ++c) {
					if (f->get_cells()[l][c] == es) continue;
					//std::cout << l << "/" << c << std::endl;
					//std::cout << "X=" << l + f->get_x() << std::endl;
					//std::cout << l + f->get_y() << "/" << c + f->get_x() << std::endl;
					moving_cells[l+f->get_y()][c+f->get_x()] = f->get_cells()[l][c];
				}
			}
		}

		bool check_if_figure_touched(shared_ptr<kudzem_games::figure> f)
		{
			for (size_t c = 0; c < f->get_width(); ++c) {
				for (int l = f->get_height() - 1; l >= 0; --l) {
					//std::cout << l << "/" << c << std::endl;
					if (f->get_cells()[l][c] != es) {
						if (l + f->get_y() == _board_height - 1) return true;
						if (hard_cells[1 + l + f->get_y()][c + f->get_x()] != es) return true;
					}
				}
			}
			return false;
		}

		void freeze(shared_ptr<kudzem_games::figure> f)
		{
			for (int l = 0; l < f->get_height(); ++l) {
				for (int c = 0; c < f->get_width(); ++c) {
					if (f->get_cells()[l][c] != es) {
						//std::cout << l << "/" << c << std::endl;
						//std::cout << "X=" << l + f->get_x() << std::endl;
						hard_cells[l + f->get_y()][c + f->get_x()] = f->get_cells()[l][c];
					}
				}
			}
		}

		size_t exploid()
		{
			std::vector<size_t> lines_to_exploid;

			for (int l = _board_height - 1; l >= 0; --l) {
				int cell_count = 0;
				for (int c = 0; c < _board_width; ++c) {
					if (hard_cells[l][c] == es) break;
					if (++cell_count == _board_width)
						lines_to_exploid.push_back(l);
				}
			}

			if (lines_to_exploid.empty()) return 0;

			vector<vector<char>> hard_cells_new;
			hard_cells_new.resize(_board_height);

			for (int i = 0; i < lines_to_exploid.size(); ++i) {
				std::cout << "Added a new line" << std::endl;
				hard_cells_new[i] = empty_line;
			}

			for (int l = _board_height - 1, l_new = _board_height - 1; l >= 0; --l) {
				if (std::find(lines_to_exploid.begin(), lines_to_exploid.end(), l) == lines_to_exploid.end()) {
					std::cout << "Copy line " << l << std::endl;
					hard_cells_new[l_new--] = hard_cells[l];
				}
			}

			hard_cells = hard_cells_new;


			return lines_to_exploid.size();
		}

		void flush_space() {
			for (int l = 0; l < _board_height; ++l) {
				for (int c = 0; c < _board_width; ++c) {
					all_cells[l][c] = es;
				}
			}
		}

		void clean() {
			for (int l = 0; l < _board_height; ++l) {
				for (int c = 0; c < _board_width; ++c) {
					all_cells[l][c] = es;
				}
			}
		}

        void merge_moving_and_hard_cells() {
			for (int l = 0; l < _board_height; ++l) {
				for (int c = 0; c < _board_width; ++c) {
					if (moving_cells[l][c] != es) {
						all_cells[l][c] = moving_cells[l][c];
					}
					else {
						all_cells[l][c] = hard_cells[l][c];
					}
				}
			}
		}

		void render() {

			clean();
			merge_moving_and_hard_cells();
		}

		void show() {
			for (int l = 0; l < _board_height + 1; ++l) {
				for (int c = 0; c < _board_width + 1; ++c) {
					if (l == _board_height || c == _board_width) {
					    std:cout << "#";
					}
					else {
						std::cout << all_cells[l][c];
					}
				}
				std::cout << endl;
			}
		}

	};


}
