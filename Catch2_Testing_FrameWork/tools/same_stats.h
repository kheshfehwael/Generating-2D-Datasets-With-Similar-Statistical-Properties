//
// Created by MHD WAEL KHESHFEH on 26.02.2022.
//

#ifndef TEST_PI_SAME_STATS_H
#define TEST_PI_SAME_STATS_H

#include <vector>
#include "string"
#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <random>
#include <tuple>
#include <fstream>
#include <chrono>

using namespace std;

bool check_error(vector<double> old_values, vector<int> x_new, vector<int> y_new, int* parameters, int length, int decimals =  2 );
auto perturb(vector<int> x, vector<int> y, double temp, int length, vector<int>& distances, int discr_length, int shake, int allowed_squared  = 40) -> tuple<vector<int>, vector<int>>;
double curve(double t);
auto run_patern(vector<int> x, vector<int> y, int* parameters, int length, vector<int>& distances, int discr_length, int iter, int shake, double max_temp) -> tuple<vector<int>, vector<int>>;
void output1();
void output_help();
void output_usage();



#endif //TEST_PI_SAME_STATS_H
