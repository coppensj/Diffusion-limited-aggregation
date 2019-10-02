#include <random>
#include <cmath>
#include <stdio.h>
#include <fstream>
#include "Vec2D.h"
#include <ctime>

class DLA_2d {
	//Data
	private:
		int L = 600;
		float particleSize = 1;
		std::random_device rd;
		std::mt19937 generator;
		std::normal_distribution<float> movement;
        float xbias, ybias;
        std::uniform_real_distribution<float> startAngle;
        Vec<float> walker;
        vector<Vec<float>> cluster;
        vector<std::pair<float,int>> time_to_add;
        Vec<float> seed;
        int nParticles = 2000;
        int clusterSize;
        float Rmax = 2;
        int binsize = 10;
        vector<int> radialDensity;
        std::ofstream clusterData, radialData, timeToAdd;
        clock_t begin;
		
	//Methods
    public:
        DLA_2d(): 
            movement(0, 1), 
            startAngle(0, 359),
			generator(std::mt19937(rd())),
            seed(0,0),
            xbias(1),
            ybias(-0.5) { }

        void Initialize(){
           AddNewWalker();          //init random walker
           cluster.push_back(seed); //add seed particle to cluster
           clusterSize = 1;
           begin = clock();
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
                if((n % 1000000) == 0){
                    printf("dt = %5.2f cycles = %8i clustersize = %4i\n", (float)(clock() - begin)/CLOCKS_PER_SEC, n, clusterSize);
                    printf("Spawnrange= (%f, %f)\n", Rmax+25, Rmax + 50);
                    time_to_add.push_back( make_pair((float)(clock() - begin)/CLOCKS_PER_SEC, clusterSize) );
                }
                n++;
            }
            printf("dt = %5.2f cycles = %8i clustersize = %4i\n", (float)(clock() - begin)/CLOCKS_PER_SEC, n, clusterSize);
            time_to_add.push_back( make_pair((float)(clock() - begin)/CLOCKS_PER_SEC, clusterSize) );
            RadialDensity();
            SaveCluster();
        }
	private:
        //create a new 'walker' particle a large distance from the origin
		void AddNewWalker(){
            //std::uniform_real_distribution<float> startRadius(0.2*L,0.3*L);
            std::uniform_real_distribution<float> startRadius(Rmax + 30, Rmax + 35);
            float r = startRadius(generator);
            float theta = startAngle(generator);
            walker.x = r*std::cos(theta);    
            walker.y = r*std::sin(theta);    
		}

		void MoveWalker(){
            walker.x += movement(generator) + xbias;
            walker.y += movement(generator) + ybias; 
		}

		void AddToCluster(){
            cluster.push_back(walker);
            UpdateRmax();
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

        void UpdateRmax(){
            float r = std::sqrt(walker.x * walker.x + walker.y * walker.y) + particleSize;
            if( L/2 < (r + 50)) return;
            Rmax = (r < Rmax)*Rmax + (Rmax < r)*r;
        }

        void RadialDensity(){
            radialDensity.resize((int)(Rmax/binsize+1), 0);
            printf("Rmax = %f\n", Rmax);
            for(int i=0; i<cluster.size(); i++){
                float r = std::sqrt(cluster[i].x * cluster[i].x + cluster[i].y * cluster[i].y);
                for(int n=0; n<radialDensity.size(); n++)
                    if(r < (n+1)*binsize) ++radialDensity[n];
            }
            for(int n=0; n<radialDensity.size(); n++)
                printf("rad=%3i  particle count=%3i\n", (n+1)*binsize, radialDensity[n]);
        }

        void SaveCluster(){
            clusterData.open("Data/clusterData.csv");
            for (int i=0; i<cluster.size(); i++) 
                clusterData << i << "," << cluster[i].x << "," << cluster[i].y << endl; 
            clusterData.close();

            radialData.open("Data/radialData.csv");
            for(int n=0; n<radialDensity.size(); n++)
                radialData << (n+1)*binsize << "," << radialDensity[n] << endl;
            radialData.close();
            
            timeToAdd.open("Data/time_to_add.csv");
            for(int i=0; i<time_to_add.size(); i++)
                timeToAdd <<  time_to_add[i].first << "," << time_to_add[i].second << endl;
            timeToAdd.close();
        }

};
