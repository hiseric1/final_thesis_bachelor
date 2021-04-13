#ifndef LOGICTOOLBOX_CML
#define LOGICTOOLBOX_CML

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert> //Zbog asserta
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <fstream>

#include "Net.h"
#include "ResultTree.h"
#include "Expression.h"  //U njoj su uključene i nama potrebene klase Universe i Expression

using namespace std;

class Cml
{
    Universe universe;
    Expression expression;
    ResultTree resultTree;

    unsigned inputNum;
    unsigned hiddemNum;

    vector<vector<double>> inputVals;
	vector<double> outputVals;


    unsigned trainingExamples;


public:
    Cml (Universe uni, string stringExpression, ResultTree resultTree);
    
    void setNumTrainingExamples(unsigned trExmp) {trainingExamples = trExmp;}
    void train(vector<vector<double>> ulazi,vector<double> izlazi);
    void writeResults(vector<double> results,std::string name);
    vector<double> getResults() {return outputVals;};
};


#endif  //LOGICTOOLBOX_CML