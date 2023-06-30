#pragma once
#include <vector>
#include <iostream>

using namespace std;

class field {
	vector<vector<char>> cells;
	static const unsigned border_width = 1;

public:
	field(size_t width, size_t height) {
		width += 2 * border_width;
		height += 2 * border_width;

		cells.resize(width);

		for (auto& column : cells) {
			column.resize(height);
			std::fill(column.begin(), column.end(), false);
		}
	}

	void draw() {
		for (const auto& line : cells) {
			for (const auto& cell : line) {
				std::cout << cell;
			}
			std::cout << std::endl;
		}
	}
};