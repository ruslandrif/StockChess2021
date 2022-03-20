#include "bishop.h"
#include "board.h"
bishop::bishop(colors color,QWidget *parent,int cost,figure_weight weight) : figure(color,figure_type::Bishop,parent,cost,weight)
{

}

void bishop::touch_attacking_squares(int how) {

    //marking diagonal right up
    position p;
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) + 1);
    p.row++;
    while(p.column <= columns::H && p.row <= 8 && (at(p)._figure == EMPTY_SQUARE || (at(p)._figure->name() == figure_type::King && at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == colors::White) {
            at(p).attacking_white_figures += how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }

        p.column = columns(static_cast<int>(p.column) + 1);
        p.row++;
    }
    if(p.column <= columns::H && p.row <= 8) {
        if(this->get_color() == colors::White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }
    }


    //marking diagonal left down
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) - 1);
    p.row--;
    while(p.column >=columns:: A && p.row >= 1 && (at(p)._figure == EMPTY_SQUARE || (at(p)._figure->name() == figure_type::King && at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == colors::White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }

        p.column = columns(static_cast<int>(p.column) - 1);
        p.row--;
    }
    if(p.column >= columns::A && p.row >= 1 && at(p)._figure != EMPTY_SQUARE) {
        if(this->get_color() == colors::White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }
    }

    //marking diagonal right down
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) + 1);
    p.row--;
    while(p.column <= columns::H && p.row >= 1 && (at(p)._figure == EMPTY_SQUARE || (at(p)._figure->name() == figure_type::King && at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == colors::White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }

        p.column = columns(static_cast<int>(p.column) + 1);
        p.row--;
    }
    if(p.column <= columns::H && p.row >= 1 && at(p)._figure != EMPTY_SQUARE) {
        if(this->get_color() == colors::White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }
    }


    //marking diagonal left up
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) - 1);
    p.row++;
    while(p.column >= columns::A && p.row <= 8 && (at(p)._figure == EMPTY_SQUARE || (at(p)._figure->name() == figure_type::King && at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == colors::White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }

        p.column = columns(static_cast<int>(p.column) - 1);
        p.row++;
    }
    if(p.column >= columns::A && p.row <= 8 && at(p)._figure != EMPTY_SQUARE) {
        if(this->get_color() == colors::White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }
    }
}



std::vector<position> bishop::possible_squares() {
    std::vector<position> result;
    position p;
    //check squares from righ up
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) + 1);
    p.row++;
    while(p.column <= columns::H && p.row <= 8 && at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(static_cast<int>(p.column) + 1);
        p.row++;
    }
    if(p.column <= columns::H && p.row <= 8 && at(p)._figure != EMPTY_SQUARE && at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }

    //check squares from left down
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) - 1);
    p.row--;
    while(p.column >= columns::A && p.row >= 1 && at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(static_cast<int>(p.column) - 1);
        p.row--;
    }
    if(p.column >= columns::A && p.row >= 1 && at(p)._figure != EMPTY_SQUARE && at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }

    //check squares from right down
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) + 1);
    p.row--;
    while(p.column <= columns::H && p.row >= 1 && at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(static_cast<int>(p.column) + 1);
        p.row--;
    }
    if(p.column <= columns::H && p.row >= 1 && at(p)._figure != EMPTY_SQUARE && at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }


    //check squares from left up
    p = this->get_pos();
    p.column = columns(static_cast<int>(p.column) - 1);
    p.row++;
    while(p.column >= columns::A && p.row <= 8 && at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(static_cast<int>(p.column) - 1);
        p.row++;
    }
    if(p.column >= columns::A && p.row <= 8 && at(p)._figure != EMPTY_SQUARE && at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }

    return result;
}
