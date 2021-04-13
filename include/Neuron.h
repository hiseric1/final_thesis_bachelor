#ifndef LOGICTOOLBOX_NEURON
#define LOGICTOOLBOX_NEURON

#include <vector>
#include <iostream>
#include <cstdlib>  //uključeno zbog rand()
#include <cassert>
#include <cmath> //za tanh()
#include <fstream>
#include <sstream>

using namespace std;

class Neuron;

typedef vector<Neuron> Layer;

struct Connection
{
	double weight;
	double deltaWeight;
};

class Neuron
{

	static double eta;   // [0.0..1.0] brzina učenja / learning rate
	static double alpha; // [0.0..n] momentum - da bi se lakše izbjegao lokalni minimum
	static double transferFunction(double x);
	static double transferFunctionDerivative(double x);
	static double setWeight(void) { return rand() / double(RAND_MAX); }  //ili 0.5
	double sumDOW(const Layer &nextLayer) const;
	double m_outputVal;
	vector<Connection> m_outputWeights;
	unsigned m_myIndex;
	double m_gradient;
	bool activation;


public:
	Neuron(unsigned numOutputs, unsigned myIndex);
	void setOutputVal(double val) { m_outputVal = val; }
	double getOutputVal(void) const { return m_outputVal; }
	void feedForward(const Layer &prevLayer);
	void calcOutputGradients(double targetVal);
	void calcHiddenGradients(const Layer &nextLayer);
	void updateInputWeights(Layer &prevLayer);


};

#endif //LOGICTOOLBOX_NEURON