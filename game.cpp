#include "game.h"
#include "figure.h"
#include "board.h"

#include <QTextStream>

state Game::st = STOCKFISH;
std::array<std::array<square,8>,8> Game::board = {
};

hard_modes Game::hard_mode = EASY;

colors Game::now_move = White;

colors Game::Player_color = White;

std::string Game::string_for_stockfish = "position startpos moves ";

std::size_t Game::count_move = 0;


void traverse_board(std::function<void(square&)> func_to_traverse) {
    for(int i = 0;i<8;++i) {
        for(int j = 0;j<8;++j) {
            func_to_traverse(Game::board[i][j]);
        }
    }
}

square& find_some_figure(std::function<bool(square&)> chech_figure) {
    for(int i = 0;i<8;++i) {
        for(int j = 0;j<8;++j) {
            if(chech_figure(Game::board[i][j]))
                return Game::board[i][j];
        }
    }
    square s;
    s._figure = nullptr;
    return s;
}

bool check_some_board_condition(std::function<bool(square&)> check_false) {
    for(int i = 0;i<8;++i) {
        for(int j = 0;j<8;++j) {
            if(check_false(Game::board[i][j]))
                return false;
        }
    }
    return true;
}

Game::Game(QWidget *parent) : QWidget(parent)
{
    setFixedSize(800,500);
    this->setWindowTitle("StockChess 2021");
    play_btn = new QPushButton("Play");
    play_btn->setIcon(QIcon("pics\\play_icon.jpg"));


    settings_btn = new QPushButton("Settings");
    settings_btn->setIcon(QIcon("pics\\setting_icon.png"));
    exit_btn = new QPushButton("Exit");
    exit_btn->setIcon(QIcon("pics\\exit_icon.png"));

    return_to_main_menu = new QPushButton("Return to menu");
    return_to_main_menu->setIcon(QIcon("pics\\menu_icon.png"));

    main_vb = new QVBoxLayout(this);



    write_games_settings = new QComboBox(this);

    play_mode_setting = new QComboBox(this);

    hard_mode_setting = new QComboBox(this);

    QStringList lst = {"Easy","Medium","Hard","Expert"};
    hard_mode_setting->addItems(lst);
    hard_mode_setting->hide();

    lst = QStringList{"Write all games","Write only last game","Do not write games"};
    write_games_settings->addItems(lst);
    write_games_settings->hide();

    lst = QStringList{"play with computer", "play against yourself"};
    play_mode_setting->addItems(lst);
    play_mode_setting->hide();

    final_lbl = new QLabel("",this);
    final_lbl->hide();

    write_games_lbl = new QLabel("How do you like to write your games",this);
    write_games_lbl->setAlignment(Qt::AlignCenter);
    play_mode_lbl = new QLabel("Play with chess engine or with yourself",this);
    play_mode_lbl->setAlignment(Qt::AlignCenter);
    hard_mode_lbl = new QLabel("Hard mode",this);
    hard_mode_lbl->setAlignment(Qt::AlignCenter);
    write_games_lbl->hide();
    play_mode_lbl->hide();
    hard_mode_lbl->hide();

    color_choose_lbl = new QLabel(this);
    color_choose_lbl->setText("Choose a color you want to play");
    color_choose_lbl->hide();

    white_choise = new QPushButton("White");
    white_choise->setIcon(QIcon("pics\\figures\\wN.png"));
    white_choise->hide();

    black_choise = new QPushButton("Black");
    black_choise->setIcon(QIcon("pics\\figures\\bN.png"));
    black_choise->hide();

    random_choise = new QPushButton("Random color");
    random_choise->setIcon(QIcon("pics\\black_white_knight.png"));
    random_choise->hide();

    connect(exit_btn,&QPushButton::clicked,qApp,&QApplication::quit);
    connect(play_btn,&QPushButton::clicked,this,&Game::choose_color);
    connect(settings_btn,&QPushButton::clicked,this,&Game::show_settings);

    how_to_white = write_all;

    hard_mode = EASY;

    show_menu();

}

Game::~Game() {
    delete play_btn;
    delete exit_btn;
    delete settings_btn;
    delete final_lbl;
    delete write_games_settings;
    delete play_mode_setting;
    delete b;
}


