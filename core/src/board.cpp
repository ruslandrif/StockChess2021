#include "board.h"
#include "game.h"
#include "figure.h"

#include <QPicture>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include "easylogging++.h"


figure* Board::last_move = nullptr;

single_move::single_move(figure_type fig, position f, position w, bool t) : name(fig), from(f), where(w), taking(t) {

}

position single_move::get_from() { return from; }
position single_move::get_where() { return where; }

std::string single_move::to_str(bool isCheck, bool is_mate, bool isBlack, bool transform, char transform_first_symbol)  const { //function to make a string for writing in file that represents player move
    std::string result;

    if (!transform)
        switch (name) {
        case figure_type::Rook:
            result.push_back('R');
            break;
        case figure_type::Knight:
            result.push_back('N');
            break;
        case figure_type::Bishop:
            result.push_back('B');
            break;
        case figure_type::Queen:
            result.push_back('Q');
            break;
        case figure_type::King:
            result.push_back('K');
            break;
        default:
            break;
        }

    if (transform) {
        result += from.to_str();
        if (taking) result.push_back('x');     //string if the move is piece transformation
        else result.push_back('-');

        result += where.to_str();
        result.push_back(transform_first_symbol);

    }
    else {
        if (name == figure_type::Piece && taking) {   //make a short move string like ef or gf
            result.push_back(from.to_str()[0]);
            result.push_back(where.to_str()[0]);

        }
        else {
            result += from.to_str();

            if (taking) result.push_back('x');
            else result += "-";
            result += where.to_str();
        }
    }
    result += (isCheck) ? "+" : "";
    result += (is_mate) ? "+" : "";
    result += (isBlack) ? "\n" : " ";  //if the move is by black - then go to the new line


    return result;
}

//this  function returns string which represents the move
std::string single_move::to_string_for_stockfish(char transform) {
    std::string result = from.to_str() + where.to_str();

    if (transform != ' ') result.push_back(transform); //transform is the additional char that is ' ' if there is no piece transformation, else it is 'q','r', etc.

    return result;
}

int Board::get_square_size() { return square_size; } //geometrical size of the square on the board

const figure* Board::get_last_moved() { return Board::last_move; }

QString Board::get_write_filename() { return filename_to_write; } //file in which game is written

Board::Board(Game* game,QWidget* parent) : QWidget(parent), game_ptr_(game)
{
    try {
        square_size = (this->height() - 30) / 8;

        give_up = std::make_unique<QPushButton>(this);                    //setting the give-up button
        give_up->setIcon(QIcon(":\\pics\\give_up_icon.png"));
        give_up->setIconSize(QSize(square_size, square_size));


        give_up->setEnabled(true);
        char c('A');
        LOG(INFO) << "before loop";
        //auto shared_ptr = shared_from_this();
        LOG(INFO) << "shared_ptr";
        for (int i = 0; i < 8; ++i) {
            QString s;
            s.push_back(c);
            c++;
            letters[i] = std::make_unique<QLabel>(s, this);
            letters[i]->setTextFormat(Qt::PlainText); //create a letter label

            s.setNum(8 - i);
            digits[i] = std::make_unique<QLabel>(s, this);
            digits[i]->setTextFormat(Qt::PlainText); //create a digit label

        }

        stockfish_process = new QProcess(this);      //starting the process which will interract with a chess engine
        stockfish_process->start("stockfish_20090216_x64_modern");
        stockfish_process->waitForReadyRead();

        stockfish_process->readAll();

        connect(give_up.get(), &QPushButton::clicked, this, [this]() {
            emit mate();
            });    //if give-up button is pressed
        }
    catch(std::exception& ex) {
        LOG(ERROR) << "Board::Board std::esception:" << ex.what();
    }
}


//this function is drawing squares on the board, which shows where player can move
void Board::create_possible_moves_signs(std::vector<position>& positions) {
    possible_moves_signs.reserve(positions.size());

    for (auto pos : positions) {
        possible_moves_signs.push_back(std::make_unique<QLabel>(this));
        possible_moves_signs.back()->setFrameStyle(QFrame::Box);
        possible_moves_signs.back()->setLineWidth(3);

        if (game_ptr_->Player_color == colors::White) possible_moves_signs.back()->setGeometry((static_cast<int>(pos.column) - 1) * square_size + 30, (8 - pos.row) * square_size, square_size, square_size);
        else possible_moves_signs.back()->setGeometry((8 - static_cast<int>(pos.column)) * square_size + 30, (pos.row - 1) * square_size, square_size, square_size);

        possible_moves_signs.back()->show();
    }
}

//this function clear all squares from the last function, if the move is made, or the move is impossible
void Board::clear_possible_moves_signs() {
    for (auto& pos : possible_moves_signs) {
        pos->hide();
    }
    possible_moves_signs.clear();
}

//function to search the square with the king on the board
square& Board::get_king(colors c) {
    return game_ptr_->find_some_figure([c](square& s) {return s._figure != EMPTY_SQUARE && s._figure->name() == figure_type::King && s._figure->get_color() == c; });
}

