#pragma once
#include <vector>
#include <iostream>
#include <algorithm>
#include "figure.h"
#include "field.h"
#include <memory>

using namespace std;

namespace kudzem_games {

	class board {
		static const unsigned border_width = 1;
		static const unsigned info_field_width = 10;
		size_t _board_width;
		size_t _board_height;

		vector<char> empty_line;

	public:

	    shared_ptr<field> field;

	    board(size_t field_width, size_t field_height) {

			_board_width = field_width + 2*border_width + info_field_width;
			_board_height = field_width + 2*field_height;

			field = std::make_shared<kudzem_games::field>(field_width, field_height);
		}

		void render()
		{
			field->render();
		}

		void show()
		{
			field->show();
		}

	};


}
