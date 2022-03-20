#include "knight.h"
#include "board.h"
knight::knight(colors color,QWidget *parent,int cost,figure_weight weight) : figure(color,figure_type::Knight,parent,cost,weight)
{

}

void knight::touch_attacking_squares(int how) {
   position curr_pos = this->get_pos();

   const int column = static_cast<int>(curr_pos.column);

   if(curr_pos.row <= 6) {
       if(curr_pos.column <= columns::G) {
           ((this->get_color() == colors::White) ? at(position(columns(column + 1),curr_pos.row + 2)).attacking_white_figures : at(position(columns(column + 1),curr_pos.row + 2)).attacking_black_figures)+= how;
            //    --
            //    |
            //    |
       }


       if(curr_pos.column >= columns::B) {
           ((this->get_color() == colors::White) ? at(position(columns(column - 1),curr_pos.row + 2)).attacking_white_figures : at(position(columns(column - 1),curr_pos.row + 2)).attacking_black_figures)+= how;
           //   --
           //    |
           //    |
       }
   }

   if(curr_pos.column <= columns::F) {
       if(curr_pos.row <= 7) {
           ((this->get_color() == colors::White) ? at(position(columns(column + 2),curr_pos.row + 1)).attacking_white_figures : at(position(columns(column + 2),curr_pos.row + 1)).attacking_black_figures)+= how;
           //        |
           //    ----
           //
       }
       if(curr_pos.row >= 2) {
           ((this->get_color() == colors::White) ? at(position(columns(column + 2),curr_pos.row - 1)).attacking_white_figures : at(position(columns(column + 2),curr_pos.row - 1)).attacking_black_figures)+= how;
           //
           //    ----
           //        |
       }
   }

   if(curr_pos.row >= 3) {
       if(curr_pos.column <= columns::G) {
           ((this->get_color() == colors::White) ? at(position(columns(column + 1),curr_pos.row - 2)).attacking_white_figures : at(position(columns(column + 1),curr_pos.row - 2)).attacking_black_figures)+= how;
           //    |
           //    |
           //     --
       }
       if(curr_pos.column >= columns::B) {
           ((this->get_color() == colors::White) ? at(position(columns(column - 1),curr_pos.row - 2)).attacking_white_figures : at(position(columns(column - 1),curr_pos.row - 2)).attacking_black_figures)+= how;
           //    |
           //    |
           //  --
       }
   }

   if(curr_pos.column >= columns::C) {
       if(curr_pos.row <= 7) {
           ((this->get_color() == colors::White) ? at(position(columns(column - 2),curr_pos.row + 1)).attacking_white_figures : at(position(columns(column - 2),curr_pos.row + 1)).attacking_black_figures)+= how;
           //     |
           //      ----
           //
       }
       if(curr_pos.row >= 2) {
           ((this->get_color() == colors::White) ? at(position(columns(column - 2),curr_pos.row - 1)).attacking_white_figures : at(position(columns(column - 2),curr_pos.row - 1)).attacking_black_figures)+= how;
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
    const int col = static_cast<int>(curr_pos.column);
    if(curr_pos.row <= 6) {
        if(curr_pos.column <= columns::G) {
            if(at(position(columns(col + 1),curr_pos.row + 2))._figure == EMPTY_SQUARE || ((at(position(columns(col + 1),curr_pos.row + 2))._figure != EMPTY_SQUARE) && at(position(columns(col + 1),curr_pos.row + 2))._figure->get_color() != c))
                result.push_back(position(columns(col + 1),curr_pos.row + 2));
        }
        if(curr_pos.column >= columns::B) {
            if(at(position(columns(col - 1),curr_pos.row + 2))._figure == EMPTY_SQUARE || ((at(position(columns(col - 1),curr_pos.row + 2))._figure != EMPTY_SQUARE) && at(position(columns(col - 1),curr_pos.row + 2))._figure->get_color() != c))
                result.push_back(position(columns(col - 1),curr_pos.row + 2));
        }
    }

    if(curr_pos.column <= columns::F) {
        if(curr_pos.row <= 7) {
            if(at(position(columns(col + 2),curr_pos.row + 1))._figure == EMPTY_SQUARE || ((at(position(columns(col + 2),curr_pos.row + 1))._figure != EMPTY_SQUARE) && at(position(columns(col + 2),curr_pos.row + 1))._figure->get_color() != c))
                result.push_back(position(columns(col + 2),curr_pos.row + 1));
        }
        if(curr_pos.row >= 2) {
            if(at(position(columns(col + 2),curr_pos.row - 1))._figure == EMPTY_SQUARE || ((at(position(columns(col + 2),curr_pos.row - 1))._figure != EMPTY_SQUARE) && at(position(columns(col + 2),curr_pos.row - 1))._figure->get_color() != c))
                result.push_back(position(columns(col + 2),curr_pos.row - 1));
        }
    }

    if(curr_pos.row >= 3) {

        if(curr_pos.column <= columns::G) {
            if(at(position(columns(col + 1),curr_pos.row - 2))._figure == EMPTY_SQUARE || ((at(position(columns(col + 1),curr_pos.row - 2))._figure != EMPTY_SQUARE) && at(position(columns(col + 1),curr_pos.row - 2))._figure->get_color() != c))
                result.push_back(position(columns(col + 1),curr_pos.row - 2));
        }
        if(curr_pos.column >= columns::B) {
            if(at(position(columns(col - 1),curr_pos.row - 2))._figure == EMPTY_SQUARE || ((at(position(columns(col - 1),curr_pos.row - 2))._figure != EMPTY_SQUARE) && at(position(columns(col - 1),curr_pos.row - 2))._figure->get_color() != c))
                result.push_back(position(columns(col - 1),curr_pos.row - 2));
        }
    }

    if(curr_pos.column >= columns::C) {
        if(curr_pos.row <= 7) {
            if(at(position(columns(col - 2),curr_pos.row + 1))._figure == EMPTY_SQUARE || ((at(position(columns(col - 2),curr_pos.row + 1))._figure != EMPTY_SQUARE) && at(position(columns(col - 2),curr_pos.row + 1))._figure->get_color() != c))
                result.push_back(position(columns(col - 2),curr_pos.row + 1));
        }
        if(curr_pos.row >= 2) {
            if(at(position(columns(col - 2),curr_pos.row - 1))._figure == EMPTY_SQUARE || ((at(position(columns(col - 2),curr_pos.row - 1))._figure != EMPTY_SQUARE) && at(position(columns(col - 2),curr_pos.row - 1))._figure->get_color() != c))
                result.push_back(position(columns(col - 2),curr_pos.row - 1));

        }
    }


    return result;
}
