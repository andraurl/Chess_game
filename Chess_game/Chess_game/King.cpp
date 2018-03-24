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


bool King::legal_move(Chess& game, array<array<unique_ptr<Piece>, 8>, 8>& board, Move move, Chess_piece capture, Color players_turn) const {
    if (!is_players_turn(players_turn)) {
        return false;
    }
    else if (!is_legal_capture(capture)) {
        
        return false;
    }
    else if (game.run_is_in_check_simulation(move, players_turn)) {
        cout << "Check detected" << endl;
        return false;
    }
    else if (is_one_step(move)) {
        return true;
    }
    else if (is_legal_casteling(game, move)) {
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
    
    
    else {
        cout << "No vialations of the casteling rules" << endl;
        return true;
    }
}

