#ifndef LOGICTOOLBOX_NET
#define LOGICTOOLBOX_NET

#include <vector>
#include <iostream>
#include <cstdlib>
#include <cassert> //Zbog asserta
#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>

#include "Neuron.h"

using namespace std;

class Net
{
	vector<Layer> allLayers; // allLayers[layerNum][neuronNum]
	double m_error;
	double m_recentAverageError;
	static double m_recentAverageSmoothingFactor;
public:
	Net(const vector<unsigned> &topology);
	void feedForward(const vector<double> &inputVals); //referenca da se ne bi kopirao čitav vektor
	void backPropagation(const vector<double> &targetVals);
	void getResults(vector<double> &resultVals) const;
	double getRecentAverageError(void) const { return m_recentAverageError; }
};


#endif  //LOGICTOOLBOX_NET