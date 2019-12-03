/*
 * fileOperationsUtil.h
 *
 *  Created on: Nov 29, 2019
 *  Author: noopurrkalawatia
 *  Description : This class is a file utility class in order to carry out operations
 *                like reading the contents of the file, writing the contents to the CNF file.
 */


#include<iostream>
#include<vector>
#include<string>
#include<fstream>
#include<sstream>

using namespace std;


#ifndef FILEOPERATIONSUTIL_H_
#define FILEOPERATIONSUTIL_H_
#define SPACE " "
#define DELIMITER "0"

class fileOperationsUtil
{
    string fileName;
    void resolveFileName(string input);

public:
    fileOperationsUtil();
    void writeToCNFFile(vector<string> input, int noOfVariables, int noOfClauses,string firstAppend,vector<string> outputClauses);
    vector<string> readContentsOfFile(string fileName);
    virtual ~fileOperationsUtil();
};

#endif /* FILEOPERATIONSUTIL_H_ */
