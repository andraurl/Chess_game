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
    
    
    unique_ptr<Chess_piece> last_moved_piece_before_move;
    unique_ptr<Move> last_move;

    unique_ptr<Chess_piece> capture;
    unique_ptr<Move> new_move;

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
    bool is_inside_board(int row, int col) const;
    bool is_an_passant_move() const;
    void set_last_moved_piece(Chess_piece piece);
    void set_last_move(Move move);
    
    void make_simulated_board(array<array<unique_ptr<Piece>, 8>, 8>& board_copy) const;
    Position find_king_of_interest(array<array<unique_ptr<Piece>, 8>, 8>& board_copy) const;
    bool is_check_form_lines(array<array<unique_ptr<Piece>, 8>, 8>& board_copy, Position king_pos) const;
    bool is_check_form_knight(array<array<unique_ptr<Piece>, 8>, 8>& board_copy, Position king_pos) const;
    bool run_is_in_check_simulation() const;

    bool try_move_piece();
    // bool is_leagal_move() const {return true;} // SKAL VÆRE I PIECE SÅ MÅ FJERNES!!!
    int get_number_of_marked_tiles() const {return number_of_marked_tiles;}
    void change_players_turn();
    
    friend class Piece;
    friend class King;
    // friend class Queen;
    // friend class Rook;
    // friend class Bishop;
    friend class Knight;
    friend class Pawn;
    
    
    
    // std::unique_ptr<Piece>& get_pointer(int row, int col) const;
    // std::unique_ptr<Piece> get_start_piece(int row, int col) const;
    
    
};
