#ifndef STRUCTURES_H_
#define STRUCTURES_H_

#include <string>
#include <queue>

#include "tile.h"

class minesweeper_gameboard {

    private:

        int _side_length;
        int _num_tiles;
        int _num_mines;
        int _num_empty_tiles;
        int _num_visited;
        int _num_marked;

        std::string _difficulty;
        std::vector<std::vector<tile> > _gameboard;

    public:
        
        minesweeper_gameboard(int side_length, std::string difficult);
        
        void print_side_length();
        void print_difficulty();
        void print_num_mines();
        
        void show_mine_board();
        void show_text_board();

        void calc_num_mines();
        void populate_board_with_mines();

        void step(std::queue<std::vector<int> > ordered_pair_queue);
        void surveil_region(std::queue<std::vector<int> > ordered_pair_queue);
        std::queue<std::vector<int> > uncover_tiles(std::queue<std::vector<int> > ordered_pair_queue);

        void visit_tile(int x, int y);
        bool visited_all_empty_tiles();

        void toggle_mark_tile(int x, int y);
};

#endif