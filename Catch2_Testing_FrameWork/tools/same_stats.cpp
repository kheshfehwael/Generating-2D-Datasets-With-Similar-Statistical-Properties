#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <random>
#include <tuple>
#include <fstream>
#include <chrono>
#include "same_stats_tools.h"
#include "same_stats.h"


using namespace std;

/**
* Random number generators to be used in while permutation
*/
default_random_engine re{static_cast<long unsigned int>(0)};
uniform_int_distribution<int>  rand_num(0, RAND_MAX);
uniform_real_distribution<double> zero_to_one(0, 1.0);
uniform_real_distribution<double> uni_plus_minus_one(-1.0, 1.0);
normal_distribution<double> normal_plus_minus_one(0.0, 1.0);
binomial_distribution<int> binomial_generator(10, 0.5);

/**
* Function to determine if the statistical values of two given 1D arrays x and y differ from a
* given set of statistical values up to a given amount of decimal points. The statistical values
* beeing compared are mean value of x and y respectively, variance of x and y respectively and
* pearsons correlation.
*
* @param old_values the statistical values that beeing comapred to
* @param x_new the first vector
* @param y_new the second vector
* @param parameters an array that gives mofication parameters of x and y.
* @param length the length of the vectors x and y
* @param decimals the amount of decimal points that are taken into account in the comparison
*/
bool check_error(vector<double> old_values, vector<int> x_new, vector<int> y_new, int* parameters, int length, int decimals ){
    vector<double> new_values = get_stat_values_int(x_new, y_new, parameters, length);
    double sum = 0;
    for(int i = 0; i < 5; i++){
        sum += abs(((double)floor(old_values[i]*100)/100) - ((double)floor(new_values[i]*100)/100));
    }
    return sum == 0.0;
}

/**
* Function that manipulates one point of a 2D array. For the modification a random number
* generator is used. The modification only takes place if at least one of multiple conditions
* are satisfied. One condition is that the respective distance value in the distance matrix
* is smaller than the previous one. Another condition is that the perspective distance is
* smaller than a given value. Another condition is that an error is allowed. This last
* condition is part of the simulated annealing.
*
* @param x vector that contains the x-values of the 2D dataset
* @param y vector that contains the y-values of the 2D dataset
* @param temp the value to determine the allowed error in the simulated annealing
* @param length the length of the vectors x and y
* @param distances a vector representing a 2D discrete matrix containing distances
* @param discr_length the amount of discretization points per dimension
* @param shake the radius factor for the modification of the one point
* @param allowed_squared the squared distance value that is tollerated while pertubating
* @returns the resulting vectors x and y after the pertubation
*/
auto perturb(vector<int> x, vector<int> y, double temp, int length, vector<int>& distances, int discr_length, int shake, int allowed_squared ) -> tuple<vector<int>, vector<int>>
{
	int element = rand_num(re)%length;
    int x_el = x[element];
    int y_el = y[element];
    int x1;
    int y1;
    int old_dis = distances[(discr_length-1-y_el)*discr_length + x_el];
    int new_dis;

    bool found = false;
    bool do_bad = zero_to_one(re) < temp;

	while(!found){
		x1 = x_el + (binomial_generator(re)-5)*shake;
		y1 = y_el + (binomial_generator(re)-5)*shake;
		if(x1<discr_length && x1>=0 && y1<discr_length && y1 >=0){
			new_dis = distances[(discr_length-1-y1)*discr_length + x1];
		}else{
			continue;
		}
		if(old_dis>new_dis || new_dis<allowed_squared || do_bad){
			x[element] = x1;
			y[element] = y1;
			found = 1;
		}
	}
    return{ x, y};
}

/**
* Function for in and out quadratic easing.
*
* @param t function argument
* @return resulting value if the easing function
*/
double curve(double t){
    return t < 0.5 ? 2 * t * t : 1 - (-2 * t + 2)*(-2 * t + 2) / 2;
}

