
#include "figure.h"
#include "board.h"
#include <QTextStream>
#include "game.h"
figure::figure(colors color,figure_type type,std::shared_ptr<Board> parent,int cost,figure_weight fw) : QLabel(parent.get()), board_ptr_(parent), c(color), cost(cost), weight(fw)
{
    QPixmap pix;

    //set icon of the figure
    switch (type) {
        case figure_type::King:
            if(c == colors::White) {
                pix = QPixmap(":/pics/figures/wK.png");
            }
            else {
                pix = QPixmap(":/pics/figures/bK.png");
            }
            break;
        case figure_type::Queen:
            if(c == colors::White) {
                pix = QPixmap(":/pics/figures/wQ.png");
            }
            else {
                pix = QPixmap(":/pics/figures/bQ.png");
            }
            break;
        case figure_type::Bishop:
            if(c == colors::White) {
                pix = QPixmap(":/pics/figures/wB.png");
            }
            else {
                pix = QPixmap(":/pics/figures/bB.png");
            }
            break;
        case figure_type::Knight:
            if(c == colors::White) {
                pix = QPixmap(":/pics/figures/wN.png");
            }
            else {
                pix = QPixmap(":/pics/figures/bN.png");
            }
            break;
        case figure_type::Rook:
            if(c == colors::White) {
                pix = QPixmap(":/pics/figures/wR.png");
            }
            else {
                pix = QPixmap(":/pics/figures/bR.png");
            }
            break;
        case figure_type::Piece:
            if(c == colors::White) {
                pix = QPixmap(":/pics/figures/wP.png");
            }
            else {
                pix = QPixmap(":/pics/figures/bP.png");
            }
            break;
    }

    this->setPixmap(pix);
    count_moves = 0;
}

void figure::set_pos(position newpos)
{
    p.column = newpos.column;
    p.row = newpos.row;
}

square& figure::at(position p) {
    return board_ptr_.lock()->at(p);
}

square& figure::at(columns c, std::size_t row) {
    return board_ptr_.lock()->at(c, row);
}

figure::~figure() {

}



