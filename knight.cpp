#include "knight.h"
#include "board.h"
knight::knight(std::string text,QWidget *parent,int cost,figure_weight weight) : figure(text,parent,cost,weight)
{

}

void knight::touch_attacking_squares(int how) {
   position curr_pos = this->get_pos();

   if(curr_pos.row <= 6) {
       if(curr_pos.column <= G) {
           ((this->get_color() == White) ? at(position(columns(curr_pos.column + 1),curr_pos.row + 2)).attacking_white_figures : at(position(columns(curr_pos.column + 1),curr_pos.row + 2)).attacking_black_figures)+= how;
            //    --
            //    |
            //    |
       }


       if(curr_pos.column >= B) {
           ((this->get_color() == White) ? at(position(columns(curr_pos.column - 1),curr_pos.row + 2)).attacking_white_figures : at(position(columns(curr_pos.column - 1),curr_pos.row + 2)).attacking_black_figures)+= how;
           //   --
           //    |
           //    |
       }
   }

   if(curr_pos.column <= F) {
       if(curr_pos.row <= 7) {
           ((this->get_color() == White) ? at(position(columns(curr_pos.column + 2),curr_pos.row + 1)).attacking_white_figures : at(position(columns(curr_pos.column + 2),curr_pos.row + 1)).attacking_black_figures)+= how;
           //        |
           //    ----
           //
       }
       if(curr_pos.row >= 2) {
           ((this->get_color() == White) ? at(position(columns(curr_pos.column + 2),curr_pos.row - 1)).attacking_white_figures : at(position(columns(curr_pos.column + 2),curr_pos.row - 1)).attacking_black_figures)+= how;
           //
           //    ----
           //        |
       }
   }

   if(curr_pos.row >= 3) {
       if(curr_pos.column <= G) {
           ((this->get_color() == White) ? at(position(columns(curr_pos.column + 1),curr_pos.row - 2)).attacking_white_figures : at(position(columns(curr_pos.column + 1),curr_pos.row - 2)).attacking_black_figures)+= how;
           //    |
           //    |
           //     --
       }
       if(curr_pos.column >= B) {
           ((this->get_color() == White) ? at(position(columns(curr_pos.column - 1),curr_pos.row - 2)).attacking_white_figures : at(position(columns(curr_pos.column - 1),curr_pos.row - 2)).attacking_black_figures)+= how;
           //    |
           //    |
           //  --
       }
   }

   if(curr_pos.column >= C) {
       if(curr_pos.row <= 7) {
           ((this->get_color() == White) ? at(position(columns(curr_pos.column - 2),curr_pos.row + 1)).attacking_white_figures : at(position(columns(curr_pos.column - 2),curr_pos.row + 1)).attacking_black_figures)+= how;
           //     |
           //      ----
           //
       }
       if(curr_pos.row >= 2) {
           ((this->get_color() == White) ? at(position(columns(curr_pos.column - 2),curr_pos.row - 1)).attacking_white_figures : at(position(columns(curr_pos.column - 2),curr_pos.row - 1)).attacking_black_figures)+= how;
           //
           //      ----
           //     |
       }
   }
}

std::vector<position> knight::possible_squares() {
    QTextStream out(stdout);
    std::vector<position> result;
    colors c = this->get_color();
    position curr_pos = this->get_pos();
    if(curr_pos.row <= 6) {
        if(curr_pos.column <= G) {
            if(at(position(columns(curr_pos.column + 1),curr_pos.row + 2))._figure == EMPTY_SQUARE || ((at(position(columns(curr_pos.column + 1),curr_pos.row + 2))._figure != EMPTY_SQUARE) && at(position(columns(curr_pos.column + 1),curr_pos.row + 2))._figure->get_color() != c))
                result.push_back(position(columns(curr_pos.column + 1),curr_pos.row + 2));
        }
        if(curr_pos.column >= B) {
            if(at(position(columns(curr_pos.column - 1),curr_pos.row + 2))._figure == EMPTY_SQUARE || ((at(position(columns(curr_pos.column - 1),curr_pos.row + 2))._figure != EMPTY_SQUARE) && at(position(columns(curr_pos.column - 1),curr_pos.row + 2))._figure->get_color() != c))
                result.push_back(position(columns(curr_pos.column - 1),curr_pos.row + 2));
        }
    }

    if(curr_pos.column <= F) {
        if(curr_pos.row <= 7) {
            if(at(position(columns(curr_pos.column + 2),curr_pos.row + 1))._figure == EMPTY_SQUARE || ((at(position(columns(curr_pos.column + 2),curr_pos.row + 1))._figure != EMPTY_SQUARE) && at(position(columns(curr_pos.column + 2),curr_pos.row + 1))._figure->get_color() != c))
                result.push_back(position(columns(curr_pos.column + 2),curr_pos.row + 1));
        }
        if(curr_pos.row >= 2) {
            if(at(position(columns(curr_pos.column + 2),curr_pos.row - 1))._figure == EMPTY_SQUARE || ((at(position(columns(curr_pos.column + 2),curr_pos.row - 1))._figure != EMPTY_SQUARE) && at(position(columns(curr_pos.column + 2),curr_pos.row - 1))._figure->get_color() != c))
                result.push_back(position(columns(curr_pos.column + 2),curr_pos.row - 1));
        }
    }

    if(curr_pos.row >= 3) {

        if(curr_pos.column <= G) {
            if(at(position(columns(curr_pos.column + 1),curr_pos.row - 2))._figure == EMPTY_SQUARE || ((at(position(columns(curr_pos.column + 1),curr_pos.row - 2))._figure != EMPTY_SQUARE) && at(position(columns(curr_pos.column + 1),curr_pos.row - 2))._figure->get_color() != c))
                result.push_back(position(columns(curr_pos.column + 1),curr_pos.row - 2));
        }
        if(curr_pos.column >= B) {
            if(at(position(columns(curr_pos.column - 1),curr_pos.row - 2))._figure == EMPTY_SQUARE || ((at(position(columns(curr_pos.column - 1),curr_pos.row - 2))._figure != EMPTY_SQUARE) && at(position(columns(curr_pos.column - 1),curr_pos.row - 2))._figure->get_color() != c))
                result.push_back(position(columns(curr_pos.column - 1),curr_pos.row - 2));
        }
    }

    if(curr_pos.column >= C) {
        if(curr_pos.row <= 7) {
            if(at(position(columns(curr_pos.column - 2),curr_pos.row + 1))._figure == EMPTY_SQUARE || ((at(position(columns(curr_pos.column - 2),curr_pos.row + 1))._figure != EMPTY_SQUARE) && at(position(columns(curr_pos.column - 2),curr_pos.row + 1))._figure->get_color() != c))
                result.push_back(position(columns(curr_pos.column - 2),curr_pos.row + 1));
        }
        if(curr_pos.row >= 2) {
            if(at(position(columns(curr_pos.column - 2),curr_pos.row - 1))._figure == EMPTY_SQUARE || ((at(position(columns(curr_pos.column - 2),curr_pos.row - 1))._figure != EMPTY_SQUARE) && at(position(columns(curr_pos.column - 2),curr_pos.row - 1))._figure->get_color() != c))
                result.push_back(position(columns(curr_pos.column - 2),curr_pos.row - 1));

        }
    }


    return result;
}
