#include "wifi/wifi.h"
#include "vision/vision.h"
#include "shared/vision_data.h"

int main(int argc, char **argv)
{
    Wifi wifi();
    Vision vision();

    while (true)
    {
        const VisionData data = vision.fetchData();
        wifi.setVisionData(&data);
        wifi.sendData();
        // wacht een tijdje
    }

    return 0;
}
