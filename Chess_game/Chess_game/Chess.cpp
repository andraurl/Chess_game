
//
//  Chess.cpp
//  Chess
//
//  Created by Andreas Aurlien on 15.03.2018.
//  Copyright © 2018 Andreas Aurlien. All rights reserved.
//

#include "Chess.hpp"

using namespace std;

Chess::Chess()
{
    // reset_maked_tiles();
    number_of_marked_tiles = 0;
    players_turn = Color::White;
    first_marked_piece = nullptr;
    second_marked_piece = nullptr;
    capture = nullptr;
    new_move = nullptr;
    
    // PAWNS
    for (int i = 0; i < 8; i++)
    {
        board[1][i] = make_unique<Pawn>(Color::White);
        board[6][i] = make_unique<Pawn>(Color::Black);
    }
    // WHITE
    board[0][0] = move(make_unique<Rook>(Color::White));
    board[0][1] = move(make_unique<Knight>(Color::White));
    board[0][2] = move(make_unique<Bishop>(Color::White));
    board[0][3] = move(make_unique<Queen>(Color::White));
    board[0][4] = move(make_unique<King>(Color::White));
    board[0][5] = move(make_unique<Bishop>(Color::White));
    board[0][6] = move(make_unique<Knight>(Color::White));
    board[0][7] = move(make_unique<Rook>(Color::White));
    
    // BLACK
    board[7][0] = move(make_unique<Rook>(Color::Black));
    board[7][1] = move(make_unique<Knight>(Color::Black));
    board[7][2] = move(make_unique<Bishop>(Color::Black));
    board[7][3] = move(make_unique<Queen>(Color::Black));
    board[7][4] = move(make_unique<King>(Color::Black));
    board[7][5] = move(make_unique<Bishop>(Color::Black));
    board[7][6] = move(make_unique<Knight>(Color::Black));
    board[7][7] = move(make_unique<Rook>(Color::Black));
    
    
    // SETS THE REST TO NULLPTR;
    for (int row = 2; row < 6; row++) {
        for (int col = 0; col < 7; col ++)
            board[row][col] = nullptr;
    }
    
    /*
     int row_count = 0;
     for (auto& row : board)
     {
     int col_count = 0;
     for (auto& piece : row)
     {
     if (has_start_piece(row_count))
     {
     
     //auto temp_piece = get_start_piece(row_count, col_count);
     
     //board[row_count][col_count] = move(temp_piece);
     }
     col_count++;
     }
     row_count++;
     }
     */
    
}

bool Chess::try_move_piece() {
    
    assert(number_of_marked_tiles == 2);
    
    Position start(first_marked_piece->pos_y, first_marked_piece->pos_x);
    Position end(second_marked_piece->pos_y, second_marked_piece->pos_x);
    new_move = move(make_unique<Move>(start, end));
    
    Color color_start;
    Type type_start;
    
    piece_on_tile(start.pos_y, start.pos_x, color_start, type_start);
    Chess_piece chess_piece_start = Chess_piece (color_start, type_start);
    
    Color color_end;
    Type type_end;
    
    piece_on_tile(end.pos_y, end.pos_x, color_end, type_end);
    
    capture = move(make_unique<Chess_piece>(color_end, type_end));
    
    if (chess_piece_start.type == Type::None) {
        return false;
    }
    cout << "First marked piece: (" << first_marked_piece->pos_y << ", " << first_marked_piece->pos_x << ")" << endl;
    auto marked_piece = board[first_marked_piece->pos_y][first_marked_piece->pos_x].get();
    assert (marked_piece != nullptr);
    // is_piece_nullptr(first_marked_piece->pos_y, first_marked_piece->pos_x);
    // assert (is_piece_nullptr(first_marked_piece->pos_y, first_marked_piece->pos_x));

    if (marked_piece->legal_move(*this)){
        cout << "Trying to move piece (" << first_marked_piece->pos_y << ", " << first_marked_piece->pos_x
        << ") to (" << second_marked_piece->pos_y <<", " <<  second_marked_piece->pos_x << ")" << endl;
        
        if (marked_piece->get_type() == Type::King && marked_piece->get_is_moved() == false) {
            
            bool castle_move = (Move(Position(0,4), Position(0,6)) == *new_move || Move(Position(7,4), Position(7,6)) == *new_move
                                || Move(Position(0,4), Position(0,2)) == *new_move || Move(Position(7,4), Position(7,2)) == *new_move);
            
            if (marked_piece->is_legal_casteling(*this)) {
               
                
                if (Move(Position(0,4), Position(0,6)) == *new_move) {
                    board[0][5] = move(board[0][7]);
                    auto tower = board[0][5].get();
                    tower->set_is_moved();
                    
                }
                else if (Move(Position(7,4), Position(7,6)) == *new_move) {
                    board[7][5] = move(board[7][7]);
                    auto tower = board[7][5].get();
                    tower->set_is_moved();
                    
                }
                else if (Move(Position(0,4), Position(0,2)) == *new_move) {
                    board[0][3] = move(board[0][0]);
                    auto tower = board[0][3].get();
                    tower->set_is_moved();
                }
                else if (Move(Position(7,4), Position(7,2)) == *new_move) {
                    board[7][3] = move(board[7][0]);
                    auto tower = board[7][3].get();
                    tower->set_is_moved();
                }
                else {
                    assert(false && "Detected castleing but move not matching casteling move");
                }
            }
        }
        
        board[second_marked_piece->pos_y][second_marked_piece->pos_x] = move(board[first_marked_piece->pos_y][first_marked_piece->pos_x]);
        
        if (marked_piece->get_is_moved() == false){
            marked_piece->set_is_moved();
        }
        first_marked_piece = nullptr;
        second_marked_piece = nullptr;
        number_of_marked_tiles = 0;
        return true;
    }
    
    first_marked_piece = nullptr;
    second_marked_piece = nullptr;
    number_of_marked_tiles = 0;
    return false;
    
    
}



