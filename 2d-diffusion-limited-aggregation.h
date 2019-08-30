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
        std::uniform_real_distribution<double> startRadius;
        std::uniform_real_distribution<double> startAngle;
        Vec<double> walker;
        vector<Vec<double>> cluster;
        Vec<double> seed;
		
	//Methods
    public:
        DLA_2d(): 
            movement(0, 1), 
            startRadius(0.25*L,0.5*L),
            startAngle(0, 359),
			generator(std::mt19937(rd())),
            walker(0,0),
            seed(0,0){ }

        void Initialize(){
           AddNewWalker();          //init random walker
           cluster.push_back(seed); //add seed particle to cluster
        }

        void SingleStep(){
            for(int i=0; i<10; ++i){
                printf("%5.2f, %5.2f\n", walker.x, walker.y);
                printf("%i\n", OutOfBounds());
                if (OutOfBounds())
                    printf("Bad\n");
                else
                    printf("Good\n");
                AddNewWalker();
                //MoveWalker();
                /* AddToCluster(); */
            }
            /* printf("%i\n", int(cluster.size())); */
        }
	private:
        //create a new 'walker' particle a large distance from the origin
		void AddNewWalker(){
            double r = startRadius(generator);
            double theta = startAngle(generator);
            walker.x = r*std::cos(theta);    
            walker.y = r*std::sin(theta);    
		}

		void MoveWalker(){
            walker.x += movement(generator);
            walker.y += movement(generator); 
		}

		void AddToCluster(){
            cluster.push_back(walker);
		}

        int OutOfBounds(){
            if ((std::fabs(walker.x) >= 0.5*L) || (std::fabs(walker.y) >= 0.5*L))
                return 1;
            else
                return 0;
        }
};