void Game::choose_color() {

    //out << "color begin\n";
    srand(time(NULL));
    main_vb->removeWidget(play_btn);
    main_vb->removeWidget(settings_btn);
    main_vb->removeWidget(final_lbl);
    final_lbl->hide();
    play_btn->hide();
    settings_btn->hide();
    main_vb->insertWidget(0,white_choise);
    main_vb->insertWidget(0,black_choise);
    main_vb->insertWidget(0,random_choise);
    main_vb->insertWidget(0,color_choose_lbl,1,Qt::AlignCenter);
    main_vb->insertWidget(4,return_to_main_menu);
    return_to_main_menu->show();
    color_choose_lbl->show();
    white_choise->show();
    black_choise->show();
    random_choise->show();

    connect(white_choise,&QPushButton::clicked,this,[this](){Game::Player_color = White; play();});
    connect(black_choise,&QPushButton::clicked,this,[this](){Game::Player_color = Black; play();});
    connect(random_choise,&QPushButton::clicked,this,[this](){
        if(rand() % 2 == 0) {
            Game::Player_color = White;
        }
        else {
            Game::Player_color = Black;
        }
        play();
    });
    connect(return_to_main_menu,&QPushButton::clicked,this,&Game::show_menu);
    //out << "color end\n";
}





void Game::show_menu() {



    //out << "menu begin\n";

    return_to_main_menu->hide();

    main_vb->removeWidget(hard_mode_lbl);
    main_vb->removeWidget(play_mode_lbl);
    main_vb->removeWidget(write_games_lbl);
    main_vb->removeWidget(black_choise);
    main_vb->removeWidget(white_choise);
    main_vb->removeWidget(random_choise);
    main_vb->removeWidget(return_to_main_menu);
    main_vb->removeWidget(color_choose_lbl);
    main_vb->removeWidget(final_lbl);

    hard_mode_lbl->hide();
    play_mode_lbl->hide();
    write_games_lbl->hide();
    black_choise->hide();
    white_choise->hide();
    random_choise->hide();
    return_to_main_menu->hide();
    color_choose_lbl->hide();
    final_lbl->hide();

    main_vb->removeWidget(write_games_settings);
    write_games_settings->hide();
    main_vb->removeWidget(return_to_main_menu);
    main_vb->removeWidget(play_mode_setting);
    play_mode_setting->hide();

    main_vb->removeWidget(hard_mode_setting);
    hard_mode_setting->hide();


    QVBoxLayout *vb = new QVBoxLayout();
    play_btn->setText("Play");
    play_btn->setEnabled(true);
    settings_btn->setEnabled(true);
    exit_btn->setEnabled(true);

    play_btn->show();
    settings_btn->show();
    exit_btn->show();

    vb->setSpacing(5);
    vb->addWidget(play_btn,2);
    vb->addWidget(settings_btn,2);
    vb->addWidget(exit_btn,2);
    main_vb->addLayout(vb,1);
    setLayout(main_vb);


    //out << "menu end\n";
}

void Game::show_settings() {


    play_btn->hide();
    settings_btn->hide();



    main_vb->removeWidget(play_btn);
    main_vb->removeWidget(settings_btn);
    main_vb->removeWidget(final_lbl);
    final_lbl->hide();

    main_vb->insertWidget(0,return_to_main_menu);


    QHBoxLayout *write_l = new QHBoxLayout;
    QHBoxLayout *play_mode_l = new QHBoxLayout;
    QHBoxLayout *hard_mode_l = new QHBoxLayout;

    write_l->addWidget(write_games_lbl);
    write_l->addWidget(write_games_settings);

    play_mode_l->addWidget(play_mode_lbl);
    play_mode_l->addWidget(play_mode_setting);

    hard_mode_l->addWidget(hard_mode_lbl);
    hard_mode_l->addWidget(hard_mode_setting);

    main_vb->insertLayout(0,hard_mode_l);
    main_vb->insertLayout(0,play_mode_l);
    main_vb->insertLayout(0,write_l);


   hard_mode_lbl->show();
   hard_mode_setting->show();
   write_games_lbl->show();
   write_games_settings->show();
   play_mode_lbl->show();
   play_mode_setting->show();




    return_to_main_menu->show();

    setLayout(main_vb);
    connect(return_to_main_menu,&QPushButton::clicked,this,&Game::show_menu);
    connect(write_games_settings,static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::textActivated),this,[this](const QString& s){
        if(s == "Write all games") how_to_white = write_all;
        if(s == "Write only last game") how_to_white = write_last;
        if(s == "Do not write games") how_to_white = do_not_write;
    });
    connect(play_mode_setting,static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::textActivated),this,[](const QString& s){
        if(s == "play against yourself") Game::st = BY_MYSELF;
        if(s == "play with computer") Game::st = STOCKFISH;
    });
    connect(hard_mode_setting,static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::textActivated),this,[](const QString& s){
        if(s == "Easy") hard_mode = EASY;
        if(s == "Medium") hard_mode = MEDIUM;
        if(s == "Hard") hard_mode = HARD;
        if(s == "Expert") hard_mode = EXPERT;
    });
}


