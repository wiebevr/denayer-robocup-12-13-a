/*
*	Author: Mathieu Theerens
*	Description: Deze functie zal de bal detecteren en het middenpunt ervan
*			 als output terugsturen
*/

#include "Balls.h"
#include "DataCircle.h"

#define MAXIMG 15

Mat images[MAXIMG];
int whichimage = 0;

void showBalls(int, void* );

Ball::Ball( Mat img ): image(img)
{
	window_dest = "Images";
}  
    
Point2f Ball::getCoords(){
      Mat hsv;
	cvtColor(image, hsv, CV_RGB2HSV);
	
	//imshow("hsv", hsv);

	// Met deze range kunnen we de bal detecteren
	Mat bw;
	inRange(hsv, Scalar(50, 210, 110), Scalar(180, 255, 255), bw);

	// We zoeken naar contouren in de foto, deze stellen de bal(len) voor
	vector<vector<Point> > contours;
	findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	Mat dst = Mat::zeros(image.size(), image.type());
	drawContours(dst, contours, -1, Scalar::all(255), CV_FILLED);
	
	
	// Deze parameters gaan we gebruiken om het midden van de cirkel te vinden
	DataCircle dc(contours);
	
	vector<Point2f> center = dc.getCenters();
	
	if ( center.size() > 0 )
	{
		cout << center[0] << endl;
		
		// logic AND om het masker op de image te leggen, zodat enkel dat deel
		// getoond zal worden
		dst &= image;		
		imshow(window_dest, dst);
		
		// Enkel het 0e center wordt gereturned omdat we aannemen dat we maar met
		// 1 bal werken.
		return center[0];
	}
	else
	{
		Point2f x;
		
		return x;
	}
}

/*	Om dit te testen moet er een Image map zijn op ../Images/ van de executable
*	Dan voert men het programma uit mbv ./Balls robot3 robot4
*	Hier zijn robot3 en robot4 de namen van de images, men mag niet .jpg erachter zetten
*	en men moet minstens 2 images hebben.
*/

int main(int argc, char** argv)
{	
	int i, pressedkey, numberofimages;
	string names[MAXIMG];
	ReadImg myclass(argc, argv, names);

	for ( i = 0; !names[i].empty(); i++ )
	{
		images[i] = imread( names[i], 1 ); //Indien het 2e argument 1 is wordt het een rgb foto, indien 0 een grayscale
	}
	numberofimages = i;
	
	namedWindow( "Images", CV_WINDOW_AUTOSIZE );
	createTrackbar( "Output:", "Images", &whichimage, numberofimages-1, showBalls );
	showBalls(0, 0);
	
	waitKey(0);

	return 0;
}

void showBalls(int, void* )
{
	Ball bal(images[whichimage]);
	
	bal.getCoords();
}


