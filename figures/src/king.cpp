#include "king.h"
#include "board.h"
king::king(colors color,std::shared_ptr<Board> parent,int cost,figure_weight weight) : figure(color,figure_type::King,parent,cost,weight)
{
    was_checked = false;

}

std::vector<position> king::possible_squares() {
    std::vector<position> result;

    position p = this->get_pos();

    bool nearest_square_free;
    bool nearest_square_not_attacked;
    bool nearest_square_not_occuped_same_color;

    const int col = static_cast<int>(p.column);

    //vertical up next square
    if(p.row != 8) {
        auto temp = at(columns(p.column),p.row + 1);
        nearest_square_free = temp._figure == EMPTY_SQUARE;

        //out << "nearest = " << nearest_square_free << endl;
        nearest_square_not_attacked = (this->get_color() == colors::White) ? (temp.attacking_black_figures == 0) : (temp.attacking_white_figures == 0);
        if(nearest_square_free && nearest_square_not_attacked) {

            result.push_back(position(columns(p.column),p.row + 1));
        }
        else if(!nearest_square_free && nearest_square_not_attacked) {
            nearest_square_not_occuped_same_color = temp._figure->get_color() != this->get_color();

            if(nearest_square_not_occuped_same_color)
                result.push_back(position(columns(p.column),p.row + 1));
        }
    }

    //diagonal up right next square
    if(p.row != 8 && p.column != columns::H) {
        auto temp = at(columns(col + 1),p.row + 1);
        nearest_square_free = temp._figure == EMPTY_SQUARE;
        nearest_square_not_attacked = (this->get_color() == colors::White) ? temp.attacking_black_figures == 0 : temp.attacking_white_figures == 0;
        if(nearest_square_free && nearest_square_not_attacked) {

            result.push_back(position(columns(col + 1),p.row + 1));
        }
        else if(!nearest_square_free && nearest_square_not_attacked) {
            nearest_square_not_occuped_same_color = temp._figure->get_color() != this->get_color();
            if(nearest_square_not_occuped_same_color)
                result.push_back(position(columns(col + 1),p.row + 1));
        }
    }

    //horizontal right next square
    if(p.column != columns::H) {

        auto temp = at(columns(col + 1),p.row);
        nearest_square_free = temp._figure == EMPTY_SQUARE;
        nearest_square_not_attacked = (this->get_color() == colors::White) ? temp.attacking_black_figures == 0 : temp.attacking_white_figures == 0;
        if(nearest_square_free && nearest_square_not_attacked) {

            result.push_back(position(columns(col + 1),p.row));
        }
        else if(!nearest_square_free && nearest_square_not_attacked) {
            nearest_square_not_occuped_same_color = temp._figure->get_color() != this->get_color();
            if(nearest_square_not_occuped_same_color)
                result.push_back(position(columns(col + 1),p.row));
        }
    }

    //diagonal right down next square
    if(p.column != columns::H && p.row != 1) {
        auto temp = at(columns(col + 1),p.row - 1);
        nearest_square_free = temp._figure == EMPTY_SQUARE;
        nearest_square_not_attacked = (this->get_color() == colors::White) ? temp.attacking_black_figures == 0 : temp.attacking_white_figures == 0;
        if(nearest_square_free && nearest_square_not_attacked) {

            result.push_back(position(columns(col + 1),p.row - 1));
        }
        else if(!nearest_square_free && nearest_square_not_attacked) {
            nearest_square_not_occuped_same_color = temp._figure->get_color() != this->get_color();
            if(nearest_square_not_occuped_same_color)
                result.push_back(position(columns(col + 1),p.row - 1));
        }
    }

    //vertical down next square
    if(p.row != 1) {

        auto temp = at(columns(p.column),p.row - 1);


        nearest_square_free = (temp._figure == EMPTY_SQUARE);

        nearest_square_not_attacked = (this->get_color() == colors::White) ? (temp.attacking_black_figures == 0) : (temp.attacking_white_figures == 0);

        if(nearest_square_free && nearest_square_not_attacked) {

            result.push_back(position(columns(p.column),p.row - 1));
        }
        else if(!nearest_square_free && nearest_square_not_attacked) {

            nearest_square_not_occuped_same_color = temp._figure->get_color() != this->get_color();
            if(nearest_square_not_occuped_same_color)
                result.push_back(position(columns(p.column),p.row - 1));
        }
    }

    //diagonal left down next square
    if(p.row != 1 && p.column != columns::A) {
        auto temp = at(columns(col - 1),p.row - 1);
        nearest_square_free = temp._figure == EMPTY_SQUARE;
        nearest_square_not_attacked = (this->get_color() == colors::White) ? temp.attacking_black_figures == 0 : temp.attacking_white_figures == 0;
        if(nearest_square_free && nearest_square_not_attacked) {

            result.push_back(position(columns(col - 1),p.row - 1));
        }
        else if(!nearest_square_free && nearest_square_not_attacked) {
            nearest_square_not_occuped_same_color = temp._figure->get_color() != this->get_color();
            if(nearest_square_not_occuped_same_color)
                result.push_back(position(columns(col - 1),p.row - 1));
        }
    }

    //vertical left next square
    if(p.column != columns::A) {
        auto temp = at(columns(col - 1),p.row);
        nearest_square_free = temp._figure == EMPTY_SQUARE;
        nearest_square_not_attacked = (this->get_color() == colors::White) ? temp.attacking_black_figures == 0 : temp.attacking_white_figures == 0;
        if(nearest_square_free && nearest_square_not_attacked) {

            result.push_back(position(columns(col - 1),p.row));
        }
        else if(!nearest_square_free && nearest_square_not_attacked) {
            nearest_square_not_occuped_same_color = temp._figure->get_color() != this->get_color();
            if(nearest_square_not_occuped_same_color)
                result.push_back(position(columns(col - 1),p.row));
        }
    }

    //diagonal right up next square
    if(p.column != columns::A && p.row != 8) {
        auto temp = at(columns(col - 1),p.row + 1);
        nearest_square_free = temp._figure == EMPTY_SQUARE;
        nearest_square_not_attacked = (this->get_color() == colors::White) ? temp.attacking_black_figures == 0 : temp.attacking_white_figures == 0;
        if(nearest_square_free && nearest_square_not_attacked) {

            result.push_back(position(columns(col - 1),p.row + 1));
        }
        else if(!nearest_square_free && nearest_square_not_attacked) {
            nearest_square_not_occuped_same_color = temp._figure->get_color() != this->get_color();
            if(nearest_square_not_occuped_same_color)
                result.push_back(position(columns(col - 1),p.row + 1));
        }
    }


    //check castling posibility
    p = this->get_pos();

    bool king_not_attacked = ((this->get_color() == colors::White) ? (at(this->get_pos()).attacking_black_figures == 0) : (at(this->get_pos()).attacking_white_figures == 0));

    //check short castling
    bool first_move = get_count_moves() == 0;
    bool nearest_two_squares_right_free = (p.column <= columns::F && at(position(columns(col + 1),p.row))._figure == EMPTY_SQUARE && at(position(columns(col + 2),p.row))._figure == EMPTY_SQUARE);
    bool nearest_two_squares_right_not_attacked;
    if(this->get_color() == colors::White)
       nearest_two_squares_right_not_attacked = (p.column <= columns::F && at(position(columns(col + 1),p.row)).attacking_black_figures == 0 && at(position(columns(col + 2),p.row)).attacking_black_figures == 0);
    else
        nearest_two_squares_right_not_attacked = (p.column <= columns::F && at(position(columns(col + 1),p.row)).attacking_white_figures == 0 && at(position(columns(col + 2),p.row)).attacking_white_figures == 0);
    bool is_rook_on_start_place = (((this->get_color() == colors::White) ? at(columns::H,1)._figure : at(columns::H,8)._figure) != nullptr && ((this->get_color() == colors::White) ? at(columns::H,1)._figure : at(columns::H,8)._figure)->name() == figure_type::Rook);
    bool rook_first_move = (is_rook_on_start_place && ((this->get_color() == colors::White) ? at(columns::H,1)._figure : at(columns::H,8)._figure)->get_count_moves() == 0);

    bool castling_short = (king_not_attacked && first_move && nearest_two_squares_right_free && nearest_two_squares_right_not_attacked && rook_first_move);
    if(castling_short) result.push_back(position(columns(col + 2),p.row));



    //check long castling
    bool nearest_two_squares_left_free = (p.column >= columns::C && at(position(columns(col - 1),p.row))._figure == EMPTY_SQUARE && at(position(columns(col - 2),p.row))._figure == EMPTY_SQUARE);
    bool nearest_two_squares_left_not_attacked;
    if(this->get_color() == colors::White)
       nearest_two_squares_left_not_attacked = (p.column >= columns::C && at(position(columns(col - 1),p.row)).attacking_black_figures == 0 && at(position(columns(col - 2),p.row)).attacking_black_figures == 0);
    else
        nearest_two_squares_left_not_attacked = (p.column >= columns::C && at(position(columns(col - 1),p.row)).attacking_white_figures == 0 && at(position(columns(col - 2),p.row)).attacking_white_figures == 0);

    is_rook_on_start_place = (((this->get_color() == colors::White) ? at(columns::A,1)._figure : at(columns::A,8)._figure) != EMPTY_SQUARE && ((this->get_color() == colors::White) ? at(columns::A,1)._figure : at(columns::A,8)._figure)->name() == figure_type::Rook);
    rook_first_move = (is_rook_on_start_place && ((this->get_color() == colors::White) ? at(columns::A,1)._figure : at(columns::A,8)._figure)->get_count_moves() == 0);

    bool castling_long = (king_not_attacked && first_move && nearest_two_squares_left_free && nearest_two_squares_left_not_attacked && rook_first_move);
    if(castling_long) result.push_back(position(columns(col - 2),p.row));


    return result;
}



