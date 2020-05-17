#include <iostream>
#include <math.h>
#include <vector>
#include <algorithm>
#include <random>

#include "structures.h"

// constructor
minesweeper_gameboard::minesweeper_gameboard(int side_length, std::string difficulty) {

    _side_length = side_length;
    _gameboard.resize(_side_length);
    
    for (int i = 0; i < _side_length; i++) {

        _gameboard[i].resize(_side_length);

    }

    _difficulty = difficulty;

    minesweeper_gameboard::print_difficulty();

    _num_tiles = pow(_side_length, 2);

    std::cout << "num_tiles = " << _num_tiles << std::endl;

    minesweeper_gameboard::calc_num_mines();
    _num_empty_tiles = _num_tiles - _num_mines;
    _num_visited = 0;
    _num_marked = 0;

    minesweeper_gameboard::populate_board_with_mines();

}

// print functions for debugging
void minesweeper_gameboard::print_side_length() {

    std::cout << _side_length << std::endl;

}

void minesweeper_gameboard::print_difficulty() {

    std::cout << _difficulty << std::endl;

}

void minesweeper_gameboard::print_num_mines() {

    std::cout << _num_mines << "\n";

}

void minesweeper_gameboard::show_mine_board() {

    for (int i = 0; i < _side_length; i++) {
        for (int j = 0; j < _side_length; j++) {

            _gameboard[i][j].print_mine_status();

        }
        std::cout << std::endl;
    }

}

// print whole board for user / debugging
void minesweeper_gameboard::show_text_board() {

    for (int i = 0; i < _side_length; i ++) {
        for (int j = 0; j < _side_length; j++) {

            if (_gameboard[i][j].get_visited()) {
                
                if (_gameboard[i][j].get_mine()) {
                    std::cout << "* ";
                } else {
                    if (_gameboard[i][j].get_num_neighbor_mines() == 0) {
                        std::cout << "  ";
                    } else {
                        std::cout << _gameboard[i][j].get_num_neighbor_mines() << " ";
                    }
                }
            } else {
                if (_gameboard[i][j].get_marked()) {
                    std::cout << "M ";
                } else {
                    std::cout << "? ";
                }
            }
        };

        std::cout << std::endl;
    };

    std::cout << std::endl;
}

// board setup functions
void minesweeper_gameboard::calc_num_mines() {

    if (_difficulty == "Easy") {

        _num_mines = (int)float(_num_tiles / 12);

    } else if (_difficulty == "Intermediate") {

        _num_mines = (int)float(_num_tiles / 10);

    } else if (_difficulty == "Hard") {

        _num_mines = (int)float(_num_tiles / 8);

    }

}

void minesweeper_gameboard::populate_board_with_mines() {

    int mine_row, mine_col;
    std::random_device myRandomDevice;
    unsigned seed = myRandomDevice();
    std::default_random_engine myRandomEngine(seed);
    std::vector<int> flattened_indices;

    for (int i = 0; i < _num_tiles; i++) {

        flattened_indices.push_back(i);

    }

    std::shuffle(std::begin(flattened_indices), std::end(flattened_indices), myRandomEngine);

    for (int i = 0; i < _num_mines; i++) {

        mine_row = flattened_indices[i] % _side_length;
        mine_col = flattened_indices[i] / _side_length;

        std::cout << mine_row << "," << mine_col << std::endl;

        _gameboard[mine_row][mine_col].set_mine();

    }   

}

void minesweeper_gameboard::visit_tile(int x, int y) {

    _num_visited += 1;
    _gameboard[x][y].visit();

}

void minesweeper_gameboard::toggle_mark_tile(int x, int y) {

    if (!_gameboard[x][y].get_visited()) {
        if (_num_marked < _num_mines) {
            if (!_gameboard[x][y].get_marked()) {
                _num_marked += 1;
                _gameboard[x][y].mark();
            } else {
                _num_marked -= 1;
                _gameboard[x][y].unmark();
            }
        } else {
            std::cout << "Sorry, can't mark any more mines." << std::endl;
        }
    } else {
        std::cout << "Sorry, can't mark a visited square." << std::endl;
    }
}

