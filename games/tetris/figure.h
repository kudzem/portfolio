#pragma once

#include <cstdint>
#include <array>
#include <vector>
#include <memory>
#include <iostream>

namespace kudzem_games {

	enum class figure_types : uint8_t {
		J,
		I,
		L,
		O,
		T,
		S,
		Z
	};

typedef std::vector<std::vector<std::vector<char>>> figure_cells;

const figure_cells figure_t_matrix = { {{' ','x',' '}, {'x','x','x'}},
									   {{'x',' '}, {'x','x'}, {'x',' '}},
	                                   {{'x','x','x'}, {' ','x',' '}},
									   {{' ','x'}, {'x','x'}, {' ','x'}} };

const figure_cells figure_i_matrix = { {{'x','x','x','x'}},
									   {{'x'},{'x'},{'x'},{'x'}},
									   {{'x','x','x','x'}},
									   {{'x'},{'x'},{'x'},{'x'}} };

const figure_cells figure_o_matrix = { {{'x','x'},{'x','x'}},
									   {{'x','x'},{'x','x'}},
									   {{'x','x'},{'x','x'}},
									   {{'x','x'},{'x','x'}} };

const figure_cells figure_s_matrix = { {{' ','x','x'},{'x','x',' '}},
									   {{'x',' '},{'x','x'},{' ','x'}},
									   {{' ','x','x'},{'x','x',' '}},
									   {{'x',' '},{'x','x'},{' ','x'}} };

const figure_cells figure_z_matrix = { {{'x','x',' '},{' ','x','x'}},
									   {{' ','x'},{'x','x'},{'x',' '}},
									   {{'x','x',' '},{' ','x','x'}},
									   {{' ','x'},{'x','x'},{'x',' '}} };

const figure_cells figure_l_matrix = { {{' ',' ','x'},{'x','x','x'}},
									   {{'x',' '},{'x',' '},{'x','x'}},
									   {{'x','x','x'},{'x',' ',' '}},
									   {{'x','x'},{' ','x'},{' ','x'}} };

const figure_cells figure_j_matrix = { {{'x','x','x'},{' ',' ','x'}},
									   {{' ','x'},{' ','x'},{'x','x'}},
									   {{'x',' ',' '},{'x','x','x'}},
									   {{'x','x'},{'x',' '},{'x',' '}} };
class figure {
protected:
	size_t _pos_x = 0;
	size_t _pos_y = 0;
	size_t _angle = 0;
	size_t _width = 0;
	size_t _height = 0;

	const figure_cells& _mtx;

public:

	figure(const figure_cells& cells) : _pos_x(0), _pos_y(0), _angle(0), _mtx(cells) {
		set_pos(5, 0);
		update_figure_size();
	}

	void update_figure_size() {
		_height = _mtx[_angle].size();

		_width = 0;
		for (auto& row : _mtx[_angle]) {
			_width = std::max(_width, row.size());
		}
	}

	void update_figure_pos() {

		while (_pos_x + get_width() > 10) {
			--_pos_x;
		};
	}


	const std::vector<std::vector<char>>& get_cells() const { return _mtx[_angle]; }

	bool is_not_moved() const { return get_y() == 0; }
	size_t get_height() const {	return _height; }
	size_t get_width() const { return _width; }
	size_t get_x() const { return _pos_x; }
	size_t get_y() const { return _pos_y; }
	void rotate() { _angle = ++_angle % 4; update_figure_size(); update_figure_pos(); }
	void shift_left() { if (_pos_x > 0) --_pos_x; }
	void shift_right() { if(_pos_x + get_width() < 10) ++_pos_x; }
	void shift_down() { ++_pos_y; }
	void set_pos(size_t x, size_t y) { _pos_x = x; _pos_y = y; }
};

class figure_t : public figure {

public:
	figure_t() : figure(figure_t_matrix) {}
};

class figure_i : public figure {

public:
	figure_i() : figure(figure_i_matrix) {}
};

class figure_o : public figure {

public:
	figure_o() : figure(figure_o_matrix) {}
};

class figure_s : public figure {

public:
	figure_s() : figure(figure_s_matrix) {}
};

class figure_z : public figure {

public:
	figure_z() : figure(figure_z_matrix) {}
};

class figure_j : public figure {

public:
	figure_j() : figure(figure_j_matrix) {}
};

class figure_l : public figure {

public:
	figure_l() : figure(figure_l_matrix) {}
};




}