#include "catch.h"
#include "tools/include/same_stats_tools.h"
#include "tools/same_stats.h"
#include <cmath>
#include <vector>
#include <math.h>
#include <random>

TEST_CASE("Test the Read of Data  ", "get_stat")
{

	// Test Read CSV
	vector<vector < double>> init_data, vec_exact;
	bool header = true, csv_index = true;
	int len = 182;
	string vec_field, i_line, inputfile = "D:/Generating-2D-Datasets-With-Similar-Statistical-Properties-main/Generating-2D-Datasets-With-Similar-Statistical-Properties-main/project/additional_files/slanted_less.csv";
	read_csv(inputfile, init_data, header, csv_index);
	vector<double> vec_line;
	int discr_length = 1000;
	int parameters[4];

	ifstream myfile(inputfile);
	while (getline(myfile, i_line))
	{
		if (header)
		{
			header = false;
			continue;
		}

		string::const_iterator aChar = i_line.begin();
		while (aChar != i_line.end())
		{
			if (*aChar == ',')
			{
				vec_line.push_back(atof(vec_field.c_str()));
				vec_field.clear();
			}
			else
			{
				vec_field += *aChar;
			}

			aChar++;
		}

		if (vec_field.size())
		{
			vec_line.push_back(atof(vec_field.c_str()));
			vec_field.clear();
		}

		if (csv_index)
			vec_line.erase(vec_line.begin());
		if (vec_line.size())
			vec_exact.push_back(vec_line);

		vec_line.clear();
	}

	// Test the Values
	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_exact.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i] == vec_exact[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 1);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][0] == vec_line[i]);
		}
	}
}

TEST_CASE("Test of Extract vector ", "get_stat")
{

	// Test Read CSV
	vector<vector < double>> init_data, vec_exact;
	bool header = true, csv_index = true;
	int len = 182;
	string vec_field, i_line, inputfile = "D:/Generating-2D-Datasets-With-Similar-Statistical-Properties-main/Generating-2D-Datasets-With-Similar-Statistical-Properties-main/project/additional_files/slanted_less.csv";
	read_csv(inputfile, init_data, header, csv_index);
	vector<double> vec_line;
	int discr_length = 1000;
	int parameters[4];

	ifstream myfile(inputfile);
	while (getline(myfile, i_line))
	{
		if (header)
		{
			header = false;
			continue;
		}

		string::const_iterator aChar = i_line.begin();
		while (aChar != i_line.end())
		{
			if (*aChar == ',')
			{
				vec_line.push_back(atof(vec_field.c_str()));
				vec_field.clear();
			}
			else
			{
				vec_field += *aChar;
			}

			aChar++;
		}

		if (vec_field.size())
		{
			vec_line.push_back(atof(vec_field.c_str()));
			vec_field.clear();
		}

		if (csv_index)
			vec_line.erase(vec_line.begin());
		if (vec_line.size())
			vec_exact.push_back(vec_line);

		vec_line.clear();
	}

	// Test the Values
	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_exact.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i] == vec_exact[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 1);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][0] == vec_line[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 1);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][0] == vec_line[i]);
		}
	}
}

