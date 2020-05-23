#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <queue>

#include "minesweeper_gameboard.h"
#include "tile.h"

using namespace std;

int main()
{

    //std::vector<int> coord_ordered_pair;
    std::queue<std::vector<int> > op_queue;

    // declare gameboard
    minesweeper_gameboard myGameboard(25, "Easy");

    // display user-facing gameboard
    myGameboard.show_text_board();

    while(1) {
        
        myGameboard.step(op_queue);

    } 

    return 0;

}