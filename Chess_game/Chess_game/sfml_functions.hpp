//
//  sfml_functions.hpp
//  Chess
//
//  Created by Andreas Aurlien on 16.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#ifndef sfml_functions_hpp
#define sfml_functions_hpp

#include <stdio.h>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "Chess.hpp"
#include "Piece.hpp"


sf::Sprite get_sprite(Color color, Chess_piece piece);

#endif /* sfml_functions_hpp */