void king::touch_attacking_squares(int how) {

    position p = this->get_pos();
    const int col = static_cast<int>(p.column);
    if(this->get_color() == colors::White) {
        if(p.row != 8) {

            at(p.column,p.row + 1).attacking_white_figures += how; //vertical up next square
            if(p.column != columns::A) {
                at(columns(col - 1),p.row + 1).attacking_white_figures+= how; //diagonal left up
            }
            if(p.column != columns::H) {
                at(columns(col + 1),p.row + 1).attacking_white_figures+= how;  //diagonal right up

            }
        }

        if(p.column != columns::A) {
            at(columns(col - 1),p.row).attacking_white_figures+= how;  //horizontal left
        }

        if(p.column != columns::H) {
            at(columns(col + 1),p.row).attacking_white_figures+= how;   //horizontal right
        }

        if(p.row != 1) {
            at(p.column,p.row - 1).attacking_white_figures += how;   //vertical down
            if(p.column != columns::A) {
                at(columns(col - 1),p.row - 1).attacking_white_figures+= how; //diagonal left down
            }
            if(p.column != columns::H) {
                at(columns(col + 1),p.row - 1).attacking_white_figures+= how;  //diagonal right down

            }
        }
    }
    else {   //the same logic, but touching like a black figure
        if(p.row != 8) {
            at(p.column,p.row + 1).attacking_black_figures += how;
            if(p.column != columns::A) {
                at(columns(col - 1),p.row + 1).attacking_black_figures+= how;
            }
            if(p.column != columns::H) {
                at(columns(col + 1),p.row + 1).attacking_black_figures+= how;

            }
        }

        if(p.column != columns::A) {
            at(columns(col - 1),p.row).attacking_black_figures+= how;
        }

        if(p.column != columns::H) {
            at(columns(col + 1),p.row).attacking_black_figures+= how;
        }

        if(p.row != 1) {
            at(p.column,p.row - 1).attacking_black_figures += how;
            if(p.column != columns::A) {
                at(columns(col - 1),p.row - 1).attacking_black_figures+= how;
            }
            if(p.column != columns::H) {
                at(columns(col + 1),p.row - 1).attacking_black_figures+= how;

            }
        }
    }
}