//this function gives the current position to chess engine and get the best move from it
std::string Board::get_stockfish_best_move() {

    std::string stockfish_result;


    stockfish_process->write((game_ptr_->string_for_stockfish + "\n").data());
    stockfish_process->waitForBytesWritten();                                //write current position

    stockfish_process->write("go depth ");
    stockfish_process->waitForBytesWritten();

    char hard = '0' + static_cast<char>(game_ptr_->hard_mode);  //how much moves chess will calculate

    std::string hard_str;
    hard_str.push_back(hard);
    hard_str.push_back('\n');

    //    out << hard_str.data();
    stockfish_process->write(hard_str.data());
    stockfish_process->waitForBytesWritten();
    stockfish_process->waitForReadyRead();
    stockfish_result = stockfish_process->readAll().toStdString(); //read all engine input

    int pos = stockfish_result.find("bestmove"); //find the position of the move in the string
    const int offset = QString("bestmove").size() + 1;

    //out << stockfish_result.data();

    std::string result;
    for (int i = 0; i < 5; ++i)
        result.push_back(stockfish_result[pos + offset + i]);

    //    out << result.data() << "\n";
    return result;
}

//this function create single_move structure from the string which chess engine returned
single_move Board::convert_stockfish_move_to_single_move(std::string stockstr) {


    position from = position(columns(stockstr[0] - 'a' + 1), stockstr[1] - '0');
    position where = position(columns(stockstr[2] - 'a' + 1), stockstr[3] - '0');
    figure_type f = at(from)._figure->name();
    single_move res = single_move(f, from, where);

    return res;
}

//set filename of the file, in which we will write moves
void Board::set_write_filename(QString s) {
    filename_to_write = s;

}


//function to set all figures on the board and set them some start conditions
void Board::figures_start_set() {

    //out << "start set begin\n";
    auto shared_ptr = shared_from_this();
    for (int i = 0; i < 8; ++i) {
        pieces_black[i] = std::make_shared<piece>(colors::Black, shared_ptr);         //set pieces
        pieces_black[i]->set_pos(position(columns(i + 1), 7));
        pieces_white[i] = std::make_shared<piece>(colors::White, shared_ptr);
        pieces_white[i]->set_pos(position(columns(i + 1), 2));
    }

    white_king = std::make_shared<king>(colors::White, shared_ptr);
    black_king = std::make_shared<king>(colors::Black, shared_ptr);        //set kings
    white_king->set_pos(position(columns::E, 1));
    black_king->set_pos(position(columns::E, 8));

    rooks_black[0] = std::make_shared<rook>(colors::Black, shared_ptr);
    rooks_black[1] = std::make_shared<rook>(colors::Black, shared_ptr);
    rooks_black[0]->set_pos(position(columns::A, 8));     //set black rooks
    rooks_black[1]->set_pos(position(columns::H, 8));

    rooks_white[0] = std::make_shared<rook>(colors::White, shared_ptr);
    rooks_white[1] = std::make_shared<rook>(colors::White, shared_ptr);
    rooks_white[0]->set_pos(position(columns::A, 1));    //set white rooks
    rooks_white[1]->set_pos(position(columns::H, 1));

    knights_black[0] = std::make_shared<knight>(colors::Black, shared_ptr);
    knights_black[1] = std::make_shared<knight>(colors::Black, shared_ptr);
    knights_black[0]->set_pos(position(columns::B, 8));   //set black knights
    knights_black[1]->set_pos(position(columns::G, 8));

    knights_white[0] = std::make_shared<knight>(colors::White, shared_ptr);
    knights_white[1] = std::make_shared<knight>(colors::White, shared_ptr);   //set white knights
    knights_white[0]->set_pos(position(columns::B, 1));
    knights_white[1]->set_pos(position(columns::G, 1));

    bishops_black[0] = std::make_shared<bishop>(colors::Black, shared_ptr);
    bishops_black[1] = std::make_shared<bishop>(colors::Black, shared_ptr);
    bishops_black[0]->set_pos(position(columns::C, 8));  //set black bishops
    bishops_black[1]->set_pos(position(columns::F, 8));

    bishops_white[0] = std::make_shared<bishop>(colors::White, shared_ptr);
    bishops_white[1] = std::make_shared<bishop>(colors::White, shared_ptr);  //set white bishops
    bishops_white[0]->set_pos(position(columns::C, 1));
    bishops_white[1]->set_pos(position(columns::F, 1));


    queen_black = std::make_shared<queen>(colors::Black, shared_ptr);
    queen_black->set_pos(position(columns::D, 8));
    queen_white = std::make_shared<queen>(colors::White, shared_ptr);       //set queens
    queen_white->set_pos(position(columns::D, 1));

    //game_ptr_->traverse_board([](square& s) {s = { std::shared_ptr<figure>(nullptr),0,0 }; }); //clear board
    LOG(INFO) << "game_ptr_->traverse_board";
    //clear additional figures vector
    for (auto& i : odd_figures) {
        i->hide();
    }
    if (odd_figures.size() != 0)
        odd_figures.clear();


    /*set all figures positions*/
    board[0][4] = { black_king,0,0 };
    black_king->set_pos(position(columns::E, 8));

    board[7][4] = { white_king,0,0 };
    white_king->set_pos(position(columns::E, 1));

    board[0][3] = { queen_black,0,0 };
    board[7][3] = { queen_white,0,0 };
    queen_black->set_pos(position(columns::D, 8));
    queen_white->set_pos(position(columns::D, 1));

    board[0][0] = { rooks_black[0],0,0 };
    board[0][7] = { rooks_black[1],0,0 };
    rooks_black[0]->set_pos(position(columns::A, 8));
    rooks_black[1]->set_pos(position(columns::H, 8));

    board[7][0] = { rooks_white[0],0,0 };
    board[7][7] = { rooks_white[1],0,0 };
    rooks_white[0]->set_pos(position(columns::A, 1));
    rooks_white[1]->set_pos(position(columns::H, 1));


    board[0][1] = { knights_black[0],0,0 };
    board[0][6] = { knights_black[1],0,0 };
    knights_black[0]->set_pos(position(columns::B, 8));
    knights_black[1]->set_pos(position(columns::G, 8));

    board[7][1] = { knights_white[0],0,0 };
    board[7][6] = { knights_white[1],0,0 };
    knights_white[0]->set_pos(position(columns::B, 1));
    knights_white[1]->set_pos(position(columns::G, 1));

    board[0][2] = { bishops_black[0],0,0 };
    board[0][5] = { bishops_black[1],0,0 };
    bishops_black[0]->set_pos(position(columns::C, 8));
    bishops_black[1]->set_pos(position(columns::F, 8));


    board[7][2] = { bishops_white[0],0,0 };
    board[7][5] = { bishops_white[1],0,0 };
    bishops_white[0]->set_pos(position(columns::C, 1));
    bishops_white[1]->set_pos(position(columns::F, 1));

    for (int i = 0; i < 8; ++i) {
        board[1][i] = { pieces_black[i],0,0 };
        board[6][i] = { pieces_white[i],0,0 };
        pieces_black[i]->set_pos(position(columns(i + 1), 7));
        pieces_white[i]->set_pos(position(columns(i + 1), 2));
    }
    LOG(INFO) << "Set pos to all" << (game_ptr_ == nullptr);
    //null figures moves (if this is not a first game)
    game_ptr_->traverse_board([](square& s) {
        if (s._figure != EMPTY_SQUARE)
            s._figure->null_count_moves();
        });

    //mark all squares that figures attack
    mark_all();

    //white begins
    game_ptr_->now_move = colors::White;

    //if the first move is by chess engine
    if (game_ptr_->Player_color == colors::Black && game_ptr_->get_state() == state::STOCKFISH) {
        std::string move = get_stockfish_best_move();
        single_move move_struct = convert_stockfish_move_to_single_move(move);
        make_move(move_struct.get_from(), move_struct.get_where(), true, ' ');
        //write_move(move_struct,((Game::now_move == Black) ? get_king(Game::now_move).attacking_white_figures : get_king(Game::now_move).attacking_black_figures) != 0,check_for_mate(),Game::now_move == White);
    }


}


