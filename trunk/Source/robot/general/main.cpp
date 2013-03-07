#include "wifi/wifi.h"
#include "shared/vision_data.h"

int main(int argc, char **argv)
{
    Wifi wifi();
    Strategy strategy();

    while (true)
    {
        const VisionData data = wifi.getVisionData();
        strategy.setCoords(&data);
        strategy.run();
    }

    return 0;
}