TEST_CASE("Test of extract_vector with different values ", "get_stat")
{

	// Test Read CSV
	vector<vector < double>> init_data, vec_exact;
	bool header = true, csv_index = true;
	int len = 182;
	string vec_field, i_line, inputfile = "D:/Generating-2D-Datasets-With-Similar-Statistical-Properties-main/Generating-2D-Datasets-With-Similar-Statistical-Properties-main/project/additional_files/slanted_less.csv";
	read_csv(inputfile, init_data, header, csv_index);
	vector<double> vec_line;
	int discr_length = 1000;
	int parameters[4];

	ifstream myfile(inputfile);
	while (getline(myfile, i_line))
	{
		if (header)
		{
			header = false;
			continue;
		}

		string::const_iterator aChar = i_line.begin();
		while (aChar != i_line.end())
		{
			if (*aChar == ',')
			{
				vec_line.push_back(atof(vec_field.c_str()));
				vec_field.clear();
			}
			else
			{
				vec_field += *aChar;
			}

			aChar++;
		}

		if (vec_field.size())
		{
			vec_line.push_back(atof(vec_field.c_str()));
			vec_field.clear();
		}

		if (csv_index)
			vec_line.erase(vec_line.begin());
		if (vec_line.size())
			vec_exact.push_back(vec_line);

		vec_line.clear();
	}

	// Test the Values
	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_exact.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i] == vec_exact[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 1);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][0] == vec_line[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 1);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][0] == vec_line[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 2);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][1] == vec_line[i]);
		}
	}
}
TEST_CASE("Test 4 ", "get_stat")
{

	// Test Read CSV
	vector<vector < double>> init_data, vec_exact;
	bool header = true, csv_index = true;
	int len = 182;
	string vec_field, i_line, inputfile = "D:/Generating-2D-Datasets-With-Similar-Statistical-Properties-main/Generating-2D-Datasets-With-Similar-Statistical-Properties-main/project/additional_files/slanted_less.csv";
	read_csv(inputfile, init_data, header, csv_index);
	vector<double> vec_line;
	int discr_length = 1000;
	int parameters[4];

	ifstream myfile(inputfile);
	while (getline(myfile, i_line))
	{
		if (header)
		{
			header = false;
			continue;
		}

		string::const_iterator aChar = i_line.begin();
		while (aChar != i_line.end())
		{
			if (*aChar == ',')
			{
				vec_line.push_back(atof(vec_field.c_str()));
				vec_field.clear();
			}
			else
			{
				vec_field += *aChar;
			}

			aChar++;
		}

		if (vec_field.size())
		{
			vec_line.push_back(atof(vec_field.c_str()));
			vec_field.clear();
		}

		if (csv_index)
			vec_line.erase(vec_line.begin());
		if (vec_line.size())
			vec_exact.push_back(vec_line);

		vec_line.clear();
	}

	// Test the Values
	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_exact.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i] == vec_exact[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 1);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][0] == vec_line[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 1);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][0] == vec_line[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 2);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][1] == vec_line[i]);
		}
	}

	vec_line.clear();
	vector<double> x_exact = extract_vector(init_data, 1);
	vector<double> y_exact = extract_vector(init_data, 2);

	// Discretize initial dataset
	vector<int> x = modify_vector(x_exact, parameters, 1, len);
	vector<int> y = modify_vector(y_exact, parameters, 2, len);

	vec_line.push_back(149999);
	vec_line.push_back(149215);
	vec_line.push_back(0);
	vec_line.push_back(-7739);
	vec_line.push_back(0);

	if (get_stat_values_int(x, y, parameters, len).size() != 0)
	{
		for (int i = 0; i < 5; i++)
		{
			REQUIRE((int)(100000* get_stat_values_int(x, y, parameters, len)[i]) == vec_line[i]);
		}
	}
}

TEST_CASE("Test the Get stat values   ", "get_stat")
{

	// Test Read CSV
	vector<vector < double>> init_data, vec_exact;
	bool header = true, csv_index = true;
	int len = 182;
	string vec_field, i_line, inputfile = "D:/Generating-2D-Datasets-With-Similar-Statistical-Properties-main/Generating-2D-Datasets-With-Similar-Statistical-Properties-main/project/additional_files/slanted_less.csv";
	read_csv(inputfile, init_data, header, csv_index);
	vector<double> vec_line;
	int discr_length = 1000;
	int parameters[4];

	ifstream myfile(inputfile);
	while (getline(myfile, i_line))
	{
		if (header)
		{
			header = false;
			continue;
		}

		string::const_iterator aChar = i_line.begin();
		while (aChar != i_line.end())
		{
			if (*aChar == ',')
			{
				vec_line.push_back(atof(vec_field.c_str()));
				vec_field.clear();
			}
			else
			{
				vec_field += *aChar;
			}

			aChar++;
		}

		if (vec_field.size())
		{
			vec_line.push_back(atof(vec_field.c_str()));
			vec_field.clear();
		}

		if (csv_index)
			vec_line.erase(vec_line.begin());
		if (vec_line.size())
			vec_exact.push_back(vec_line);

		vec_line.clear();
	}

	// Test the Values
	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_exact.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i] == vec_exact[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 1);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][0] == vec_line[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 1);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][0] == vec_line[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 2);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][1] == vec_line[i]);
		}
	}

	vec_line.clear();
	vector<double> x_exact = extract_vector(init_data, 1);
	vector<double> y_exact = extract_vector(init_data, 2);

	// Discretize initial dataset
	vector<int> x = modify_vector(x_exact, parameters, 1, len);
	vector<int> y = modify_vector(y_exact, parameters, 2, len);

	vec_line.push_back(149999);
	vec_line.push_back(149215);
	vec_line.push_back(0);
	vec_line.push_back(-7739);
	vec_line.push_back(0);

	if (get_stat_values_int(x, y, parameters, len).size() != 0)
	{
		for (int i = 0; i < 5; i++)
		{
			REQUIRE((int)(100000* get_stat_values_int(x, y, parameters, len)[i]) == vec_line[i]);
		}
	}
	vec_line.clear();
	vec_line.push_back(-100000);
	vec_line.push_back(-100000);
	vec_line.push_back(0);
	vec_line.push_back(0);
	vec_line.push_back(32806);

	if (get_stat_values_double(x_exact, y_exact, parameters, len).size() != 0)
	{
		for (int i = 0; i < 5; i++)
		{
			REQUIRE((int)(100000* get_stat_values_double(x_exact, y_exact, parameters, len)[i]) == vec_line[i]);
		}
	}
}

