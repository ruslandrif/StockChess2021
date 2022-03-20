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
    piece(colors color,QWidget *parent = nullptr,int cost = 1,figure_weight weight = figure_weight::LIGHT);

    figure_type name() override {return figure_type::Piece;}

    void touch_attacking_squares(int how) override;


    std::vector<position> possible_squares() override;

    ~piece() override {};
};

#endif // PIECE_H