//function to say the main class that the board is closed
void Board::closeEvent(QCloseEvent* e) {
    Q_UNUSED(e);

    emit windowClosed();
}

//function to redraw board
void Board::paintEvent(QPaintEvent* e) {
    Q_UNUSED(e);
    draw();
}



//function to draw board and show all figures
void Board::draw() {

    QPainter qp(this);

    bool black = false; //bool variable to check if need to draw black or white square

    square_size = (this->height() - 30) / 8;

    give_up->setGeometry(8 * square_size + 30, 3 * square_size, square_size, square_size);
    for (int i = 0; i < 8; ++i) {
        if (i % 2 == 0) black = false;
        else black = true;
        for (int j = 0; j < 8; ++j) {
            board[i][j].square_color = (black) ? colors::Black : colors::White;
            qp.setBrush(QBrush(black ? Qt::gray : Qt::yellow));
            qp.drawRect(30 + j * square_size, i * square_size, square_size, square_size);
            black = !black;
        }
    }

    for (int i = 0; i < 8; ++i) {
        int letters_x = game_ptr_->Player_color == colors::White ? 50 + i * square_size : 50 + (7 - i) * square_size;
        int letters_y = square_size * 8;
        letters[i]->setGeometry(letters_x, letters_y, 30, 30);
        letters[i]->show();

        int digits_x = 20;
        int digits_y = game_ptr_->Player_color == colors::White ? i * square_size : (7 - i) * square_size;
        digits[i]->setGeometry(digits_x, digits_y, 30, 30);
        digits[i]->show();
    }
    auto& b = board;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (b[i][j]._figure != EMPTY_SQUARE) {
                int figure_x = game_ptr_->Player_color == colors::White ? j * square_size + 30 : (7 - j) * square_size + 30;
                int figure_y = game_ptr_->Player_color == colors::White ? i * square_size : (7 - i) * square_size;
                b[i][j]._figure->setGeometry(figure_x, figure_y, square_size, square_size);
                b[i][j]._figure->show();
            }
        }
    }


}

//function to mark all squares that all figures attack
void Board::mark_all() {
    game_ptr_->traverse_board([](square& s) {
        if (s._figure != EMPTY_SQUARE)
            s._figure->touch_attacking_squares(MARK_ATTACKING_SQUARES);
        });
}

