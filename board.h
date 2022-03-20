/*This class contain a game board with all of the figures, functions to make move,write move, get move from engine, etc.*/
#ifndef BOARD_H
#define BOARD_H
#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QFile>
#include <QDebug>
#include <QProcess>
#include <QPushButton>
#include <exception>
#include <thread>
#include <vector>

class figure;
#include "piece.h"
#include "king.h"
#include "queen.h"
#include "rook.h"
#include "bishop.h"
#include "knight.h"
#include "common_used.h"

void mark_all();
void unmark_all();

struct single_move {

private:
    figure_type name; //which figure moved

    position from;
    position where;

    bool taking{ false };
public:

    single_move(figure_type fig, position f, position w, bool t = false);

    position get_from();
    position get_where();

    std::string to_str(bool isCheck = false, bool is_mate = false, bool isBlack = false, bool transform = false, char transform_first_symbol = ' ') const; //convert move to string

    std::string to_string_for_stockfish(char transform = ' ');

};

struct full_move {
    single_move white;
    single_move black;
};

square& at(position p);                    //returns board squares, that represent the given position
square& at(columns c, std::size_t row);     // because the board is an array, and there we need to calculate indices correctly

class Board : public QWidget
{
    Q_OBJECT
public:

    Board(QWidget* parent = nullptr);
    virtual ~Board();

    void draw();
    void figures_start_set();

    int get_square_size();
    const figure*  get_last_moved();
    QString get_write_filename();

    void closeEvent(QCloseEvent* e) override;
    void paintEvent(QPaintEvent* e) override;
    void mousePressEvent(QMouseEvent* e) override;  //event handlers
    void mouseReleaseEvent(QMouseEvent* e) override;

    single_move convert_stockfish_move_to_single_move(std::string stockstr);

    std::string get_stockfish_best_move(); //connect to chess engine and get best move


    bool check_for_mate();
    bool check_for_draw(); //check for mate or draw

    std::size_t how_much_material_left();   //calculate how much material left

    static figure* last_move; //figure that moved last

    void choose_figure_to_transform(position where); //function that shows a window where player can choose figure for piece transformation

    void set_write_filename(QString s);
    void make_move(position handled, position release_pos, bool stockfish, char transform_figure);  //function that try to make move
    void write_move(const single_move& s, bool is_check = false, bool is_mate = false, bool Black = false, bool transform = false, char transform_first_symbol = ' '); //write move to file


    std::shared_ptr<king> white_king{};
    std::shared_ptr<king> black_king{};

    std::shared_ptr<queen>  queen_black{};
    std::shared_ptr<queen>  queen_white{};

    std::vector<std::shared_ptr<rook> > rooks_black{ 2 };
    std::vector<std::shared_ptr<rook> > rooks_white{ 2 };

    std::vector<std::shared_ptr<knight> > knights_black{ 2 };
    std::vector<std::shared_ptr<knight> > knights_white{ 2 };

    std::vector<std::shared_ptr<bishop> > bishops_black{ 2 };
    std::vector<std::shared_ptr<bishop> > bishops_white{ 2 };

    std::vector<std::shared_ptr<piece> > pieces_black{ 8 };
    std::vector<std::shared_ptr<piece> > pieces_white{ 8 };

signals:
    void windowClosed();
    void mate(final_states f = win);
    void draw_signal(final_states f = final_states::draw);

private:
    bool no_pieces();
    bool only_two_kings();
    bool two_bishops();
    bool only_light_figures_left();  //some booleans
    bool stalemate();

    bool was_pressed{ false };

    square& get_king(colors c); //return the square with the king of the color c

    QWidget* figure_choose{ nullptr };
    position where_to_transform;

    void transform();  //function to transform piece to other figure

    QProcess* stockfish_process{ nullptr }; //process to interract with chess engine

    std::unique_ptr<QPushButton> give_up{ nullptr };  //give up button

    QString filename_to_write{ "" };   //in which file program will write game


    std::size_t square_size; //geometrical size of the square on the board

    position handled;//position where player handle mouse now

    std::vector<std::shared_ptr<figure>> odd_figures{};

    //start figures


    std::vector<std::unique_ptr<QLabel> > letters{ 8 };
    std::vector<std::unique_ptr<QLabel> > digits{ 8 };

    std::vector<std::unique_ptr<QLabel>> possible_moves_signs{};

    //this functions create or clear squares on the board, which show where player can move
    void create_possible_moves_signs(std::vector<position>& positions);
    void clear_possible_moves_signs();

    //show in what figure player wants to transform piece
    figure_type transform_figure{ figure_type::Queen };
};

#endif // BOARD_H
