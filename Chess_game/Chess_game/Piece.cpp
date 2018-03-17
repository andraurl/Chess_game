//
//  Piece.cpp
//  Chess
//
//  Created by Andreas Aurlien on 15.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#include "Piece.hpp"

Piece::Piece(Color color, Type type) : color(color), type(type) {}


// /* TA VEKK DENNE FOR Å FÅ TILBAKE
King::King(Color color) : Piece(color, Type::King) {}

std::string King::to_string() const {
    if (get_color() == Color::Black) return "Black King";
    else return "White King";
}

Queen::Queen(Color color) : Piece(color, Type::Queen) {}

std::string Queen::to_string() const {
    if (get_color() == Color::Black) return "Black Queen";
    else return "White Queen";
}


Rook::Rook(Color color) : Piece(color, Type::Rook){}

std::string Rook::to_string() const {
    if (get_color() == Color::Black) return "Black Rook";
    else return "White Rook";
}

Bishop::Bishop(Color color) : Piece(color, Type::Bishop){}

std::string Bishop::to_string() const {
    if (get_color() == Color::Black) return "Black Bishop";
    else return "White Bishop";
}


Knight::Knight(Color color) : Piece(color, Type::Kningt){}

std::string Knight::to_string() const {
    if (get_color() == Color::Black) return "Black Knight";
    else return "White Knight";
}


Pawn::Pawn(Color color) : Piece(color, Type::Pawn){}

std::string Pawn::to_string() const {
    if (get_color() == Color::Black) return "Black Pawn";
    else return "White Pawn";
}

bool Pawn::leagal_move(Move move, Chess_piece capture) const {
    if (capture.color == get_color()) return false;
    
    return true;
}

// TA VEKK DENNE FOR Å FÅ TILBAKE */

