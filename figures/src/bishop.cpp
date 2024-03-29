#include "bishop.h"
#include "board.h"
bishop::bishop(colors color,std::shared_ptr<Board> parent,int cost,figure_weight weight) : figure(color,figure_type::Bishop,parent,cost,weight)
{

}

void bishop::touch_attacking_squares(int how) {

    //marking diagonal right up

    auto b = board_ptr_.lock();
    position p;
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) + 1);
    p.row++;
    while(p.column <= columns::H && p.row <= 8 && (b->at(p)._figure == EMPTY_SQUARE || (b->at(p)._figure->name() == figure_type::King && b->at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == colors::White) {
            b->at(p).attacking_white_figures += how;
        }
        else {
            b->at(p).attacking_black_figures+= how;
        }

        p.column = columns(static_cast<int>(p.column) + 1);
        p.row++;
    }
    if(p.column <= columns::H && p.row <= 8) {
        if(this->get_color() == colors::White) {
            b->at(p).attacking_white_figures+= how;
        }
        else {
            b->at(p).attacking_black_figures+= how;
        }
    }


    //marking diagonal left down
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) - 1);
    p.row--;
    while(p.column >=columns:: A && p.row >= 1 && (b->at(p)._figure == EMPTY_SQUARE || (b->at(p)._figure->name() == figure_type::King && b->at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == colors::White) {
            b->at(p).attacking_white_figures+= how;
        }
        else {
            b->at(p).attacking_black_figures+= how;
        }

        p.column = columns(static_cast<int>(p.column) - 1);
        p.row--;
    }
    if(p.column >= columns::A && p.row >= 1 && b->at(p)._figure != EMPTY_SQUARE) {
        if(this->get_color() == colors::White) {
            b->at(p).attacking_white_figures+= how;
        }
        else {
            b->at(p).attacking_black_figures+= how;
        }
    }

    //marking diagonal right down
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) + 1);
    p.row--;
    while(p.column <= columns::H && p.row >= 1 && (b->at(p)._figure == EMPTY_SQUARE || (b->at(p)._figure->name() == figure_type::King && b->at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == colors::White) {
            b->at(p).attacking_white_figures+= how;
        }
        else {
            b->at(p).attacking_black_figures+= how;
        }

        p.column = columns(static_cast<int>(p.column) + 1);
        p.row--;
    }
    if(p.column <= columns::H && p.row >= 1 && b->at(p)._figure != EMPTY_SQUARE) {
        if(this->get_color() == colors::White) {
            b->at(p).attacking_white_figures+= how;
        }
        else {
            b->at(p).attacking_black_figures+= how;
        }
    }


    //marking diagonal left up
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) - 1);
    p.row++;
    while(p.column >= columns::A && p.row <= 8 && (b->at(p)._figure == EMPTY_SQUARE || (at(p)._figure->name() == figure_type::King && b->at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == colors::White) {
            b->at(p).attacking_white_figures+= how;
        }
        else {
            b->at(p).attacking_black_figures+= how;
        }

        p.column = columns(static_cast<int>(p.column) - 1);
        p.row++;
    }
    if(p.column >= columns::A && p.row <= 8 && b->at(p)._figure != EMPTY_SQUARE) {
        if(this->get_color() == colors::White) {
            b->at(p).attacking_white_figures+= how;
        }
        else {
            b->at(p).attacking_black_figures+= how;
        }
    }
}



std::vector<position> bishop::possible_squares() {
    std::vector<position> result;
    position p;
    auto b = board_ptr_.lock();
    //check squares from righ up
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) + 1);
    p.row++;
    while(p.column <= columns::H && p.row <= 8 && b->at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(static_cast<int>(p.column) + 1);
        p.row++;
    }
    if(p.column <= columns::H && p.row <= 8 && b->at(p)._figure != EMPTY_SQUARE && b->at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }

    //check squares from left down
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) - 1);
    p.row--;
    while(p.column >= columns::A && p.row >= 1 && b->at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(static_cast<int>(p.column) - 1);
        p.row--;
    }
    if(p.column >= columns::A && p.row >= 1 && b->at(p)._figure != EMPTY_SQUARE && b->at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }

    //check squares from right down
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) + 1);
    p.row--;
    while(p.column <= columns::H && p.row >= 1 && b->at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(static_cast<int>(p.column) + 1);
        p.row--;
    }
    if(p.column <= columns::H && p.row >= 1 && b->at(p)._figure != EMPTY_SQUARE && b->at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }


    //check squares from left up
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) - 1);
    p.row++;
    while(p.column >= columns::A && p.row <= 8 && b->at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(static_cast<int>(p.column) - 1);
        p.row++;
    }
    if(p.column >= columns::A && p.row <= 8 && b->at(p)._figure != EMPTY_SQUARE && b->at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }

    return result;
}
