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


bool King::legal_move(array<array<unique_ptr<Piece>, 8>, 8>& board, Move move, Chess_piece capture, Color players_turn) const {
    if (!is_players_turn(players_turn)) {
        return false;
    }
    else if (!is_legal_capture(capture)) {
        return false;
    }
    else if (is_one_step(move)) {
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

