
#ifndef KING_H
#define KING_H
#include <QWidget>

#include "figure.h"


class king : public figure
{
public:
    king(std::string text,QWidget *parent = nullptr,int cost = 0,figure_weight weight = HEAVY);
    figure_type name() override {return figure_type::King;}


    void touch_attacking_squares(int how) override;

    std::vector<position> possible_squares() override;

    void set_checked() {was_checked = true;}

    ~king() override {};
private:
    bool was_checked {false};  //check if the king was attacked in current game
};
#endif // KING_H
