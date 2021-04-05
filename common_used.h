
#ifndef COMMON_USED_H
#define COMMON_USED_H
#include <memory>
#define EMPTY_SQUARE nullptr
#define MARK_ATTACKING_SQUARES 1
#define UNMARK_ATTACKING_SQUARES -1
#define PLAYER_MOVE false
#define STOCKFISH_MOVE true
class figure;
class Game;
enum final_states{draw,win};

enum state{BY_MYSELF,STOCKFISH};

enum how_to_write_games{write_all,write_last,do_not_write};

enum columns{A = 1,B,C,D,E,F,G,H};

enum colors{Black,White};

enum figure_type{Piece,King,Queen,Bishop,Knight,Rook};

enum hard_modes {EASY = 1,MEDIUM = 3,HARD = 5,EXPERT = 7};  //how much moves will chess engine calculate

enum figure_weight {LIGHT,HEAVY};

struct square {  //this structure holds info about square on the board
    square() : _figure(nullptr),attacking_white_figures(0),attacking_black_figures(0) {

    }

    square( std::shared_ptr<figure> f,int white,int black) : _figure(f.get()),attacking_white_figures(white),attacking_black_figures(black) {

    }
    figure* _figure;
    int attacking_white_figures;
    int attacking_black_figures;
    colors square_color{White};


};



#endif // COMMON_USED_H
