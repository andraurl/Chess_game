//
//  King.cpp
//  Chess_game
//
//  Created by Andreas Aurlien on 18.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#include "Piece.hpp"

King::King(Color color) : Piece(color, Type::King) {}

std::string King::to_string() const {
    if (get_color() == Color::Black) return "Black King";
    else return "White King";
}


bool King::legal_move(Chess& game) const {
    if (!is_players_turn(game)) {
        return false;
    }
    else if (!is_legal_capture(game)) {
        
        return false;
    }
    else if (game.run_is_in_check_simulation()) {
        cout << "Check detected" << endl;
        return false;
    }
    else if (is_one_step(game)) {
        return true;
    }
    else if (is_legal_casteling(game)) {
        cout << "Legal casteling" << endl;
        return true;
    }
    else
        return false;
}


bool King::is_one_step(Chess& game) const{
    Position up_left(game.new_move->get_start().get_row() + 1, game.new_move->get_start().get_col() - 1);
    Position up(game.new_move->get_start().get_row() + 1, game.new_move->get_start().get_col());
    Position up_right(game.new_move->get_start().get_row() + 1, game.new_move->get_start().get_col() + 1);
    Position right(game.new_move->get_start().get_row(), game.new_move->get_start().get_col() + 1);
    Position down_right(game.new_move->get_start().get_row() - 1, game.new_move->get_start().get_col() + 1);
    Position down(game.new_move->get_start().get_row() - 1, game.new_move->get_start().get_col());
    Position down_left(game.new_move->get_start().get_row() - 1, game.new_move->get_start().get_col() - 1);
    Position left(game.new_move->get_start().get_row(), game.new_move->get_start().get_col() - 1);
    
    bool one_step = (game.new_move->get_end() == up_left ||game.new_move->get_end() == up || game.new_move->get_end() == up_right
                     ||game.new_move->get_end() == left ||game.new_move->get_end() == right
                     ||game.new_move->get_end() == down_left ||game.new_move->get_end() == down ||game.new_move->get_end() == down_right
    );
    
    return one_step;
}

bool King::is_two_steps_left(Chess& game) const {
    Position two_left(game.new_move->get_start().get_row(), game.new_move->get_start().get_col() - 2);
    return game.new_move->get_end() == two_left;
}

bool King::is_two_steps_right(Chess& game) const {
    Position two_right(game.new_move->get_start().get_row(), game.new_move->get_start().get_col() + 2);
    return game.new_move->get_end() == two_right;
    
}

bool King::is_check_through_casteling(Chess &game) const {
    int col_differance = game.new_move->get_end().get_col() - game.new_move->get_start().get_col();
    int col_dir = col_differance / abs(col_differance);
    
    for (int i = 0; i < 2; i++) {
        
        Position walk_it(game.new_move->get_start().get_row(), game.new_move->get_start().get_col() + i * col_dir);
        Move king_first_step(game.new_move->get_start(), walk_it);
        
        if (game.run_is_in_check_simulation()) {
            return true;
        }
    }
    return false;
}

bool King::is_legal_casteling(Chess& game) const {
    cout << "Calculating legal casteling move" << endl;
    if (get_is_moved()) {
        cout << "King has moved. Casteling not allowed." << endl;
        return false;
    }
        
    if (!is_two_steps_left(game) && !is_two_steps_right(game)) {
        cout << "This is not a casteling move for black" << endl;
        return false;
    }
    
    
    Position casteling_tower;
    bool empty_between;
    
    switch (get_color()) {
        case Color::White: {
            if (is_two_steps_left(game)) {
                casteling_tower = Position(0, 0);
                empty_between = (game.is_piece_nullptr(0, 1) && game.is_piece_nullptr(0, 2) && game.is_piece_nullptr(0, 3));
            }
            else {
                casteling_tower = Position(0, 7);
                empty_between = (game.is_piece_nullptr(0, 5) && game.is_piece_nullptr(0, 6));
            }
            break;
        }
        case Color::Black: {
            if (is_two_steps_left(game)) {
                casteling_tower = Position(7, 0);
                empty_between = (game.is_piece_nullptr(7, 1) && game.is_piece_nullptr(7, 2) && game.is_piece_nullptr(7, 3));
            }
            else {
                casteling_tower = Position(7, 7);
                empty_between = (game.is_piece_nullptr(7, 5) && game.is_piece_nullptr(7, 6));
            }
            break;
        }
        default:
            break;
    }
    if (!empty_between) {
        cout << "Pieces are in the way. Not legal move" << endl;
        return false;
    }
    if (game.is_piece_moved(casteling_tower)) {
        cout << "Casteling tower has moved. Not legal move" << endl;
        return false;
    }
    if (is_check_through_casteling(game)) {
        cout << "King moves through check. Casteling not allowed." << endl;
        return false;
    }
    else {
        cout << "No vialations of the casteling rules" << endl;
        return true;
    }
}

