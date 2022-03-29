#include "easylogging++.h"
INITIALIZE_EASYLOGGINGPP
#include "game.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::shared_ptr<Game> g_ptr = std::make_shared<Game>();   //main class object
    g_ptr->show();

    return a.exec();
}
