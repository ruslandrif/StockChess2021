/*this class is abstract class which describes figure behaviour, making move, finding squares to move, and check which squares is attacked by the figure.*/
#ifndef FIGURE_H
#define FIGURE_H
#include <QLabel>
#include <string>
#include <QTextStream>
#include <cmath>
#include <vector>
#include <memory>
#include <algorithm>
#include "common_used.h"
#include "easylogging++.h"

class Board;

//structure that handle position on the board
struct position {
    position(columns col = columns::A,std::size_t r = 1) : column(col),row(r) { }

    columns column;
    std::size_t row;

    bool operator == (position p) {
        return this->column == p.column && this->row == p.row;
    }

    void print() {
        LOG(INFO) << std::string(columns_alias.at(column) + std::to_string(row));
     }

    std::string to_str() const {
        std::string result;

        result += columns_alias.at(column);
        char last = row + '0';
        result.push_back(last);
        return result;
    }
};



class figure : public QLabel
{
public:
    figure(colors color,figure_type type,std::shared_ptr<Board> parent = nullptr,int cost = -1,figure_weight weight = figure_weight::LIGHT);

    virtual figure_type name() = 0;

    //this function touch all squares that figure attack. how - how to touch  - start attacking, or stop attcking
    //for example - the rook position is A1 and A2 is free. Then after that function A2 will have one more white attacking figure.
    virtual void touch_attacking_squares(int how) = 0;

    //function to get all possible squares, where figure can move
    virtual std::vector<position> possible_squares() = 0;

    position get_pos() {return this->p;}
    std::size_t get_count_moves() {return this->count_moves;}
    colors get_color() {return this->c;}
    int get_cost() {return cost;}
    figure_weight get_weight() {return weight;}

    void increment_moves() {count_moves++;}
    void set_pos(position newpos);

    void null_count_moves() {count_moves = 0;}

    virtual ~figure();
protected:
    square& at(position p);
    square& at(columns c, std::size_t row);
    const int cost;
    const figure_weight weight;
    std::size_t count_moves;
    position p;
    QPixmap pix;
    colors c;
    std::weak_ptr<Board> board_ptr_;
private:


};



#endif // FIGURE_H
