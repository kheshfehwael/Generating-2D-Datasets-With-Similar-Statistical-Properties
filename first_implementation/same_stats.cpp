#include <iostream>
#include <vector>
#include <math.h>
#include <time.h>
#include <random>
#include <tuple>
#include <fstream>
#include <chrono>
#include "interface_CSV.cpp"
#include <string>
#include <fstream>
#include <windows.h>


using namespace std;

// Set up random generators
default_random_engine re{static_cast<long unsigned int>(0)};
uniform_int_distribution<int>  rand_num(0, RAND_MAX);
uniform_real_distribution<double> zero_to_one(0, 1.0);
uniform_real_distribution<double> uni_plus_minus_one(-1.0, 1.0);
normal_distribution<double> normal_plus_minus_one(0.0, 1.0);

// getting the statistical values of the vectors x and y
vector<double> get_stat_values(vector<double> x_data, vector<double> y_data, int n){
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
    values[4] = sum_x /	(values[2]*values[3]*n);

    return values;
}

// check if the manipulated set still has the same stat. values with tolerance <decimals>
bool check_error(vector<double> old_values, vector<double> x_new, vector<double> y_new, int length, int decimals = 2){
    vector<double> new_values = get_stat_values(x_new, y_new, length);
    double sum = 0;
    for(int i = 0; i < 5; i++){
        sum += abs((floor(old_values[i]*100)/100) - (floor(new_values[i]*100)/100));
    }
    return sum == 0.0;
}

// Eucledian norm
double point_distance(double x1, double y1, double x2, double y2){
    return sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2));
}

double  min_vec(vector <double> vec){
    for (int i = 0; i < vec.size(); i++) {
        vec[0] = min(vec[0],vec[i]);
    }
    return vec[0];
}

double distance_line_point(double px, double py, double lx1, double ly1, double lx2, double ly2){
	double magn = point_distance(lx1, ly1, lx2, ly2);
	// hier entweder eine Abfrage machen ob magn nicht zu klein ist
	// oder vorher sicherstellen dass linien keine Punkte sind !!!
	
	double dist = (((px - lx1) * (lx2 - lx1)) + ((py - ly1) * (ly2 - ly1)));
	dist = dist/(magn*magn);
	
	if(dist < 1e-5 || dist >1){
		double i1 = point_distance(px, py, lx1, ly1);
		double i2 = point_distance(px, py, lx2, ly2);
		dist = i1 > i2? i2 : i1;
	}else{
		double i1 = lx1 + dist * (lx2 - lx1);
		double i2 = ly1 + dist * (ly2 - ly1);
		dist = point_distance(px, py, i1, i2);
	}
	return dist;
	
}


// manipulating one random 2D-point.
// <temp> is the tolerance with whch we allow an error.
// only implementet for circle form yet.
// <allowed> is the allowed distance from the form.
auto perturb(vector<double> x, vector<double> y,double temp, int length,const string shape, vector<vector<double>> shape_data, double allowed = 2,vector<double> y_bounds={-200, 200},vector<double> x_bounds={-200, 200}) -> tuple<vector<double>, vector<double>>
{
    int element = rand_num(re)%length;
    double x_el = x[element];
    double y_el = y[element];
    double x1;
    double y1;
    double old_dis;
    double new_dis;
	const int amount_of_shapes = shape_data.size();
	vector<double> distances(amount_of_shapes);

    double shake = 0.1;
    bool found = 0;
    bool do_bad = zero_to_one(re) < temp;
	
	if(shape == "circles")
	{
		for(int i = 0;i < amount_of_shapes; i++){
			distances[i] = abs(point_distance(x_el,y_el,shape_data[i][0],shape_data[i][1])-shape_data[i][2]);
		}
		old_dis = min_vec(distances);
		found = 0;
		while(!found){
			x1 = x_el + normal_plus_minus_one(re)*shake;
			y1 = y_el + normal_plus_minus_one(re)*shake;
			for(int i = 0;i < amount_of_shapes; i++){
				distances[i] = abs(point_distance(x1,y1,shape_data[i][0],shape_data[i][1])-shape_data[i][2]);
			}	
			new_dis = min_vec(distances);
			if((old_dis>new_dis || new_dis<allowed || do_bad) && y1 > y_bounds[0] && y1  < y_bounds[1] &&  x1 > x_bounds[0] && x1 < x_bounds[1] ){
				x[element] = x1;
				y[element] = y1;
				found = 1;
			}
		}
	}
	if(shape == "dots")
	{
		for(int i = 0;i < amount_of_shapes; i++){
			distances[i] = point_distance(x_el, y_el, shape_data[i][0],shape_data[i][1]);
		}
		old_dis = min_vec(distances);
		found = 0;
		while(!found){
			x1 = x_el + normal_plus_minus_one(re)*shake;
			y1 = y_el + normal_plus_minus_one(re)*shake;
			for(int i = 0;i < amount_of_shapes; i++){
				distances[i] = point_distance(x1, y1, shape_data[i][0],shape_data[i][1]);
			}	
			new_dis = min_vec(distances);
			if((old_dis>new_dis || new_dis<allowed || do_bad) && y1 > y_bounds[0] && y1  < y_bounds[1] &&  x1 > x_bounds[0] && x1 < x_bounds[1] ){
				x[element] = x1;
				y[element] = y1;
				found = 1;
			}
		}

	}
	if(shape == "lines")
	{
		for(int i = 0;i < amount_of_shapes; i++){
			distances[i] = distance_line_point(x_el,y_el,shape_data[i][0],shape_data[i][1],shape_data[i][2],shape_data[i][3]);
		}
		old_dis = min_vec(distances);
		found = 0;
		while(!found){
			x1 = x_el + normal_plus_minus_one(re)*shake;
			y1 = y_el + normal_plus_minus_one(re)*shake;
			for(int i = 0;i < amount_of_shapes; i++){
				distances[i] = distance_line_point(x1,y1,shape_data[i][0],shape_data[i][1],shape_data[i][2],shape_data[i][3]);
			}	
			new_dis = min_vec(distances);
			if((old_dis>new_dis || new_dis<allowed || do_bad) && y1 > y_bounds[0] && y1  < y_bounds[1] &&  x1 > x_bounds[0] && x1 < x_bounds[1] ){
				x[element] = x1;
				y[element] = y1;
				found = 1;
			}
		}

	}
	else // if no shape is given, just make one circle
	{
		// coordinates of the circle
		double cx = 54.26;
		double cy = 47.83;
		double r = 30.0;
		old_dis = abs(point_distance(x_el,y_el,cx,cy)-r);
		found = 0;
		while(!found){
			x1 = x_el + normal_plus_minus_one(re)*shake;
			y1 = y_el + normal_plus_minus_one(re)*shake;
			new_dis = abs(point_distance(x1,y1,cx,cy)-r);
			if((old_dis>new_dis || new_dis<allowed || do_bad) && y1 > y_bounds[0] && y1  < y_bounds[1] &&  x1 > x_bounds[0] && x1 < x_bounds[1] ){
				x[element] = x1;
				y[element] = y1;
				found = 1;
			}
		}
	}
    return{ x, y};
}