//function to unmark all squares that all figures attack
void Board::unmark_all() {
    game_ptr_->traverse_board([](square& s) {
        if (s._figure != EMPTY_SQUARE)
            s._figure->touch_attacking_squares(UNMARK_ATTACKING_SQUARES);
        });
}

//function to check if that's mate now
bool Board::check_for_mate() {
    bool is_mate = true;


    if (get_king(game_ptr_->now_move)._figure->possible_squares().size() != 0) { /*out << "check for mate end,returning false\n";*/ return false; }

    colors c = game_ptr_->now_move;
    if (c == colors::White && get_king(game_ptr_->now_move).attacking_black_figures == 0) { /*out << "check for mate end,returning false\n";*/ return false; }
    if (c == colors::Black && get_king(game_ptr_->now_move).attacking_white_figures == 0) { /*out << "check for mate end,returning false\n";*/return false; }

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            if (board[i][j]._figure != nullptr) {
                if (board[i][j]._figure->name() != figure_type::King && board[i][j]._figure->get_color() == game_ptr_->now_move) {
                    auto squares = board[i][j]._figure->possible_squares();
                    position from = board[i][j]._figure->get_pos();
                    for (auto release_pos : squares) {

                        unmark_all();
                        position by_pass;
                        for (int k = 0; k < 8; ++k)
                            for (int l = 0; l < 8; ++l)
                                if (board[k][l]._figure == nullptr)
                                    by_pass = position(columns(l - 1), 8 - k);

                        figure* fig_by_pass{nullptr};

                        bool is_by_pass = false;
                        if (board[i][j]._figure->name() == figure_type::Piece && from.row != release_pos.row && from.column != release_pos.column && at(release_pos)._figure == nullptr) { //taking by pass
                            is_by_pass = true;
                            if (from.column != columns::A && at(columns(static_cast<int>(from.column) - 1), from.row)._figure == Board::last_move) { //check if piece to be taken is from left
                                bool not_empty = (at(columns(static_cast<int>(from.column) - 1), from.row)._figure != nullptr); //not empty square
                                by_pass = position(columns(static_cast<int>(from.column) - 1), from.row);
                                if (not_empty && at(columns(static_cast<int>(from.column) - 1), from.row)._figure == Board::last_move) {
                                    fig_by_pass = at(columns(static_cast<int>(from.column) - 1), from.row)._figure;
                                    at(columns(static_cast<int>(from.column) - 1), from.row)._figure->hide();
                                    at(columns(static_cast<int>(from.column) - 1), from.row)._figure = nullptr;
                                }
                            }
                            if (from.column != columns::H && at(columns(static_cast<int>(from.column) + 1), from.row)._figure == Board::last_move) { //check if piece to be taken is from right
                                bool not_empty = (board[8 - from.row][static_cast<int>(from.column) - 1 + 1]._figure != nullptr);
                                by_pass = position(columns(static_cast<int>(from.column) + 1), from.row);
                                if (not_empty) {
                                    fig_by_pass = at(columns(static_cast<int>(from.column) + 1), from.row)._figure;
                                    at(columns(static_cast<int>(from.column) + 1), from.row)._figure->hide();
                                    at(columns(static_cast<int>(from.column) + 1), from.row)._figure = nullptr;
                                }
                            }
                        }

                        auto temp = at(release_pos)._figure;
                        at(release_pos)._figure = at(from)._figure;
                        at(release_pos)._figure->set_pos(release_pos);
                        if (is_by_pass) at(by_pass)._figure = nullptr;
                        at(from)._figure = nullptr;
                        mark_all();

                        if ((c == colors::White && get_king(colors::White).attacking_black_figures == 0) || (c == colors::Black && get_king(colors::Black).attacking_white_figures == 0)) {
                            is_mate = false;

                        }

                        unmark_all();
                        at(from)._figure = at(release_pos)._figure;
                        if (is_by_pass) at(by_pass)._figure = fig_by_pass;
                        at(release_pos)._figure = temp;
                        at(from)._figure->set_pos(from);
                        mark_all();
                        if (!is_mate) return false;

                    }
                }
            }
        }
    }


    return is_mate;
}


//these two functions returns reference to square at given position
square& Board::at(position p) {
    return board[8 - p.row][static_cast<int>(p.column) - 1];
    //return Game::board[p.row - 1][8 - p.c];
}

square& Board::at(columns c, std::size_t row) {
    return board[8 - row][static_cast<int>(c) - 1];
    //return Game::board[row - 1][8 - c];
}


//board dtor
Board::~Board() {

    //there we just finish the process which interract with chess engine
    stockfish_process->write("quit\n");
    stockfish_process->waitForBytesWritten();
    stockfish_process->waitForFinished(100);


}

