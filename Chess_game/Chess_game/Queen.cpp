//
//  Queen.cpp
//  Chess_game
//
//  Created by Andreas Aurlien on 18.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#include "Piece.hpp"

Queen::Queen(Color color) : Piece(color, Type::Queen) {}

std::string Queen::to_string() const {
    if (get_color() == Color::Black) return "Black Queen";
    else return "White Queen";
}

bool Queen::legal_move(Chess& game) const {
    
    cout << "Claculating legal move for queen" << endl;
    
    if (!is_players_turn(game.players_turn)) {
        cout << "Not players turn" << endl;
        return false;
    }
    if (!is_legal_capture(*game.capture)) {
        cout << "Not legal capture" << endl;
        return false;
    }
    else if (game.run_is_in_check_simulation(*game.new_move, game.players_turn)) {
        cout << "Check detected" << endl;
        return false;
    }
    else if (legal_straigt_move(game.board, *game.new_move)) {
        cout << "Legal straight move" << endl;
        return true;
    }
    else if (legal_diagonal_move(game.board, *game.new_move)) {
        cout << "Legal diagonal move" << endl;
        return true;
    }
    else
        cout << "Not legal move" << endl;
        return false;
}