void Chess::piece_on_tile(int row, int col, Color& color, Type& piece) const{
    
    if (is_piece_nullptr(row, col)){
        color = Color::None;
        piece = Type::None;
    }
    else {
        color = board[row][col]->get_color();
        piece = board[row][col]->get_type();

    }
}

bool Chess::is_piece_moved(Position p) const {
    if (is_piece_nullptr(p.get_row(), p.get_col())) {
        return true;
    }
    else {
        auto piece = board[p.get_row()][p.get_col()].get();
        return piece->get_is_moved();
    }
}

void Chess::list_all_pieces() const
{
    for (const auto& row : board)
    {
        for (const auto& piece : row)
        {
            if (piece != nullptr)
            {
                std::cout << piece->to_string() << std::endl;
            }
        }
    }
}

/* void Chess::reset_maked_tiles() {
 for (auto row : marked_tiles)
 for (auto value : row) {
 value = false;
 }
 */// }


void Chess::set_marked_tile(int row, int col) {
    bool correct_marked = (number_of_marked_tiles >= 0 || number_of_marked_tiles <= 2);
    
    assert(correct_marked);
    if (!first_marked_piece) {
        if (is_piece_nullptr(row, col)) {
            number_of_marked_tiles = 0;
            return;
        }
        first_marked_piece = move(make_unique<Position>(row, col));
        number_of_marked_tiles = 1;
        // cout << "number_of_marked_tiles" << number_of_marked_tiles << "bool: " << correct_marked << endl;
    }
    
    
    else if (!second_marked_piece) {
        Position pos2 = Position{row, col};
        second_marked_piece = move(make_unique<Position>(row, col));
        number_of_marked_tiles = 2;
    }
    else assert(false && "Already marked pieces!");
    /*
     if (!marked_tiles[row][col])
     {
     marked_tiles[row][col] = true;
     number_of_marked_tiles++;
     }
     else{
     marked_tiles[row][col] = false;
     number_of_marked_tiles--;
     }
     */
}


void Chess::change_players_turn() {
    if (players_turn == Color::White){
        players_turn = Color::Black;
        cout << "Blacks turn" << endl << endl;
    }
    else{
        players_turn = Color::White;
        cout << "Whites turn" << endl << endl;
    }
}


/*bool Chess::is_piece(int row, int col, Chess_piece piece) const
{   if (!board[row][col])
{
    cout << "tried to find nullptr" << endl;;
    return false;
}
    if (board[row][col]->get_type() == piece.type && board[row][col]->get_color() == piece.color)
    {
        return true;
    }
    else return false;
} */

bool Chess::is_piece_nullptr(int row, int col) const
{
    if (board[row][col] == nullptr) return true;
    else return false;
}


