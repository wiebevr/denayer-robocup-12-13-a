// @author Bart Volkaerts
// Functies voor het testen van de game klasse.

#include <iostream>
#include <fstream>
#include "wifi.h"

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
    ofstream out;
    out.open("game.pb", ios::out);

    Game *game = new Game;
    Player *player_a = game->mutable_player_a(); 
    player_a->set_x(1.0);
    player_a->set_y(2.0);
    player_a->set_rotate_x(11.0);
    player_a->set_rotate_y(12.0);
    
    game->mutable_player_b()->set_x(2.0);
    game->mutable_player_b()->set_y(3.0);
    game->mutable_player_b()->set_rotate_x(22.0);
    game->mutable_player_b()->set_rotate_y(23.0);

    game->mutable_ball()->set_x(3.0);
    game->mutable_ball()->set_y(4.0);

    game->mutable_goal()->set_pole1_x(5.0);
    game->mutable_goal()->set_pole1_y(6.0);
    game->mutable_goal()->set_pole2_x(7.0);
    game->mutable_goal()->set_pole2_y(8.0);

    printGameContent(game); 

    if(game->IsInitialized())
    {
        //game->SerializeWithCachedSizes();
        // EENS NADER BEKIJKEN. IS MAAR IETS VREEMD
    }

    out.close();
    return 0;    
}
