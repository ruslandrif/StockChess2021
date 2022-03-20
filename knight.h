#ifndef KNIGHT_H
#define KNIGHT_H
#include "figure.h"


class knight : public figure
{
public:
    knight(colors color,QWidget *parent = nullptr,int cost = 3,figure_weight weight = figure_weight::LIGHT);

    figure_type name() override {return figure_type::Knight;}

    void touch_attacking_squares(int how) override;


    std::vector<position> possible_squares() override;

    ~knight() override {};
};

#endif // KNIGHT_H
