#pragma once
#include <vector>
#include <iostream>

#include "figure.h"

using namespace std;

namespace kudzem_games {

	class field {
		vector<vector<char>> hard_cells;
		vector<vector<char>> moving_cells;
		static const unsigned border_width = 0;
		size_t _board_width;
		size_t _board_height;

	public:
		field(size_t width, size_t height) {

			_board_width = width + 2 * border_width;
			_board_height = height + 2 * border_width;

			hard_cells.resize(_board_height);
			moving_cells.resize(_board_height);

			for (auto& column : hard_cells) {
				column.resize(_board_width);
				std::fill(column.begin(), column.end(), false);
			}

			for (auto& column : moving_cells) {
				column.resize(_board_width);
				std::fill(column.begin(), column.end(), false);
			}
		}

		void draw_hard_cells() {
			for (const auto& line : hard_cells) {
				for (const auto& cell : line) {
					std::cout << cell;
				}
				std::cout << std::endl;
			}
		}

		void draw_figure(shared_ptr<kudzem_games::figure> f) {

			for (int l = 0; l < f->get_size(); ++l) {
				for (int c = 0; c < f->get_size(); ++c) {
					//std::cout << l << "/" << c << std::endl;
					//std::cout << "X=" << l + f->get_x() << std::endl;
					moving_cells[l+f->get_y()][c+f->get_x()] = (*(f->_mtx))[0][l][c];
				}
			}
		}

		void render_sceen() {
			for (int l = 0; l < _board_height; ++l) {
				for (int c = 0; c < _board_width; ++c) {
					if (moving_cells[l][c]) {
						std::cout << moving_cells[l][c];
					}
					else if (hard_cells[l][c]) {
						std::cout << hard_cells[l][c];
					}
					else
					{
						std::cout << ' ';
					}
				}
				std::cout << endl;
			}
		}

	};


}