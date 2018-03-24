//
//  Piece.hpp
//  Chess
//
//  Created by Andreas Aurlien on 15.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <assert.h>
#include <array>
#include "Unique_ptr.hpp"


enum class Type;
enum class Color;
struct Position;
struct Move;
struct Chess_piece;
class Piece;
class Chess;

#include "Chess.hpp"

using namespace std;



enum class Type
{
    King = 0, Queen, Rook, Bishop, Kningt, Pawn, None
};

enum class Color
{
    White = 0, Black, None
};


struct Position {
    int pos_y;
    int pos_x;
public:
    Position() {};
    Position(int row, int col) {pos_y = row; pos_x = col;}
    int get_row() const {return pos_y;}
    int get_col() const {return pos_x;}
    bool is_inside_board() const;
    bool operator==(Position& rhs) const;
    bool operator!=(Position& rhs) const;
};


struct Move {
    Position p1;
    Position p2;
public:
    Move(Position start, Position end) {p1 = start; p2 = end;}
    Position get_start() const {return p1;}
    Position get_end() const {return p2;}
    bool operator==(Move& rhs) const;
};


struct Chess_piece{
    Color color;
    Type type;
public:
    Chess_piece(Color c, Type t) {color = c; type = t;}
    bool operator==(Chess_piece& rhs);
};


class Piece
{
private:
    Color color;
    Type type;
    bool is_moved;
public:
    Piece(Color color, Type type);
    Type get_type() const {return type;}
    Color get_color() const {return color;}
    bool get_is_moved() const {return is_moved;}
    void set_is_moved() {is_moved = true;}
    bool is_players_turn(Chess& game) const;
    bool is_legal_capture(Chess& game) const;
    bool legal_straigt_move(Chess& game) const;
    bool legal_diagonal_move(Chess& game) const;
    virtual bool is_legal_casteling(Chess& game) const {return false;}
    virtual std::string to_string() const = 0;
    virtual bool legal_move(Chess& game) const = 0;
    
};

// /* TA VEKK DENNE FOR Å FÅ TILBAKE

class King : public Piece
{
private:
public:
    King(Color color);
    bool legal_move(Chess& game) const;
    bool is_one_step(Chess& game) const;
    bool is_two_steps_left(Chess& game) const;
    bool is_two_steps_right(Chess& game) const;
    bool is_legal_casteling(Chess& game) const;
    bool is_check_through_casteling(Chess& game) const;
    std::string to_string() const;
    
};


class Queen : public Piece
{
private:
public:
    Queen(Color color);
    bool legal_move(Chess& game) const;
    std::string to_string() const;
    
};


class Rook : public Piece
{
private:
public:
    Rook(Color color);
    bool legal_move(Chess& game) const;
    std::string to_string() const;
    
};

class Bishop : public Piece
{
private:
public:
    Bishop(Color color);
    bool legal_move(Chess& game) const;
    std::string to_string() const;
    
};

class Knight : public Piece
{
private:
public:
    Knight(Color color);
    bool legal_move(Chess& game) const;
    std::string to_string() const;
    
};

class Pawn : public Piece
{
private:
public:
    Pawn(Color color);
    bool legal_move(Chess& game) const;
    std::string to_string() const;
    
};
// */ TA VEKK DENNE FOR Å FÅ TILBAKE


