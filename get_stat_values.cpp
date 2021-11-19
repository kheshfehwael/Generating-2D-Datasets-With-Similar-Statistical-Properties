#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

vector<float> get_stat_values(vector<float> x_data, vector<float> y_data){
	vector<float> values(5);
	int n = x_data.size();
	float sum = 0;
	// the following loops can easily be parallelized 
	// with OMP (e.g. reductions)
	
	for(int i = 0; i < n; i++){
		sum += x_data[i];
	}
	values[0] = sum / n;
	
	sum = 0;
	for(int i = 0; i < n; i++){
		sum += y_data[i];
	}
	values[1] = sum / n;
	sum = 0;
	
	int diff;
	for(int i = 0; i < n; i++){
		diff = x_data[i] - values[0];
		sum += diff*diff;
	}
	values[2] = sqrt(sum / n);
	
	sum = 0;
	
	for(int i = 0; i < n; i++){
		diff = y_data[i] - values[1];
		sum += diff*diff;
	}
	values[3] = sqrt(sum / n);
	
	sum = 0;
	
	int diff2;
	for(int i = 0; i < n; i++){
		diff = x_data[i] - values[0];
		diff2 = y_data[i] - values[1];
		sum += diff*diff2;
	}
	values[4] = sqrt(sum / (values[2]*values[3]*n));
	
	return values;
}


int main() {
	vector<float> x = {90.36,68.43,41.07,53.46,52.35,31.77,37.97,64.22,47.37,27.37,33.26,88.92,14.56,4.87,16.77,39.78,19.45,95.96,75.76,22.12,65.92,10.88,52.53,4.64,69.12,2.86,77.05,59.09,25.98,78.65,20.7,34.71,73.92,3.03,19.16,12.58,67.12,42.3,61.42,29.38,77.24,21.15,11.63,21.37,19.69,72.33,10.45,73.6,74.59,97.94,66.89,43.37,76.65,85.52,36.36,50.88,4.56,59.71,62.35,9.47,10.57,20.9,56.48,31.65,52.72,41.83,81.16,26.8,6.14,35.23,50.67,52.97,4.43,75.89,32.97,43.87,21.38,89.05,70.78,2.92,26.16,80.97,86.97,74.98,5.25,54.21,5.91,73.53,83.06,79.17,22.12,57.13,33.51,18.53,47.07,51.65,29.55,75.83,51.63,81,4.53,83.58,6.63,59.36,26.69,55.18,85.42,27.47,90.54,30.11,52.42,12.39,54.33,7.39,82.8,72.24,48.08,83.83,64.71,93.57,65.5,24.56,77.67,2.81,45.6,77.13,94.2,3.39,87.72,22.89,20.91,4.68,66.11,91.8,39.7,94.58,27.73,47.85,30.12,3.49,32.34,12.9,96.3,61.75,53.62,57.18,7.75,81.82,58.11,67.17,38.21,92.59,66.28,81.85,75.81,85.42,32.04,58.99,1.1,67.17,58.02,12.4,38.04,47.88,86.54,23.65,14.1,91.74,58.61,90.55,71.14,49.81,81.59,93.89,44.06,56.52,83.18,90.07,86.17,89.89,64.03,70.36,85.22,55.6,30.66,39.85,18.92,14.35,12.56,93.54,48.71,61.13,30.96,77.94,3.89,85,73.09,98.39,18.35,75.11};
	vector<float> y = {60.67,48.12,37.46,53.37,43.87,1.68,78.63,71.21,41.84,21.59,6.74,22.12,62.01,57.94,21.8,17.49,78.61,21.35,71.29,44.05,69.65,87.52,86.13,24.13,72.91,71.11,67.74,95.03,18.29,6.43,92.45,45,96.84,52.6,15.92,75.9,3.56,81.38,63.81,82.61,59.32,70.19,79.79,45.42,45.3,64.54,46.28,11.46,95.27,81.36,53.27,36.77,53.33,49.6,65.15,12.49,7.19,45.71,66.95,41,58.16,85.97,93.04,8.57,89.32,32.89,85.08,16.92,53.79,81.19,41.53,13.28,62.54,43.68,34.75,89.56,29.21,31.78,10.36,2.15,79.4,41.58,5.82,29.14,79.43,58.94,35.94,70.03,81.54,16.24,41.45,12.44,11.61,60.04,67.75,88.86,5.17,21.33,76.9,10.7,16.81,5.3,86.41,94.74,57.62,99.78,95.85,2.63,6.28,75.46,1.36,33.52,46.64,54.01,54.72,46.31,98.86,43.26,90.38,66.81,98.99,44.12,6.21,74.15,88.7,92.53,64.66,45.94,11.41,27.54,43,87.14,94.59,25.36,38.42,8.23,47.36,96.28,32.11,13.08,17.64,37.45,79.19,15.95,20.97,79.88,9.99,84.53,26.16,66.69,46.05,46.29,50.55,61.38,49.25,18.44,33.75,69.96,6.84,96.2,62.05,56.8,15.02,23.08,24.42,45.86,91.3,95.68,66.9,51.98,8.77,81.36,57.63,79.49,51.21,10.28,49.87,79.88,87.78,27.12,92.22,3.91,38.25,18.55,22.91,37.13,59.56,35.36,2.21,66.97,42.41,91.02,69.11,76.33,69.31,89.31,77.16,75.39,92.09,18.89};
	for(int i = 0; i < 5; i++){
		cout << get_stat_values(x,y)[i] << "\n";
	}
	return 0;
}
