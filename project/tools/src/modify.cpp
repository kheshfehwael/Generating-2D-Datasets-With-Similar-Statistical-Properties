#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include "same_stats_tools.h"

using  namespace  std;

/**
* Function to round a double number into an integer. e.g. 1.4 is rounded to 1 while 1.6 is rounded to 2.
*
* @param x the number to be rounded
* @return the interger result
*/
int int_round(double x){
	return (int)(x+0.5 - (x<0));
}

/**
* Function to determine the parameters that are beeing used to discretize a 2D dataset. The idea here
* is that for the discretization of two sets of numbers from the type double we stretch or retract the dataset
* to an integer 2D field of the form 1000x10000 located at the origin. With the calculated parameters we
* receive the factor and offset of each x and y coordinates to map the initial dataset to the 1000x1000 field.
*
* @param[out] parameters the calculated parameters needed for the modification
* @param[in] x the values representing the first dimension of the dataset
* @param[in] y the values representing the second dimension of the dataset
* @param[in] disc_length the amount of points in each dimension of the discretization
*/
void get_modification_parameters(int* parameters, vector<double> x, vector<double> y, int disc_length){
	int window = (int)(disc_length*0.94);
	int lower_window_bound = (int)(disc_length*0.03);
	double x_max = *max_element(x.begin(), x.end());
	double x_min = *min_element(x.begin(), x.end());
	double y_max = *max_element(y.begin(), y.end());
	double y_min = *min_element(y.begin(), y.end());
	double x_dist = x_max-x_min;
	double y_dist = y_max-y_min;
	
	parameters[0] = x_dist!=0 ? (int)(window/x_dist) : 1;	// factor x
	parameters[1] = y_dist!=0 ? (int)(window/y_dist) : 1;
    // this part guaranties no stretching of the target shape.
    // if the ratio (x_max-x_min)/(y_max-y_min) is close to 1
    // then the following if statement can be commended out.
    // we did our experiments without this part.
    /*if(parameters[0] < parameters[1]){
        parameters[1] = parameters[0];
    }else{
        parameters[0] = parameters[1];
    }*/
	parameters[2] = (int)(lower_window_bound - x_min*parameters[0]);	// offset x
	parameters[3] = (int)(lower_window_bound - y_min*parameters[1]);
}

/**
* Function to modify a vector with respect to given parameters as factor and offset.
*
* @param x the initial vector that is to be modified
* @param parameters the parameters factro and offset that are beeing used for the modification
* @param dim the offset to receive the right factor and offset from the array parameters
* @param length the length of the vector x
* @return the modified (stretched and moved) vector
*/
vector<int> modify_vector(vector<double> x, int* parameters, int dim, int length){
	vector<int> discrete(length);
	int factor = parameters[dim-1];
	int offset = parameters[dim+1];
	for(int i = 0; i < length; i++){
		discrete[i] = int_round(x[i]*factor + offset);
	}
	return discrete;
}

/**
* Reverse function to the function above.
*
* For parameters see above.
*/
vector<double> modify_vector_back(vector<int>& x, int* parameters, int dim, int length){
	vector<double> original(length);
	int factor = parameters[dim-1];
	int offset = parameters[dim+1];
	for(int i = 0; i < length; i++){
		original[i] = (double)(x[i] - offset)/factor;
	}
	return original;
}

/**
* Function to modify three variables. Therefore a user query is used.
*
* Parameters are integer and double variables that are beeing modified.
*/
void change_params(int* iter, int* shake, double* max_temp){
	int prev_iter = *iter;
	int prev_shake = *shake;
	double prev_matx_temp = *max_temp;
	string input;
	cin.clear();
	fflush(stdin);
	getline(cin, input);
	input.append(" ");
	size_t pos = input.find(" ");
	size_t pos_inner = 0;
	string token,param;
	while (pos != string::npos) {
		token = input.substr(0, pos);
		pos_inner = token.find("=");
		param = token.substr(0, pos_inner);
		token = token.substr(pos_inner+1, token.length());
		if(!param.compare("iter")){
			*iter = stoi(token);
		}else if(!param.compare("shake")){
			*shake = stoi(token);
		}else if(!param.compare("max_temp")){
			*max_temp = stod(token);
		}
			
		input.erase(0, pos+1);
		pos = input.find(" ");
	}
	*iter = *iter == 0 ? prev_iter : *iter; 
	*shake = *shake == 0 ? prev_shake : *shake; 
	*max_temp = *max_temp == 0 ? prev_matx_temp : *max_temp; 
}