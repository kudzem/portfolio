#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "figure.h"
#include "field.h"
#include <memory>

using namespace std;

namespace kudzem_games {

	class info_panel {

		vector<vector<char>> all_cells;

		static const unsigned _width = 10;
		size_t _height;

		friend class board;

		const char* topics[5] = { "Level:", "Score:", "Figures:", "Lines:", "Record:"};

		unsigned _level;
		unsigned _score;
		unsigned _lines;
		unsigned _figures;

	public:

	    info_panel(size_t height) {

			_height = height;

			all_cells.resize(height);

			for (auto& column : all_cells) {
				column.resize(_width);
				std::fill(column.begin(), column.end(), es);
			}

			render_topics();
		}

		void render_topics()
		{
			size_t line_shift = 1;
			for (const char* topic : topics) {
				std::copy(topic, topic + strlen(topic), all_cells[line_shift].begin());
				line_shift+=3;
			}
		}

		void set_level(unsigned level)
		{
			std::fill(all_cells[2].begin(), all_cells[2].end(), es);
			all_cells[2][1] = level%10 + 48;
		}

		void set_score(unsigned score)
		{
			std::fill(all_cells[5].begin(), all_cells[5].end(), es);
			auto score_str = std::to_string(score);
			std::copy(score_str.begin(), score_str.end(), all_cells[5].begin() + 1);
		}

		void set_figures(unsigned figures)
		{
			std::fill(all_cells[8].begin(), all_cells[8].end(), es);
			auto score_str = std::to_string(figures);
			std::copy(score_str.begin(), score_str.end(), all_cells[8].begin() + 1);
		}

	};

	class board {

		vector<vector<char>> all_cells;

		static const unsigned border_width = 1;
		static const unsigned info_field_width = 10;
		size_t _board_width;
		size_t _board_height;

		size_t _field_width;
		size_t _field_height;

		vector<char> empty_line;

	public:

	    shared_ptr<field> field;
		shared_ptr<info_panel> info_panel;

	    board(size_t field_width, size_t field_height) {

			_field_width = field_width;
			_field_height = field_height;

			_board_width = field_width + 2*border_width + info_field_width;
			_board_height = field_height + 2*border_width;

			field = std::make_shared<kudzem_games::field>(field_width, field_height);
			info_panel = std::make_shared<kudzem_games::info_panel>(field_height);

			all_cells.resize(_board_height);

			for (auto& column : all_cells) {
				column.resize(_board_width);
				std::fill(column.begin(), column.end(), es);
			}

			render_border();
		}

		void get_field()
		{
			for (int l = 0; l < field->_board_height; ++l) {
				for (int c = 0; c < field->_board_width; ++c) {
					all_cells[l][c] = field->all_cells[l][c];
				}
			}
		}

		void get_info_panel()
		{
			for (int l = 0; l < info_panel->_height; ++l) {
				for (int c = 0; c < info_panel->_width; ++c) {
					all_cells[l][c + _field_width + border_width] = info_panel->all_cells[l][c];
				}
			}
		}

		void update_level(unsigned level)
		{
            info_panel->set_level(level);
		}

		void update_score(unsigned level)
		{
            info_panel->set_score(level);
		}

		void update_figures(unsigned level)
		{
            info_panel->set_figures(level);
		}

		// board->update_level(_level);
		// board->update_score(_score);
		// board->update_lines(1);
		// board->update_figures(_number_of_generated_obj);

		void render_border()
		{
			for (int l = 0; l < _field_height + 1; ++l) {
				for (int c = 0; c < _field_width + 1; ++c) {
					if (l == _field_height || c == _field_width) {
					    all_cells[l][c] = '#';
					}
				}
			}
		}

		void render()
		{
			field->render();
			get_field();
			get_info_panel();
		}

		void show() {
			for (int l = 0; l < _board_height; ++l) {
				for (int c = 0; c < _board_width; ++c) {
					std::cout << all_cells[l][c];
				}
				std::cout << endl;
			}
		}

	};


}
