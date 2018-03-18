//
//  Piece.cpp
//  Chess
//
//  Created by Andreas Aurlien on 15.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#include "Piece.hpp"

using namespace std;

bool Position::operator==(Position& rhs) {
    return (pos_y == rhs.get_row() && pos_x == rhs.get_col());

}

bool Position::operator!=(Position& rhs) {
    return (pos_y != rhs.get_row() || pos_x != rhs.get_col());
    
}

bool Position::is_inside_board() {
    return (0 <= pos_x && pos_x <= 7 && 0 <= pos_y && pos_y <= 7);
}


bool Chess_piece::operator==(Chess_piece& rhs) {
    return (color == rhs.color && type == rhs.type);
}


Piece::Piece(Color color, Type type) : color(color), type(type), is_moved(false) {}


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









// TA VEKK DENNE FOR Å FÅ TILBAKE */

