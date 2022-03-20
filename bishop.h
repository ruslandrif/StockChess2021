/*
This class describes bishop behaviour

*/
#ifndef BISHOP_H
#define BISHOP_H
#include "figure.h"

class bishop : public figure
{
public:
    bishop(colors color,QWidget *parent = nullptr,int cost = 3,figure_weight weight = figure_weight::LIGHT);
    figure_type name() override {return figure_type::Bishop;}
    void touch_attacking_squares(int how) override;

    std::vector<position> possible_squares() override;
};

#endif // BISHOP_H
