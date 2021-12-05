#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <fstream>
#include <stdexcept>

using  namespace  std;


void ParseCSV(const string& csvSource, vector<vector<string> >& lines)
{
    bool inQuote(false);
    bool newLine(false);
    string field;
    lines.clear();
    vector<string> line;

    string::const_iterator aChar = csvSource.begin();
    while (aChar != csvSource.end())
    {
        switch (*aChar)
        {
            case '"':
                newLine = false;
                inQuote = !inQuote;
                break;

            case ',':
                newLine = false;
                if (inQuote == true)
                {
                    field += *aChar;
                }
                else
                {
                    line.push_back(field);
                    field.clear();
                }
                break;

            case '\n':
            case '\r':
                if (inQuote == true)
                {
                    field += *aChar;
                }
                else
                {
                    if (newLine == false)
                    {
                        line.push_back(field);
                        lines.push_back(line);
                        field.clear();
                        line.clear();
                        newLine = true;
                    }
                }
                break;

            default:
                newLine = false;
                field.push_back(*aChar);
                break;
        }

        aChar++;
    }

    if (field.size())
        line.push_back(field);

    if (line.size())
        lines.push_back(line);
}
std::vector<std::pair<std::string, std::vector<int>>> read_csv(std::string filename){
    // vector als Ergebnis
    std::vector<std::pair<std::string, std::vector<int>>> result;

    // import von File
    std::ifstream myFile(filename);

    // ist die Data vorhanden ?
    if(!myFile.is_open()) throw std::runtime_error("Could not open file");


    std::string line, colname;
    int val;


    if(myFile.good())
    {
        std::getline(myFile, line);
        std::stringstream ss(line);
        while(std::getline(ss, colname, ',')){
            result.push_back({colname, std::vector<int> {}});
        }
    }


    while(std::getline(myFile, line))
    {
        std::stringstream ss(line);
        int colIdx = 0;
        while(ss >> val){
            result.at(colIdx).second.push_back(val);
            if(ss.peek() == ',') ss.ignore();
            colIdx++;
        }
    }

    // schlißen vom  file
    myFile.close();

    return result;
}



void write_csv(std::string filename, std::vector<std::pair<std::string, std::vector<int>>> dataset){

    // öffnen von File zum speichern
    std::ofstream myFile(filename);

    for(int j = 0; j < dataset.size(); ++j)
    {
        myFile << dataset.at(j).first;
        if(j != dataset.size() - 1) myFile << ",";
    }
    myFile << "\n";
    for(int i = 0; i < dataset.at(0).second.size(); ++i)
    {
        for(int j = 0; j < dataset.size(); ++j)
        {
            myFile << dataset.at(j).second.at(i);
            if(j != dataset.size() - 1) myFile << ",";
        }
        myFile << "\n";
    }

    // Close the file
    myFile.close();
}

int main() {


    // erste Loesung
    // write vectors to example
    std::vector<int> vec1(100, 1);
    std::vector<int> vec2(100, 2);
    std::vector<int> vec3(100, 3);


    std::vector<std::pair<std::string, std::vector<int>>> vals = {{"One", vec1}, {"Two", vec2}, {"Three", vec3}};

    // Vector in Csv umschreiben
    write_csv("three_cols.csv", vals);
    std::vector<std::pair<std::string, std::vector<int>>> three_cols = read_csv("three_cols.csv");



    // zweite Loesung
    vector<vector<string> > str_vec;
    ParseCSV("three_cols.csv",str_vec);
    cout << str_vec.size() <<endl;


    return 0;
}
