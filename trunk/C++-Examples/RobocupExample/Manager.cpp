/*
 * Author: Floris De Smedt - EAVISE/VISICS
 *
 * Manager.cpp
 */

#include "Manager.h"

		void Manager::AddRobot(string name, Point Location){
			RBots.push_back(new Robot(name,Location));
		}

		int Manager::FindPosition(string name){
			for(int i=0;i<this->RBots.size();i++){
				if(RBots[i]->getName()==name)
					return i;
			}
		}

		void Manager::DeleteRobot(string name){
			int Pos = FindPosition(name);
			delete RBots[Pos];
			RBots.erase(RBots.begin()+Pos);
		}

		void Manager::PrintRobots(){
		for(int i=0;i<RBots.size();i++)
			RBots[i]->PrintRobot();
		
		}

		void Manager::Move(string name, Point P){
			int Pos = FindPosition(name);

			RBots[Pos]->DriveTo(P);
		}


		Manager::~Manager(){
			cout << "deleting the remaining robots: " << endl;
			for(int i=0;i<RBots.size();i++)
				delete RBots[i];
		}