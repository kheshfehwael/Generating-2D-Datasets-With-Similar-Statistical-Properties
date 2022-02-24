#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include "same_stats_tools.h"

using  namespace  std;

/**
* Function to read data for a 2D vector from a .csv file.
*
* @param[in] csvSource the name of the .csv file from which the data is read from
* @param[out] lines 2D vector to store the data from the .csv file
* @param[in] header a boolean variable, when set to true the first line of the .csv file is beeing ignored
* @param[in] index a boolean variable, when set to true the first number of each line in the .csv file is ignored
*/
void read_csv(string& csvSource, vector<vector<double>>& lines, bool header, bool index)
{
    string field;
    lines.clear();
    vector<double> line;
	string i_line;
	ifstream myfile(csvSource);
	if(!myfile.is_open()){
		cout << "Could not open file " << csvSource;
		return;
	}
	
	while(getline(myfile,i_line)){
		if(header){
			header = false;
			continue;
		}
		string::const_iterator aChar = i_line.begin();
		while (aChar != i_line.end())
		{
			if (*aChar == ',')
			{
				line.push_back(atof(field.c_str()));
				field.clear();
			}else{
				field += *aChar;
			}
			aChar++;
		}
		if (field.size()){
			line.push_back(atof(field.c_str()));
			field.clear();
		}
		if (index) line.erase(line.begin());
		if (line.size())
			lines.push_back(line);
		
		line.clear();
	}
}

/**
* Function to exctract a 1D vector that contain the elements of one specific column
* out of a multidimensional vector.
*
* @param input the multidimensional vector, from which the data are extracted
* @param col gives the column number from which the data is extracted
* @return the 1D vector containing the extracted data
*/
vector<double> extract_vector(vector<vector<double>> input, int col){
	int length = input.size();
	vector<double> vec(length);
	for(int i = 0; i<length; i++){
		vec[i] = input[i][col-1];
	}
	return vec;
}

/**
* Function to create a .csv file containing the data of two 1D vectors
*
* @param filename the name of the file that is to be created
* @param x the first 1D vector
* @param y the second 1D vector
* @param length the length of the vectors
*/
void overwrite_csv(string filename, vector<double> x, vector<double> y, int length){
    ofstream myfile1;
    myfile1.open (filename);
    myfile1 << "x,y\n";
    for(int i = 0; i < length; i++){
        myfile1 << x[i]<<","<<y[i]<<"\n";
    }
    myfile1.close();
}