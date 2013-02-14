/*
* Author: Floris De Smedt - EAVISE/VISICS 
*
* copy constructor problem  example: the objects use a pointer to a local variable. 
* By using the default copy constructor, the pointer of the new object still points to the variable of the original object
*/
#include <iostream>

using namespace std;

class Robot{
public:
	Robot(){
		cout << "Setting variable" << endl;
		this->a = 5;
		b = &a;
	}

	void changeB(int b){
		*(this->b) = b;
	}
	
	void Print(){
		cout << "A is " << a << endl;
	}

private:
	int a;
	int *b;
};


int main(){
	Robot R1;
	Robot R2 = R1;

	R2.changeB(15);

	R1.Print();

return 0;
}