void Game::play() {

    //out << "play begin\n";
    count_move = 1;

    main_vb->removeWidget(white_choise);
    main_vb->removeWidget(black_choise);
    main_vb->removeWidget(random_choise);
    white_choise->hide();
    black_choise->hide();
    random_choise->hide();
    color_choose_lbl->hide();                  //remove menu buttons from screen

    main_vb->insertWidget(0,settings_btn);
    main_vb->insertWidget(0,play_btn);
    play_btn->show();
    settings_btn->show();


    const QString games_directory_name = "Previous games";
    QDir games_directory;

    Game::string_for_stockfish = "position startpos moves ";

    QString file_to_write_filename;
    QFile file_to_write;

    traverse_board([](square& s){
        s = {nullptr,0,0};
    });

    //set the filename of the file
    file_to_write_filename = "Previous games\\\\";
    file_to_write_filename += QDate::currentDate().toString("yyyy-MM-dd");
    file_to_write_filename += "__";
    file_to_write_filename += QTime::currentTime().toString();

    file_to_write_filename[file_to_write_filename.size() - 3] = file_to_write_filename[file_to_write_filename.size() - 6] = '-';
    file_to_write_filename += ".txt";

    if(final_lbl) final_lbl->hide();
    if(write_games_settings) write_games_settings->hide();

    Game::now_move = White;
    Board::last_move = nullptr;
    play_btn->setEnabled(false);
    settings_btn->setEnabled(false);

    if(b == nullptr)
        b = new Board();

    b->setGeometry(100,100,730,670);
    b->setWindowTitle("Game by " + file_to_write_filename.mid(16,20));


    if(how_to_white == write_all) { //if player wants to write all games
        games_directory.mkdir(games_directory_name);
        games_directory.setPath(games_directory_name);

        b->set_write_filename(file_to_write_filename);
    }
    else if(how_to_white == write_last) { //if player wants to write only last game
        games_directory.setPath(games_directory_name);
        if(games_directory.exists()) games_directory.removeRecursively();

        games_directory.setPath(QDir::currentPath());
        games_directory.mkdir(games_directory_name);
        games_directory.setPath(games_directory_name);

        b->set_write_filename(file_to_write_filename);
    }

    else {  //if player does not wants to write games, then delete directory with the files
        games_directory.setPath(games_directory_name);
        if(games_directory.exists())
            games_directory.removeRecursively();
    }

    b->figures_start_set();
    b->show();
    //out << "play end\n";
    connect(b,&Board::windowClosed,this,&Game::show_menu);
    connect(b,&Board::mate,this,&Game::show_final_screen);
    connect (b,&Board::draw_signal,this,&Game::show_final_screen);

}


//function to show final screen when the game ends
void Game::show_final_screen(final_states f) {

    traverse_board([](square &s){
        if(s._figure != EMPTY_SQUARE)
            s._figure->hide();          //hide all figures
    });

    b->hide();

    settings_btn->setEnabled(true);


    if(f == win) {
        final_lbl->setText((Game::now_move == White) ? "Black win!" : "White win");
    }
    else final_lbl->setText("Draw!");

    final_lbl->setAlignment(Qt::AlignCenter);

    main_vb->insertWidget(0,final_lbl);
    final_lbl->show();

    play_btn->setText("Start new Game");
    play_btn->setEnabled(true);

    connect(play_btn,&QPushButton::clicked,this,&Game::choose_color);

}


