#include <random>
#include <cmath>
#include <stdio.h>

/* template <typename T, typename U> */
/* std::pair<T,U> operator+(const std::pair<T,U> &l, const std::pair<T,U> & r) { */
/*         return{l.first+r.first, l.second+r.second}; */
/*         } */

class DLA_2d {
	//Data
	private:
		int L = 300;
		double particleSize = 1;
		std::random_device rd;
		std::mt19937 generator;
		std::normal_distribution<double> movement;
        std::pair<double,double> walkerPosition;
		
	//Methods
    public:
        DLA_2d(): 
            movement(0, 1), 
			generator(std::mt19937(rd())),
            walkerPosition(0,0) { }

        void SingleStep(){
            for(int i=0; i<20; ++i){
                printf("%5.2f, %5.2f\n", walkerPosition.first, walkerPosition.second);
                walkerPosition.first += movement(generator);
                walkerPosition.second += movement(generator);
            }
        }
	private:
		void AddNewWalker(){

		}

		void MoveWalker(){

		}

		void AddToCluster(){

		}
};