//this function is called when piece reach 1-st or 8-s row, and player should choose new figure
void Board::choose_figure_to_transform(position where) {


    //show all buttons with possible figures
    figure_choose = new QWidget;
    QHBoxLayout* hb = new QHBoxLayout(figure_choose);
    QPushButton* queen = new QPushButton(figure_choose);
    if (where.row == 8) queen->setIcon(QIcon(":\\pics\\figures\\wQ.png"));
    else queen->setIcon(QIcon(":\\pics\\figures\\bQ.png"));

    QPushButton* rook = new QPushButton(figure_choose);
    if (where.row == 8) rook->setIcon(QIcon(":\\pics\\figures\\wR.png"));
    else rook->setIcon(QIcon(":\\pics\\figures\\bR.png"));

    QPushButton* bishop = new QPushButton(figure_choose);
    if (where.row == 8) bishop->setIcon(QIcon(":\\pics\\figures\\wB.png"));
    else bishop->setIcon(QIcon(":\\pics\\figures\\bB.png"));

    QPushButton* knight = new QPushButton(figure_choose);
    if (where.row == 8) knight->setIcon(QIcon(":\\pics\\figures\\wN.png"));
    else knight->setIcon(QIcon(":\\pics\\figures\\bN.png"));

    hb->setSpacing(5);
    hb->addWidget(queen);
    hb->addWidget(rook);
    hb->addWidget(bishop);
    hb->addWidget(knight);
    queen->show();
    rook->show();
    bishop->show();
    knight->show();
    figure_choose->setLayout(hb);
    figure_choose->setGeometry(this->width() / 2, this->height(), 640, 80);
    figure_choose->show();

    this->setEnabled(false); //board is not enabled while choosing

    where_to_transform = where; //fix transform position

    connect(queen, &QPushButton::clicked, this, [this]() {transform_figure = figure_type::Queen; transform(); });
    connect(rook, &QPushButton::clicked, this, [this]() {transform_figure = figure_type::Rook; transform(); });
    connect(bishop, &QPushButton::clicked, this, [this]() {transform_figure = figure_type::Bishop; transform(); });
    connect(knight, &QPushButton::clicked, this, [this]() {transform_figure = figure_type::Knight; transform(); });

}

//function to transform piece to other figure
void Board::transform() {

    if (figure_choose) {
        figure_choose->hide();
        figure_choose->close(); //hide label with figures buttons
    }

    this->setEnabled(true);
    unmark_all();


    char transform_figure_first_symbol = 'q'; //symbol for writing to file

    at(where_to_transform)._figure->hide();
    at(where_to_transform)._figure = nullptr;  //hide piece

    switch (transform_figure) { //depends on player choose, set the new figure on the board
    case figure_type::Queen:
        transform_figure_first_symbol = 'q';
        odd_figures.push_back(std::make_shared<queen>(game_ptr_->now_move, shared_from_this()));
        break;
    case figure_type::Rook:
        transform_figure_first_symbol = 'r';
        odd_figures.push_back(std::make_shared<rook>(game_ptr_->now_move, shared_from_this()));
        break;
    case figure_type::Knight:
        transform_figure_first_symbol = 'k';
        odd_figures.push_back(std::make_shared<knight>(game_ptr_->now_move, shared_from_this()));
        break;
    case figure_type::Bishop:
        transform_figure_first_symbol = 'b';
        odd_figures.push_back(std::make_shared<bishop>(game_ptr_->now_move, shared_from_this()));
        break;
    default:
        break;
    }


    at(where_to_transform)._figure = odd_figures.back().get();
    at(where_to_transform)._figure->set_pos(where_to_transform);

    //set geometry of the new figure
    if (game_ptr_->Player_color == colors::White) at(where_to_transform)._figure->setGeometry((static_cast<int>(where_to_transform.column) - 1) * square_size, (8 - where_to_transform.row) * square_size, square_size, square_size);
    else at(where_to_transform)._figure->setGeometry((8 - static_cast<int>(where_to_transform.column)) * square_size, (where_to_transform.row - 1) * square_size, square_size, square_size);

    at(where_to_transform)._figure->show();
    mark_all();

    //check if there is mate or check after transformation
    bool is_mate = check_for_mate();
    bool is_check = ((game_ptr_->now_move == colors::Black) ? get_king(game_ptr_->now_move).attacking_white_figures : get_king(game_ptr_->now_move).attacking_black_figures) != 0;

    //thread for write move to file
    std::thread write_move_to_file([this, is_check, is_mate, transform_figure_first_symbol]() {
        write_move(single_move(at(where_to_transform)._figure->name(), handled, where_to_transform, false), is_check, is_mate, game_ptr_->now_move == colors::White, true, transform_figure_first_symbol);
        });
    write_move_to_file.detach();

    //move is made, so clear squares signs
    if (possible_moves_signs.size() != 0) clear_possible_moves_signs();
    was_pressed = false;


    if (is_mate)  emit mate();
}


void Board::mousePressEvent(QMouseEvent* e) {

    if (was_pressed) {
        //if player has already pressed to some figure, then return and go to mouse release event
        return;
    }


    //set handled mouse position, depends on color
    handled.column = columns((e->pos().x() - 30) / get_square_size() + 1);
    handled.row = 8 - (e->pos().y()) / get_square_size();


    if (game_ptr_->Player_color == colors::Black) {
        handled.column = columns(8 - static_cast<int>(columns((e->pos().x() - 30) / get_square_size())));
        handled.row = (e->pos().y()) / get_square_size() + 1;

    }




    if (at(handled)._figure != EMPTY_SQUARE && at(handled)._figure->get_color() == game_ptr_->now_move) {
        std::vector<position> pos = at(handled)._figure->possible_squares();  //create possible squares signs
        if (pos.size() != 0) {
            create_possible_moves_signs(pos);
            if (!was_pressed) was_pressed = true;
        }
    }



}

