#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <random>
#include <tuple>
#include <fstream>
#include <chrono>
#include "same_stats_tools.h"



using namespace std;

/**
* Random number generators to be used in while permutation
*/
default_random_engine re{static_cast<long unsigned int>(0)};
uniform_int_distribution<int>  rand_num(0, RAND_MAX);
uniform_real_distribution<double> zero_to_one(0, 1.0);
uniform_real_distribution<double> uni_plus_minus_one(-1.0, 1.0);
normal_distribution<double> normal_plus_minus_one(0.0, 1.0);
binomial_distribution<int> binomial_generator(10, 0.5);

/**
* Function to determine if the statistical values of two given 1D arrays x and y differ from a
* given set of statistical values up to a given amount of decimal points. The statistical values
* beeing compared are mean value of x and y respectively, variance of x and y respectively and
* pearsons correlation.
*
* @param old_values the statistical values that beeing comapred to
* @param x_new the first vector
* @param y_new the second vector
* @param parameters an array that gives mofication parameters of x and y.
* @param length the length of the vectors x and y
* @param decimals the amount of decimal points that are taken into account in the comparison
*/
bool check_error(vector<double> old_values, vector<int> x_new, vector<int> y_new, int* parameters, int length, int decimals = 2){
    vector<double> new_values = get_stat_values_int(x_new, y_new, parameters, length);
    double sum = 0;
    for(int i = 0; i < 5; i++){
        sum += abs(((double)floor(old_values[i]*100)/100) - ((double)floor(new_values[i]*100)/100));
    }
    return sum == 0.0;
}

/**
* Function that manipulates one point of a 2D array. For the modification a random number
* generator is used. The modification only takes place if at least one of multiple conditions
* are satisfied. One condition is that the respective distance value in the distance matrix
* is smaller than the previous one. Another condition is that the perspective distance is
* smaller than a given value. Another condition is that an error is allowed. This last
* condition is part of the simulated annealing.
*
* @param x vector that contains the x-values of the 2D dataset
* @param y vector that contains the y-values of the 2D dataset
* @param temp the value to determine the allowed error in the simulated annealing
* @param length the length of the vectors x and y
* @param distances a vector representing a 2D discrete matrix containing distances
* @param discr_length the amount of discretization points per dimension
* @param shake the radius factor for the modification of the one point
* @param allowed_squared the squared distance value that is tollerated while pertubating
* @returns the resulting vectors x and y after the pertubation
*/
auto perturb(vector<int> x, vector<int> y, double temp, int length, vector<int>& distances, int discr_length, int shake, int allowed_squared = 40) -> tuple<vector<int>, vector<int>>
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

/**
* Function for in and out quadratic easing.
*
* @param t function argument
* @return resulting value if the easing function
*/
double curve(double t){
    return t < 0.5 ? 2 * t * t : 1 - (-2 * t + 2)*(-2 * t + 2) / 2;
}

