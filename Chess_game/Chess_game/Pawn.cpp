//
//  Pawn.cpp
//  Chess_game
//
//  Created by Andreas Aurlien on 18.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#include "Piece.hpp"

using namespace std;

Pawn::Pawn(Color color) : Piece(color, Type::Pawn) {}

std::string Pawn::to_string() const {
    if (get_color() == Color::Black) return "Black Pawn";
    else return "White Pawn";
}

bool Pawn::legal_move(Chess& game) const {
    
    if (!is_players_turn(game)) {
        cout << "Not players turn" << endl;
      return false;
    }
    else if (!(is_legal_capture(game))) {
        cout << "Not legal capture" << endl;
        return false;
    }
    if (game.run_is_in_check_simulation(*game.new_move, game.players_turn)) {
        cout << "Check detected" << endl;
        return false;
    }
    cout << "No check dedected" << endl;
    
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
    
    Position one_step(game.new_move->get_start().get_row() + one_row_ahead, game.new_move->get_start().get_col());
    
    if (game.new_move->get_end() == one_step && game.capture->type == Type::None) {
        cout << "One step" << endl;
        return true;
    }
    
    Position diag_move_left(game.new_move->get_start().get_row() + one_row_ahead, game.new_move->get_start().get_col() - 1);
    Position diag_move_right(game.new_move->get_start().get_row() + one_row_ahead, game.new_move->get_start().get_col() + 1);
    bool side_move = (game.new_move->get_end() == diag_move_left || game.new_move->get_end() == diag_move_right);
    
    
    if (side_move && game.capture->type != Type::None) {
        cout << "Sidemove done" << endl;
        return true;
    }
    
    if (!get_is_moved()) {
        cout << "Pawn not moved" << endl;
        Position two_steps(game.new_move->get_start().get_row() + two_rows_ahead, game.new_move->get_start().get_col());
        
        if (game.new_move->get_end() == two_steps && game.capture->type == Type::None) {
            cout << "Special start move" << endl;
            return true;
        }
    }
    
    cout << "not legal move" << endl << endl;
    return false;
}
