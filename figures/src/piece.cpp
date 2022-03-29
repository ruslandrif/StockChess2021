#include "piece.h"
#include "board.h"
#include <QTextStream>
#include <algorithm>
piece::piece(colors color,std::shared_ptr<Board> parent,int cost,figure_weight weight) : figure(color,figure_type::Piece,parent,cost,weight)
{
    LOG(INFO) << "piece constr";
}

std::vector<position> piece::possible_squares() {

    position p = this->get_pos();
    const int column = static_cast<int>(p.column);
    std::vector<position> result;

    if(this->get_color() == colors::White) {  //logic of the moves is different depends on color

        bool near_square_free = p.row != 8 && at(p.column,p.row + 1)._figure == EMPTY_SQUARE;
        if(near_square_free) result.push_back(position(p.column,p.row + 1));  //near square

        bool first_move_by_two = (count_moves == 0 && near_square_free && p.row < 7 && at(p.column,p.row + 2)._figure == EMPTY_SQUARE);
        if(first_move_by_two) result.push_back(position(p.column,p.row + 2));  //first move by two squares

        bool ordinary_taking_right = (p.row != 8 && p.column != columns::H && at(columns(column + 1),p.row + 1)._figure != EMPTY_SQUARE && at(columns(column + 1),p.row + 1)._figure->get_color() != this->get_color());
        bool ordinary_taking_left = (p.row != 8 && p.column != columns::A && at(columns(column - 1),p.row + 1)._figure != EMPTY_SQUARE && at(columns(column - 1),p.row + 1)._figure->get_color() != this->get_color());
        if(ordinary_taking_left) result.push_back(position(columns(column - 1),p.row + 1));
        if(ordinary_taking_right) result.push_back(position(columns(column + 1),p.row + 1));  //taking other figure from left or from right


        bool piece_from_right = (p.column != columns::H && at(columns(column + 1),p.row)._figure != EMPTY_SQUARE && at(columns(column + 1),p.row)._figure->name() == figure_type::Piece);
        bool taking_by_pass_right = (p.row == 5 && piece_from_right && at(columns(column + 1),p.row + 1)._figure == EMPTY_SQUARE &&  at(columns(column + 1),p.row)._figure->get_color() != this->get_color() && at(columns(column + 1),p.row)._figure->get_count_moves() == 1);
        bool last_move_piece_from_right = (p.column != columns::H && at(columns(column + 1),p.row)._figure == Board::last_move);
        if(taking_by_pass_right && last_move_piece_from_right){ result.push_back(position(columns(column + 1),p.row + 1));}  //taking by pass from right

        bool piece_from_left = (p.column != columns::A && at(columns(column - 1),p.row)._figure != EMPTY_SQUARE && at(columns(column - 1),p.row)._figure->name() == figure_type::Piece);
        bool taking_by_pass_left = (p.row == 5 && piece_from_left && at(columns(column - 1),p.row + 1)._figure == EMPTY_SQUARE &&  at(columns(column - 1),p.row)._figure->get_color() != this->get_color() && at(columns(column - 1),p.row)._figure->get_count_moves() == 1);
        bool last_move_piece_from_left = (p.column != columns::A && at(columns(column - 1),p.row)._figure == Board::last_move);
        if(taking_by_pass_left && last_move_piece_from_left) result.push_back(position(columns(column - 1),p.row + 1)); //taking by pass from left

    }
    else { //black piece

        bool near_square_free = p.row != 1 && at(p.column,p.row - 1)._figure == EMPTY_SQUARE;
        if(near_square_free) result.push_back(position(p.column,p.row - 1)); //near square

        bool first_move_by_two = (count_moves == 0 && near_square_free && p.row > 2 && at(p.column,p.row - 2)._figure == EMPTY_SQUARE);
        if(first_move_by_two) result.push_back(position(p.column,p.row - 2));  //first move by two squares

        bool ordinary_taking_right = (p.row != 1 && p.column != columns::H && at(columns(column + 1),p.row - 1)._figure != EMPTY_SQUARE && at(columns(column + 1),p.row - 1)._figure->get_color() != this->get_color());
        bool ordinary_taking_left = (p.row != 1 && p.column != columns::A && at(columns(column - 1),p.row - 1)._figure != EMPTY_SQUARE && at(columns(column - 1),p.row - 1)._figure->get_color() != this->get_color());
        if(ordinary_taking_left) result.push_back(position(columns(column - 1),p.row - 1));
        if(ordinary_taking_right) result.push_back(position(columns(column + 1),p.row - 1));   //taking other figure from left or from right=

        bool piece_from_right = (p.column != columns::H && at(columns(column + 1),p.row)._figure != EMPTY_SQUARE && at(columns(column + 1),p.row)._figure->name() == figure_type::Piece);

        bool taking_by_pass_right = (p.row == 4 && piece_from_right && at(columns(column + 1),p.row - 1)._figure == EMPTY_SQUARE &&  at(columns(column + 1),p.row)._figure->get_color() != this->get_color() && at(columns(column + 1),p.row)._figure->get_count_moves() == 1);
        bool last_move_piece_from_right = (p.column != columns::H && at(columns(column + 1),p.row)._figure == Board::last_move);
        if(taking_by_pass_right && last_move_piece_from_right) result.push_back(position(columns(column + 1),p.row - 1)); //taking by pass from right

        bool piece_from_left = (p.column != columns::A && at(columns(column - 1),p.row)._figure != EMPTY_SQUARE && at(columns(column - 1),p.row)._figure->name() == figure_type::Piece);

        bool taking_by_pass_left = (p.row == 4 && piece_from_left && at(columns(column - 1),p.row - 1)._figure == EMPTY_SQUARE &&  at(columns(column - 1),p.row)._figure->get_color() != this->get_color() && at(columns(column - 1),p.row)._figure->get_count_moves() == 1);
        bool last_move_piece_from_left = (p.column != columns::A && at(columns(column - 1),p.row)._figure == Board::last_move);
        if(taking_by_pass_left && last_move_piece_from_left) result.push_back(position(columns(column - 1),p.row - 1)); //taking by pass from left
    }

    return result;
}





void piece::touch_attacking_squares(int how) {

    auto p = this->get_pos();
    const int col = static_cast<int>(p.column);
    if(this->get_color() == colors::White) {
        if(p.row != 8) {
            if(p.column != columns::A) {
                at(columns(col - 1),p.row + 1).attacking_white_figures+= how;   //diagonal left up
            }
            if(p.column != columns::H) {
                at(columns(col + 1),p.row + 1).attacking_white_figures+= how;   //diagonal right up
            }
        }
    }
    else {
        if(p.row != 1) {
            if(p.column != columns::A) {
                at(columns(col - 1),p.row - 1).attacking_black_figures+= how; //diagonal left down
            }
            if(p.column != columns::H) {
                at(columns(col + 1),p.row - 1).attacking_black_figures+= how;   //diagonal right down
            }
        }
    }

}






