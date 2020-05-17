#include <iostream>

#include "tile.h"

// default constructor
tile::tile() {

    _mine = false;
    _visited = false;
    _marked = false;
    _neighbor_mines_counted = false;

}

// parameterized constructor
tile::tile(bool mine) {

    tile::set_mine();
    _visited = false;

}

void tile::visit() {

    _visited = true;
 
}

bool tile::get_visited() {

    return _visited;

}

void tile::set_mine() {

    _mine = true;

}

bool tile::get_mine() {

    return _mine;

}

void tile::mark() {

    _marked = true;

}

void tile::unmark() {

    _marked = false;

}

bool tile::get_marked() {

    return _marked;

}

void tile::set_num_neighbor_mines(int num_mines) {

    _num_neighbor_mines = num_mines;
    _neighbor_mines_counted = true;

}

bool tile::get_neighbor_mines_counted() {

    return _neighbor_mines_counted;

}

int tile::get_num_neighbor_mines() {

    return _num_neighbor_mines;

}

void tile::print_mine_status() {

    std::cout << _mine << " " ;

}