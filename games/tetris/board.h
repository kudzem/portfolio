#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "figure.h"
#include "field.h"
#include <memory>
#include <cstring>

using namespace std;

namespace kudzem_games {

	class info_panel {

		vector<vector<char>> all_cells;

		static const unsigned _width = 10;
		static const unsigned topic_top = 5;
		static const unsigned topic_gap = 3;
		size_t _height;

		friend class board;

		const char* topics[4] = { "Level:", "Score:", "Figures:", "Lines:"};

		const char empty_space_filler = space;

	public:

	    info_panel(size_t height) {

			_height = height;

			all_cells.resize(height);

			for (auto& column : all_cells) {
				column.resize(_width);
				std::fill(column.begin(), column.end(), empty_space_filler);
			}

			render_topics();
		}

		void render_topics()
		{
			size_t line_shift = topic_top;
			for (const char* topic : topics) {
				std::copy(topic, topic + strlen(topic), all_cells[line_shift].begin());
				line_shift += topic_gap;
			}
		}

		void set_next_figure(std::shared_ptr<figure> next_figure)
		{
			const auto& figure_cells = next_figure->get_cells();

			std::fill(all_cells[1].begin(), all_cells[1].end(), empty_space_filler);
			std::fill(all_cells[2].begin(), all_cells[2].end(), empty_space_filler);

			size_t line_number = 1;
			for (const auto& line : figure_cells) {
				std::copy(line.begin(), line.end(), all_cells[line_number].begin());
				line_number++;
			}
		}

		void set_level(unsigned level)
		{
			write_number_in_line(level, topic_top + 1);
		}

		void set_score(unsigned score)
		{
			write_number_in_line(score, topic_top + topic_gap + 1);
		}

		void set_figures(unsigned figures)
		{
			write_number_in_line(figures, topic_top + 2*topic_gap + 1);
		}

		void set_lines(unsigned lines)
		{
			write_number_in_line(lines, topic_top + 3*topic_gap + 1);
		}

		void write_number_in_line(unsigned num, size_t line_number)
		{
			std::fill(all_cells[line_number].begin(), all_cells[line_number].end(), empty_space_filler);
			auto str = std::to_string(num);
			std::copy(str.begin(), str.end(), all_cells[line_number].begin());
		}
	};

	class board {

		vector<vector<char>> all_cells;

		static const unsigned border_width = 2;
		static const unsigned info_panel_padding = 1;
		static const unsigned info_field_width = 10;
		size_t _board_width;
		size_t _board_height;

		size_t _field_width;
		size_t _field_height;

		vector<char> empty_line;

	public:

	    shared_ptr<field> field_ptr;
	    shared_ptr<info_panel> info_panel_ptr;

	    board(size_t field_width, size_t field_height) {

			_field_width = field_width;
			_field_height = field_height;

			_board_width = field_width + 2*border_width + info_field_width + info_panel_padding;
			_board_height = field_height + border_width;

			field_ptr = std::make_shared<kudzem_games::field>(field_width, field_height);
			info_panel_ptr = std::make_shared<kudzem_games::info_panel>(field_height);

			all_cells.resize(_board_height);

			for (auto& column : all_cells) {
				column.resize(_board_width);
			}

			render_border();
		}

		void get_field()
		{
			for (int l = 0; l < field_ptr->_board_height; ++l) {
				for (int c = 0; c < field_ptr->_board_width; ++c) {
					all_cells[l][c + border_width] = field_ptr->all_cells[l][c];
				}
			}
		}

		void get_info_panel()
		{
			for (int l = 0; l < info_panel_ptr->_height; ++l) {
				for (int c = 0; c < info_panel_ptr->_width; ++c) {
					all_cells[l][c + _field_width + 2*border_width + info_panel_padding] = info_panel_ptr->all_cells[l][c];
				}
			}
		}

		void update_level(unsigned level)
		{
            info_panel_ptr->set_level(level);
		}

		void update_score(unsigned level)
		{
            info_panel_ptr->set_score(level);
		}

		void update_figures(unsigned level)
		{
            info_panel_ptr->set_figures(level);
		}

		void update_next_figure(std::shared_ptr<figure> next_figure)
		{
            info_panel_ptr->set_next_figure(next_figure);
		}

		void update_lines(unsigned lines)
		{
            info_panel_ptr->set_lines(lines);
		}

		void render_border()
		{
			for (int l = 0; l < _field_height + 1; ++l) {
				all_cells[l][0] = '<';
				all_cells[l][1] = '!';
				all_cells[l][_field_width + border_width] = '!';
				all_cells[l][_field_width + border_width + 1] = '>';

				for (size_t i = 0; i < info_panel_padding; i++)
				{
					all_cells[l][_field_width + border_width + 2] = ' ';
				}
			}

			for (int c = 0; c < _field_width; ++c) {
                all_cells[_field_height][c + border_width] = '=';
			}

			all_cells[_field_height + 1][0] = space;
			all_cells[_field_height + 1][1] = space;

			for (int c = 0; c < _field_width/2; ++c) {
				all_cells[_field_height + 1][2*c + 2] = '\\';
				all_cells[_field_height + 1][2*c+1 + 2] = '/';
			}
		}

		void render()
		{
			field_ptr->render();
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