TEST_CASE("Test of geting modification the parameters ", "get_stat")
{

	// Test Read CSV
	vector<vector < double>> init_data, vec_exact;
	bool header = true, csv_index = true;
	int len = 182;
	string vec_field, i_line, inputfile = "D:/Generating-2D-Datasets-With-Similar-Statistical-Properties-main/Generating-2D-Datasets-With-Similar-Statistical-Properties-main/project/additional_files/slanted_less.csv";
	read_csv(inputfile, init_data, header, csv_index);
	vector<double> vec_line;
	int discr_length = 1000;
	int parameters[4];

	ifstream myfile(inputfile);
	while (getline(myfile, i_line))
	{
		if (header)
		{
			header = false;
			continue;
		}

		string::const_iterator aChar = i_line.begin();
		while (aChar != i_line.end())
		{
			if (*aChar == ',')
			{
				vec_line.push_back(atof(vec_field.c_str()));
				vec_field.clear();
			}
			else
			{
				vec_field += *aChar;
			}

			aChar++;
		}

		if (vec_field.size())
		{
			vec_line.push_back(atof(vec_field.c_str()));
			vec_field.clear();
		}

		if (csv_index)
			vec_line.erase(vec_line.begin());
		if (vec_line.size())
			vec_exact.push_back(vec_line);

		vec_line.clear();
	}

	// Test the Values
	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_exact.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i] == vec_exact[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 1);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][0] == vec_line[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 1);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][0] == vec_line[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 2);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][1] == vec_line[i]);
		}
	}

	vec_line.clear();
	vector<double> x_exact = extract_vector(init_data, 1);
	vector<double> y_exact = extract_vector(init_data, 2);

	// Discretize initial dataset
	vector<int> x = modify_vector(x_exact, parameters, 1, len);
	vector<int> y = modify_vector(y_exact, parameters, 2, len);

	vec_line.push_back(149999);
	vec_line.push_back(149215);
	vec_line.push_back(0);
	vec_line.push_back(-7739);
	vec_line.push_back(0);

	if (get_stat_values_int(x, y, parameters, len).size() != 0)
	{
		for (int i = 0; i < 5; i++)
		{
			REQUIRE((int)(100000* get_stat_values_int(x, y, parameters, len)[i]) == vec_line[i]);
		}
	}
	vec_line.clear();
	vec_line.push_back(-100000);
	vec_line.push_back(-100000);
	vec_line.push_back(0);
	vec_line.push_back(0);
	vec_line.push_back(32806);

	if (get_stat_values_double(x_exact, y_exact, parameters, len).size() != 0)
	{
		for (int i = 0; i < 5; i++)
		{
			REQUIRE((int)(100000* get_stat_values_double(x_exact, y_exact, parameters, len)[i]) == vec_line[i]);
		}
	}
}
TEST_CASE("Test the geting modification of parameters ", "get_stat")
{
	// Test Read CSV
	vector<vector < double>> init_data, vec_exact;
	bool header = true, csv_index = true;
	int len = 182;
	string vec_field, i_line, inputfile = "D:/Generating-2D-Datasets-With-Similar-Statistical-Properties-main/Generating-2D-Datasets-With-Similar-Statistical-Properties-main/project/additional_files/slanted_less.csv";
	read_csv(inputfile, init_data, header, csv_index);
	vector<double> vec_line;
	int discr_length = 1000;
	int parameters[4];

	ifstream myfile(inputfile);
	while (getline(myfile, i_line))
	{
		if (header)
		{
			header = false;
			continue;
		}

		string::const_iterator aChar = i_line.begin();
		while (aChar != i_line.end())
		{
			if (*aChar == ',')
			{
				vec_line.push_back(atof(vec_field.c_str()));
				vec_field.clear();
			}
			else
			{
				vec_field += *aChar;
			}

			aChar++;
		}

		if (vec_field.size())
		{
			vec_line.push_back(atof(vec_field.c_str()));
			vec_field.clear();
		}

		if (csv_index)
			vec_line.erase(vec_line.begin());
		if (vec_line.size())
			vec_exact.push_back(vec_line);

		vec_line.clear();
	}

	// Test the Values
	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_exact.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i] == vec_exact[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 1);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][0] == vec_line[i]);
		}
	}

	vec_line.clear();
	vec_line = extract_vector(init_data, 2);

	if (init_data.size() != 0)
	{
		REQUIRE(init_data.size() == vec_line.size());
		for (int i = 0; i < len; i++)
		{
			REQUIRE(init_data[i][1] == vec_line[i]);
		}
	}

	vec_line.clear();
	vector<double> x_exact = extract_vector(init_data, 1);
	vector<double> y_exact = extract_vector(init_data, 2);

	// Discretize initial dataset
	vector<int> x = modify_vector(x_exact, parameters, 1, len);
	vector<int> y = modify_vector(y_exact, parameters, 2, len);

	vec_line.push_back(149999);
	vec_line.push_back(149215);
	vec_line.push_back(0);
	vec_line.push_back(-7739);
	vec_line.push_back(0);

	if (get_stat_values_int(x, y, parameters, len).size() != 0)
	{
		for (int i = 0; i < 5; i++)
		{
			REQUIRE((int)(100000* get_stat_values_int(x, y, parameters, len)[i]) == vec_line[i]);
		}
	}

	vec_line.clear();
	vec_line.push_back(-100000);
	vec_line.push_back(-100000);
	vec_line.push_back(0);
	vec_line.push_back(0);
	vec_line.push_back(32806);

	if (get_stat_values_double(x_exact, y_exact, parameters, len).size() != 0)
	{
		for (int i = 0; i < 5; i++)
		{
			REQUIRE((int)(100000* get_stat_values_double(x_exact, y_exact, parameters, len)[i]) == vec_line[i]);
		}
	}

	if (get_stat_values_double(x_exact, y_exact, parameters, len).size() != 0)
	{
		for (int i = 0; i < 5; i++)
		{
			REQUIRE((int)(100000* get_stat_values_double(x_exact, y_exact, parameters, len)[i]) == vec_line[i]);
		}
	}

	int test_parameters[] = { 1200000, 900000, -17700000, 2400000, -80000, 100000000 };

	get_modification_parameters(parameters, x_exact, y_exact, discr_length);

	for (int i = 0; i < 6; i++)
	{
		REQUIRE((int)(100000 *parameters[i]) == test_parameters[i]);
	}
}

