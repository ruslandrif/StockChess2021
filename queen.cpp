#include "queen.h"
#include "board.h"
queen::queen(std::string text,QWidget *parent,int cost,figure_weight weight) : figure(text,parent,cost,weight)
{

}

void queen::touch_attacking_squares(int how) {
    QTextStream out(stdout);


    //marking vertical up
    position p = this->get_pos();
    p.row += 1;



    while(p.row <= 8 && (at(p)._figure == EMPTY_SQUARE || (at(p)._figure->name() == King && at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }
        p.row++;
    }
    if(p.row <= 8 && at(p)._figure != EMPTY_SQUARE) {
        if(this->get_color() == White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }
    }


    //marking vertical down
    p = this->get_pos();
    p.row -= 1;
    while(p.row >= 1 && (at(p)._figure == EMPTY_SQUARE || (at(p)._figure->name() == King && at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }
        p.row--;
    }
    if(p.row >= 1 && at(p)._figure != EMPTY_SQUARE) {
        if(this->get_color() == White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }
    }



    //marking horizontal right
    p = this->get_pos();
    p.column = columns(p.column + 1);
    while(p.column <= H && (at(p)._figure == EMPTY_SQUARE || (at(p)._figure->name() == King && at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }

        p.column = columns(p.column + 1);
    }
    if(p.column <= H && at(p)._figure != EMPTY_SQUARE) {
        if(this->get_color() == White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }
    }


    //marking horizontal left
    p = this->get_pos();
    p.column = columns(p.column - 1);
    while(p.column >= A && (at(p)._figure == EMPTY_SQUARE || (at(p)._figure->name() == King && at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }

        p.column = columns(p.column - 1);
    }
    if(p.column >= A && at(p)._figure != nullptr) {
        if(this->get_color() == White) {
            at(p).attacking_white_figures+= how;
        }
        else {
            at(p).attacking_black_figures+= how;
        }
    }


    //marking diagonal right up
    p = this->get_pos();
    p.column = columns(p.column + 1);
    p.row++;
    while(p.column <= H && p.row <= 8 && (at(p)._figure == EMPTY_SQUARE || (at(p)._figure->name() == King && at(p)._figure->get_color() != get_color()))) {
        if(this->get_color() == White) {
            at(p).attacking_white_figures+= how;
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



std::vector<position> queen::possible_squares() {
    std::vector<position> result;
    //check vertical up
    position p = this->get_pos();
    p.row += 1;
    while(p.row <= 8 && at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);
        p.row++;
    }
    if(p.row <= 8 && at(p)._figure != EMPTY_SQUARE && at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }


    //check vertical down
    p = this->get_pos();
    p.row -= 1;
    while(p.row >= 1 && at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);
        p.row--;
    }
    if(p.row >= 1 && at(p)._figure != EMPTY_SQUARE && at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }



    //check horizontal right
    p = this->get_pos();
    p.column = columns(p.column + 1);
    while(p.column <= H && at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(p.column + 1);
    }
    if(p.column <= H && at(p)._figure != EMPTY_SQUARE && at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }


    //check horizontal left
    p = this->get_pos();
    p.column = columns(p.column - 1);
    while(p.column >= A && at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(p.column - 1);
    }
    if(p.column >= A && at(p)._figure != EMPTY_SQUARE && at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }


    //check diagonal right up
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

    //check diagonal left down
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

    //check diagonal right down
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


    //check diagonal left up
    p = this->get_pos();
    p.column = columns(p.column - 1);
    p.row++;
    while(p.column >= A && p.row <= 8 && at(p)._figure == EMPTY_SQUARE) {
        result.push_back(p);

        p.column = columns(p.column - 1);
        p.row++;
    }
    if(p.column >= A && p.row <= 8 && at(p)._figure != nullptr && at(p)._figure->get_color() != this->get_color()) {
        result.push_back(p);
    }

    return result;
}
