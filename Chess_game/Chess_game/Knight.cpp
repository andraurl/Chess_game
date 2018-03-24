//
//  Knight.cpp
//  Chess_game
//
//  Created by Andreas Aurlien on 18.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#include <stdio.h>

#include "Piece.hpp"

Knight::Knight(Color color) : Piece(color, Type::Kningt) {}

std::string Knight::to_string() const {
    if (get_color() == Color::Black) return "Black Knight";
    else return "White Knight";
}

bool Knight::legal_move(Chess& game, array<array<unique_ptr<Piece>, 8>, 8>& board, Move move, Chess_piece capture, Color players_turn) const {
    
    if (players_turn != get_color()) return false;
    
    if (capture.color == get_color()) return false;
    
    Position up_left(move.get_start().get_row() + 2, move.get_start().get_col() - 1);
    Position up_right(move.get_start().get_row() + 2, move.get_start().get_col() + 1);
    Position right_up(move.get_start().get_row() + 1, move.get_start().get_col() + 2);
    Position right_down(move.get_start().get_row() - 1, move.get_start().get_col() + 2);
    Position down_right(move.get_start().get_row() - 2, move.get_start().get_col() + 1);
    Position down_left(move.get_start().get_row() - 2, move.get_start().get_col() - 1);
    Position left_down(move.get_start().get_row() - 1, move.get_start().get_col() - 2);
    Position left_up(move.get_start().get_row() + 1, move.get_start().get_col() - 2);
    
    bool normal_move  =   (move.get_end() == up_left || move.get_end() == up_right
                        || move.get_end() == right_up || move.get_end() == right_down
                        || move.get_end() == down_right || move.get_end() == down_left
                        || move.get_end() == left_down || move.get_end() == left_up);
    
    if (!normal_move) {
        return false;
    }
    
    if (game.run_is_in_check_simulation(move, players_turn)) {
        cout << "Check detected" << endl;
        return false;
    }
    
    else {
        return true;
    }
}

