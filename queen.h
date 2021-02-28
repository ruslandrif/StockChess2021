//this class describes the behaviour of the queen on the board
#ifndef QUEEN_H
#define QUEEN_H
#include "figure.h"

class queen : public figure
{
public:
    queen(std::string text,QWidget *parent = nullptr,int cost = 9,figure_weight weight = HEAVY);

    figure_type name() override {return figure_type::Queen;};
    void touch_attacking_squares(int how) override;

    std::vector<position> possible_squares() override;
};

#endif // QUEEN_H
