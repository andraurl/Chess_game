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


Knight::Knight(Color color) : Piece(color, Type::Kningt) {}

std::string Knight::to_string() const {
    if (get_color() == Color::Black) return "Black Knight";
    else return "White Knight";
}


Pawn::Pawn(Color color) : Piece(color, Type::Pawn) {}

std::string Pawn::to_string() const {
    if (get_color() == Color::Black) return "Black Pawn";
    else return "White Pawn";
}

bool Pawn::leagal_move(Move move, Chess_piece capture, Color players_turn) const {
    
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

// TA VEKK DENNE FOR Å FÅ TILBAKE */

