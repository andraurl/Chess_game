//
//  Queen.cpp
//  Chess_game
//
//  Created by Andreas Aurlien on 18.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#include "Piece.hpp"

Queen::Queen(Color color) : Piece(color, Type::Queen) {}

std::string Queen::to_string() const {
    if (get_color() == Color::Black) return "Black Queen";
    else return "White Queen";
}

bool Queen::legal_move(Chess& game, array<array<unique_ptr<Piece>, 8>, 8>& board, Move move, Chess_piece capture, Color players_turn) const {
    
    cout << "Claculating legal move for queen" << endl;
    
    if (!is_players_turn(players_turn)) {
        return false;
    }
    if (!is_legal_capture(capture)) {
        return false;
    }
    else if (legal_straigt_move(board, move)) {
        return true;
    }
    else if (legal_diagonal_move(board, move)) {
        return true;
    }
    else
        return false;
}


