#include "tower.h"

tower::tower(Board *b,const QString &text) : figure(b,text)
{

}

QString tower::name() {return "tower";}
