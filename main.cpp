#include "game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Game game;   //main class object
    game.show();

    return a.exec();
}