std::unique_ptr<Piece> get_start_piece(int row, int col)
{
    bool white_start_row = (row == 0 || row == 1);
    bool black_start_row = (row == 6 || row == 7);
    if(!(white_start_row || black_start_row))
    {
        printf("It can´n be a start piece in this position");
        assert(!(white_start_row || black_start_row));
    }
    
    bool pawn = (row == 1 || row == 6), rook = (col == 0 || col == 7), knight = (col == 1 || col == 6),
    bishop = (col == 2 || col == 5), queen = (col == 3), king = (col == 4);
    
    Color color; // 1 = black, 0 = white
    if (black_start_row){
        color = Color::Black;
    }
    else color = Color::White;
    
    
    if (pawn) return move(make_unique<Pawn>(color));
    if (rook) return move(make_unique<Pawn>(color));
    if (knight) return move(make_unique<Pawn>(color));
    if (bishop) return move(make_unique<Pawn>(color));
    if (queen) return move(make_unique<Pawn>(color));
    if (king) return move(make_unique<Pawn>(color));
}

bool Chess::has_start_piece(int row) const
{
    if (row == 0 || row == 1 || row == 6 || row == 7)
        return true;
    
    else return false;
}

bool Chess::is_inside_board(int row, int col) const{
    return 0 <= row && row <= 7 && 0 <= col && col <= 7;
}

void Chess::make_simulated_board(array<array<unique_ptr<Piece>, 8>, 8>& board_copy) const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            Color color;
            Type type;
            piece_on_tile(i, j, color, type);
            
            switch (type) {
                case Type::King:
                    board_copy[i][j] = make_unique<King>(color);
                    break;
                    
                case Type::Queen:
                    board_copy[i][j] = make_unique<Queen>(color);
                    break;
                    
                case Type::Rook:
                    board_copy[i][j] = make_unique<Rook>(color);
                    break;
                    
                case Type::Bishop:
                    board_copy[i][j] = make_unique<Bishop>(color);
                    break;
                    
                case Type::Kningt:
                    board_copy[i][j] = make_unique<Knight>(color);
                    break;
                    
                case Type::Pawn:
                    board_copy[i][j] = make_unique<Pawn>(color);
                    break;
                    
                case Type::None:
                    board_copy[i][j] = nullptr;
                    break;
                    
                default:
                    break;
            }
        }
    }
    board_copy[new_move->get_end().get_row()][new_move->get_end().get_col()] = move(board_copy[new_move->get_start().get_row()][new_move->get_start().get_col()]);
    //auto piece = board_copy[new_move.get_end().get_row()][new_move.get_end().get_col()].get();
    //cout << "Did last move. " << "piece in this position: " << piece->to_string() << endl;
}

Position Chess::find_king_of_interest(array<array<unique_ptr<Piece>, 8>, 8>& board_copy) const {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            auto piece = board_copy[i][j].get();
            Type piece_type;
            Color piece_color;
            if (piece == nullptr) {
                continue;
            }
            // cout << "Type: " << piece->to_string() << endl;
            if (piece->get_type() == Type::King && piece->get_color() == players_turn) {
                return Position(i,j);
            }
        
        }
    }
    assert (false && "Did not find King of interest");
    return;
}

