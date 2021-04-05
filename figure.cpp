
#include "figure.h"
#include <QTextStream>
#include "game.h"
figure::figure(std::string text,QWidget *parent,int cost,figure_weight fw) : QLabel(text.data(),parent),cost(cost),weight(fw)
{
    c = (text[0] == 'w') ? White : Black;
    QPixmap pix;

    //set icon of the figure
    switch (text[1]) {
        case 'K':
            if(text[0] == 'w') {
                pix = QPixmap("pics/figures/wK.png");
            }
            else {
                pix = QPixmap("pics/figures/bK.png");
            }
            break;
        case 'Q':
            if(text[0] == 'w') {
                pix = QPixmap("pics/figures/wQ.png");
            }
            else {
                pix = QPixmap("pics/figures/bQ.png");
            }
            break;
        case 'B':
            if(text[0] == 'w') {
                pix = QPixmap("pics/figures/wB.png");
            }
            else {
                pix = QPixmap("pics/figures/bB.png");
            }
            break;
        case 'N':
            if(text[0] == 'w') {
                pix = QPixmap("pics/figures/wN.png");
            }
            else {
                pix = QPixmap("pics/figures/bN.png");
            }
            break;
        case 'R':
            if(text[0] == 'w') {
                pix = QPixmap("pics/figures/wR.png");
            }
            else {
                pix = QPixmap("pics/figures/bR.png");
            }
            break;
        case 'P':
            if(text[0] == 'w') {
                pix = QPixmap("pics/figures/wP.png");
            }
            else {
                pix = QPixmap("pics/figures/bP.png");
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

figure::~figure() {

}



