/*this class is abstract class which describes figure behaviour, making move, finding squares to move, and check which squares is attacked by the figure.*/
#ifndef FIGURE_H
#define FIGURE_H
#include <QLabel>
#include <string>
#include <QTextStream>
#include <cmath>
#include <vector>
#include <algorithm>
#include "common_used.h"



//structure that handle position on the board
struct position {
    position(columns col = columns::A,std::size_t r = 1) : column(col),row(r){}
    columns column;
    std::size_t row;
    bool operator == (position p) {
        return this->column == p.column && this->row == p.row;
    }
    void print() {
        QTextStream out(stdout);
        //out << "printing func " << endl;
        switch(column) {
            case columns::A:
                out << "A";
                break;
            case columns::B:
                out << "B";
                break;
            case columns::C:
                out << "C";
            break;
            case columns::D:
                out << "D";
            break;
            case columns::E:
                out << "E";
            break;
            case columns::F:
                out << "F";
            break;
            case columns::G:
                out << "G";
            break;
            case columns::H:
                out << "H";
            break;
        }
        out << row << "\n";
     }

    std::string to_str() const {
        std::string result;

        switch(column) {
            case columns::A:
                result.push_back('a');
                break;
            case columns::B:
                result.push_back('b');
                break;
            case columns::C:
                result.push_back('c');
            break;
            case columns::D:
                result.push_back('d');
            break;
            case columns::E:
                result.push_back('e');
            break;
            case columns::F:
                result.push_back('f');
            break;
            case columns::G:
                result.push_back('g');
            break;
            case columns::H:
                result.push_back('h');
            break;
        }
        char last = row + '0';
        result.push_back(last);
        return result;
    }
};



class figure : public QLabel
{
public:
    figure(colors color,figure_type type,QWidget *parent = nullptr,int cost = -1,figure_weight weight = figure_weight::LIGHT);

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
    const int cost;
    const figure_weight weight;
    std::size_t count_moves;
    position p;
    QPixmap pix;
    colors c;
signals:

};



#endif // FIGURE_H
