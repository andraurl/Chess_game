//
//  Piece.hpp
//  Chess
//
//  Created by Andreas Aurlien on 15.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#ifndef Piece_hpp
#define Piece_hpp

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
    // virtual void leagal_move() = 0;
    
};

// /* TA VEKK DENNE FOR Å FÅ TILBAKE

class King : public Piece
{
private:
public:
    King(Color color);
    void leagal_move() const;
    std::string to_string() const;
    
};


class Queen : public Piece
{
private:
public:
    Queen(Color color);
    void leagal_move() const;
    std::string to_string() const;
    
};


class Rook : public Piece
{
private:
public:
    Rook(Color color);
    void leagal_move() const;
    std::string to_string() const;
    
};

class Bishop : public Piece
{
private:
public:
    Bishop(Color color);
    void leagal_move() const;
    std::string to_string() const;
    
};

class Knight : public Piece
{
private:
public:
    Knight(Color color);
    void leagal_move() const;
    std::string to_string() const;
    
};

class Pawn : public Piece
{
private:
public:
    Pawn(Color color);
    void leagal_move() const;
    std::string to_string() const;
    
};
// */ TA VEKK DENNE FOR Å FÅ TILBAKE
#endif /* Piece_hpp */