//function to make move from "from" position, to "release_pos" position, checking if this is stockfish's move, and if this is piece transformation
void Board::make_move(position from, position release_pos, bool stockfish, char transform_figure) {
   // LOG(INFO) << "make_move";
    if (possible_moves_signs.size() != 0 && (from.column != release_pos.column || from.row != release_pos.row)) clear_possible_moves_signs();

    auto fig = at(from); //get figure from square, which is handled
    if (fig._figure == nullptr) { throw std::exception(); }  //empty square was handled

    //get figure's possible moves, and check if there is our move
    auto squares = fig._figure->possible_squares();
    auto find_square = std::find(std::begin(squares), std::end(squares), release_pos);

    if (find_square == squares.end()) {/*out << "impossible move\n";*/ throw std::exception(); } //impossible move or color to move took is incorrect
    if (at(from)._figure->get_color() != game_ptr_->now_move) {/*out << "incorrect color\n";*/throw std::exception(); }

    unmark_all();//unmarking all the attacking squares
    //LOG(INFO) << "After unmark";
    //check if our move is taking by pass by piece
    position by_pass;
    figure* fig_by_pass = at(by_pass)._figure;
    if (fig._figure->name() == figure_type::Piece && from.row != release_pos.row && from.column != release_pos.column && at(release_pos)._figure == nullptr) { //taking by pass
        if (from.column != columns::A) { //check if piece to be taken is from left
            bool not_empty = (at(columns(static_cast<int>(from.column) - 1), from.row)._figure != EMPTY_SQUARE); //not empty square
            by_pass = position(columns(static_cast<int>(from.column) - 1), from.row);
            if (not_empty && at(columns(static_cast<int>(from.column) - 1), from.row)._figure == Board::last_move) { //then that is taking by pass
                fig_by_pass = at(columns(static_cast<int>(from.column) - 1), from.row)._figure;
                at(columns(static_cast<int>(from.column) - 1), from.row)._figure->hide();
                at(columns(static_cast<int>(from.column) - 1), from.row)._figure = EMPTY_SQUARE;
            }
        }

        if (from.column != columns::H && at(columns(static_cast<int>(from.column) + 1), from.row)._figure == Board::last_move) { //check if piece to be taken is from right
            bool not_empty = (at(columns(static_cast<int>(from.column) + 1), from.row)._figure != EMPTY_SQUARE);
            by_pass = position(columns(static_cast<int>(from.column) + 1), from.row);
            if (not_empty && at(columns(static_cast<int>(from.column) + 1), from.row)._figure == Board::last_move) { //then that is taking by pass
                fig_by_pass = at(columns(static_cast<int>(from.column) + 1), from.row)._figure;
                at(columns(static_cast<int>(from.column) + 1), from.row)._figure->hide();
                at(columns(static_cast<int>(from.column) + 1), from.row)._figure = nullptr;
            }
        }
    }
    //LOG(INFO) << "before bool taking";
    bool taking = at(release_pos)._figure != nullptr;

    //make move
    figure* temp = at(release_pos)._figure;

    //check if the move is king castling
    bool castling_short = (fig._figure->name() == figure_type::King && release_pos.row == from.row && static_cast<int>(release_pos.column) - static_cast<int>(from.column) == 2);
    bool castling_long = (fig._figure->name() == figure_type::King && release_pos.row == from.row && static_cast<int>(release_pos.column) - static_cast<int>(from.column) == -2);

    if (at(release_pos)._figure != nullptr) at(release_pos)._figure->hide();
    at(release_pos)._figure = at(from)._figure;
    at(release_pos)._figure->set_pos(release_pos);
    if (game_ptr_->Player_color == colors::White) at(release_pos)._figure->setGeometry((static_cast<int>(release_pos.column) - 1) * square_size, (8 - release_pos.row) * square_size + 30, square_size, square_size);
    else at(release_pos)._figure->setGeometry((8 - static_cast<int>(release_pos.column) + 1) * square_size, (release_pos.row - 1) * square_size, square_size, square_size);
    at(from)._figure = nullptr;

    //LOG(INFO) << "before if (castling_short) {";
    //if the move is castling, then also move rook to needed position
    if (castling_short) {

        auto rook = at(columns(static_cast<int>(release_pos.column) + 1), release_pos.row);

        at(columns(static_cast<int>(release_pos.column) + 1), release_pos.row)._figure->set_pos(position(columns(static_cast<int>(rook._figure->get_pos().column) - 2), rook._figure->get_pos().row));
        at(columns(static_cast<int>(release_pos.column) - 1), release_pos.row)._figure = at(columns(static_cast<int>(release_pos.column) + 1), release_pos.row)._figure;
        at(columns(static_cast<int>(release_pos.column) + 1), release_pos.row)._figure = nullptr;
        if (game_ptr_->Player_color == colors::White) at(columns(static_cast<int>(release_pos.column) - 1), release_pos.row)._figure->setGeometry((static_cast<int>(release_pos.column) - 1 - 1) * square_size, (8 - release_pos.row) * square_size + 30, square_size, square_size);
        else at(columns(static_cast<int>(release_pos.column) - 1), release_pos.row)._figure->setGeometry((8 - static_cast<int>(release_pos.column)) * square_size, (release_pos.row - 1) * square_size + 30, square_size, square_size);
    }
    //LOG(INFO) << "before if (castling_long) {";
    if (castling_long) {
        //auto rook = at(columns(release_pos.c - 2),release_pos.row);
        at(columns(static_cast<int>(release_pos.column) - 2), release_pos.row)._figure->set_pos(position(columns(static_cast<int>(release_pos.column) + 1), release_pos.row));
        at(columns(static_cast<int>(release_pos.column) + 1), release_pos.row)._figure = at(columns(static_cast<int>(release_pos.column) - 2), release_pos.row)._figure;
        at(columns(static_cast<int>(release_pos.column) - 2), release_pos.row)._figure = nullptr;
        if (game_ptr_->Player_color == colors::White) at(columns(static_cast<int>(release_pos.column) + 1), release_pos.row)._figure->setGeometry((static_cast<int>(release_pos.column) + 1 - 1) * square_size, (8 - release_pos.row) * square_size, square_size, square_size);
        else at(columns(static_cast<int>(release_pos.column) + 1), release_pos.row)._figure->setGeometry((8 - static_cast<int>(release_pos.column) + 1) * square_size, (release_pos.row - 1) * square_size, square_size, square_size);
    }
    //set all attacking squares for all figures
    mark_all();

    //check whether the king is attacked after the move, if he is, then return moving figures to the past position, and return from function
    colors c = game_ptr_->now_move;

    if ((c == colors::Black && get_king(colors::Black).attacking_white_figures != 0) || (c == colors::White && get_king(colors::White).attacking_black_figures != 0)) {

        unmark_all();
        at(from)._figure = at(release_pos)._figure;
        at(by_pass)._figure = fig_by_pass;
        if (at(by_pass)._figure != nullptr) at(by_pass)._figure->show();
        at(release_pos)._figure = temp;
        if (at(release_pos)._figure != nullptr) at(release_pos)._figure->show();
        at(from)._figure->set_pos(from);
        if (game_ptr_->Player_color == colors::White) at(from)._figure->setGeometry((static_cast<int>(from.column) - 1) * square_size + 30, (8 - from.row) * square_size, square_size, square_size);
        else at(from)._figure->setGeometry((8 - static_cast<int>(from.column)) * square_size, (from.row - 1) * square_size + 30, square_size, square_size);
        mark_all();

        LOG(ERROR) << "king is attacked\n";
        throw std::exception();
    }

    //if we are here, then move is correct, changing color, which is move now, and increment the count of moves of figure
    at(release_pos)._figure->increment_moves();




    //LOG(INFO) << "before bool piece_transformation";
    bool piece_transformation = at(release_pos)._figure->name() == figure_type::Piece && (release_pos.row == 8 || release_pos.row == 1);

    if (piece_transformation) {
        if (stockfish == false) {
            choose_figure_to_transform(release_pos);

        }
        else { //if this is stockfish move
            where_to_transform = release_pos;
            switch (transform_figure) {
            case 'q':
                transform_figure = static_cast<char>(figure_type::Queen);
                transform();
                break;
            case 'r':
                transform_figure = static_cast<char>(figure_type::Rook);
                transform();
                break;
            case 'n':
                transform_figure = static_cast<char>(figure_type::Knight);
                transform();
                break;
            case 'b':
                transform_figure = static_cast<char>(figure_type::Bishop);
                transform();
                break;
            default:
                break;
            }
        }
    }

    game_ptr_->now_move = (game_ptr_->now_move == colors::White) ? colors::Black : colors::White;

    last_move = at(release_pos)._figure;

    std::string stock = single_move(at(release_pos)._figure->name(), from, release_pos, taking).to_string_for_stockfish(piece_transformation ? transform_figure : ' ');

    //add last move to common string, which will be given to chess engine
    game_ptr_->string_for_stockfish += std::string(stock.data());
    game_ptr_->string_for_stockfish += " ";




    bool is_check = ((game_ptr_->now_move == colors::Black) ? get_king(game_ptr_->now_move).attacking_white_figures : get_king(game_ptr_->now_move).attacking_black_figures) != 0;
    if (is_check) dynamic_cast<king*>((get_king(game_ptr_->now_move)._figure))->set_checked();

    bool is_mate = check_for_mate();

    if (game_ptr_->now_move == colors::White) game_ptr_->count_move++;

    if (!piece_transformation) {
        //launching independence thread, which will write last move to the file
        std::thread write_move_to_file([this, from, release_pos, taking, is_check, is_mate]() {
            write_move(single_move(at(release_pos)._figure->name(), from, release_pos, taking), is_check, is_mate, game_ptr_->now_move == colors::White, false);
            });
        write_move_to_file.detach();
    }
    //move is made, so clear squares signs
    if (possible_moves_signs.size() != 0) clear_possible_moves_signs();
    was_pressed = false;

    if (is_mate) {
        emit mate();
    }
    if (check_for_draw()) emit draw_signal();
    //LOG(INFO) << "make move end";
}

