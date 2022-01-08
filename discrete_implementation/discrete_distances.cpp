#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;

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
/*
int main()
{
	int length = 3;
	int complete_length = length*length;
    vector<int> distances(complete_length,0);
    vector<bool> shape(complete_length,false);
	//for(int i = 0; i<1; i++){
	//	shape[i] = true;
	//}
	int index = 0;
	ifstream is("test_small.txt");
	char c;
	while(is.get(c)){
		if(c!='0' && c!='1'){continue;}
		if(c=='1'){
			shape[index] = true;
		}
		index++;
	}
	if(length<=10){
		for(int i = 0; i<complete_length; i++){
			cout << shape[i] << " ";
			if((i+1)%length == 0){
				cout << "\n";
			}
		}
	}
	
	auto time_start = chrono::steady_clock::now();
	discrete_distance(distances, shape, length);
	auto time_end = chrono::steady_clock::now();
	cout << "Time needed: "<<chrono::duration_cast<chrono::milliseconds>(time_end - time_start).count()<<" milliseconds\n";
	
	if(length<=10){
		for(int i = 0; i<complete_length; i++){
			cout << distances[i] << " ";
			if((i+1)%length == 0){
				cout << "\n";
			}
		}
	}

}
*/
