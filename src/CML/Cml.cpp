#include "../../include/Cml.h"

void showVectorVals(string label, vector<double> &v)
{
	cout << label << " ";
	for (unsigned i = 0; i < v.size(); ++i) {
		cout << v[i] << " ";
	}

	cout << endl;
}

//Treba nam Expression, ResultTree i Universe
Cml::Cml(Universe uni, string stringExpression, ResultTree resultTree_) {
    
    
    universe = uni;
    resultTree = resultTree_;
    
    
	Expression exp (stringExpression);
    expression = exp;

	vector<Token> vektorTokena = expression.getTokens();

    //Dobavljanje broja neurona koji svako od slojeva treba da posjeduje
	int numbrerOfOperators(0);  //Broj neurona u skrivenom layeru

	for(int i=0;i<vektorTokena.size();i++) {
		if(vektorTokena[i].type == TokenType::UNARY_OP ||  vektorTokena[i].type == TokenType::BINARY_OP)
			numbrerOfOperators++;
	}

	
	int numberOfVariables = universe.getVariableNames().size(); // Broj ulaznih neurona

    auto rootResult = resultTree.getFinalResult();


	std::vector<std::vector<int>> moguciUlazi;

	std::vector<int> moguciIzlazi;

//Dobavljanje svih mogućih kombinacija u univerzumu za potrebe testiranja mreže
    for(auto i = rootResult.begin(); i != rootResult.end(); i++){
        char* color = (i->second? const_cast<char*>("green"): const_cast<char*>("red"));
        //moje dodano za potrebe testiranja
		std::vector<int> pojedinacniUlazi;
        auto niz_pomocni_varijable = (*(i->first)).getVariables();
        for(int l =0;l< (*(i->first)).getVariables().size();l++)
			pojedinacniUlazi.push_back((int)niz_pomocni_varijable[l].getValue());
        moguciUlazi.push_back(pojedinacniUlazi);
		moguciIzlazi.push_back((int)i->second);
        //kraj
    }


//Kreiranje ulaza i željenih izlaza iz mreže
    vector<vector<double>> ulazi;
	vector<double> izlazi;
	int controller = moguciUlazi.size();

	for (int i = 0; i < 500 * controller; i++) {
        for(int j=0;j<moguciUlazi.size();j++) {
            std::vector<double> za_ubaciti(moguciUlazi[j].begin(),moguciUlazi[j].end());
            ulazi.push_back(za_ubaciti);
            izlazi.push_back((double)moguciIzlazi[j]);
        }
	}
	inputNum = (unsigned)numberOfVariables;
    hiddemNum = (unsigned)numbrerOfOperators;

	train(ulazi,izlazi);


}

void Cml::train(vector<vector<double>> ulazi,vector<double> izlazi) {
	//2,1 ;; hiddenNum
	std::vector<unsigned> topology = { inputNum,(unsigned)std::pow(2,inputNum),1 };

	Net myNet(topology);

	std::vector<double> inputVals;
	std::vector<double> targetVals, resultVals, allResultVals, allRecentAverageErrors;

	for (int i = 0; i < ulazi.size(); i++) {

		std::cout << endl << "Pass " << i + 1;

		//Prosljeđivanje ulaznih vrijenosti mreži 
		 
		inputVals = ulazi[i];
		if (inputVals.size() != topology[0]) {
			std::cout << "Doslo je do greske";
			break;
		}
		showVectorVals(": Inputs:", inputVals);
		myNet.feedForward(inputVals);

		// Pokupi rezultate mreže
		myNet.getResults(resultVals);
		showVectorVals("Outputs:", resultVals);

		//Spašavanje svih rezultata mreže zarad plotanja
		if(resultVals.size()==1)
			allResultVals.push_back(resultVals[0]);

		// Teniranje 
		std::cout <<  "Targets: " << izlazi[i] << std::endl;

		std::vector <double> k;
		k.push_back(izlazi[i]);
		myNet.backPropagation(k);
		k.clear();
		// Pokupi relativnu grešku i prikaži

		allRecentAverageErrors.push_back(myNet.getRecentAverageError());
		std::cout << "Net recent average error: "
			<< myNet.getRecentAverageError() << endl;
	}

	//Upisivanje u datoteke željene vrijednosti
	writeResults(allResultVals, "DobiveneVrijednosti");
	writeResults(izlazi, "OcekivaneVrijednosti");
	writeResults(allRecentAverageErrors, "RecentError");


}

void Cml::writeResults(vector<double> results, std::string name) {
	try {
	ofstream myfile;
	myfile.open (name + ".txt");
	for(int i(0);i<results.size();i++) {
 		myfile << results[i];
		myfile <<  "\n";
	}
  	myfile.close();
	} catch(...) {
		std::cout << "Došlo je do greške prilikom otvaranja datoteke";
	}
}