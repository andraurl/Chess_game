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
    
    if (game.capture->color == get_color()) {
        cout << "Not legal capture" << endl;
        return false;
    }
    
    Position up_left(game.new_move->get_start().get_row() + 2, game.new_move->get_start().get_col() - 1);
    Position up_right(game.new_move->get_start().get_row() + 2, game.new_move->get_start().get_col() + 1);
    Position right_up(game.new_move->get_start().get_row() + 1, game.new_move->get_start().get_col() + 2);
    Position right_down(game.new_move->get_start().get_row() - 1, game.new_move->get_start().get_col() + 2);
    Position down_right(game.new_move->get_start().get_row() - 2, game.new_move->get_start().get_col() + 1);
    Position down_left(game.new_move->get_start().get_row() - 2, game.new_move->get_start().get_col() - 1);
    Position left_down(game.new_move->get_start().get_row() - 1, game.new_move->get_start().get_col() - 2);
    Position left_up(game.new_move->get_start().get_row() + 1, game.new_move->get_start().get_col() - 2);
    
    bool normal_move  =   (game.new_move->get_end() == up_left || game.new_move->get_end() == up_right
                        || game.new_move->get_end() == right_up || game.new_move->get_end() == right_down
                        || game.new_move->get_end() == down_right || game.new_move->get_end() == down_left
                        || game.new_move->get_end() == left_down || game.new_move->get_end() == left_up);
    
    if (!normal_move) {
        cout << "Not normal move" << endl;
        return false;
    }
    
    if (game.run_is_in_check_simulation()) {
        cout << "Check detected" << endl;
        return false;
    }
    
    else {
        return true;
    }
}