/**
* Function that runs multiple iterations to modify a 2D dataset into a given shape
* while maintaining certain statistical values.
*
* @param x vector that contains the x-values of the initial 2D dataset
* @param y vector that contains the y-values of the initial 2D dataset
* @param parameters the parameters that determine how the 2D dataset was modified
*	for the discretization
* @param length the length of the vectors x and y
* @param distances a vector representing a 2D discrete matrix containing distances
* @param iter the amount of iterations
* @param shake the radius factor for the modification of one point
* @param max_temp the maximal value for the error allowed in the simulated annealing
* @returns the modified vectors x and y
*/
auto run_patern(vector<int> x, vector<int> y, int* parameters, int length, vector<int>& distances, int discr_length, int iter, int shake, double max_temp) -> tuple<vector<int>, vector<int>>
{
    vector<double> init_values = get_stat_values_int(x, y, parameters, length);
    double t;
    int changes = 0;
    for(int i = 0;i < iter;i++){
        t = (max_temp) * curve(((double)iter-(double)i)/(double)iter);

        auto [x1,y1] = perturb(x,y,t,length,distances,discr_length,shake);

        if(check_error(init_values,x1,y1,parameters,length)){
            changes++;
            x = move(x1);
            y = move(y1);
        }

        // print progress

        if((i+1) % (int)(iter/10) == 0){
            cout << 100*(double)(i+1)/(double)iter << "%";
			if((i+1)!=iter){
				cout << " - ";
			}else{
				cout << "\n";
			}
        }
    }
    // print how many manipulations were really done
    cout << changes << " changes made\n";
    return{x,y};
}

/**
* Function to print information for the user
*/
void output1(){
	cout << "\nUsage: same_stats INFILE SHAPEFILE [OPTION...]\n";
	cout <<	"Try `same_stats --help' or `same_stats --usage' for more information.\n";
}

/**
* Function to print information for the user
*/
void output_help(){
	cout << "\nUsage: same_stats INFILE SHAPEFILE [OPTION...]\n\n";
	cout <<	"same_stats is a program to generate a 2D dataset based on a given dataset and a given shape.\n"
	"For this the initial dataset is beeing mapped to a discrete 1000x1000 points field. This discretized\n"
	"dataset then is beeing modified into a given shape defined in SHAPEFILE while maintaining certain\n"
	"statistical values. After the modification of the dataset is done the discrete dataset is being mapped\n"
	"back to the initial scaling. The initial dataset (after the discretization) is beeing saved in INITFILE\n"
	"and the resulting file in RESULTFILE."
	"\n\n"
	"The file SHAPEFILE has to be a binary .txt file with the dimension 1000x1000. With the shape defined in\n"
	"this file a distance matrix is being calculated so the distances don't have to be calculated multiple times.\n"
	"After the calculation the user can modify following parameters regarding the modification of the dataset:\n"
	"iter - amount of iterations beeing done, shake - radius factor for modification of one single point, max_temp -\n"
	"maximal value allowed in the simulated annealing.\n"
	"One option to create such a .txt file is to paint a 1000x1000 bitmap and then use the tool one the website\n"
	"https://www.dcode.fr/binary-image. The coordinates of the shape must have the value 1."
	"\n\n"
	"\tINFILE\t\t\t the name of the .csv file that contains the origin dataset\n"
	"\tSHAPEFILE\t\t the name of the .txt file that contains the shape of the target dataset\n"
	"\t-h, --header\t\t use in case the input .csv file contains a header\n"
	"\t-i, --index\t\t use in case the input .csv file is indecied\n"
	"\t-oi, --output_init\t use to set the name for the output file containing the discretized initial dataset\n"
	"\t-or, --output_result\t use to set the name for the output file containing the discretized result dataset\n"
	;
}

/**
* Function to print information for the user
*/
void output_usage(){
	cout << "\nUsage: same_stats OUTFILE SHAPEFILE [-h] [-i] [-oi INITFILE] [-or RESULTFILE] [--header]\n"
	"[--index] [--output_init INITFILE] [--output_result RESULTFILE] [--help] [--usage]\n";
}

