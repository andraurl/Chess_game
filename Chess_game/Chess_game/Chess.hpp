//
//  Chess.hpp
//  Chess
//
//  Created by Andreas Aurlien on 15.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#pragma once

#include <stdio.h>
// #include <vector>
#include <array>
#include <assert.h>
#include <iostream>

#include "Piece.hpp"
#include "Unique_ptr.hpp"

using namespace std;
struct Position;
struct Move;

class Chess
{
private:
    array<array<unique_ptr<Piece>, 8>, 8> board;
    int number_of_marked_tiles;
    Color players_turn;
    unique_ptr<Position> first_marked_piece;
    unique_ptr<Position> second_marked_piece;
public:
    Chess();
    bool has_start_piece(int row) const;
    void list_all_pieces() const;
    
    // bool is_piece(int row, int col, Chess_piece piece) const;
    bool is_piece_nullptr(int row, int col) const;
    void piece_on_tile(int row, int col, Color& color, Type& piece_to_draw) const;
    bool is_piece_moved(Position p) const;
    bool isGameOver() const {return false;};
    bool isGameWon() const {return false;};
    void set_marked_tile(int row, int col);
    bool try_move_piece();
    // bool is_leagal_move() const {return true;} // SKAL VÆRE I PIECE SÅ MÅ FJERNES!!!
    int get_number_of_marked_tiles() const {return number_of_marked_tiles;}
    void change_players_turn();
    
    
    
    // std::unique_ptr<Piece>& get_pointer(int row, int col) const;
    // std::unique_ptr<Piece> get_start_piece(int row, int col) const;
    
    
};
