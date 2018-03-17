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

enum class Chess_piece
{
    King = 0, Queen, Rook, Bishop, Kningt, Pawn
};

enum class Color
{
    White = 0, Black
};

struct Position {
    int pos_y;
    int pos_x;
public:
    Position() {};
    Position(int row, int col) {pos_y = row; pos_x = col;}
};


struct Move {
private:
    Position p1;
    Position p2;
public:
    Move(Position start, Position end) {p1 = start; p2 = end;}
};


class Piece
{
private:
    Color color;
    Chess_piece type;
public:
    Piece(Color color, Chess_piece type);
    Chess_piece get_type() const {return type;}
    Color get_color() const {return color;}
    virtual std::string to_string() const = 0;
    virtual bool leagal_move(Move move) const = 0;
    
};

// /* TA VEKK DENNE FOR Å FÅ TILBAKE

class King : public Piece
{
private:
public:
    King(Color color);
    bool leagal_move(Move move) const {return true;}
    std::string to_string() const;
    
};


class Queen : public Piece
{
private:
public:
    Queen(Color color);
    bool leagal_move(Move move) const {return true;}
    std::string to_string() const;
    
};


class Rook : public Piece
{
private:
public:
    Rook(Color color);
    bool leagal_move(Move move) const {return true;}
    std::string to_string() const;
    
};

class Bishop : public Piece
{
private:
public:
    Bishop(Color color);
    bool leagal_move(Move move) const {return true;}
    std::string to_string() const;
    
};

class Knight : public Piece
{
private:
public:
    Knight(Color color);
    bool leagal_move(Move move) const {return true;}
    std::string to_string() const;
    
};

class Pawn : public Piece
{
private:
public:
    Pawn(Color color);
    bool leagal_move(Move move) const {return false;}
    std::string to_string() const;
    
};
// */ TA VEKK DENNE FOR Å FÅ TILBAKE


