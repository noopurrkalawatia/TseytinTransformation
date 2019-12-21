/*
 * tseytinUtil.cpp
 *
 *  Created on: Nov 29, 2019
 *      Author: noopurrkalawatia
 */

#include "tseytinUtil.h"

tseytinUtil::tseytinUtil()
{
    fileOperationOB = new fileOperationsUtil();
    noOfClausesInCNF = 0;
    noOfVariables = 0;
}

tseytinUtil::~tseytinUtil()
{
    free(fileOperationOB);
}

/*
 * Name         : resolveClauses
 * Parameters   : none
 * return       : void
 * Description  : The function is responsible for resolving the clauses for gates mentioned in the .bench file
 */
void tseytinUtil::resolveClauses()
{
    vector<string> CNFlines;
    string CNFclause;
    int noOfClauses = 0;
    string firstAppend;
    /*
     *
     Supported Gates for BENCH Format
     -------------------------------------------------------
     syntax                   gate type
     -------------------------------------------------------
     INPUT                    primary input
     OUTPUT                   primary output
     AND                      and gate
     NAND                     nand gate
     OR                       or gate
     NOR                      nor gate
     XOR                      2 input exclusive-or gate
     BUFF or BUF              buffer
     NOT                      inverter
      -------------------------------------------------------
     */
    for(auto inputLine : processedBenchLines)
    {

        string prefix = inputLine[0];
        if(INPUT != prefix && OUTPUT != prefix)
        {
            string gateToBeAnalysed = inputLine[1];
            transform(gateToBeAnalysed.begin(), gateToBeAnalysed.end(), gateToBeAnalysed.begin(), ::toupper);

            if("AND" == gateToBeAnalysed)
            {
                string a = to_string(lookupInputOutput[inputLine[2]]);
                string b = to_string(lookupInputOutput[inputLine[3]]);
                string c = to_string(lookupInputOutput[inputLine[0]]);


                CNFlines.push_back("-" + a + SPACE +  "-" + b + SPACE + c + SPACE + DELIMITER);
                CNFlines.push_back(a + SPACE +  "-" + c + SPACE + DELIMITER);
                CNFlines.push_back(b + SPACE +  "-" + c + SPACE + DELIMITER);

                noOfClauses += 3;

            }

            else if("NAND" == gateToBeAnalysed)
            {

                string a = to_string(lookupInputOutput[inputLine[2]]);
                string b = to_string(lookupInputOutput[inputLine[3]]);
                string c = to_string(lookupInputOutput[inputLine[0]]);

                CNFlines.push_back("-" + a + SPACE +  "-" + b + SPACE + "-" + c + SPACE + DELIMITER);
                CNFlines.push_back(a + SPACE + c + SPACE + DELIMITER);
                CNFlines.push_back(b + SPACE + c + SPACE + DELIMITER);

                noOfClauses += 3;
            }

            else if("OR" == gateToBeAnalysed)
            {
                string a = to_string(lookupInputOutput[inputLine[2]]);
                string b = to_string(lookupInputOutput[inputLine[3]]);
                string c = to_string(lookupInputOutput[inputLine[0]]);

                CNFlines.push_back(a + SPACE + b + SPACE + "-" + c + SPACE + DELIMITER);
                CNFlines.push_back("-" + a + SPACE + c + SPACE + DELIMITER);
                CNFlines.push_back("-" + b + SPACE + c + SPACE + DELIMITER);

                noOfClauses += 3;
            }

            else if("NOR" == gateToBeAnalysed)
            {
                string a = to_string(lookupInputOutput[inputLine[2]]);
                string b = to_string(lookupInputOutput[inputLine[3]]);
                string c = to_string(lookupInputOutput[inputLine[0]]);


                CNFlines.push_back(a + SPACE +  b + SPACE + c + SPACE + DELIMITER);
                CNFlines.push_back("-" + a + SPACE + "-" + c + SPACE + DELIMITER);
                CNFlines.push_back("-" + b + SPACE + "-" + c + SPACE + DELIMITER);

                noOfClauses += 3;
            }

            else if("XOR" == gateToBeAnalysed)
            {
                string a = to_string(lookupInputOutput[inputLine[2]]);
                string b = to_string(lookupInputOutput[inputLine[3]]);
                string c = to_string(lookupInputOutput[inputLine[0]]);



                CNFlines.push_back("-" + a + SPACE + "-" + b + SPACE + "-" + c + SPACE + DELIMITER);
                CNFlines.push_back(a + SPACE + b + SPACE + "-" + c + SPACE + DELIMITER);
                CNFlines.push_back(a + SPACE + "-" + b + SPACE + c + SPACE + DELIMITER);
                CNFlines.push_back("-" + a + SPACE + b + SPACE + c + SPACE + DELIMITER);

                noOfClauses += 4;
            }

            else if("BUFF" == gateToBeAnalysed || "BUF" == gateToBeAnalysed)
            {

                string a = to_string(lookupInputOutput[inputLine[2]]);
                string c = to_string(lookupInputOutput[inputLine[0]]);



                CNFlines.push_back("-" + a + SPACE + c + SPACE + DELIMITER);
                CNFlines.push_back(a + SPACE + "-" + c + SPACE + DELIMITER);

                noOfClauses += 2;
            }

            else if("NOT" == gateToBeAnalysed)
            {

                string a = to_string(lookupInputOutput[inputLine[2]]);
                string c = to_string(lookupInputOutput[inputLine[0]]);


                CNFlines.push_back("-" + a + SPACE + "-" + c + SPACE + DELIMITER);
                CNFlines.push_back(a + SPACE + c + SPACE + DELIMITER);

                noOfClauses += 2;
            }

            else if ("vdd" == gateToBeAnalysed)
            {
                string c = to_string(lookupInputOutput[inputLine[0]]);



                CNFlines.push_back(c + SPACE + DELIMITER);
                noOfClauses += 1;
            }

            else
            {
                cout << "Invalid type of gate" << endl;
                cout << "valid gates include : AND , OR, XOR, NOT" << endl;
                exit(0);
            }
        }
    }
    noOfClausesInCNF = noOfClauses;
    noOfClausesInCNF += outputIndices.size();

    resolveInputIndices(firstAppend);
    vector<string> outputClauses = resolveOutputClauses();
    fileOperationOB->writeToCNFFile(CNFlines,noOfVariables,noOfClausesInCNF,firstAppend,outputClauses);
}

