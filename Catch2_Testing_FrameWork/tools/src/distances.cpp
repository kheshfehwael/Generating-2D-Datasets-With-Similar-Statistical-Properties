#include <iostream>
#include <fstream>
#include <vector>
#include <omp.h>
#include "same_stats_tools.h"

using namespace std;

/**
* Given a 2D shape in form of coordinates, this function calculates the squared distances
* from this shape in a discrete 2D field. The return is a 1D vector that represents the 2D
* discrete field.
*
* @param[in] distances the vector where the distances are stored
* @param[out] shape a boolean vector that contains the shape form which the distances are
* 			calculated
* @param[in] length the amount of points contained in one dimension of the 2D discretized
* 			field, i.e. the matrix distances has length*length elements
*/
void discrete_distance(vector<int>& distances, vector<bool> shape, int length){
	int dis,temp_dis,row,col;
	vector<int> coords; // vector of coordinates of the elements of shape
	int complete_length = length*length;
	for(int i = 0; i < complete_length; i++){
		if(shape[i]){
			coords.push_back(int(i/length));
			coords.push_back(i%length);
		}
	}
	int points_length = coords.size()/2;
#pragma omp parallel for private(dis,temp_dis,row,col) schedule(static)
	for(int i = 0; i < complete_length; i++){
		if(shape[i]){
			continue;
		}
		dis = INT_MAX;
		row = int(i/length);
		col = i%length;
		for(int j = 0; j < points_length; j++){
			temp_dis = (row-coords[2*j])*(row-coords[2*j]) + (col-coords[2*j+1])*(col-coords[2*j+1]);
			dis = dis < temp_dis ? dis : temp_dis;
		}
		distances[i] = dis;
	}
}