bool minesweeper_gameboard::visited_all_empty_tiles() {

    if (_num_visited < _num_empty_tiles) {
        return(false);
    } else {
        return(true);
    };

}

void minesweeper_gameboard::step(std::queue<std::vector<int>> ordered_pair_queue) {

        int x, y;
        std::string turn_type;
        std::vector<int> op;

        std::cout << "Turn type? < click (c) > or < mark (m) > :" << std::endl;
        std::cin >> turn_type;

        /* this looks flipped, but recall that c++'s indexing flips x,y and i,j */
        std::cout << "Please enter x-coord (gotta be an int): " << std::endl;
        std::cin >> y;

        std::cout << "Please enter y-coord (gotta be an int): " << std::endl;
        std::cin >> x;
        
        if (turn_type == "m") {

            toggle_mark_tile(x, y);
            show_text_board();

        } else if (turn_type == "c") {        

            if (_gameboard[x][y].get_marked()) {
                std::cout << "Can't click a marked square!" << std::endl;
            } else {
                if (_gameboard[x][y].get_mine()) {

                    visit_tile(x, y);
                    show_text_board();
                    std::cout << "You lose!" << std::endl;
                    exit(EXIT_SUCCESS);
        
                }

                op.push_back(x);
                op.push_back(y);
                ordered_pair_queue.push(op);

                std::cout << ordered_pair_queue.front()[0] << ", " << ordered_pair_queue.front()[1] << std::endl;
        
                surveil_region(ordered_pair_queue);
                show_text_board();
        
                if (visited_all_empty_tiles()) {
                    std::cout << "You win!" << std::endl;
                    exit(EXIT_SUCCESS);
                }
            }
        }

        std::cout << "You can mark " << _num_mines - _num_marked << " more squares." << std::endl;
}

void minesweeper_gameboard::surveil_region(std::queue<std::vector<int>> current_ordered_pair_queue) {
    
    std::queue<std::vector<int>> updated_ordered_pair_queue;
    updated_ordered_pair_queue = uncover_tiles(current_ordered_pair_queue);

    if (!updated_ordered_pair_queue.empty()) {
        surveil_region(updated_ordered_pair_queue);
    } else {
        return;
    }

}

std::queue<std::vector<int>> minesweeper_gameboard::uncover_tiles(std::queue<std::vector<int>> ordered_pair_queue) {

    int x, y, xx, yy;
    int minecount = 0;
    std::vector<int> neighbor;
    std::queue<std::vector<int>> neighbors;

    x = ordered_pair_queue.front()[0];
    y = ordered_pair_queue.front()[1];
    ordered_pair_queue.pop();
    
    if (!_gameboard[x][y].get_visited()) {
        visit_tile(x, y);
    }

    for (int i = x - 1; i <= x + 1; i++ ) {
        for (int j = y - 1; j <= y + 1; j++ ) {
            if (i >= 0 && i < _side_length && j >=0 && j < _side_length && !(i == x && j == y)) {
                if (_gameboard[i][j].get_mine()) {

                    minecount += 1;    

                } else if (! _gameboard[i][j].get_visited()) {

                    neighbor.push_back(i);
                    neighbor.push_back(j);
                    neighbors.push(neighbor);
                    
                    neighbor.clear();

                }
            }
        }
    }

    if (minecount == 0) {
        
        while(!neighbors.empty()) {

            ordered_pair_queue.push(neighbors.front());
            
            xx = neighbors.front()[0];
            yy = neighbors.front()[1];

            if (! _gameboard[xx][yy].get_visited()) {
                visit_tile(xx, yy);
            }  

            neighbors.pop(); 

        }
    }
    _gameboard[x][y].set_num_neighbor_mines(minecount);

    return(ordered_pair_queue);

}