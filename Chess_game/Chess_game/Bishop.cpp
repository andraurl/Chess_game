//
//  Bishop.cpp
//  Chess_game
//
//  Created by Andreas Aurlien on 18.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#include "Piece.hpp"

Bishop::Bishop(Color color) : Piece(color, Type::Bishop){}

std::string Bishop::to_string() const {
    if (get_color() == Color::Black) return "Black Bishop";
    else return "White Bishop";
}

bool Bishop::legal_move(Chess& game) const {
    
    if (!is_players_turn(players_turn)) {
        cout << "Not players turn" << endl;
        return false;
    }
    else if (!is_legal_capture(capture)) {
        cout << "Not legal capture" << endl;
        return false;
    }
    else if (game.run_is_in_check_simulation(move, players_turn)) {
        cout << "Check detected" << endl;
        return false;
    }
    else if (legal_diagonal_move(board, move)) {
        cout << "Legal diagonal move" << endl;
        return true;
    }
    else
        cout << "Not legal move" << endl;
        return false;
}
