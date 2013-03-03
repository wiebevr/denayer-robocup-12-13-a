/**
 * @file vision_field.h
 * @classe VisionField
 * @author Den Dooven Raphael
 *
 * @brief
 * Deze klasse zorgt voor de omzetting van een positie op de
 * afbeelding naar een coordinaat op het veld
 *
 *
 */

#ifndef VISION_FIELD_H
#define VISION_FIELD_H

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/nonfree/features2d.hpp>

#include <iostream>

using namespace std;
using namespace cv;


class VisionField
{
private:
    //@
    vector<Point2f> cornersPoints;
    vector<Point2f> cornersGoal;
    Mat tmp;

    int Width, Height;

    int nPoints;

    int border;

    /**
     * mouseCallback is een callback functie die er voor zorgt dat alle activiteiten in de
     * gekozen figuur wordt verwerkt.
     * @param event muis event
     * @param x x positie
     * @param y y positie
     *
     */
    static void mouseCallback(int event, int x, int y, int flags, void* param);
    void mouse(int event, int x, int y);

public:
    /**
     * @brief VisionField Deze constructor zal de andere constructor oproepen met een
     * vaste grote van 300 op 300.
     * @param img camera beeld
     */
    VisionField(Mat img);
    /**
     * @brief VisionField Deze constructor zal een venster oproepen waar men manueel
     * de hoeken van het veld moet selecteren beginnend met de linker boven hoek en
     * dan met de klok verder selecteren. Na deze actie zal er een 2de venster
     * aangemaakt worden om de goal te selecteren.
     * @param img camera beeld
     * @param Width uiteindelijke breedte veld
     * @param Height uiteindelijke breedte veld
     */
    VisionField(Mat img, int Width, int Height, int setBorder);

    /**
     * @brief getCorrectedImage Deze geet het gecalibreede veld terug met een
     * rand rond
     * @param img nieuw camera beeld
     * @return gecoalibreede veld
     */
    Mat getCorrectedImage( Mat img );

    /**
     * @brief getCoordinateGoal Met deze methode krijg je de veld coordinaten van de goal terug
     * @return vector van 2 coordinaten (elks x en y waarde)
     */
    Vector<Point2f> getCoordinateGoal();

    /**
     * @brief getCoordinate Zet de pixel waarde om naar veld coordinaten
     * @param pixel
     * @return
     */
    Vector<Point2f> getCoordinate(Vector<Point2f> pixel);
};

#endif // VISION_FIELD_H
