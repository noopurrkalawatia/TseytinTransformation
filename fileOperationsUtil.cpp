/*
 * fileOperationsUtil.cpp
 *
 *  Created on: Nov 29, 2019
 *      Author: noopurrkalawatia
 */

#include "fileOperationsUtil.h"

fileOperationsUtil::fileOperationsUtil()
{
    // TODO Auto-generated constructor stub

}

fileOperationsUtil::~fileOperationsUtil()
{
    // TODO Auto-generated destructor stub
}

/*
 * Name         : resolveFileName
 * Paramters    : input<string> - the name of the fileName specified.
 * return       : void
 * Description  : resolve the file name from the command line argument and set the member variable.
 */
void fileOperationsUtil::resolveFileName(string input)
{
    stringstream check1(input);
    string intermediate;
    vector<string> tokens;
    while(getline(check1, intermediate, '.'))
    {
        tokens.push_back(intermediate);
    }
    fileName = tokens[0];
}

/*
 * Name         : writeToCNFFile
 * Parameters   : input - The strings to be written to the file.
 *                noOfVariables - The total number of variables in the .bench file
 *                noOfClauses - The total number of clauses calculated after performing the tranformation
 *                firstAppend - The sampling set of inputs
 * return       : void
 * Description  : The function is responsible for writing the contents to the CNF file
 */
void fileOperationsUtil::writeToCNFFile(vector<string> input, int noOfVariables, int noOfClauses,string firstAppend,
        vector<string> outputClauses)
{
    string first = "c ind ";
    string second = "p cnf " + to_string(noOfVariables) + SPACE + to_string(noOfClauses);

    first += firstAppend;

    ofstream myFile(fileName + ".cnf", std::ofstream::out | std::ofstream::app);

    if(myFile.is_open())
    {
        myFile << first << endl;
        myFile << second << endl;

        for(auto line : input)
        {
            myFile << line << endl;
        }

        for(auto line : outputClauses)
        {
            myFile << line << endl;
        }
    }
    else
    {
        std::cout << "writeToCNFFile :: Error is opening the .cnf file" << endl;
        exit(0);
    }

    myFile.close();
    cout << "Successfully converted the .bench file to .cnf file using Tseytin Transformation" << endl;
}

/*
 * Name         : readContentsOfFile
 * Parameters   : _fileName - The name of the filename as read from the command line..
 * return       : vector<string> - All the lines as read from the file
 * Description  : The function is responsible for reading the contents of the file
 */
vector<string> fileOperationsUtil::readContentsOfFile(string _fileName)
{
    resolveFileName(_fileName);

    ifstream myFile(_fileName);
    string line;
    vector<string> result;

    if(myFile.is_open())
    {
        while(getline(myFile,line))
        {
            result.push_back(line);
        }
    }
    else
    {
        cout << "readContentsOfFile :: Error in opening the file " << endl;
        exit(0);
    }
    myFile.close();

    return result;
}