/**
* Function that runs multiple iterations to modify a 2D dataset into a given shape
* while maintaining certain statistical values.
*
* @param x vector that contains the x-values of the initial 2D dataset
* @param y vector that contains the y-values of the initial 2D dataset
* @param parameters the parameters that determine how the 2D dataset was modified
*	for the discretization
* @param length the length of the vectors x and y
* @param distances a vector representing a 2D discrete matrix containing distances
* @param iter the amount of iterations
* @param shake the radius factor for the modification of one point
* @param max_temp the maximal value for the error allowed in the simulated annealing
* @returns the modified vectors x and y
*/
auto run_patern(vector<int> x, vector<int> y, int* parameters, int length, vector<int>& distances, int discr_length, int iter, int shake, double max_temp) -> tuple<vector<int>, vector<int>>
{
    vector<double> init_values = get_stat_values_int(x, y, parameters, length);
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

/**
* Function to print information for the user
*/
void output1(){
	cout << "\nUsage: same_stats INFILE SHAPEFILE [OPTION...]\n";
	cout <<	"Try `same_stats --help' or `same_stats --usage' for more information.\n";
}

/**
* Function to print information for the user
*/
void output_help(){
	cout << "\nUsage: same_stats INFILE SHAPEFILE [OPTION...]\n\n";
	cout <<	"same_stats is a program to generate a 2D dataset based on a given dataset and a given shape.\n"
	"For this the initial dataset is beeing mapped to a discrete 1000x1000 points field. This discretized\n"
	"dataset then is beeing modified into a given shape defined in SHAPEFILE while maintaining certain\n"
	"statistical values. After the modification of the dataset is done the discrete dataset is being mapped\n"
	"back to the initial scaling. The initial dataset (after the discretization) is beeing saved in INITFILE\n"
	"and the resulting file in RESULTFILE."
	"\n\n"
	"The file SHAPEFILE has to be a binary .txt file with the dimension 1000x1000. With the shape defined in\n"
	"this file a distance matrix is being calculated so the distances don't have to be calculated multiple times.\n"
	"After the calculation the user can modify following parameters regarding the modification of the dataset:\n"
	"iter - amount of iterations beeing done, shake - radius factor for modification of one single point, max_temp -\n"
	"maximal value allowed in the simulated annealing.\n"
	"One option to create such a .txt file is to paint a 1000x1000 bitmap and then use the tool one the website\n"
	"https://www.dcode.fr/binary-image. The coordinates of the shape must have the value 1."
	"\n\n"
	"\tINFILE\t\t\t the name of the .csv file that contains the origin dataset\n"
	"\tSHAPEFILE\t\t the name of the .txt file that contains the shape of the target dataset\n"
	"\t-h, --header\t\t use in case the input .csv file contains a header\n"
	"\t-i, --index\t\t use in case the input .csv file is indecied\n"
	"\t-oi, --output_init\t use to set the name for the output file containing the discretized initial dataset\n"
	"\t-or, --output_result\t use to set the name for the output file containing the discretized result dataset\n"
	;
}

/**
* Function to print information for the user
*/
void output_usage(){
	cout << "\nUsage: same_stats OUTFILE SHAPEFILE [-h] [-i] [-oi INITFILE] [-or RESULTFILE] [--header]\n"
	"[--index] [--output_init INITFILE] [--output_result RESULTFILE] [--help] [--usage]\n";
}

/**
* Main function for the interaction with the user. First the parsing of arguments are checked. When arguments
* are valid the distance matrix is calculated and the user has the oportunity to change some modification
* parameters, then the modification takes place. After that the user can check the resulting output file and
* decide whether the result is satisfying. If not then the parameters can be modified and a new modification
* takes place without having to calculate the distance matrix again.
*/
int main(int argc, char * argv[]) {
	vector<std::string> args(argv, argv+argc);
	string inputfile,shapefile;
	string output_init = "init.csv";
	string output_result = "result.csv";
	bool header = false;
	bool csv_index = false;
	
	// Checking parsed parameters
	if(argc == 1){
		output1();
		return 0;
	}else if(argc == 2){
		if (args[1].rfind("--help", 0) == 0){
			output_help();
		}else if(args[1].rfind("--usage", 0) == 0){
			output_usage();
		}else{
			output1();
		}
		return 0;
	}else{
		inputfile = args[1] + ".csv";
		shapefile = args[2] + ".txt";
		for(int i = 3; i<argc; i++){
			string temp_string = args[i];
			if(temp_string == "-h" || temp_string=="--header"){
				header = true;
			}else if(temp_string == "-i" || temp_string=="--index"){
				csv_index=true;
			}else if(temp_string == "-oi" || temp_string=="--output_init"){
				i++;
				output_init = args[i] + ".csv";
			}else if(temp_string == "-or" || temp_string=="--output_result"){
				i++;
				output_result = args[i] + ".csv";
			}else{
			cout << "option " << temp_string << " not recognized\n";
			}			
		}
	}
	
	int discr_length = 1000;	// Length discretization
    string names[5]= {"Average x", "Average y", "Variance x", "Variance y", "Correlation xy"};
	
	// Datasets for discrete results
	vector<double> x_start;
	vector<double> y_start;
	vector<double> x_result;
	vector<double> y_result;
	
	// Dataset for initial data
	vector<vector<double>> init_data;
	read_csv(inputfile,init_data, header, csv_index);
	if(init_data.size()==0) return 0;
	vector<double> x_exact = extract_vector(init_data, 1);
	vector<double> y_exact = extract_vector(init_data, 2);
	int length = x_exact.size();	
	
	cout << "\nLength of the vectors: " << length <<"\n";
	
	// Print statistical values of initial data set
	cout << "\nStatistical values before discretization:\n";
	int no_change[4] = {1,1,0,0};
    for(int i = 0; i < 5; i++){
        cout << names[i] << ":		" << get_stat_values_double(x_exact,y_exact,no_change,length)[i] << "\n";
    }
	cout <<"\n";
	
	// Calculation of factors and offsets
	int parameters[4];
	get_modification_parameters(parameters, x_exact, y_exact, discr_length);
	
	// Discretize initial dataset
	vector<int> x = modify_vector(x_exact, parameters, 1, length);
	vector<int> y = modify_vector(y_exact, parameters, 2, length);
	

	// Print statistical values of initial discrete data set
	cout << "Statistical values after discretization:\n";
    for(int i = 0; i < 5; i++){
        cout << names[i] << ":		" << get_stat_values_int(x,y,parameters,length)[i] << "\n";
    }
	cout <<"\n";
	
	// Calculate distance matrix
	auto time_start = chrono::steady_clock::now();
	vector<bool> shape(discr_length*discr_length,0);
	vector<int> distances(discr_length*discr_length,0);	// look-up matrix, discrete 2d field
	int index = 0;
	int compl_length = discr_length*discr_length;
	ifstream is(shapefile);
	if(!is.is_open()){
		cout << "\nCould not open file " << shapefile << "\n";
		return 0;
	}
	char c;
	while(is.get(c) && index < compl_length){
		if(c!='0' && c!='1'){continue;}
		if(c=='1'){
			shape[index] = true;
		}
		index++;
	}
	is.close();
	if(index < compl_length){
		cout << "\nShapefile has not the required sizes.\n";
		return 0;
	}
	cout << "Calculating distances...\n";
	discrete_distance(distances, shape, discr_length);
	auto time_end = chrono::steady_clock::now();
	cout << "Done. Time needed: "<<chrono::duration_cast<chrono::milliseconds>(time_end - time_start).count()<<" milliseconds\n";
	
	// Write init discrete dataset in csv file
	x_start = modify_vector_back(x, parameters, 1, length);
	y_start = modify_vector_back(y, parameters, 2, length);
	overwrite_csv(output_init,x_start,y_start, length);
    
	// Run modifications with different parameters until user is satisfied
    // Approxim. 2000 * size_of_x seems to be a good number of itterations
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
			cout << names[i] << ":		" << get_stat_values_int(x1,y1,parameters,length)[i] << "\n";
		}
	
		cout <<"\n";
		cout << "Time needed: "<<chrono::duration_cast<chrono::milliseconds>(time_end - time_start).count()<<" milliseconds\n";
	
		// final datasets 
		x_result = modify_vector_back(x1, parameters, 1, length);
		y_result = modify_vector_back(y1, parameters, 2, length);
	
		// write result in csv
		overwrite_csv(output_result,x_result,y_result, length);
		cout << "\nPlease check the file " << output_result << " to see your results.\n";
		cout << "Satisfied with the result? If yes please enter 'y' to end the program.\nOtherwise enter 'n' to reset your parameters. y/[n]\n";
		cin.clear();
		fflush(stdin);
		getline(cin, satisf);
		done = satisf.compare("y")>=0;
		cout << "---------------------------------------------------------------------\n";
	}while(!done);
return 0;
}