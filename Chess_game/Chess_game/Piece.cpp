//
//  Piece.cpp
//  Chess
//
//  Created by Andreas Aurlien on 15.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#include "Piece.hpp"

using namespace std;


bool Position::operator==(Position& rhs) const{
    return (pos_y == rhs.get_row() && pos_x == rhs.get_col());

}

bool Position::operator!=(Position& rhs) const{
    return (pos_y != rhs.get_row() || pos_x != rhs.get_col());
    
}

bool Position::is_inside_board() const{
    return (0 <= pos_x && pos_x <= 7 && 0 <= pos_y && pos_y <= 7);
}


bool Chess_piece::operator==(Chess_piece& rhs) {
    return (color == rhs.color && type == rhs.type);
}



bool Move::operator==(Move& rhs) const {
    return (get_start().pos_y == rhs.get_start().pos_y && get_start().pos_x == rhs.get_start().pos_x
            && get_end().pos_y == rhs.get_end().pos_y && get_end().pos_x == rhs.get_end().pos_x);
}





Piece::Piece(Color color, Type type) : color(color), type(type), is_moved(false) {}


// /* TA VEKK DENNE FOR Å FÅ TILBAKE





bool Piece::is_players_turn(Chess& game) const {
    return game.players_turn == get_color();
}

bool Piece::is_legal_capture(Chess& game) const {
    return (game.capture->color != get_color());
}



bool Piece::legal_diagonal_move(Chess& game) const {
    
    int difference_row = (game.new_move->get_end().get_row() - game.new_move->get_start().get_row());
    int differece_col = (game.new_move->get_end().get_col() - game.new_move->get_start().get_col());
    
    bool move_on_diagonal_A1_H8 = (differece_col == difference_row);
    bool move_on_diagonal_A8_H1 = (differece_col == (difference_row * -1));
    
    // cout << "Checking diag move" << endl;
    // cout << "dif row: " << game.new_move->get_end().get_row() - game.new_move->get_start().get_row() << endl;
    // cout << "dif col: " << game.new_move->get_end().get_col() - game.new_move->get_start().get_col() << endl;
    // cout << "Diag move A1 - H8: " << move_on_diagonal_A1_H8 << endl;;
    // cout << "Diag move A8 - H1: " << move_on_diagonal_A8_H1 << endl;;
    
    
    if (!move_on_diagonal_A1_H8 && !move_on_diagonal_A8_H1) return false;
    cout << "Diagonal move" << endl;
    
    
    int horisontal_itteration;
    int vertical_itteration;
    
    if (game.new_move->get_end().get_col() > game.new_move->get_start().get_col()) {
        horisontal_itteration = 1;
    } else horisontal_itteration = -1;
    
    if (game.new_move->get_end().get_row() > game.new_move->get_start().get_row()) {
        vertical_itteration = 1;
    } else vertical_itteration = -1;
    
    int i = game.new_move->get_start().get_row() + vertical_itteration;
    int j = game.new_move->get_start().get_col() + horisontal_itteration;
    
    while (i != game.new_move->get_end().get_row() && j != game.new_move->get_end().get_col()){
        cout << "Checking for obstacles at (" << i << ", " << j << ")" << endl;
        cout << "Vertical itteration: " << vertical_itteration << endl;
        cout << "Horisantal itteration: " << horisontal_itteration << endl;
        if( game.board[i][j] != nullptr) {
            return false;
        }
        i += vertical_itteration;
        j += horisontal_itteration;
    }
    
    
    return true;
}

bool Piece::legal_straigt_move(Chess& game) const {

    // cout << "2. Got here" << endl;
    int difference_row = (game.new_move->get_end().get_row() - game.new_move->get_start().get_row());
    int difference_col = (game.new_move->get_end().get_col() - game.new_move->get_start().get_col());
    
    bool horisontal_move = (difference_row == 0);
    bool vertical_move = (difference_col == 0);
    
    /*
     cout << "Difference row: " << game.new_move->get_end().get_row() - game.new_move->get_start().get_row() << endl;
     cout << "difference col: " << game.new_move->get_end().get_col() - game.new_move->get_start().get_col() << endl;
     cout << "Horisontal move: " << horisontal_move << endl;
     cout << "Vertical move: " << vertical_move << endl;
     */
    
    if (!horisontal_move && !vertical_move) return false;
    // cout << "3. Got here" << endl;
    cout << "Straight move" << endl;
    
    int horisontal_itteration;
    int vertical_itteration;
    
    if (game.new_move->get_end().get_col() > game.new_move->get_start().get_col()) {
        horisontal_itteration = 1;
    }
    else if (game.new_move->get_end().get_col() < game.new_move->get_start().get_col()){
        horisontal_itteration = -1;
        
    } else horisontal_itteration = 0;
    
    if (game.new_move->get_end().get_row() > game.new_move->get_start().get_row()) {
        vertical_itteration = 1;
    } else if (game.new_move->get_end().get_row() < game.new_move->get_start().get_row()){
        vertical_itteration = -1;
    }
    else vertical_itteration = 0;
    
    int i = game.new_move->get_start().get_row() + vertical_itteration;
    int j = game.new_move->get_start().get_col() + horisontal_itteration;
    
    /*
     cout << "Vertical itteration: " << vertical_itteration << endl;
     cout << "Horisantal itteration: " << horisontal_itteration << endl;
     cout << " End position: (" << game.new_move->get_end().get_row() << ", " << game.new_move->get_end().get_col() << ")" << endl;
     */
    
    Position itteration_pos(i, j);
    
    while (game.new_move->get_end() != itteration_pos){
        cout << "Checking for obstacles at (" << i << ", " << j << ")" << endl;
        if( game.board[i][j] != nullptr) {
            return false;
        }
        i += vertical_itteration;
        j += horisontal_itteration;
        itteration_pos = Position(i, j);
    }
    return true;
}










// TA VEKK DENNE FOR Å FÅ TILBAKE */

