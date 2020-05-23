#ifndef TILE_H_
#define TILE_H_

class tile {

    private:
        
        bool _mine;
        bool _visited;
        bool _marked;
        bool _neighbor_mines_counted;

        int _num_neighbor_mines;
        int _num_neighbors_marked;
    
    public:

        tile();
        tile(bool mine);

        void set_mine();
        void visit();
        void mark();
        void unmark();
        
        bool get_mine();
        bool get_visited();
        bool get_marked();

        void set_num_neighbor_mines(int num_mines);
        bool get_neighbor_mines_counted();
        int get_num_neighbor_mines();

        void mark_neighbor();
        void unmark_neighbor();
        int get_num_marked_neighbors();
        
        void print_mine_status();

};

#endif