bool Chess::is_check_form_lines(array<array<unique_ptr<Piece>, 8>, 8>& board_copy, Position king_pos) const {
    Color players_turn = board_copy[king_pos.get_row()][king_pos.get_col()].get()->get_color();
    Color enemy_color;
    
    if (players_turn == Color::White) {
        enemy_color = Color::Black;
    }
    else {
        assert(players_turn == Color::Black);
        enemy_color = Color::White;
    }
    
    for (int row_dir = -1; row_dir <= 1; row_dir++) {
        for (int col_dir = -1; col_dir <= 1; col_dir++) {
            
            if (row_dir == 0 && col_dir == 0) {
                continue;
            }
            
            int pos_y = king_pos.get_row() + row_dir;
            int pos_x = king_pos.get_col() + col_dir;
            
            // cout << "First in this dir :(" << pos_y << ", " << pos_x << ")" << endl;
            
            
            if (!is_inside_board(pos_y, pos_x)) {
                continue;
            }
            
            auto piece = board_copy[pos_y][pos_x].get();
            
            Color it_color;
            Type it_type;
            
            if (piece == nullptr) {
                it_color = Color::None;
                it_type = Type::None;
            }
            else {
                it_color = piece->get_color();
                it_type = piece->get_type();
            }
            if (it_type == Type::King && it_color == enemy_color) {
                cout << "Chech detected from (" << pos_y << ", " << pos_x << ")" << endl;
                return true;
            }
            if (it_type == Type::Pawn && it_color == enemy_color) {
                
                switch (players_turn) {
                        
                    case Color::White:
                        if (row_dir == 1 && (col_dir == -1 || col_dir == 1)) {
                            cout << "Chech detected from (" << pos_y << ", " << pos_x << ")" << endl;
                            return true;
                        }
                        break;
                        
                    case Color::Black:
                        if (row_dir == -1 && (col_dir == -1 || col_dir == 1)) {
                            cout << "Chech detected from (" << pos_y << ", " << pos_x << ")" << endl;
                            return true;
                        }
                        break;
                        
                    default:
                        break;
                }
            }
            // cout << "iterator color vs players turn " << static_cast<int>(it_color) << ", " << static_cast<int>(color) << endl;
            while (is_inside_board(pos_y, pos_x)) {
                
                
                // cout << "iterator color vs players turn " << static_cast<int>(it_color) << ", " << static_cast<int>(color) << endl;
                // cout << "Loop Pos (" << pos_y << ", " << pos_x << ")" <<  endl;
                
                
                piece = board_copy[pos_y][pos_x].get();
                /*
                 if (piece == nullptr) {
                 cout << "Loop :Nullpointer" << endl;
                 
                 }
                 else {
                 cout << "Loop :" << piece->to_string() << endl;
                 }
                 */
                
                
                if (piece == nullptr) {
                    it_color = Color::None;
                    it_type = Type::None;
                }
                else {
                    it_color = piece->get_color();
                    it_type = piece->get_type();
                }
                if (it_color == players_turn) {
                    break;
                }
                
                if (row_dir != 0 && col_dir != 0 && (it_type == Type::Queen || it_type == Type::Bishop)) {
                    cout << "Chech detected from (" << pos_y << ", " << pos_x << ")" << endl;
                    return true;
                }
                if ((row_dir == 0 || col_dir == 0) && (it_type == Type::Queen || it_type == Type::Rook)) {
                    cout << "Chech detected from (" << pos_y << ", " << pos_x << ")" << endl;
                    return true;
                }
                
                pos_y += row_dir;
                pos_x += col_dir;
            }
        }
    }
    return false;
}

bool Chess::is_check_form_knight(array<array<unique_ptr<Piece>, 8>, 8>& board_copy, Position king_pos) const {
    
    Color players_turn = board_copy[king_pos.get_row()][king_pos.get_col()].get()->get_color();
    Color enemy_color;
    
    if (players_turn == Color::White) {
        enemy_color = Color::Black;
    }
    else {
        assert(players_turn == Color::Black);
        enemy_color = Color::White;
    }
    
    for (int i = -2; i <= 2; i++) {
        for (int j = -2; j <= 2; j++) {
            
            if (!((abs(i) == 2 && abs(j) == 1) || (abs(i) == 1 && abs(j) == 2)))  {
                continue;
            }
            
            if (!(is_inside_board(king_pos.get_row() + i, king_pos.get_col() + j))) {
                continue;
            }
            // cout << "Position :(" << 2 + i << ", " << 2 + j << ")" << endl;
            
            auto piece = board_copy[king_pos.get_row() + i][king_pos.get_col() + j].get();
            
            if (piece == nullptr) {
                continue;
            }
            assert(!(piece == nullptr));
            
            if (piece->get_type() == Type::Kningt && piece->get_color() == enemy_color) {
                cout << "Chech detected from (" << king_pos.get_row() + i << ", " << king_pos.get_col() + j << ")" << endl;
                return true;
            }
        }
    }
    return false;
}

bool Chess::run_is_in_check_simulation() const{
    cout << "Doing check analysis" << endl;
    array<array<unique_ptr<Piece>, 8>, 8> board_copy;
    make_simulated_board(board_copy);
    
    // auto piece = board_copy[new_move.get_end().get_row()][new_move.get_end().get_col()].get();
    // cout << "Did last move. " << "piece in position: (" << new_move.get_end().get_row() << ", " << new_move.get_end().get_col() << ") " << piece->to_string() << endl;
    
    Position king_pos = find_king_of_interest(board_copy);
    // cout << "King position :(" << king_pos.get_row() << ", " << king_pos.get_col() << ")" << endl;
    Color enemy_color;
    if (players_turn == Color::White) {
        enemy_color = Color::Black;
    }
    else {
        assert(players_turn == Color::Black);
        enemy_color = Color::White;
    }
    if (is_check_form_lines(board_copy, king_pos)) {
        cout << "Check form line detected" << endl;
        return true;
    }
    else if (is_check_form_knight(board_copy, king_pos)) {
        cout << "Check form knight detected" << endl;
        return true;
    }
    else {
        return false;
    }
}








