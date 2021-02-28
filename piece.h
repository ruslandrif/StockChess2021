//this class describes peace behaviour on the board
#ifndef PIECE_H
#define PIECE_H
#include "figure.h"
#include <QObject>
#include <cmath>
class piece : public figure
{
    Q_OBJECT
public:
    piece(std::string text,QWidget *parent = nullptr,int cost = 1,figure_weight weight = LIGHT);

    figure_type name() override {return figure_type::Piece;}

    void touch_attacking_squares(int how) override;


    std::vector<position> possible_squares() override;


};

#endif // PIECE_H
