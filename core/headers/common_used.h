
#ifndef COMMON_USED_H
#define COMMON_USED_H
#include <memory>
#include <unordered_map>
#define EMPTY_SQUARE nullptr
const int MARK_ATTACKING_SQUARES = 1;
const int UNMARK_ATTACKING_SQUARES = -1;
const bool PLAYER_MOVE = false;
const int STOCKFISH_MOVE = true;
class figure;
class Game;
enum final_states{draw,win};

enum class state{BY_MYSELF,STOCKFISH};

enum class how_to_write_games{write_all,write_last,do_not_write};

enum class columns{A = 1,B,C,D,E,F,G,H};

const std::unordered_map<columns,std::string> columns_alias = {
    {columns::A, "a"},
    {columns::B, "b"},
    {columns::C, "c"},
    {columns::D, "d"},
    {columns::E, "e"},
    {columns::F, "f"},
    {columns::G, "g"},
    {columns::H, "h"},
};

enum class colors{Black,White};

enum class figure_type{Piece,King,Queen,Bishop,Knight,Rook};

enum class hard_modes {EASY = 1,MEDIUM = 3,HARD = 5,EXPERT = 7};  //how much moves will chess engine calculate

enum class figure_weight {LIGHT,HEAVY};

struct square {  //this structure holds info about square on the board
    square() : _figure(nullptr),attacking_white_figures(0),attacking_black_figures(0) {

    }

    square( std::shared_ptr<figure> f,int white,int black) : _figure(f.get()),attacking_white_figures(white),attacking_black_figures(black) {

    }
    figure* _figure{ nullptr };
    int attacking_white_figures{ 0 };
    int attacking_black_figures{ 0 };
    colors square_color{ colors::White };


};



#endif // COMMON_USED_H
