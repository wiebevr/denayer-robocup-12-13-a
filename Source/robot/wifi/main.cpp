// @author Bart Volkaerts
// Functies voor het testen van de game klasse.

#include <iostream>
#include <fstream>
#include "wifi.h"
#include <fcntl.h>
#include <unistd.h>

#include <google/protobuf/io/zero_copy_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/io/coded_stream.h>

using namespace std;

void printGameContent(Game *game)
{
    cout << "Content of game object" << endl;
    cout << "Player A:\tx:\t\t" << game->player_a().x() << endl; 
    cout << "Player A:\ty:\t\t" << game->player_a().y() << endl; 
    cout << "Player A:\trotate x:\t" << game->player_a().rotate_x() << endl; 
    cout << "Player A:\trotate y:\t" << game->player_a().rotate_y() << endl; 
    
    cout << "Player B:\tx:\t\t" << game->player_b().x() << endl; 
    cout << "Player B:\ty:\t\t" << game->player_b().y() << endl; 
    cout << "Player B:\trotate x:\t" << game->player_b().rotate_x() << endl; 
    cout << "Player B:\trotate y:\t" << game->player_b().rotate_y() << endl; 
    
    cout << "Ball:\t\tx:\t\t" << game->ball().x() << endl; 
    cout << "Ball:\t\ty:\t\t" << game->ball().y() << endl; 

    cout << "Goal pole1:\tx:\t\t" << game->goal().pole1_x() << endl; 
    cout << "Goal pole1:\ty:\t\t" << game->goal().pole1_y() << endl; 
    cout << "Goal pole2:\tx:\t\t" << game->goal().pole2_x() << endl; 
    cout << "Goal pole2:\ty:\t\t" << game->goal().pole2_y() << endl; 
}

int main(int argc, char *argv[])
{
    int fd = open("game.pb", O_RDONLY); 
    
    google::protobuf::io::ZeroCopyInputStream* raw_input = new google::protobuf::io::FileInputStream(fd);
    google::protobuf::io::CodedInputStream* coded_input = new google::protobuf::io::CodedInputStream(raw_input);

    Game *game = new Game;
    printGameContent(game); 

    game->MergePartialFromCodedStream(coded_input); 
    
    printGameContent(game); 

    delete coded_input;
    delete raw_input;
    close(fd);

    return 0;    
}
