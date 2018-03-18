//
//  Pawn.cpp
//  Chess_game
//
//  Created by Andreas Aurlien on 18.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#include "Piece.hpp"

using namespace std;

Pawn::Pawn(Color color) : Piece(color, Type::Pawn) {}

std::string Pawn::to_string() const {
    if (get_color() == Color::Black) return "Black Pawn";
    else return "White Pawn";
}

bool Pawn::legal_move(array<array<unique_ptr<Piece>, 8>, 8>& board, Move move, Chess_piece capture, Color players_turn) const {
    
    if (players_turn != get_color()) return false;
    
    if (capture.color == get_color()) return false;
    
    int one_row_ahead;
    int two_rows_ahead;
    switch (get_color()) {
        case Color::Black: {
            one_row_ahead = -1;
            two_rows_ahead = -2;
            cout << "Claculating leagal move for black pawn" << endl;
            break;
        }
            
        case Color::White: {
            one_row_ahead = 1;
            two_rows_ahead = 2;
            cout << "Claculating leagal move for white pawn" << endl;
            break;
        }
        default: {
            bool not_black_or_white = (get_color() != Color::White && get_color() != Color::Black);
            assert(not_black_or_white);
            break;
        }
    }
    
    Position one_step(move.get_start().get_row() + one_row_ahead, move.get_start().get_col());
    
    if (move.get_end() == one_step && capture.type == Type::None) {
        cout << "One step" << endl;
        return true;
    }
    
    Position diag_move_left(move.get_start().get_row() + one_row_ahead, move.get_start().get_col() - 1);
    Position diag_move_right(move.get_start().get_row() + one_row_ahead, move.get_start().get_col() + 1);
    bool side_move = (move.get_end() == diag_move_left || move.get_end() == diag_move_right);
    
    
    if (side_move && capture.type != Type::None) {
        cout << "Sidemove done" << endl;
        return true;
    }
    
    if (!get_is_moved()) {
        cout << "Pawn not moved" << endl;
        Position two_steps(move.get_start().get_row() + two_rows_ahead, move.get_start().get_col());
        
        if (move.get_end() == two_steps && capture.type == Type::None) {
            cout << "Special start move" << endl;
            return true;
        }
    }
    cout << "not legal move" << endl << endl;
    return false;
}
