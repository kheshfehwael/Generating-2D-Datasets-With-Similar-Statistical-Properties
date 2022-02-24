#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <random>
#include <tuple>
#include <fstream>
#include <chrono>
#include "interface_CSV_discrete.cpp"
#include "discrete_distances.cpp"
#include "modify_discrete.cpp"
#include "get_stat_values.cpp"



using namespace std;

// Set up random generators
default_random_engine re{static_cast<long unsigned int>(0)};
uniform_int_distribution<int>  rand_num(0, RAND_MAX);
uniform_real_distribution<double> zero_to_one(0, 1.0);
uniform_real_distribution<double> uni_plus_minus_one(-1.0, 1.0);
normal_distribution<double> normal_plus_minus_one(0.0, 1.0);
binomial_distribution<int> binomial_generator(10, 0.5);

// check if the manipulated set still has the same stat. values with tolerance <decimals>
bool check_error(vector<double> old_values, vector<int> x_new, vector<int> y_new, int* parameters, int length, int decimals = 2){
    vector<double> new_values = get_stat_values(x_new, y_new, parameters, length);
    double sum = 0;
    for(int i = 0; i < 5; i++){
        sum += abs(((double)floor(old_values[i]*100)/100) - ((double)floor(new_values[i]*100)/100));
    }
    return sum == 0.0;
}

// manipulating one random 2D-point.
// <temp> is the tolerance with which we allow an error.
// only implementet for circle form yet.
// <allowed> is the allowed distance from the form.
auto perturb(vector<int> x, vector<int> y,double temp, int length,vector<int>& distances, int discr_length, int shake, int allowed_squared = 40) -> tuple<vector<int>, vector<int>>
{
	int element = rand_num(re)%length;
    int x_el = x[element];
    int y_el = y[element];
    int x1;
    int y1;
    int old_dis = distances[(discr_length-1-y_el)*discr_length + x_el];
    int new_dis;

    bool found = false;
    bool do_bad = zero_to_one(re) < temp;

	while(!found){
		x1 = x_el + (binomial_generator(re)-5)*shake;
		y1 = y_el + (binomial_generator(re)-5)*shake;
		if(x1<discr_length && x1>=0 && y1<discr_length && y1 >=0){
			new_dis = distances[(discr_length-1-y1)*discr_length + x1];
		}else{
			continue;
		}
		if(old_dis>new_dis || new_dis<allowed_squared || do_bad){
			x[element] = x1;
			y[element] = y1;
			found = 1;
		}
	}
    return{ x, y};
}

double curve(double t){
    return t < 0.5 ? 2 * t * t : 1 - (-2 * t + 2)*(-2 * t + 2) / 2;
}

// function that runs the patern
auto run_patern(vector<int> x, vector<int> y, int* parameters, int length, vector<int>& distances, int discr_length, int iter, int shake, double max_temp) -> tuple<vector<int>, vector<int>>
{
    vector<double> init_values = get_stat_values(x, y, parameters, length);
    double t;
    int changes = 0;
    for(int i = 0;i < iter;i++){
        t = (max_temp) * curve(((double)iter-(double)i)/(double)iter);

        auto [x1,y1] = perturb(x,y,t,length,distances,discr_length,shake);

        if(check_error(init_values,x1,y1,parameters,length)){
            changes++;
            x = move(x1);
            y = move(y1);
        }

        // print progress

        if((i+1) % (int)(iter/10) == 0){
            cout << 100*(double)(i+1)/(double)iter << "%";
			if((i+1)!=iter){
				cout << " - ";
			}else{
				cout << "\n";
			}
        }
    }
    // print how many manipulations were really done
    cout << changes << " changes made\n";
    return{x,y};
}


