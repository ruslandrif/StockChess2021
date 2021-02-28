#ifndef TOWER_H
#define TOWER_H
#include "figure.h"
#include "board.h"
class tower : public figure
{
public:
    tower(Board *b,const QString &text);
    QString name() override;
    bool can_make_move(columns from_col,std::size_t from_r,columns to_col,std::size_t to_r) override;
};

#endif // TOWER_H
