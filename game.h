/*This is the base program class. The program only contains one copy of this class.*/
#ifndef GAME_H
#define GAME_H
#include <QWidget>
/*This file contains a common data which many of the classes use*/
#include <functional>
#include <QCoreApplication>
#include <QDateTime>
#include <QApplication>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QKeyEvent>
#include <QString>
#include <QCheckBox>
#include <QDir>
#include <array>
#include <string>
#include <QComboBox>
#include <ctime>
#include "common_used.h"

class Board;
class figure;



class Game : public QWidget
{
    Q_OBJECT
public:
    Game(QWidget *parent = nullptr);
    void show_menu();
    void show_settings();
    void play();
    void show_final_screen(final_states f);
    void choose_color();        //player choose color to play



    static std::array<std::array<square,8>,8> board;  //static array of squares that represents board

    static colors now_move;   //which side move now
    static colors Player_color;  //player color
    static hard_modes hard_mode;  //hard mode (how many moves will stockfish calculate)
    static std::string string_for_stockfish; //string which will be given to stockfish to calculate moves
    static std::size_t count_move;

    static state get_state() {return st;}


    virtual ~Game();
public slots:

private:
    static state st;  //player plays with himself, or with chess engine
    how_to_write_games how_to_white;


    Board *b{nullptr};

    QVBoxLayout *main_vb{nullptr};

    QPushButton *play_btn{nullptr};
    QPushButton *settings_btn{nullptr};           //buttons for all part of the game
    QPushButton *exit_btn{nullptr};
    QPushButton *return_to_main_menu{nullptr};
    QPushButton *white_choise{nullptr};
    QPushButton *black_choise{nullptr};
    QPushButton *random_choise{nullptr};

    QLabel *final_lbl{nullptr};
    QLabel *color_choose_lbl{nullptr};
    QLabel *hard_mode_lbl{nullptr};
    QLabel *play_mode_lbl{nullptr};
    QLabel *write_games_lbl{nullptr};

    QComboBox *write_games_settings{nullptr};
    QComboBox *play_mode_setting{nullptr};
    QComboBox *hard_mode_setting{nullptr};


};

void traverse_board(std::function<void(square&)> func_to_traverse);  //function to traverse whole board and do smth with the squares

square& find_some_figure(std::function<bool(square&)> check_figure);  //function that finds some figure by some property

bool check_some_board_condition(std::function<bool(square&)> check_false); //function to check some conditions on the board. for example: if only two kings left

#endif // GAME_H
