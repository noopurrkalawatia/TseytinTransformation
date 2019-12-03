/*
 * tseytinUtil.h
 *
 *  Created on  : Nov 29, 2019
 *  Author      : noopurrkalawatia
 *  Description : This class is responsible for implementing the main logic of converting the .bench into CNF
 *                using the Tseytin transformation.
 */

#ifndef TSEYTINUTIL_H_
#define TSEYTINUTIL_H_

#include "fileOperationsUtil.h"

#include<iostream>
#include<unordered_map>
#include<vector>
#include<string>
#include<fstream>
#include<algorithm>
#include<sstream>

using namespace std;

#define INPUT "INPUT"
#define OUTPUT "OUTPUT"
#define DELIMITER "0"
#define SPACE " "

class tseytinUtil
{
    unordered_map<string,int> lookupInputOutput;
    vector<vector<string> > processedBenchLines;
    vector<int> outputIndices;
    vector<int> inputIndices;
    int noOfVariables;
    int noOfClausesInCNF;
    fileOperationsUtil *fileOperationOB;
    void formLookUpTable(string filename);
    void resolveInputIndices(string &firstAppend);
    vector<string> resolveOutputClauses();
    void resolveClauses();
    vector<string> preProcessInputLines(string &line);

public:
    tseytinUtil();
    void performTseytinTransformation(string fileName);
    virtual ~tseytinUtil();
};

#endif /* TSEYTINUTIL_H_ */
