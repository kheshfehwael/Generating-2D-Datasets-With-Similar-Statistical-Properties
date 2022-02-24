#include <vector>
#include <math.h>

// getting the statistical values of the vectors x and y when still in double type 
template <typename T> vector<double> get_stat_values(vector<T> x_data, vector<T> y_data, int* parameters, int n){
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