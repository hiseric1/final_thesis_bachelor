#include <iostream>
#include "../include/Expression.h"
#include "hello.h"
#include "../include/CoreEvaluator.h"
#include "../include/Net.h"
#include "../include/Cml.h"


void hello() {
    
    CoreEvaluator coreEvaluator;
    //coreEvaluator.CreateGraph(); //zakomentarisano
    //coreEvaluator.RenderUniverse(); //zakomentarisano

	std::string stringExpression = "$(x&y&z)&x|y>$#(z=(x>y&##(z|y)))";//#(x|y)";//"$(x&y&z&k)>$#(z=(x>(k|y)&##(k|z|y)))"
    ResultTree resultTree = coreEvaluator.returnResultTree(stringExpression);
    //coreEvaluator.RenderUniverse("result.png"); //zakomentarisano
    //resultTree.Visualise("w3"); //zakomentarisano

	Cml cml (coreEvaluator.getUniverse(),stringExpression,resultTree);
}

std::string get_message() {
    // There's a mistake here
    // Try running `make check` and observe the failing testCoverage case
    // Then correct the line below and repeat
    return "Hellx, World!";
}

std::string get_message1() {
    // There's a mistake here
    // Try running `make check` and observe the failing testCoverage case
    // Then correct the line below and repeat
    return "Hello, World!";
}

