#include "board.h"
#include "game.h"
#include <QWidget>
#include "figure.h"

#include <QTextStream>

state Game::st = state::STOCKFISH;
std::array<std::array<square,8>,8> Game::board = {

};

hard_modes Game::hard_mode = hard_modes::EASY;

colors Game::now_move = colors::White;

colors Game::Player_color = colors::White;

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

    b = new Board();

    setFixedSize(800,500);
    this->setWindowTitle("StockChess 2021");
    play_btn = std::make_unique<QPushButton>("Play");
    play_btn->setIcon(QIcon(":\\pics\\play_icon.jpg"));


    settings_btn = std::make_unique<QPushButton>("Settings");
    settings_btn->setIcon(QIcon(":\\pics\\setting_icon.png"));

    exit_btn = std::make_unique<QPushButton>("Exit");
    exit_btn->setIcon(QIcon(":\\pics\\exit_icon.png"));

    return_to_main_menu = std::make_unique<QPushButton>("Return to menu");
    return_to_main_menu->setIcon(QIcon(":\\pics\\menu_icon.png"));

    main_vb = std::make_unique<QVBoxLayout>(this);



    write_games_settings = std::make_unique<QComboBox>(this);

    play_mode_setting = std::make_unique<QComboBox>(this);

    hard_mode_setting = std::make_unique<QComboBox>(this);

    QStringList lst = {"Easy","Medium","Hard","Expert"};
    hard_mode_setting->addItems(lst);
    hard_mode_setting->hide();

    lst = QStringList{"Write all games","Write only last game","Do not write games"};
    write_games_settings->addItems(lst);
    write_games_settings->hide();

    lst = QStringList{"play with computer", "play against yourself"};
    play_mode_setting->addItems(lst);
    play_mode_setting->hide();

    final_lbl = std::make_unique<QLabel>("",this);
    final_lbl->hide();

    write_games_lbl = std::make_unique<QLabel>("How do you like to write your games",this);
    write_games_lbl->setAlignment(Qt::AlignCenter);
    play_mode_lbl = std::make_unique<QLabel>("Play with chess engine or with yourself",this);
    play_mode_lbl->setAlignment(Qt::AlignCenter);
    hard_mode_lbl = std::make_unique<QLabel>("Hard mode",this);
    hard_mode_lbl->setAlignment(Qt::AlignCenter);
    write_games_lbl->hide();
    play_mode_lbl->hide();
    hard_mode_lbl->hide();

    color_choose_lbl = std::make_unique<QLabel>(this);
    color_choose_lbl->setText("Choose a color you want to play");
    color_choose_lbl->hide();

    white_choise = std::make_unique<QPushButton>("White");
    white_choise->setIcon(QIcon(":\\pics\\figures\\wN.png"));
    white_choise->hide();

    black_choise = std::make_unique<QPushButton>("Black");
    black_choise->setIcon(QIcon(":\\pics\\figures\\bN.png"));
    black_choise->hide();

    random_choise = std::make_unique<QPushButton>("Random color");
    random_choise->setIcon(QIcon(":\\pics\\black_white_knight.png"));
    random_choise->hide();



    how_to_white = how_to_write_games::write_all;

    hard_mode = hard_modes::EASY;

    show_menu();

    connect(exit_btn.get(),&QPushButton::clicked,qApp,&QApplication::quit);
    connect(play_btn.get(),&QPushButton::clicked,this,&Game::choose_color);
    connect(settings_btn.get(),&QPushButton::clicked,this,&Game::show_settings);

    connect(white_choise.get(),&QPushButton::clicked,this,[this](){Game::Player_color = colors::White; play();});
    connect(black_choise.get(),&QPushButton::clicked,this,[this](){Game::Player_color = colors::Black; play();});
    connect(random_choise.get(),&QPushButton::clicked,this,[this](){
        if(rand() % 2 == 0) {
            Game::Player_color = colors::White;
        }
        else {
            Game::Player_color = colors::Black;
        }
        play();
    });
    connect(return_to_main_menu.get(),&QPushButton::clicked,this,&Game::show_menu);

    connect(write_games_settings.get(),static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::textActivated),this,[this](const QString& s){
        if(s == "Write all games") how_to_white = how_to_write_games::write_all;
        if(s == "Write only last game") how_to_white = how_to_write_games::write_last;
        if(s == "Do not write games") how_to_white = how_to_write_games::do_not_write;
    });
    connect(play_mode_setting.get(),static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::textActivated),this,[](const QString& s){
        if(s == "play against yourself") Game::st = state::BY_MYSELF;
        if(s == "play with computer") Game::st = state::STOCKFISH;
    });
    connect(hard_mode_setting.get(),static_cast<void(QComboBox::*)(const QString &)>(&QComboBox::textActivated),this,[](const QString& s){
        if(s == "Easy") hard_mode = hard_modes::EASY;
        if(s == "Medium") hard_mode = hard_modes::MEDIUM;
        if(s == "Hard") hard_mode = hard_modes::HARD;
        if(s == "Expert") hard_mode = hard_modes::EXPERT;
    });

    connect(b,&Board::windowClosed,this,&Game::show_menu);
    connect(b,&Board::mate,this,&Game::show_final_screen);
    connect (b,&Board::draw_signal,this,&Game::show_final_screen);

    connect(play_btn.get(),&QPushButton::clicked,this,&Game::choose_color);

}

