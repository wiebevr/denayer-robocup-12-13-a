#include "wifi/wifi.h"
#include "wifi/game.pb.h"

int main(int argc, char **argv)
{
    Wifi wifi();
    Strategy strategy();

    while (true)
    {
        const Game &game = wifi.getGame();
        strategy.setGame(game);
        strategy.run();
    }

    return 0;
}
