
//
// Disclaimer:
// ----------
//
// This code will work only if you selected window, graphics and audio.
//
// Note that the "Run Script" build phase will copy the required frameworks
// or dylibs to your application bundle so you can execute it on any OS X
// computer.
//
// Your resource files (images, sounds, fonts, ...) are also copied to your
// application bundle. To get the path to these resources, use the helper
// function `resourcePath()` from ResourcePath.hpp
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

// Here is a small helper for you! Have a look.
#include "ResourcePath.hpp"
#include "Chess.hpp"
#include "sfml_functions.hpp"

const int tile_size = 70;
const int border_size = 2;

sf::Color white = sf::Color::White;
sf::Color black = sf::Color::Black;
sf::Color gray = sf::Color(100, 100, 100);
sf::Color red = sf::Color::Red;





int main(int, char const**)
{
    // assert(false && "Something wring");
    Chess* game = new Chess();
    
    
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(560, 560), "Chess");

    // Create a graphical text to display
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    
    // Set the Icon
   
    sf::Texture black_king;        if (!black_king.loadFromFile(resourcePath() + "Chess_kdt60.png")) {return EXIT_FAILURE;}
    sf::Sprite black_king_image;
    black_king_image.setTexture(black_king);
    black_king_image.setOrigin(30, 30);
    
    black_king_image.setPosition(35, 35);

    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            switch (event.type) {
                case sf::Event::Closed:{
                    window.close();
                    break;
                }
                case sf::Event::KeyPressed:
                    
                    switch (event.key.code) {
                        case sf::Event::Closed:
                        case sf::Keyboard::Q:
                            window.close();
                            break;
                        case sf::Keyboard::Space:
                            delete game;
                            game = new Chess();
                            break;
                    }
                case sf::Event::MouseButtonPressed:
                    bool outOfRange = (event.mouseButton.y / tile_size < 0 || event.mouseButton.y / tile_size > 7
                                    || event.mouseButton.x / tile_size < 0 || event.mouseButton.x / tile_size > 7);
                    if (event.mouseButton.button == sf::Mouse::Left && !game->isGameOver() && !game->isGameWon() && !outOfRange) {
                        int mouse_y = 7 - (event.mouseButton.y / tile_size);
                        int mouse_x = event.mouseButton.x / tile_size;
                        cout << "Mouse pressed at: " << mouse_y << ", " << mouse_x << endl;
                        game->set_marked_tile(mouse_y, mouse_x);
                        if(game->get_number_of_marked_tiles() == 2){
                            if (game->try_move_piece()){
                                game->change_players_turn();
                            }
                        }
                        //gam
                    break;
                    
                    
            }
            
        }

            // Escape pressed: exit
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                window.close();
            }
            
            // Mouse pressed
            
        }

        // Clear screen
        window.clear();
        
        for (int row = 0; row < 8; row++)
        {
            for (int col = 0; col < 8; col++)
            {
                const int tile_x = col * tile_size, tile_y = row * tile_size;
                sf::RectangleShape tile;
                tile.setSize(sf::Vector2f(tile_size - border_size, tile_size - border_size));
                
                sf::Color color;
                if (row % 2 == 0)
                {
                    if (col % 2 == 0)
                    {
                        color = white;
                    }
                    else
                        color = gray;
                }
                else if (col % 2 == 0)
                {
                    color = gray;
                }
                else
                {
                    color = white;
                }
                
                tile.setFillColor(color);
                
                
                tile.setPosition(tile_x + border_size / 2.0, tile_y + border_size / 2.0);
                
                window.draw(tile);
            }
        }
    
        // Draw the string
        // window.draw(text);
        
        //game->list_all_pieces();
        
        for (int row = 0; row < 8; row++)
        {
            for (int col = 0; col < 8; col++)
            {
                if (!game->is_piece_nullptr(row, col))
                {
                    
                    Chess_piece piece_to_draw;
                    Color color;
                    
                    game->piece_on_tile(row, col, color, piece_to_draw);
                    // cout << "Position: row " << row << ", col " << col << endl;
                    
                    
                    
                    // sf::Sprite piece_picture = get_sprite(Color::Black, Chess_piece::King);
                    
                    
                
                    sf::Texture texture;
                    string texture_string;
                    switch (piece_to_draw) {
                        case Chess_piece::King:
                        {
                            if (color == Color::White) texture_string = "Chess_klt60.png";
                            else texture_string = "Chess_kdt60.png";
                            break;
                        }
                            
                        case Chess_piece::Queen:
                        {
                            if (color == Color::White) texture_string = "Chess_qlt60.png";
                            else texture_string = "Chess_qdt60.png";
                            break;
                        }
                            
                        case Chess_piece::Rook:
                        {
                            if (color == Color::White) texture_string = "Chess_rlt60.png";
                            else texture_string = "Chess_rdt60.png";
                            break;
                        }
                            
                        case Chess_piece::Bishop:
                        {
                            if (color == Color::White) texture_string = "Chess_blt60.png";
                            else texture_string = "Chess_bdt60.png";
                            break;
                        }
                            
                        case Chess_piece::Kningt:
                        {
                            if (color == Color::White) texture_string = "Chess_nlt60.png";
                            else texture_string = "Chess_ndt60.png";
                            break;
                        }
                            
                        case Chess_piece::Pawn:
                        {
                            if (color == Color::White) texture_string = "Chess_plt60.png";
                            else texture_string = "Chess_pdt60.png";
                            break;
                        }
                            
                        default:
                            break;
                    }
                    
                    
                    
                    if (!texture.loadFromFile(resourcePath() + texture_string)) {cout << "Could not lode file"<< endl;}
                    
                    
                    sf::Sprite piece_picture;
                    piece_picture.setTexture(texture);
                    piece_picture.setOrigin(30, 30);
                    

                    piece_picture.setPosition(col * tile_size + tile_size / 2.0, (7 - row) * tile_size + tile_size / 2.0);
                    window.draw(piece_picture);
                    
                    
                    
                }
            }
        }
        
        //window.draw(black_king_image);

        // Update the window
        window.display();
    }

    return EXIT_SUCCESS;
}