Game::~Game() {

}


void Game::choose_color() {

    //out << "color begin\n";
    srand(time(NULL));
    main_vb->removeWidget(play_btn.get());
    main_vb->removeWidget(settings_btn.get());
    main_vb->removeWidget(final_lbl.get());
    final_lbl->hide();
    play_btn->hide();
    settings_btn->hide();
    main_vb->insertWidget(0,white_choise.get());
    main_vb->insertWidget(0,black_choise.get());
    main_vb->insertWidget(0,random_choise.get());
    main_vb->insertWidget(0,color_choose_lbl.get(),1,Qt::AlignCenter);
    main_vb->insertWidget(4,return_to_main_menu.get());
    return_to_main_menu->show();
    color_choose_lbl->show();
    white_choise->show();
    black_choise->show();
    random_choise->show();


    //out << "color end\n";
}





void Game::show_menu() {



    //out << "menu begin\n";

    return_to_main_menu->hide();

    main_vb->removeWidget(hard_mode_lbl.get());
    main_vb->removeWidget(play_mode_lbl.get());
    main_vb->removeWidget(write_games_lbl.get());
    main_vb->removeWidget(black_choise.get());
    main_vb->removeWidget(white_choise.get());
    main_vb->removeWidget(random_choise.get());
    main_vb->removeWidget(return_to_main_menu.get());
    main_vb->removeWidget(color_choose_lbl.get());
    main_vb->removeWidget(final_lbl.get());

    hard_mode_lbl->hide();
    play_mode_lbl->hide();
    write_games_lbl->hide();
    black_choise->hide();
    white_choise->hide();
    random_choise->hide();
    return_to_main_menu->hide();
    color_choose_lbl->hide();
    final_lbl->hide();

    main_vb->removeWidget(write_games_settings.get());
    write_games_settings->hide();
    main_vb->removeWidget(return_to_main_menu.get());
    main_vb->removeWidget(play_mode_setting.get());
    play_mode_setting->hide();

    main_vb->removeWidget(hard_mode_setting.get());
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
    vb->addWidget(play_btn.get(),2);
    vb->addWidget(settings_btn.get(),2);
    vb->addWidget(exit_btn.get(),2);
    main_vb->addLayout(vb,1);
    setLayout(main_vb.get());


    //out << "menu end\n";
}

void Game::show_settings() {


    play_btn->hide();
    settings_btn->hide();



    main_vb->removeWidget(play_btn.get());
    main_vb->removeWidget(settings_btn.get());
    main_vb->removeWidget(final_lbl.get());
    final_lbl->hide();

    main_vb->insertWidget(0,return_to_main_menu.get());


    QHBoxLayout *write_l = new QHBoxLayout;
    QHBoxLayout *play_mode_l = new QHBoxLayout;
    QHBoxLayout *hard_mode_l = new QHBoxLayout;

    write_l->addWidget(write_games_lbl.get());
    write_l->addWidget(write_games_settings.get());

    play_mode_l->addWidget(play_mode_lbl.get());
    play_mode_l->addWidget(play_mode_setting.get());

    hard_mode_l->addWidget(hard_mode_lbl.get());
    hard_mode_l->addWidget(hard_mode_setting.get());

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

    setLayout(main_vb.get());

}


void Game::play() {

    //out << "play begin\n";
    count_move = 1;

    main_vb->removeWidget(white_choise.get());
    main_vb->removeWidget(black_choise.get());
    main_vb->removeWidget(random_choise.get());
    white_choise->hide();
    black_choise->hide();
    random_choise->hide();
    color_choose_lbl->hide();                  //remove menu buttons from screen

    main_vb->insertWidget(0,settings_btn.get());
    main_vb->insertWidget(0,play_btn.get());
    play_btn->show();
    settings_btn->show();


    const QString games_directory_name = "Previous games";
    QDir games_directory;

    Game::string_for_stockfish = "position startpos moves ";

    QString file_to_write_filename;
    QFile file_to_write;

    traverse_board([](square& s){
        s = {std::shared_ptr<figure>(nullptr),0,0};
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

    Game::now_move = colors::White;
    Board::last_move = nullptr;
    play_btn->setEnabled(false);
    settings_btn->setEnabled(false);

    //this->b->setGeometry(100)
    b->setGeometry(100,100,730,670);
    b->setWindowTitle("Game by " + file_to_write_filename.mid(16,20));


    if(how_to_white == how_to_write_games::write_all) { //if player wants to write all games
        games_directory.mkdir(games_directory_name);
        games_directory.setPath(games_directory_name);

        b->set_write_filename(file_to_write_filename);
    }
    else if(how_to_white == how_to_write_games::write_last) { //if player wants to write only last game
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
        final_lbl->setText((Game::now_move == colors::White) ? "Black win!" : "White win");
    }
    else final_lbl->setText("Draw!");

    final_lbl->setAlignment(Qt::AlignCenter);

    main_vb->insertWidget(0,final_lbl.get());
    final_lbl->show();

    play_btn->setText("Start new Game");
    play_btn->setEnabled(true);



}


