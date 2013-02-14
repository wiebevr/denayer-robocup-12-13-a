/*
* Author: Floris De Smedt - EAVISE/VISICS 
*
* Polymorphism example: the type of the object is determined at runtime
*/

#include <iostream>
#include <cstdio>
#include <cstring>

using namespace std;

class Figure{
public:
	virtual string getType(){};
	void setType(string t){
		this->type=t;
	}
protected:
	string type;
};

class Square: public Figure{
public:
	Square(){
		this->setType("Square");
	}
	string getType(){
		return this->type;
	}
private:

};

class Triangle: public Figure{
public:
	Triangle(){
		this->setType("Triagle");
	}
	string getType(){
		return this->type;
	}
private:

};

class Circle: public Figure{
public:
	Circle(){
		this->setType("Circle");
	}
	string getType(){
		return this->type;
	}
private:

};

void ProcessChoice(int c){
Figure *F;
switch(c){
	case 1:
		F = new Triangle;
		cout << "Choice was " << F->getType() << endl;
		break;
	case 2:
		F = new Circle;
		cout << "Choice was " << F->getType() << endl;
		break;
	case 3:
		F = new Square;
		cout << "Choice was " << F->getType() << endl;
		break;
	default: 
		cout << "No valid choice!" << endl;
}
}


int main(){

cout << "Give your choice: " << endl;
cout << "1: Triagle " << endl;
cout << "2: Circle " << endl;
cout << "3: square " << endl;
char Choice = getchar();
int Ch = atoi(&Choice);
ProcessChoice(Ch);


return 0;
}