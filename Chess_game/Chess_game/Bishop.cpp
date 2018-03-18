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

bool Bishop::leagal_move(array<array<unique_ptr<Piece>, 8>, 8>& board, Move move, Chess_piece capture, Color players_turn) const {
    
    if (players_turn != get_color()) return false;
    
    if (capture.color == get_color()) return false;
    
    int difference_row = (move.get_end().get_row() - move.get_start().get_row());
    int differece_col = (move.get_end().get_col() - move.get_start().get_col());
    
    bool move_on_diagonal_A1_H8 = (differece_col == difference_row);
    bool move_on_diagonal_A8_H1 = (differece_col == -difference_row);
    
    if (!move_on_diagonal_A1_H8 || !move_on_diagonal_A1_H8) return false;

    
    int horisontal_itteration;
    int vertical_itteration;
    
    if (move.get_end().get_col() > move.get_start().get_col()) {
        horisontal_itteration = 1;
    } else horisontal_itteration = -1;

    if (move.get_end().get_row() > move.get_start().get_row()) {
        vertical_itteration = 1;
    } else vertical_itteration = -1;
    
    int j = move.get_start().get_col();
    for (int i = move.get_start().get_row(); i < move.get_end().get_row(); i += vertical_itteration) {
        //if (true)
    }

    
    return true;
    
}
