
#include "../../include/Net.h"

using namespace std;

double Net::m_recentAverageSmoothingFactor = 100.0; //Broj uzoraka testiranja iz kojih se izvodi prosjek


Net::Net(const vector<unsigned> &topology)
{
	m_recentAverageError = 1;

	int numLayers = topology.size();
	for (int layerNum = 0; layerNum < numLayers; ++layerNum) {
		allLayers.push_back(Layer());

		//broj neurona u idućem sloju
		unsigned numOutputs = layerNum == topology.size() - 1 ? 0 :topology[layerNum + 1];

		//Dodavanje Neurona u svaki layer; Ide <= zbog bias neurona
		for (int neuronNum = 0; neuronNum <= topology[layerNum]; ++neuronNum) {

			//Izbjegavanje ubacivanja biasa u izlazni sloj
			//if(layerNum == topology.back() && neuronNum == topology[layerNum]) 
			//	break;
			
			allLayers.back().push_back(Neuron(numOutputs, neuronNum)); 
			
		}

		//if(layerNum != topology.back())
			//Postavimo bias na 1; On je zadnji neuron
		allLayers.back().back().setOutputVal(1.0);
	}
}


void Net::feedForward(const vector<double> &inputVals)
{
	if(inputVals.size() != allLayers[0].size() - 1) throw domain_error("Neodgovarajuća dužina ulaznog niza.");
	//assert(inputVals.size() == allLayers[0].size() - 1); //treba pr
 
	//Dodjeljivanje vrijednosti ulaza ulaznim neuronima
	for (int input = 0; input < inputVals.size(); input++) {

		allLayers[0][input].setOutputVal(inputVals[input]);

	}

	// forward propagacija 
	for (int layerNum = 1; layerNum < allLayers.size(); layerNum++) {

		Layer &prevLayer = allLayers[layerNum - 1];

		for (int neuron = 0; neuron < allLayers[layerNum].size() - 1; neuron++) {

			allLayers[layerNum][neuron].feedForward(prevLayer);

		}
	}
}


void Net::getResults(vector<double> &resultVals) const
{
	resultVals.clear();

	for (unsigned n = 0; n < allLayers.back().size() - 1; n++) {
		resultVals.push_back(allLayers.back()[n].getOutputVal());
	}
}

void Net::backPropagation(const vector<double> &targetVals)
{
	// Računamo cjelokuonu grešku mreže

	Layer &outputLayer = allLayers.back();
	m_error = 0.0;

	for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
		double delta = targetVals[n] - outputLayer[n].getOutputVal();
		m_error += delta * delta; // Kvadriranje greske
	}
	//m_error /= outputLayer.size() - 1; // Prosjek sume
	//m_error = sqrt(m_error); // RMS

	 // Nedavni prosjek mjerenja
	m_recentAverageError =
		(m_recentAverageError * m_recentAverageSmoothingFactor + m_error)
		/ (m_recentAverageSmoothingFactor + 1.0);

	// Računanje gradijenta izlaznog sloja

	for (unsigned n = 0; n < outputLayer.size() - 1; ++n) {
		outputLayer[n].calcOutputGradients(targetVals[n]);
	}

	//Računanje gradijenta skrivenih slojeva


	for (unsigned layerNum = allLayers.size() - 2; layerNum > 0; layerNum--) {
		Layer &hiddenLayer = allLayers[layerNum];
		Layer &nextLayer = allLayers[layerNum + 1];

		for (unsigned n = 0; n < hiddenLayer.size(); ++n) {
			hiddenLayer[n].calcHiddenGradients(nextLayer);
		}
	}

	//Za sve slojeve, od izlaznog do prvog skrivenog; ažuriranje težina

	for (unsigned layerNum = allLayers.size() - 1; layerNum > 0; layerNum--) {
		Layer &layer = allLayers[layerNum];
		Layer &prevLayer = allLayers[layerNum - 1];

		for (unsigned n = 0; n < layer.size() - 1; ++n) {
			layer[n].updateInputWeights(prevLayer);
		}
	}
}



