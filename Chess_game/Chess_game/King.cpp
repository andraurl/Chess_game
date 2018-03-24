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
    if (!is_players_turn(game.players_turn)) {
        return false;
    }
    else if (!is_legal_capture(*game.capture)) {
        
        return false;
    }
    else if (game.run_is_in_check_simulation(*game.new_move, game.players_turn)) {
        cout << "Check detected" << endl;
        return false;
    }
    else if (is_one_step(*game.new_move)) {
        return true;
    }
    else if (is_legal_casteling(game, *game.new_move)) {
        cout << "Legal casteling" << endl;
        return true;
    }
    else
        return false;
}


bool King::is_one_step(Move move) const{
    Position up_left(move.get_start().get_row() + 1, move.get_start().get_col() - 1);
    Position up(move.get_start().get_row() + 1, move.get_start().get_col());
    Position up_right(move.get_start().get_row() + 1, move.get_start().get_col() + 1);
    Position right(move.get_start().get_row(), move.get_start().get_col() + 1);
    Position down_right(move.get_start().get_row() - 1, move.get_start().get_col() + 1);
    Position down(move.get_start().get_row() - 1, move.get_start().get_col());
    Position down_left(move.get_start().get_row() - 1, move.get_start().get_col() - 1);
    Position left(move.get_start().get_row(), move.get_start().get_col() - 1);
    
    bool one_step = (move.get_end() == up_left || move.get_end() == up ||move.get_end() == up_right
                     || move.get_end() == left || move.get_end() == right
                     || move.get_end() == down_left || move.get_end() == down || move.get_end() == down_right
    );
    
    return one_step;
}

bool King::is_two_steps_left(Move move) const {
    Position two_left(move.get_start().get_row(), move.get_start().get_col() - 2);
    return move.get_end() == two_left;
}

bool King::is_two_steps_right(Move move) const {
    Position two_right(move.get_start().get_row(), move.get_start().get_col() + 2);
    return move.get_end() == two_right;
    
}

bool King::is_check_through_casteling(Chess &game, Move move) const {
    int col_differance = move.get_end().get_col() - move.get_start().get_col();
    int col_dir = col_differance / abs(col_differance);
    
    for (int i = 0; i < 2; i++) {
        
        Position walk_it(move.get_start().get_row(), move.get_start().get_col() + i * col_dir);
        Move king_first_step(move.get_start(), walk_it);
        
        if (game.run_is_in_check_simulation(king_first_step, get_color())) {
            return true;
        }
    }
    return false;
}

bool King::is_legal_casteling(Chess& game, Move move) const {
    cout << "Calculating legal casteling move" << endl;
    if (get_is_moved()) {
        cout << "King has moved. Casteling not allowed." << endl;
        return false;
    }
        
    if (!is_two_steps_left(move) && !is_two_steps_right(move)) {
        cout << "This is not a casteling move for black" << endl;
        return false;
    }
    
    
    Position casteling_tower;
    bool empty_between;
    
    switch (get_color()) {
        case Color::White: {
            if (is_two_steps_left(move)) {
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
            if (is_two_steps_left(move)) {
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
    if (is_check_through_casteling(game, move)) {
        cout << "King moves through check. Casteling not allowed." << endl;
        return false;
    }
    else {
        cout << "No vialations of the casteling rules" << endl;
        return true;
    }
}