TEST_CASE("Test the Run Funktions of curve   ", "get_stat")
	{

		// Test Read CSV
		vector<vector < double>> init_data, vec_exact;
		bool header = true, csv_index = true;
		int len = 182;
		string vec_field, i_line, inputfile = "D:/Generating-2D-Datasets-With-Similar-Statistical-Properties-main/Generating-2D-Datasets-With-Similar-Statistical-Properties-main/project/additional_files/slanted_less.csv";
		read_csv(inputfile, init_data, header, csv_index);
		vector<double> vec_line;
		int discr_length = 1000;
		int parameters[4];

		ifstream myfile(inputfile);
		while (getline(myfile, i_line))
		{
			if (header)
			{
				header = false;
				continue;
			}

			string::const_iterator aChar = i_line.begin();
			while (aChar != i_line.end())
			{
				if (*aChar == ',')
				{
					vec_line.push_back(atof(vec_field.c_str()));
					vec_field.clear();
				}
				else
				{
					vec_field += *aChar;
				}

				aChar++;
			}

			if (vec_field.size())
			{
				vec_line.push_back(atof(vec_field.c_str()));
				vec_field.clear();
			}

			if (csv_index)
				vec_line.erase(vec_line.begin());
			if (vec_line.size())
				vec_exact.push_back(vec_line);

			vec_line.clear();
		}

		// Test the Values
		if (init_data.size() != 0)
		{
			REQUIRE(init_data.size() == vec_exact.size());
			for (int i = 0; i < len; i++)
			{
				REQUIRE(init_data[i] == vec_exact[i]);
			}
		}

		vec_line.clear();
		vec_line = extract_vector(init_data, 1);

		if (init_data.size() != 0)
		{
			REQUIRE(init_data.size() == vec_line.size());
			for (int i = 0; i < len; i++)
			{
				REQUIRE(init_data[i][0] == vec_line[i]);
			}
		}

		vec_line.clear();
		vec_line = extract_vector(init_data, 2);

		if (init_data.size() != 0)
		{
			REQUIRE(init_data.size() == vec_line.size());
			for (int i = 0; i < len; i++)
			{
				REQUIRE(init_data[i][1] == vec_line[i]);
			}
		}

		vec_line.clear();
		vector<double> x_exact = extract_vector(init_data, 1);
		vector<double> y_exact = extract_vector(init_data, 2);

		// Discretize initial dataset
		vector<int> x = modify_vector(x_exact, parameters, 1, len);
		vector<int> y = modify_vector(y_exact, parameters, 2, len);

        REQUIRE ( curve(2) == -1.0);

    }
