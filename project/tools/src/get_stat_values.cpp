#include <vector>
#include <math.h>
#include "same_stats_tools.h"

using namespace std;
/**
* Function to get the following statistical values for two 1D vectors x and y: mean value of x and y
* respectively, variance of x and y respectively, pearsons correlation of x and y. A modification array
* is also provided in case the initial dataset from which the statistical values have to be calculated
* is modified.
*
* @param x_data the x vector from which the values are beeing calculated
* @param y_data the y vector from which the values are beeing calculated
* @param parameters the modification parameters of the modified vectors x and y
* @param n the length of the vectors x and y
*/
vector<double> get_stat_values_int(vector<int> x_data, vector<int> y_data, int* parameters, int n){
    vector<double> values(5);

    double sum_x = 0;
    double sum_y = 0;

    for(int i = 0; i < n; i++){
        sum_x += x_data[i];
        sum_y += y_data[i];
    }
    values[0] = sum_x / n;
    values[1] = sum_y / n;

    sum_x = 0;
    sum_y = 0;

    double diff_x;
    double diff_y;
    for(int i = 0; i < n; i++){
        diff_x = x_data[i] - values[0];
        diff_y = y_data[i] - values[1];
        sum_x += diff_x*diff_x;
        sum_y += diff_y*diff_y;
    }
    values[2] = sqrt(sum_x / n);
    values[3] = sqrt(sum_y / n);

    sum_x = 0;
    diff_x = 0;
    diff_y = 0;

    for(int i = 0; i < n; i++){
        diff_x = x_data[i] - values[0];
        diff_y = y_data[i] - values[1];
        sum_x += diff_x*diff_y;
    }
	
	if(values[2] > 0 && values[3]> 0){
		values[4] = sum_x /	(values[2]*values[3]*n);
    }else{
		values[4] = values[2] == values[3] ? 1 : 0;
	}
    
	for(int i = 0; i<4; i++){
		values[i] = (values[i] - parameters[2 + i%2]*(i<2))/parameters[i%2];
	}
    return values;
}

/**
 * Same as above but with vectors containing values of the type double.
 */
vector<double> get_stat_values_double(vector<double> x_data, vector<double> y_data, int* parameters, int n){
    vector<double> values(5);

    double sum_x = 0;
    double sum_y = 0;

    for(int i = 0; i < n; i++){
        sum_x += x_data[i];
        sum_y += y_data[i];
    }
    values[0] = sum_x / n;
    values[1] = sum_y / n;

    sum_x = 0;
    sum_y = 0;

    double diff_x;
    double diff_y;
    for(int i = 0; i < n; i++){
        diff_x = x_data[i] - values[0];
        diff_y = y_data[i] - values[1];
        sum_x += diff_x*diff_x;
        sum_y += diff_y*diff_y;
    }
    values[2] = sqrt(sum_x / n);
    values[3] = sqrt(sum_y / n);

    sum_x = 0;
    diff_x = 0;
    diff_y = 0;

    for(int i = 0; i < n; i++){
        diff_x = x_data[i] - values[0];
        diff_y = y_data[i] - values[1];
        sum_x += diff_x*diff_y;
    }

    if(values[2] > 0 && values[3]> 0){
        values[4] = sum_x /	(values[2]*values[3]*n);
    }else{
        values[4] = values[2] == values[3] ? 1 : 0;
    }

    for(int i = 0; i<4; i++){
        values[i] = (values[i] - parameters[2 + i%2]*(i<2))/parameters[i%2];
    }
    return values;
}