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
    bool is_same_position = (pos_y == rhs.get_row()) && (pos_x == rhs.get_col());
    return (is_same_position);
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

bool Pawn::leagal_move(Move move, Chess_piece capture) const {
    switch (get_color()) {
        case Color::Black:
            cout << "Claculating leagal move for black pawn" << endl;
            if (!get_is_moved()) {
                cout << "Black pawn not moved" << endl;
                Position one_step = Position(move.get_start().get_row() - 1, move.get_start().get_col());
                Position two_steps = Position(move.get_start().get_row() - 2, move.get_start().get_col());
                if ((move.get_end() == one_step) || (move.get_end() == two_steps)) {
                    cout << "legal move" << endl;
                    return true;
                }
                else {
                    cout << "not legal move" << endl << endl;
                    return false;
                }
            }
            break;
        case Color::White:
            cout << "Claculating leagal move for white pawn" << endl;
            if (!get_is_moved()) {
                cout << "White pawn not moved" << endl;
                Position one_step = Position(move.get_start().get_row() + 1, move.get_start().get_col());
                Position two_steps = Position(move.get_start().get_row() + 2, move.get_start().get_col());
                
                // cout << move.get_end().get_row() << " vs " << one_step.get_row();
                
                if ((move.get_end() == one_step) || (move.get_end() == two_steps)) {
                    cout << "legal move" << endl;
                    return true;
                }
                
                else {
                    cout << "not legal move" << endl << endl;
                    return false;
                }
                
            }
            break;
            
        default:
            break;
    }
    if (capture.color == get_color()) return false;
    /* switch (get_color()) {
            
        case Color::Black: {
            cout << "Claculating leagal move for black pawn" << endl;
            break;
        }
            
        case Color::White: {
            if (!get_is_moved()) {
                cout << "Claculating leagal move for white pawn" << endl;
                Position one_step = Position(move.get_end().get_row() + 1, move.get_end().get_col());
                Position two_steps = Position(move.get_end().get_row() + 2, move.get_end().get_col());
                if (move.get_end() == one_step || move.get_end() == two_steps) {
                    return true;
                }
            }
            
            break;
        }

        default:
            break;
    }
    */
    
    return true;
}

// TA VEKK DENNE FOR Å FÅ TILBAKE */

