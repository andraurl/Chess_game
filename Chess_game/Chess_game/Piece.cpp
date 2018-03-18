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









bool Piece::is_players_turn(Color players_turn) const {
    return players_turn == get_color();
}

bool Piece::is_legal_capture(Chess_piece capture) const {
    return (capture.color != get_color());
}



bool Piece::legal_diagonal_move(array<array<unique_ptr<Piece>, 8>, 8>& board, Move move, Chess_piece capture, Color players_turn) const {
    
    int difference_row = (move.get_end().get_row() - move.get_start().get_row());
    int differece_col = (move.get_end().get_col() - move.get_start().get_col());
    
    bool move_on_diagonal_A1_H8 = (differece_col == difference_row);
    bool move_on_diagonal_A8_H1 = (differece_col == (difference_row * -1));
    
    // cout << "Checking diag move" << endl;
    // cout << "dif row: " << move.get_end().get_row() - move.get_start().get_row() << endl;
    // cout << "dif col: " << move.get_end().get_col() - move.get_start().get_col() << endl;
    // cout << "Diag move A1 - H8: " << move_on_diagonal_A1_H8 << endl;;
    // cout << "Diag move A8 - H1: " << move_on_diagonal_A8_H1 << endl;;
    
    
    if (!move_on_diagonal_A1_H8 && !move_on_diagonal_A8_H1) return false;
    cout << "Diagonal move" << endl;
    
    
    int horisontal_itteration;
    int vertical_itteration;
    
    if (move.get_end().get_col() > move.get_start().get_col()) {
        horisontal_itteration = 1;
    } else horisontal_itteration = -1;
    
    if (move.get_end().get_row() > move.get_start().get_row()) {
        vertical_itteration = 1;
    } else vertical_itteration = -1;
    
    int i = move.get_start().get_row() + vertical_itteration;
    int j = move.get_start().get_col() + horisontal_itteration;
    
    while (i != move.get_end().get_row() && j != move.get_end().get_col()){
        cout << "Checking for obstacles at (" << i << ", " << j << ")" << endl;
        cout << "Vertical itteration: " << vertical_itteration << endl;
        cout << "Horisantal itteration: " << horisontal_itteration << endl;
        if( board[i][j] != nullptr) {
            return false;
        }
        i += vertical_itteration;
        j += horisontal_itteration;
    }
    
    
    return true;
}

bool Piece::legal_straigt_move(array<array<unique_ptr<Piece>, 8>, 8>& board, Move move, Chess_piece capture, Color players_turn) const {

    // cout << "2. Got here" << endl;
    int difference_row = (move.get_end().get_row() - move.get_start().get_row());
    int difference_col = (move.get_end().get_col() - move.get_start().get_col());
    
    bool horisontal_move = (difference_row == 0);
    bool vertical_move = (difference_col == 0);
    
    /*
     cout << "Difference row: " << move.get_end().get_row() - move.get_start().get_row() << endl;
     cout << "difference col: " << move.get_end().get_col() - move.get_start().get_col() << endl;
     cout << "Horisontal move: " << horisontal_move << endl;
     cout << "Vertical move: " << vertical_move << endl;
     */
    
    if (!horisontal_move && !vertical_move) return false;
    // cout << "3. Got here" << endl;
    cout << "Straight move" << endl;
    
    int horisontal_itteration;
    int vertical_itteration;
    
    if (move.get_end().get_col() > move.get_start().get_col()) {
        horisontal_itteration = 1;
    }
    else if (move.get_end().get_col() < move.get_start().get_col()){
        horisontal_itteration = -1;
        
    } else horisontal_itteration = 0;
    
    if (move.get_end().get_row() > move.get_start().get_row()) {
        vertical_itteration = 1;
    } else if (move.get_end().get_row() < move.get_start().get_row()){
        vertical_itteration = -1;
    }
    else vertical_itteration = 0;
    
    int i = move.get_start().get_row() + vertical_itteration;
    int j = move.get_start().get_col() + horisontal_itteration;
    
    /*
     cout << "Vertical itteration: " << vertical_itteration << endl;
     cout << "Horisantal itteration: " << horisontal_itteration << endl;
     cout << " End position: (" << move.get_end().get_row() << ", " << move.get_end().get_col() << ")" << endl;
     */
    
    Position itteration_pos(i, j);
    
    while (move.get_end() != itteration_pos){
        cout << "Checking for obstacles at (" << i << ", " << j << ")" << endl;
        if( board[i][j] != nullptr) {
            return false;
        }
        i += vertical_itteration;
        j += horisontal_itteration;
        itteration_pos = Position(i, j);
    }
    return true;
}









// TA VEKK DENNE FOR Å FÅ TILBAKE */

