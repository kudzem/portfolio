#include <fstream>
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

void draw_game(char **field, unsigned rows, unsigned cols) {
  for (unsigned i = 0; i < rows; ++i) {
    for (unsigned j = 0; j < cols; ++j) {
      std::cout << field[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

bool load_game(const char *config_file_name,
               char ***field,
               unsigned &rows,
               unsigned &cols) {
  
  std::ifstream fin(config_file_name);

  if (!fin.is_open()) {
    std::cout << "Can't open config file" << std::endl;
    return false;
  }

  std::cout << "File opened" << std::endl;
  fin >> rows >> cols;

  *field = new char *[rows];
  for (unsigned i = 0; i < rows; ++i) {
    (*field)[i] = new char[cols];
    for (unsigned j = 0; j < cols; ++j) {
      (*field)[i][j] = '-';
    }
  }

  int row = 0, col = 0;
  while (fin >> row >> col) {
    (*field)[row][col] = '*';
  };

  fin.close();

  return true;
}

unsigned count_cell_neighours(unsigned row,
                         unsigned col,
                         char **field,
                         unsigned rows,
                         unsigned cols) 
{
  unsigned neighbours = 0;

  unsigned neighborhood_row_min = std::max(0, (int)row - 1);
  unsigned neighborhood_row_max = std::min(rows - 1, row + 1);
  unsigned neighborhood_col_min = std::max(0, (int)col - 1);
  unsigned neighborhood_col_max = std::min(cols - 1, col + 1);

    for (unsigned i = neighborhood_row_min; i <= neighborhood_row_max; ++i) {
    for (unsigned j = neighborhood_col_min; j <= neighborhood_col_max; ++j) {
      if (field[i][j] == '*')
        ++neighbours;
    }
  }

  if (field[row][col] == '*') {
    --neighbours;
  }
  
  return neighbours;
}

unsigned count_alive_cells(char **field,
                           unsigned rows,
                           unsigned cols)
{
  unsigned alive_cells = 0;
    for (unsigned i = 0; i < rows; ++i) {
    for (unsigned j = 0; j < cols; ++j) {
      if (field[i][j] == '*')
        ++alive_cells;
    }
  }

  return alive_cells;
}

void get_next_generation(char **field, char **field_next, unsigned rows,
                         unsigned cols) {
  for (unsigned i = 0; i < rows; ++i) {
    for (unsigned j = 0; j < cols; ++j) {
      unsigned neigh = count_cell_neighours(i,
                                            j,
                                            field,
                                            rows,
                                            cols);

      if (field[i][j] == '-') {
        if (neigh == 3) {
          field_next[i][j] = '*';
        }
        else {
          field_next[i][j] = field[i][j];
        }
      }
      else if (field[i][j] == '*') {
        if (neigh < 2 || neigh > 3) {
          field_next[i][j] = '-';
        }
        else {
          field_next[i][j] = field[i][j];
        }
      }
    }
  }
}

bool check_fields_equal(char **field, 
                        char **other, 
                        unsigned rows,
                        unsigned cols) {
  for (unsigned i = 0; i < rows; ++i) {
    for (unsigned j = 0; j < cols; ++j) {
      if (field[i][j] != other[i][j])
        return false;
    }
  }
  return true;
}

void free_allocated_memory(char** field, unsigned rows) {
  for (unsigned i = 0; i < rows; ++i) {
    delete [] field[i];
  }
  
  delete[] field;
}

int main() {
  std::cout << "Start of game" << std::endl;

  char **field;
  unsigned rows = 0;
  unsigned cols = 0;

//  if (false == load_game("generation_3_death.cfg", &field, rows, cols)) {
  if (false == load_game("../../../generation_14_stagnation.cfg", &field, rows, cols)) {
    return 1;
  }

  std::cout << "Game loaded" << std::endl;

  char **field_next = new char *[rows];
  for (unsigned i = 0; i < rows; ++i) {
    field_next[i] = new char[cols];
    for(unsigned j = 0; j < cols; ++j) {
      field_next[i][j] = '-';
    }
  }

  while (true) {
    static unsigned age = 1;

#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
    draw_game(field, rows, cols);

    unsigned alive_cells = count_alive_cells(field, rows, cols);
    std::cout << "Generation " << age << ". Alive cells " << alive_cells << std::endl;

    if (alive_cells == 0) {
      std::cout << "All cells are dead. Game over" << std::endl;
      free_allocated_memory(field, rows);
      free_allocated_memory(field_next, rows);
      return 0;
    }
    
    if (check_fields_equal(field, field_next, rows, cols)) {
      std::cout << "The world has stagnated. Game over" << std::endl;
      free_allocated_memory(field, rows);
      free_allocated_memory(field_next, rows);
      return 0;
    }

    //sleep(1);
    std::this_thread::sleep_for(1000ms);
    
    get_next_generation(field, field_next, rows, cols);
    std::swap(field, field_next);
    
    ++age;
  }

  free_allocated_memory(field, rows);
  free_allocated_memory(field_next, rows);
}