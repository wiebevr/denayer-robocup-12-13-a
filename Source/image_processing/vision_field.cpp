/*
 * @author Den Dooven Raphael
 */

#include "vision_field.h"

vector<Point2f> cornersPoints;
vector<Point2f> cornersGoal;

Mat tmp;

int nPoints;

int Width, Height;

int border;


//---------------------------------------------------------------------------------------
VisionField::VisionField( Mat img )
{
    VisionField::VisionField(img, 500, 500, 50);
}

//---------------------------------------------------------------------------------------
VisionField::VisionField(Mat img, int persWidth, int persHeight, int setBorder)
{
    cout << "   [VisionField::VisionField] -> Constructor." << endl;
    int status = 0;
    Width = persWidth;
    Height = persHeight;
    VisionField::nPoints = 0;
    img.copyTo(tmp);

    this->border = setBorder;

    namedWindow("Select 4 corners");
    cvSetMouseCallback("Select 4 corners",  (CvMouseCallback)&VisionField::mouseCallback, (void*)this);
    imshow("Select 4 corners", img);

    while( waitKey(1) == -1 && VisionField::nPoints < 4);

    destroyWindow("Select 4 corners");

    status = 1;
    getCorrectedImage( img ).copyTo(tmp);
    namedWindow("Select goal");
    cvSetMouseCallback("Select goal",  (CvMouseCallback)&VisionField::mouseCallback, (void*)this);
    imshow("Select goal", VisionField::tmp);

    while( waitKey(1) == -1 && VisionField::nPoints < 6);

    destroyWindow("Select goal");

    VisionField::nPoints = 0;

}

//---------------------------------------------------------------------------------------
void VisionField::mouse(int event, int x, int y)
{
    if (event == CV_EVENT_LBUTTONUP)
    {
        if (nPoints < 4)
        {
            cout << "       [VisionField::mouseCallback] -> coordinate corner " << nPoints << " are: " << x << ", " << y << endl;
            cornersPoints.push_back(Point2f(x, y));
            nPoints++;
            circle( tmp, Point( x, y ), 3,  Scalar(0,0,255), 1, 4, 0 );
            imshow("Select 4 corners", tmp);
        }
        else if (nPoints >= 4 && nPoints < 6)
        {
            cout << "       [VisionField::mouseCallback] -> coordinate goal " << nPoints << " are: " << x << ", " << y << endl;
            if (x > 0.8 * Width) x = Width;
            if (x < 0.2 * Width + border) x = border;
            if (y > 0.8 * Height) y = Height;
            if (y < 0.2 * Height + border) y = border;
            cornersGoal.push_back(Point2f(x, y));
            nPoints++;
            circle( tmp, Point( x, y ), 3,  Scalar(255,0,0), 1, 4, 0 );
            imshow("Select goal", tmp);
        } else {
            cout << "You selected enough corners" << endl;
        }
    }
}

//---------------------------------------------------------------------------------------
void VisionField::mouseCallback(int event, int x, int y, int flags, void* param)
{
    reinterpret_cast<VisionField *>(param)->mouse(event, x, y);
}

//---------------------------------------------------------------------------------------
Mat VisionField::getCorrectedImage( Mat img )
{
    cout << "   [VisionField::getCorrectedImage] -> Give corrected image." << endl;
    cout << "       [VisionField::getCorrectedImage] -> Border = " << this->border << endl;

    Mat trans, quad = cv::Mat::zeros(VisionField::Width + border, VisionField::Height + border, CV_8UC3);
    vector<Point2f> scalePoints;

    scalePoints.push_back(cv::Point2f(0 + border, 0 + border));
    scalePoints.push_back(cv::Point2f(quad.cols - border, 0 + border));
    scalePoints.push_back(cv::Point2f(quad.cols - border, quad.rows - border));
    scalePoints.push_back(cv::Point2f(0 + border, quad.rows - border));

    trans = getPerspectiveTransform(cornersPoints, scalePoints);
    warpPerspective(img, quad, trans, quad.size());

    return quad;
}

//---------------------------------------------------------------------------------------
Vector<Point2f> VisionField::getCoordianteGoal()
{
    return this->getCoordiante(cornersGoal);
}

//---------------------------------------------------------------------------------------
Vector<Point2f> VisionField::getCoordiante(Vector<Point2f> pixel)
{
    Vector<Point2f> coordinateList;

    for (int i = 0; i < pixel.size(); i++)
    {
        coordinateList.push_back( Point2f( -(pixel[i].x - Width - border) / Width,
                                           -(pixel[i].y - Height - border) / Height ) );
    }

    return coordinateList;
}