/*
 * Name         : resolveOutputIndices
 * Parameters   : firstAppend - Forming the input sampling set to be fed in the model counter
 * return       : void
 * Description  : The function is responsible for resolving the sampling set for gates mentioned in the .bench file
 */
void tseytinUtil::resolveInputIndices(string &firstAppend)
{
    sort(inputIndices.begin(),inputIndices.end());

    for(auto num : inputIndices)
    {
        firstAppend += to_string(num) + " ";
    }

    firstAppend += DELIMITER;
}

vector<string> tseytinUtil::resolveOutputClauses()
{
    vector<string> outputClauses;
    string inter;
    sort(outputIndices.begin(),outputIndices.end());

    for(auto out : outputIndices)
    {
        outputClauses.push_back(to_string(out) + SPACE + DELIMITER);
    }

    return outputClauses;
}

/*
 * Name         : performTseytinTransformation
 * Parameters   : fileName - fileName for the .bench file as extracted from the command line argument.
 * return       : void
 * Description  : The function is the main driver function to convert the .bench file into .cnf format
 */
void tseytinUtil::performTseytinTransformation(string fileName)
{
    formLookUpTable(fileName);
    //resolveClauses();
}

/*
 * Name         : preProcessInputLines
 * Parameters   : &line - The input line where the preprocessing has to be performed
 * return       : vector<string> - transformed input line
 * Description  : The function implements the logic to accomplish the preprocessing of the input line.
 */
vector<string> tseytinUtil::preProcessInputLines(string &line)
{
    /*
     * Preprocessing includes
     * 1. Removing the brackets
     * 2. Removing the comma in the input line.
     * 3. Tokenising the input string
     */
    replace( line.begin(), line.end(), '(', ' ');
    replace( line.begin(), line.end(), ')', ' ');

    size_t found = line.find(",");
    if (found != string::npos)
    {
        line.replace(found,1,SPACE);
        //line.erase(line.begin() + found);
    }

    size_t found2 = line.find("=");
    if (found2 != string::npos)
    {
        line.replace(found2,1,SPACE);
        //line.erase(line.begin() + found);
    }

    stringstream check1(line);

    string intermediate;
    vector<string> tokens;
    while(getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    return tokens;
}

/*
 * Name : formLookUpTable
 * parameters : filename<string>
 * out : void
 * Description : resolves the bench file and forms the lookup table for constructing the
 *               transformation
 */
void tseytinUtil::formLookUpTable(string fileName)
{
    vector<string> benchLines = fileOperationOB->readContentsOfFile(fileName);

    vector<vector<string> > allLinesPreprocessed;

    int counter = 1;

    for(auto line : benchLines)
    {
        vector<string> result = preProcessInputLines(line);
        allLinesPreprocessed.push_back(result);
    }

    processedBenchLines = allLinesPreprocessed;

    for(vector<string> inter : allLinesPreprocessed)
    {
        string prefix = inter[0];

        if(INPUT == prefix)
        {
            if(lookupInputOutput.find(inter[1]) == lookupInputOutput.end())
            {
                lookupInputOutput[inter[1]] = counter;
                inputIndices.push_back(counter);
                ++counter;
            }
        }

        else if(OUTPUT == prefix)
        {
            if(lookupInputOutput.find(inter[1]) == lookupInputOutput.end())
            {
                lookupInputOutput[inter[1]] = counter;
                outputIndices.push_back(counter);
                ++counter;
            }
        }

        else
        {
            if(lookupInputOutput.find(prefix) == lookupInputOutput.end())
            {
                lookupInputOutput[prefix] = counter;
                ++counter;
            }
        }

    }

	cout << "*******************************************************" << endl;
	cout << "Filename : " << fileName << " " <<inputIndices.size() << endl;
	cout << "********************************************************" << endl;
    noOfVariables = counter - 1;
}
