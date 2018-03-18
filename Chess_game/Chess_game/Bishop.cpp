//
//  Bishop.cpp
//  Chess_game
//
//  Created by Andreas Aurlien on 18.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#include <stdio.h>

#include "Piece.hpp"

Bishop::Bishop(Color color) : Piece(color, Type::Bishop){}

std::string Bishop::to_string() const {
    if (get_color() == Color::Black) return "Black Bishop";
    else return "White Bishop";
}

bool Bishop::legal_move(array<array<unique_ptr<Piece>, 8>, 8>& board, Move move, Chess_piece capture, Color players_turn) const {
    
    if (players_turn != get_color()) return false;
    
    if (capture.color == get_color()) return false;
    
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