//function that handle mouse release event
void Board::mouseReleaseEvent(QMouseEvent* e) {
    LOG(INFO) << "mouseReleaseEvent begin";
    if (!was_pressed) return; //if mouse was not pressed on right square

    position release_pos;

    release_pos.column = columns((e->pos().x() - 30) / get_square_size() + 1);  //get release mouse position
    release_pos.row = 8 - (e->pos().y()) / get_square_size();

    if (game_ptr_->Player_color == colors::Black) {
        release_pos.column = columns(8 - static_cast<int>(release_pos.column) + 1);  //get release mouse position if player color is black
        release_pos.row = 8 - release_pos.row + 1;
    }


    //make move, and if it is incorrect, catch an exception and return from function
    LOG(INFO) << "before try";
    try {
        make_move(handled, release_pos, PLAYER_MOVE, ' ');

    }
    catch (const std::exception& ex) {
        if (handled.column != release_pos.column || handled.row != release_pos.row) {  //if mouse was not released on the same square, where it was pressed
            was_pressed = false;
            if (possible_moves_signs.size() != 0) clear_possible_moves_signs();
        }
        return;
    }
    LOG(INFO) << "After catch";
    //if we are here, then the move was correct, and now it's time to chess engine to move (if player do not play with himself)
    if (game_ptr_->get_state() == state::STOCKFISH) {
        give_up->setEnabled(false);
        LOG(INFO) << game_ptr_->string_for_stockfish;
        std::string stockfish_result = get_stockfish_best_move();


        single_move sm = convert_stockfish_move_to_single_move(stockfish_result);
        sm.get_from().print();
        sm.get_where().print();
        try {
            make_move(sm.get_from(), sm.get_where(), STOCKFISH_MOVE, stockfish_result[4]);
        }
        catch(std::exception& ex) {
            LOG(ERROR) << "Stockfish move ex" << ex.what();
        }

        give_up->setEnabled(true);
        //write_move(sm,((Game::now_move == Black) ? get_king(Game::now_move).attacking_white_figures : get_king(Game::now_move).attacking_black_figures) != 0,check_for_mate(),Game::now_move == White);
    }

    LOG(INFO) << "mouseReleaseEvent end";
}


