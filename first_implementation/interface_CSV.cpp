#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>

using  namespace  std;


void read_csv(const string& csvSource, vector<vector<double>>& lines, bool header = true)
{
    string field;
    lines.clear();
    vector<double> line;
	string i_line;
	ifstream myfile(csvSource);
	if(!myfile.is_open()) throw std::runtime_error("Could not open file");
	
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

		if (line.size())
			lines.push_back(line);
		
		line.clear();
	}
}

vector<double> extract_vector(vector<vector<double>> input, int col){
	vector<double> vec(input.size());
	for(int i = 0; i<input.size(); i++){
		vec[i] = input[i][col-1];
	}
	return vec;
}

void overwrite_csv(const char* filename, vector<double> x, vector<double> y, int length){
	remove(filename);
    ofstream myfile1;
    myfile1.open (filename);
    myfile1 << "x,y\n";
    for(int i = 0; i < length; i++){
        myfile1 << x[i]<<","<<y[i]<<"\n";
    }
    myfile1.close();
}