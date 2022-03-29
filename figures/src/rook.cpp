#include "rook.h"
#include "board.h"
rook::rook(colors color,std::shared_ptr<Board> parent,int cost,figure_weight weight) : figure(color,figure_type::Rook,parent,cost,weight)
{

}

void rook::touch_attacking_squares(int how) {



    //marking vertical up
    position p = this->get_pos();
    p.row += 1;

    auto b = board_ptr_.lock();

    while(p.row <= 8 && (b->at(p)._figure == EMPTY_SQUARE || (b->at(p)._figure->name() == figure_type::King && b->at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == colors::White) {
            b->at(p).attacking_white_figures+= how;
        }
        else {
            b->at(p).attacking_black_figures+= how;
        }
        p.row++;
    }
    if(p.row <= 8 && b->at(p)._figure != nullptr) {
        if(this->get_color() == colors::White) {
            b->at(p).attacking_white_figures+= how;
        }
        else {
            b->at(p).attacking_black_figures+= how;
        }
    }


    //marking vertical down
    p = this->get_pos();
    p.row -= 1;
    while(p.row >= 1 && (b->at(p)._figure == EMPTY_SQUARE || (b->at(p)._figure->name() == figure_type::King && b->at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == colors::White) {
            b->at(p).attacking_white_figures+= how;
        }
        else {
            b->at(p).attacking_black_figures+= how;
        }
        p.row--;
    }
    if(p.row >= 1 && b->at(p)._figure != EMPTY_SQUARE) {
        if(this->get_color() == colors::White) {
           b->at(p).attacking_white_figures+= how;
        }
        else {
            b->at(p).attacking_black_figures+= how;
        }
    }



    //marking horizontal right
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) + 1);
    while(p.column <= columns::H && (b->at(p)._figure == EMPTY_SQUARE || (b->at(p)._figure->name() == figure_type::King && b->at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == colors::White) {
            b->at(p).attacking_white_figures+= how;
        }
        else {
           b-> at(p).attacking_black_figures+= how;
        }

        p.column = columns(static_cast<int>(p.column) + 1);
    }
    if(p.column <= columns::H && b->at(p)._figure != EMPTY_SQUARE) {
        if(this->get_color() == colors::White) {
            b->at(p).attacking_white_figures+= how;
        }
        else {
            b->at(p).attacking_black_figures+= how;
        }
    }


    //marking horizontal left
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) - 1);
    while(p.column >= columns::A && (b->at(p)._figure == EMPTY_SQUARE || (b->at(p)._figure->name() == figure_type::King && b->at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == colors::White) {
            b->at(p).attacking_white_figures+= how;
        }
        else {
            b->at(p).attacking_black_figures+= how;
        }

        p.column = columns(static_cast<int>(p.column) - 1);
    }
    if(p.column >= columns::A && b->at(p)._figure != EMPTY_SQUARE) {
        if(this->get_color() == colors::White) {
            b->at(p).attacking_white_figures+= how;
        }
        else {
            b->at(p).attacking_black_figures+= how;
        }
    }
}



std::vector<position> rook::possible_squares() {
    //check vertical up
    std::vector<position> result;
    auto b = board_ptr_.lock();
    position p = this->get_pos();
    p.row += 1;
    while(p.row <= 8 && b->at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);
        p.row++;
    }
    if(p.row <= 8 && b->at(p)._figure != EMPTY_SQUARE && b->at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }


    //check vertical down
    p = this->get_pos();
    p.row -= 1;
    while(p.row >= 1 && b->at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);
        p.row--;
    }
    if(p.row >= 1 && b->at(p)._figure != EMPTY_SQUARE && b->at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }



    //check horizontal right
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) + 1);
    while(p.column <= columns::H && b->at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(static_cast<int>(p.column) + 1);
    }
    if(p.column <= columns::H && b->at(p)._figure != EMPTY_SQUARE && b->at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }


    //check horizontal left
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) - 1);
    while(p.column >= columns::A && b->at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(static_cast<int>(p.column) - 1);
    }
    if(p.column >= columns::A && b->at(p)._figure != EMPTY_SQUARE && b->at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }

    return result;
}
