#include <vector>
#include<algorithm>

using  namespace  std;


int int_round(double x){
	return (int)(x+0.5 - (x<0));
}

void get_modification_parameters(int* parameters, vector<double> x, vector<double> y, int disc_length){
	int window = (int)(disc_length*0.94);
	int lower_window_bound = (int)(disc_length*0.03);
	double x_max = *max_element(x.begin(), x.end());
	double x_min = *min_element(x.begin(), x.end());
	double y_max = *max_element(y.begin(), y.end());
	double y_min = *min_element(y.begin(), y.end());
	double x_dist = x_max-x_min;
	double y_dist = y_max-y_min;
	
	parameters[0] = x_dist!=0 ? (int)(window/x_dist) : 1;	// Faktor x
	parameters[1] = y_dist!=0 ? (int)(window/y_dist) : 1;
	parameters[2] = (int)(lower_window_bound - x_min*parameters[0]);	// offset x
	parameters[3] = (int)(lower_window_bound - y_min*parameters[1]);
}

vector<int> modify_vector(vector<double> x, int* parameters, int dim, int length){
	vector<int> discrete(length);
	int factor = parameters[dim-1];
	int offset = parameters[dim+1];
	for(int i = 0; i < length; i++){
		discrete[i] = int_round(x[i]*factor + offset);
	}
	return discrete;
}

vector<double> modify_vector_back(vector<int>& x, int* parameters, int dim, int length){
	vector<double> original(length);
	int factor = parameters[dim-1];
	int offset = parameters[dim+1];
	for(int i = 0; i < length; i++){
		original[i] = (double)(x[i] - offset)/factor;
	}
	return original;
}