#include <random>
#include <cmath>
#include <stdio.h>
#include "Vec2D.h"

class DLA_2d {
	//Data
	private:
		int L = 300;
		double particleSize = 1;
		std::random_device rd;
		std::mt19937 generator;
		std::normal_distribution<double> movement;
        Vec<double> walker;
		
	//Methods
    public:
        DLA_2d(): 
            movement(0, 1), 
			generator(std::mt19937(rd())),
            walker(0,0) { }

        void SingleStep(){
            for(int i=0; i<20; ++i){
                printf("%5.2f, %5.2f\n", walker.x, walker.y);
                MoveWalker();
            }
        }
	private:
		void AddNewWalker(){

		}

		void MoveWalker(){
            walker.x += movement(generator);
            walker.y += movement(generator); 
		}

		void AddToCluster(){

		}
};
