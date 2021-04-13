#include "../../include/Neuron.h"

double Neuron::eta = 0.15;    //0.15
double Neuron::alpha = 0.5;   //0.5


Neuron::Neuron(unsigned numOutputs, unsigned myIndex)
{
	for (int connection = 0; connection < numOutputs; connection++) {
		m_outputWeights.push_back(Connection());
		//postavljanje težina grana
		m_outputWeights.back().weight = setWeight();
	}

	m_myIndex = myIndex;
}

void Neuron::feedForward(const Layer &prevLayer)
{
	double sum = 0.0;

	// Suma izlaza nurona iz proslog sloja a koji ulaze u trenutni neuron; uključivo sa bias-om

	for (unsigned n = 0; n < prevLayer.size(); ++n) {
		sum += prevLayer[n].getOutputVal() * prevLayer[n].m_outputWeights[m_myIndex].weight;
	}

	m_outputVal = Neuron::transferFunction(sum); //ili aktivacijska funkcija
}


void Neuron::updateInputWeights(Layer &prevLayer)
{
	// Ažuriraju se veze sa prethodnim slojem

	for (unsigned n = 0; n < prevLayer.size(); n++) {
		Neuron &neuron = prevLayer[n];
		double oldDeltaWeight = neuron.m_outputWeights[m_myIndex].deltaWeight;

		double newDeltaWeight =
			// Input pomnožen sa gradijentom i stepenom brzine učenja
			eta
			* neuron.getOutputVal()
			* m_gradient
			+ alpha  //momentum - da bi se lakše izbjegao lokalni minimum; 
			* oldDeltaWeight;

		neuron.m_outputWeights[m_myIndex].deltaWeight = newDeltaWeight;
		neuron.m_outputWeights[m_myIndex].weight += newDeltaWeight;
	}
}

double Neuron::sumDOW(const Layer &nextLayer) const //sum of the derivaives
{
	double sum = 0.0;

	for (unsigned n = 0; n < nextLayer.size() - 1; n++) {
		sum += m_outputWeights[n].weight * nextLayer[n].m_gradient;
	}

	return sum;
}

void Neuron::calcHiddenGradients(const Layer &nextLayer)
{
	double dow = sumDOW(nextLayer);
	m_gradient = dow * Neuron::transferFunctionDerivative(m_outputVal);
} 

void Neuron::calcOutputGradients(double targetVal)
{
	double delta = targetVal - m_outputVal;
	m_gradient = delta * Neuron::transferFunctionDerivative(m_outputVal);
}

double Neuron::transferFunction(double x)
{
	// Ja sam izabrao reLU:
	return x<0 ? 0 : x; //Pokazani bolji rezultati od tanh(x),...

	//2. izbor: tanh(x);
}

double Neuron::transferFunctionDerivative(double x)
{
	// reLU derivative:
	return x<0 ? 0 : 1;

	//2. izbor  1 - tanh(x)   ili 1-x*x
}



