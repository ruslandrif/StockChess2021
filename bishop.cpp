#include "bishop.h"
#include "board.h"
bishop::bishop(std::string text,QWidget *parent,int cost,figure_weight weight) : figure(text,parent,cost,weight)
{

}

void bishop::touch_attacking_squares(int how) {

    //marking diagonal right up
    position p;
    p = this->get_pos();
    p.column = columns(p.column + 1);
    p.row++;
    while(p.column <= H && p.row <= 8 && (at(p)._figure == EMPTY_SQUARE || (at(p)._figure->name() == King && at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == White) {
            at(p).attacking_white_figures += how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }

        p.column = columns(p.column + 1);
        p.row++;
    }
    if(p.column <= H && p.row <= 8) {
        if(this->get_color() == White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }
    }


    //marking diagonal left down
    p = this->get_pos();
    p.column = columns(p.column - 1);
    p.row--;
    while(p.column >= A && p.row >= 1 && (at(p)._figure == EMPTY_SQUARE || (at(p)._figure->name() == King && at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }

        p.column = columns(p.column - 1);
        p.row--;
    }
    if(p.column >= A && p.row >= 1 && at(p)._figure != EMPTY_SQUARE) {
        if(this->get_color() == White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }
    }

    //marking diagonal right down
    p = this->get_pos();
    p.column = columns(p.column + 1);
    p.row--;
    while(p.column <= H && p.row >= 1 && (at(p)._figure == EMPTY_SQUARE || (at(p)._figure->name() == King && at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }

        p.column = columns(p.column + 1);
        p.row--;
    }
    if(p.column <= H && p.row >= 1 && at(p)._figure != EMPTY_SQUARE) {
        if(this->get_color() == White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }
    }


    //marking diagonal left up
    p = this->get_pos();
    p.column = columns(p.column - 1);
    p.row++;
    while(p.column >= A && p.row <= 8 && (at(p)._figure == EMPTY_SQUARE || (at(p)._figure->name() == King && at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }

        p.column = columns(p.column - 1);
        p.row++;
    }
    if(p.column >= A && p.row <= 8 && at(p)._figure != EMPTY_SQUARE) {
        if(this->get_color() == White) {
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
    p.column = columns(p.column + 1);
    p.row++;
    while(p.column <= H && p.row <= 8 && at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(p.column + 1);
        p.row++;
    }
    if(p.column <= H && p.row <= 8 && at(p)._figure != EMPTY_SQUARE && at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }

    //check squares from left down
    p = this->get_pos();
    p.column = columns(p.column - 1);
    p.row--;
    while(p.column >= A && p.row >= 1 && at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(p.column - 1);
        p.row--;
    }
    if(p.column >= A && p.row >= 1 && at(p)._figure != EMPTY_SQUARE && at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }

    //check squares from right down
    p = this->get_pos();
    p.column = columns(p.column + 1);
    p.row--;
    while(p.column <= H && p.row >= 1 && at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(p.column + 1);
        p.row--;
    }
    if(p.column <= H && p.row >= 1 && at(p)._figure != EMPTY_SQUARE && at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }


    //check squares from left up
    p = this->get_pos();
    p.column = columns(p.column - 1);
    p.row++;
    while(p.column >= A && p.row <= 8 && at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(p.column - 1);
        p.row++;
    }
    if(p.column >= A && p.row <= 8 && at(p)._figure != EMPTY_SQUARE && at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }

    return result;
}
