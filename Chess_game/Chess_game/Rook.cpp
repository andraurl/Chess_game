//
//  Rook.cpp
//  Chess_game
//
//  Created by Andreas Aurlien on 18.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#include "Piece.hpp"


Rook::Rook(Color color) : Piece(color, Type::Rook){}

std::string Rook::to_string() const {
    if (get_color() == Color::Black) return "Black Rook";
    else return "White Rook";
}

bool Rook::legal_move(array<array<unique_ptr<Piece>, 8>, 8>& board, Move move, Chess_piece capture, Color players_turn) const {
    
    cout << "Claculating legal move for rook" << endl;
    
    if (!is_players_turn(players_turn)) {
        return false;
    }
    if (!is_legal_capture(capture)) {
        return false;
    }
    else if (legal_straigt_move(board, move)) {
        return true;
    }
    else
        return false;
}