//function to write move to file
void Board::write_move(const single_move& s, bool is_check, bool is_mate, bool is_Black, bool transform, char transform_first_symbol) {
    std::string string_move = s.to_str(is_check, is_mate, is_Black, transform, transform_first_symbol);
    if (filename_to_write != "") {

        QFile file_to_write(filename_to_write);
        file_to_write.open(QIODevice::Append);
        QTextStream out(&file_to_write);
        if (game_ptr_->now_move == colors::Black) out << game_ptr_->count_move << ". ";
        out << string_move.data();
        file_to_write.close();

    }
}

//calculate how much material left by the side, which should move now
std::size_t Board::how_much_material_left() {
    std::size_t result = 0;
    game_ptr_->traverse_board([&result, this](square& s) {
        if (s._figure != EMPTY_SQUARE && s._figure->get_color() == game_ptr_->now_move)
            result += s._figure->get_cost();
        });
    return result;
}

//check if there is only light figures left
bool Board::only_light_figures_left() {
    return game_ptr_->check_some_board_condition([this](square& s) {
        return s._figure != EMPTY_SQUARE && s._figure->get_color() == game_ptr_->now_move && s._figure->get_weight() == figure_weight::HEAVY;
        });
}

//check if there is only two bishops and king left
bool Board::two_bishops() {
    return game_ptr_->check_some_board_condition([this](square& s) {return s._figure != EMPTY_SQUARE && s._figure->get_color() == game_ptr_->now_move && s._figure->name() != figure_type::Bishop && s._figure->name() != figure_type::King; });
}


//check if the is only two kings left
bool Board::only_two_kings() {
    return game_ptr_->check_some_board_condition([](square& s) {return s._figure != EMPTY_SQUARE && s._figure->name() != figure_type::King; });
}

//check if there is stalemate
bool Board::stalemate() {


    return game_ptr_->check_some_board_condition([this](square& s) {return s._figure != EMPTY_SQUARE && s._figure->name() == figure_type::King && ((game_ptr_->now_move == colors::Black || s.attacking_white_figures != 0) || (game_ptr_->now_move == colors::White || s.attacking_black_figures != 0)); })
        &&
        game_ptr_->check_some_board_condition([this](square& s) {return s._figure != EMPTY_SQUARE && s._figure->name() != figure_type::King && s._figure->get_color() == game_ptr_->now_move && s._figure->possible_squares().size() != 0; });

}

//check if there is no pieces
bool Board::no_pieces() {
    return game_ptr_->check_some_board_condition([this](square& s) {
        return (s._figure != EMPTY_SQUARE && s._figure->name() == figure_type::Piece && s._figure->get_color() == game_ptr_->now_move);
        });
}


//function to check if there is draw
//P.S. this function do not work 100% correct, author develops it now. Play until the win or lost, like a  true warrior! :)
bool Board::check_for_draw() {
    if (stalemate() || only_two_kings())
        return true;

    if (!two_bishops() && no_pieces() && only_light_figures_left() && how_much_material_left() <= 6)
        return true;
    return false;
}
