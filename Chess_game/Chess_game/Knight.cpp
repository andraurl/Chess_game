//
//  Knight.cpp
//  Chess_game
//
//  Created by Andreas Aurlien on 18.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#include <stdio.h>

#include "Piece.hpp"

Knight::Knight(Color color) : Piece(color, Type::Kningt) {}

std::string Knight::to_string() const {
    if (get_color() == Color::Black) return "Black Knight";
    else return "White Knight";
}

bool Knight::legal_move(Chess& game) const {
    
    if (game.players_turn != get_color()) {
        
        cout << "Not players turn" << endl;
        return false;
    }
    
    else if (game.capture->color == get_color()) {
        
        cout << "Not legal capture" << endl;
        return false;
    }
    
    else if (!is_normal_move(game)){
        
        cout << "Not normal move" << endl;
        return false;
    }
    
    else if (game.run_is_in_check_simulation()) {
        
        cout << "Check detected" << endl;
        return false;
    }
    
    else {
        
        return true;
    }
}

bool Knight::is_normal_move(Chess& game) const {
    
    int row_difference = game.new_move->get_end().get_row() - game.new_move->get_start().get_row();
    int col_difference = game.new_move->get_end().get_col() - game.new_move->get_start().get_col();
    
    bool normal_move = (abs(row_difference) == 2 && abs(col_difference) == 1)
                    || (abs(row_difference) == 1 && abs(col_difference) == 2);

    return normal_move;
}

