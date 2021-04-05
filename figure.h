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
    position(columns col = A,std::size_t r = 1) : column(col),row(r){}
    columns column;
    std::size_t row;
    bool operator == (position p) {
        return this->column == p.column && this->row == p.row;
    }
    void print() {
        QTextStream out(stdout);
        //out << "printing func " << endl;
        switch(column) {
            case A:
                out << "A";
                break;
            case B:
                out << "B";
                break;
            case C:
                out << "C";
            break;
            case D:
                out << "D";
            break;
            case E:
                out << "E";
            break;
            case F:
                out << "F";
            break;
            case G:
                out << "G";
            break;
            case H:
                out << "H";
            break;
        }
        out << row << "\n";
     }

    std::string to_str() const {
        std::string result;

        switch(column) {
            case A:
                result.push_back('a');
                break;
            case B:
                result.push_back('b');
                break;
            case C:
                result.push_back('c');
            break;
            case D:
                result.push_back('d');
            break;
            case E:
                result.push_back('e');
            break;
            case F:
                result.push_back('f');
            break;
            case G:
                result.push_back('g');
            break;
            case H:
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
    figure(std::string text,QWidget *parent = nullptr,int cost = -1,figure_weight weight = LIGHT);

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