int main() {
	int discr_length = 1000;	// length discretization
    string names[5]= {"Average x", "Average y", "Variance x", "Variance y", "Correlation xy"};
	// Datasets for results
	vector<double> x_start;
	vector<double> y_start;
	vector<double> x_result;
	vector<double> y_result;
	
	vector<vector<double>> init_data;
	read_csv("angled_blob.csv",init_data, true, true);
	
	vector<double> x_exact = extract_vector(init_data, 1);
	vector<double> y_exact = extract_vector(init_data, 2);
	int length = x_exact.size();
	cout << "\nLength of the vectors: " << length <<"\n";
	cout << "\nStatistical values before discretization:\n";
	int no_change[4] = {1,1,0,0};
	// print statistical values of initial data set
    for(int i = 0; i < 5; i++){
        cout << names[i] << ":		" << get_stat_values(x_exact,y_exact,no_change,length)[i] << "\n";
    }
	cout <<"\n";
	
	// Berechnung der Streckungsfaktoren und der Offsets für x und y
	int parameters[4];
	get_modification_parameters(parameters, x_exact, y_exact, discr_length);
	
	// Erzeugen der diskreten Vektoren
	vector<int> x = modify_vector(x_exact, parameters, 1, length);
	vector<int> y = modify_vector(y_exact, parameters, 2, length);
	

	cout << "Statistical values after discretization:\n";
    // print statistical values of initial discrete data set
    for(int i = 0; i < 5; i++){
        cout << names[i] << ":		" << get_stat_values(x,y,parameters,length)[i] << "\n";
    }
	cout <<"\n";
	
	// calculate distance matrix
	auto time_start = chrono::steady_clock::now();
	
	vector<bool> shape(discr_length*discr_length,0);
	vector<int> distances(discr_length*discr_length,0);	// look-up matrix, discrete 2d field
	
	int index = 0;
	ifstream is("schleife.txt");
	char c;
	while(is.get(c)){
		if(c!='0' && c!='1'){continue;}
		if(c=='1'){
			shape[index] = true;
		}
		index++;
	}
	cout << "Calculating distances...\n";
	discrete_distance(distances, shape, discr_length);
	auto time_end = chrono::steady_clock::now();
	cout << "Done. Time needed: "<<chrono::duration_cast<chrono::milliseconds>(time_end - time_start).count()<<" milliseconds\n";
	
	// write init discrete dataset in csv file
	x_start = modify_vector_back(x, parameters, 1, length);
	y_start = modify_vector_back(y, parameters, 2, length);
	overwrite_csv("init.csv",x_start,y_start, length);
    
	// amount of iterations
    // with shake = 0.1 and temp = 0.4 i found out that approxim. 2000 * size_of_x is a good number of itterations
	bool done = false;
	int iter = 300000;
	int shake = 1;
	double max_temp = 0.4;
	string satisf;
	cout <<"\nReady to do permutations. ";
	do{
		cout <<"Currently parameters are set to: iter="<<iter<< ", shake="<<shake<<", max_temp="<<max_temp<<".\nPlease enter parameters by typing *param*=*value* for the wished parameters\n";
		change_params(&iter, &shake, &max_temp);
		cout <<"Parameters set to: iter="<<iter<< ", shake="<<shake<<", max_temp="<<max_temp<<"\n";
		time_start = chrono::steady_clock::now();
		auto [x1,y1] = run_patern(x,y,parameters,length,distances,discr_length,iter,shake,max_temp);
		time_end = chrono::steady_clock::now();


		// run the function

		// print statistical values of result data set
		cout <<"\n";
		for(int i = 0; i < 5; i++){
			cout << names[i] << ":		" << get_stat_values(x1,y1,parameters,length)[i] << "\n";
		}
	
		cout <<"\n";
		cout << "Time needed: "<<chrono::duration_cast<chrono::milliseconds>(time_end - time_start).count()<<" milliseconds\n";
	
		// final datasets 
		x_result = modify_vector_back(x1, parameters, 1, length);
		y_result = modify_vector_back(y1, parameters, 2, length);
	
		// write result in csv
		overwrite_csv("result.csv",x_result,y_result, length);
		cout << "\nPlease check the file result.csv to see your results.\n";
		cout << "Satisfied with the result? If yes please enter 'y' to end the program. Otherwise enter 'n' to reset your parameters. y/[n]\n";
		cin.clear();
		fflush(stdin);
		getline(cin, satisf);
		done = satisf.compare("y")>=0;
		cout << "---------------------------------------------------------------------\n";
	}while(!done);
return 0;
}