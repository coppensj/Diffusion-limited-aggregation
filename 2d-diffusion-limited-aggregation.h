#include <random>
#include <cmath>
#include <stdio.h>
#include <fstream>
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
        int nParticles = 2000;
        int clusterSize;
        std::ofstream clusterData;
		
	//Methods
    public:
        DLA_2d(): 
            movement(0, 1), 
            startRadius(0.25*L,0.5*L),
            startAngle(0, 359),
			generator(std::mt19937(rd())),
            seed(1,1){ }

        void Initialize(){
           AddNewWalker();          //init random walker
           cluster.push_back(seed); //add seed particle to cluster
           clusterSize = 1;
        }

        void CreateCluster(){
            int n=0;
            while(clusterSize<nParticles){
                MoveWalker();
                if(OutOfBounds())
                    AddNewWalker();
                else if (TouchingCluster()){
                    AddToCluster();
                    AddNewWalker();
                    ++clusterSize;
                }
                if((n++ % 1000000)==0)
                    printf("%4i cycles, %2i in cluster.\n", n, clusterSize);
            }
            SaveCluster();
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
        
        int TouchingCluster(){
            for(int i=0; i<cluster.size(); ++i)
                if(walker.DistFrom(cluster[i]) <= 2*particleSize)
                    return 1;
            return 0;
        }

        void SaveCluster(){
            clusterData.open("Data/clusterData.csv");
            for (int i=0; i<cluster.size(); i++) {
                clusterData << i << "," << cluster[i].x << "," << cluster[i].y << endl;
            }
            clusterData.close();
        }

};
