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
    
    // if (players_turn != get_color()) return false;
    // cout << "1. Got here" << endl;
    if (capture.color == get_color()) return false;
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

