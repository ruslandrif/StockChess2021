//this class describes the behaviour of the rook on the board
#ifndef ROOK_H
#define ROOK_H
#include "figure.h"

class rook : public figure
{
public:
    rook(std::string text,QWidget *parent = nullptr,int cost = 5,figure_weight weight = HEAVY);
    figure_type name() override{return figure_type::Rook;}
    void touch_attacking_squares(int how) override;

    std::vector<position> possible_squares() override;

    ~rook() override {}
};
#endif // ROOK_H
