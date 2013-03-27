/*
*	Author: Mathieu Theerens
*/

#include "Robot.h"

//--------------------------------------
VisionRobot::VisionRobot() {}  
    
//--------------------------------------
Point2f VisionRobot::getCoords( Mat img )
{
	image = img;
      	int angle;
	Mat hsv, dst, bw;
	vector<vector<Point> > contours, newcontours, middlecontour;
	
	cvtColor(image, hsv, CV_RGB2HSV);
	
	// Met deze range vinden we alle bollen in de foto, dus ook 
	// de bal 
	inRange(hsv, Scalar(0, 150, 60), Scalar(180, 255, 255), bw);
	
	//	We gaan we binaire foto smoothen omdat er nog wat ruis op zit
	bw = smoothImage(bw);	
    	
    	/*	Er kunnen nog gaten in de verschillende bollen zitten, 
    	*	deze verwijderen we door de contouren te vinden en deze dan te
    	*	tekenen
    	*/    	
	findContours(bw.clone(), contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	bw = removeBall(bw, contours);
	
	/*	Aangezien we nu de bal hebben verwijderd uit de foto gaan we opnieuw de
	* 	contouren berekenen en als resultaat krijgen we enkel de bollen van
	*	de robot, niet de bal
	*/
	findContours(bw.clone(), newcontours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	
	dst = Mat::zeros(image.size(), image.type());
	drawContours(dst, newcontours, -1, Scalar::all(255), CV_FILLED);

	// logic AND om het masker op de image te leggen, zodat enkel dat deel
	// getoond zal worden
	dst &= image;
	
	// Nu gaan we de middelste bol van de robot verkrijgen	
	middlecontour = extractContourMiddle(dst);

	//imshow(window_dest, dst);
	
	DataCircle dc(middlecontour);
	
	vector<Point2f> center = dc.getCenters();
	
	
	// Indien de robot gevonden is, sturen we de coordinaten van het middenpunt door	
	if ( center.size() > 0 )
	{
		calcRotation(middlecontour, newcontours);
		
		return center[0];
	}
	// Anders gaan we een lege parameter doorsturen
	else
	{
		Point2f x;	
		rotation = 0;	
		return x;
	}
}

//--------------------------------------
Mat VisionRobot::smoothImage( Mat img )
{
	Mat imgdest = img.clone();
	for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    		medianBlur ( img, imgdest, i );
    	
    	return imgdest;
}

//--------------------------------------
Mat VisionRobot::removeBall( Mat img, vector<vector<Point> > cnt )
{
	int thickness = -1;
	int linetype = 8;
	
	DataCircle dc(cnt);
	
	vector<Point2f> center = dc.getCenters();
	vector<float> radius = dc.getRadius();

	for ( int i = 0; i < cnt.size(); i++ )
	{
		if ( radius[i] > THRESHOLD )					
			circle(img, center[i], radius[i]+1.5, Scalar::all(0), thickness, linetype);			
	}
	
	return img;
}

//--------------------------------------
vector<vector<Point> > VisionRobot::extractContourMiddle( Mat img )
{
	vector<vector<Point> > cnt;
	Mat bw, hsv, dst;
	
	cvtColor(img, hsv, CV_RGB2HSV);

	// Met deze range vinden we binnenste bol van de robot
	inRange(hsv, Scalar(2, 170, 60), Scalar(4, 210, 100), bw);
	bw = smoothImage(bw);
	findContours(bw.clone(), cnt, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	
	return cnt;	
}

//--------------------------------------
void VisionRobot::calcRotation( vector<vector<Point> > mcontour, vector<vector<Point> > allcontours )
{
	int shortindex=0;
	int thickness = -1, linetype = 8;
	float dist, shortdist=MAXDIST, angle, dxred, dyred;
	Mat bw, hsv, dst = Mat::zeros(image.size(), image.type());
	vector<Point2f> centers(4);
	vector<float> radii(4);
	vector<vector<Point> > cnt;	
	DataCircle dcmiddle(mcontour), dcall(allcontours);
	
	// Hier gaan we de bollen berekenen die het dichtst bij de middenste bol van de robot zitten
	// Met deze bollen kunnen we dan de rotatie berekenen
	for ( int i = 0; i < allcontours.size(); i++ )
	{
		//cout << dcall->center[i] << endl;
		dist = calcDistance(dcall.getCenters()[i], dcmiddle.getCenters()[0]);
		
		if ( dist > 1 && dist < MAXDIST )
			circle(dst, dcall.getCenters()[i], dcall.getRadius()[i], Scalar::all(255), thickness, linetype);		
	}
	
	dst &= image;
	
	// Nu gaan we de positie bepalen van de rood/roze bol, en gaan we hiermee de 
	// rotatie berekenen	
	cvtColor(dst, hsv, CV_RGB2HSV);

	// Met deze range vinden we rode bol van de robot
	inRange(hsv, Scalar(120, 100, 100), Scalar(140, 200, 255), bw);
	
	vector<vector<Point> > redcontour;
	findContours(bw.clone(), redcontour, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
	
	DataCircle red(redcontour);
	
	/*	We berekenen de inverse tangens van de afstand tussen beiden om zo de hoek te bekomen.
	* 	Daarna tellen we er 115 graden bij om zo de hoek te bekomen tussen de kijkrichting van
	* 	de robot en de horizontale as.	
	*/
	
	dxred = red.getCenters()[0].x - dcmiddle.getCenters()[0].x;
	dyred = red.getCenters()[0].y - dcmiddle.getCenters()[0].y;
	
	angle = -atan2(dyred,dxred)/PI*180 + 115;
	
	// Indien de hoek groter wordt dan 180 graden, dan zit men in het verkeerde quadrant,
	// en moet moet 360 - hoek doen.
	if ( angle > 180 )
		angle = angle - 360;
	
	rotation = angle;
}

//--------------------------------------
float VisionRobot::calcDistance(Point2f a, Point2f b)
{
	float xdist, ydist, sum;

	xdist = a.x - b.x;
	xdist *= xdist;
	ydist = a.y - b.y;
	ydist *= ydist;
	
	sum = xdist + ydist;
	sum *= sum;
	
	return sum;
}

//--------------------------------------
float VisionRobot::getRotation()
{
	return rotation;
}

