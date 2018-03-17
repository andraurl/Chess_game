//
//  sfml_functions.cpp
//  Chess
//
//  Created by Andreas Aurlien on 16.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#include "sfml_functions.hpp"




sf::Sprite get_sprite(Color color, Type piece){
    sf::Texture texture;
    string texture_string;
    switch (piece) {
        case Type::King:
        {
            if (color == Color::White) texture_string = "Chess_klt60.png";
            else texture_string = "Chess_kdt60.png";
            break;
        }
        
        case Type::Queen:
        {
            if (color == Color::White) texture_string = "Chess_qlt60.png";
            else texture_string = "Chess_qdt60.png";
            break;
        }
            
        case Type::Rook:
        {
            if (color == Color::White) texture_string = "Chess_rlt60.png";
            else texture_string = "Chess_rdt60.png";
            break;
        }
            
        case Type::Bishop:
        {
            if (color == Color::White) texture_string = "Chess_blt60.png";
            else texture_string = "Chess_bdt60.png";
            break;
        }
            
        case Type::Kningt:
        {
            if (color == Color::White) texture_string = "Chess_nlt60.png";
            else texture_string = "Chess_ndt60.png";
            break;
        }
            
        case Type::Pawn:
        {
            if (color == Color::White) texture_string = "Chess_plt60.png";
            else texture_string = "Chess_pdt60.png";
            break;
        }
            
        default:
            break;
    }
    
    
    
    if (!texture.loadFromFile(resourcePath() + texture_string)) {cout << "Could not lode file"<< endl;}
    
    
    sf::Sprite picture;
    picture.setTexture(texture);
    picture.setOrigin(30, 30);
    
    return picture;
}

