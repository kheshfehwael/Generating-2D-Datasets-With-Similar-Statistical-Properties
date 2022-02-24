#ifndef SAME_STATS_TOOLS_H
#define SAME_STATS_TOOLS_H

#include <vector>
#include "string"

using namespace std;

void discrete_distance(vector<int>& distances, vector<bool> shape, int length);
vector<double> get_stat_values_int(vector<int> x_data, vector<int> y_data, int* parameters, int n);
vector<double> get_stat_values_double(vector<double> x_data, vector<double> y_data, int* parameters, int n);
void read_csv(string& csvSource, vector<vector<double>>& lines, bool header = true, bool index = false);
vector<double> extract_vector(vector<vector<double>> input, int col);
void overwrite_csv(string filename, vector<double> x, vector<double> y, int length);
int int_round(double x);
void get_modification_parameters(int* parameters, vector<double> x, vector<double> y, int disc_length);
vector<int> modify_vector(vector<double> x, int* parameters, int dim, int length);
vector<double> modify_vector_back(vector<int>& x, int* parameters, int dim, int length);
void change_params(int* iter, int* shake, double* max_temp);

#endif //SAME_STATS_TOOLS_H