double curve(double t){
    return t < 0.5 ? 2 * t * t : 1 - (-2 * t + 2)*(-2 * t + 2) / 2;
}

// function that runs the patern
auto run_patern(vector<double> x, vector<double> y, int length, const string shape, vector<vector<double>> shape_data, int iter = 10000000) -> tuple<vector<double>, vector<double>>
{
    vector<double> init_values = get_stat_values(x, y, length);
    double t;
    double max_temp = 0.4;
    int changes = 0;
    for(int i = 0;i < iter;i++){
        t = (max_temp) * curve(((double)iter-(double)i)/(double)iter);

        auto [x1,y1] = perturb(x,y,t,length,shape,shape_data);

        if(check_error(init_values,x1,y1,length)){
            changes++;
            x = move(x1);
            y = move(y1);
        }

        // print progress

        if((i+1) % (int)(iter/2) == 0){
            cout << 100*(double)(i+1)/(double)iter << "%\n";
        }
    }
    // print how many manipulations were really done
    cout << "\n" << changes << " changes made\n";
    return{x,y};
}
void read_docu(string line){

    ifstream myReadFile;
    myReadFile.open(line);
    char output[100];
    if (myReadFile.is_open()) {
        while (!myReadFile.eof()) {
            myReadFile >> output;
            if(output == " "){cout <<  endl;}
            cout<<output;
        }
    }
    myReadFile.close();
}

int main(int argc, char **argv) {
	
     	
		
		
	
	
	if (!strcmp(argv[1], "-h")) {
		
        // open_documentation
        string str("C:\\Users\\MHD WAEL KHESHFEH\\Desktop\\path\\project_2.ipynb");
        read_docu(str);
		
    }else if(!strcmp(argv[2], "-hw")){

    }
	
	
	
	
    string names[5]= {"Average x", "Average y", "Variance x", "Variance y", "Correlation xy"};
	vector<vector<double>> init_data;
	read_csv("start.csv",init_data);
	vector<double> x = extract_vector(init_data, 1);
	vector<double> y = extract_vector(init_data, 2);
	
    int length = x.size();
    cout << "Length of the vector: " << length <<"\n";
	cout <<"\n";
	
    // print statistical values of initial data set
    for(int i = 0; i < 5; i++){
        cout << names[i] << ":		" << get_stat_values(x,y,length)[i] << "\n";
    }
	cout <<"\n";
	
    // amount of iterations
    // with shake = 0.1 and temp = 0.4 i found out that approxim. 2000 * size_of_x is a good number of itterations
    int iter = 200000;


    // run the function
    auto time_start = chrono::steady_clock::now();
	
	const string shape = "lines";		// set which kind of shapes you want to run, currently the possible ones are "lines", "dots", "circles".
	vector<vector<double>> shape_data;
	read_csv("star_lines.csv",shape_data);	// choose csv file to get the shapes. Look at example files to see the structure of the files.
    auto [x1,y1] = run_patern(x,y,length,shape,shape_data,iter);
    auto time_end = chrono::steady_clock::now();

    // print statistical values of result data set
	cout <<"\n";
    for(int i = 0; i < 5; i++){
        cout << names[i] << ":		" << get_stat_values(x1,y1,length)[i] << "\n";
    }
	
	cout <<"\n";
	cout << "Time needed :"<<chrono::duration_cast<chrono::milliseconds>(time_end - time_start).count()<<" milliseconds\n";
	
	// write result in csv
    overwrite_csv("result.csv",x1,y1, length);
    return 0;
}
