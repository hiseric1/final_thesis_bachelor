//
// Created by infloop on 9/10/17.

#include "../../include/Graph.h"
#include <iostream>

Graph::Graph(Universe* universe) {

    if(graphContext == nullptr) graphContext = gvContext();

    agraph = agopen("Graph", Agdirected, 0);
    agattr(agraph, AGNODE, "label", "LABEL");

    for(auto i : universe->getWorlds()){
        char* name = (char *) i->getName().c_str();
        nodes[i] = agnode(agraph,name,1);
        string label = i->getName() + "\n";
        for(auto j : i->getVariables()){
            label += j.getName() + " : " + (j.getValue()?"TRUE":"FALSE") + "\n";
        }
        agset(nodes[i], "label", const_cast<char*>(label.c_str()));
    }

    for(auto i: universe->getWorlds()){
        for(auto j: i->getAdjacentList())
            edges.push_back(agedge(agraph,nodes[i],nodes[j],"",1));
    }



    FILE * result = fopen("graph.dot","w+");

    gvLayout(graphContext, agraph, "dot");
    gvRender(gvContext(), agraph, "dot", result);

    fclose(result);

    created = true;
}

Graph::~Graph() {
}

bool Graph::saveImage(string FILE_PATH)
{
    gvFreeLayout(graphContext,agraph);
    string DOT_TEXT_FILE = "graph.dot";
    string o_arg;

    if(FILE_PATH=="") o_arg = "-o img_file.png";
    else o_arg = "-o"+FILE_PATH;
    char* args[] = {const_cast<char*>("dot"), const_cast<char*>("-Tpng"),
                    const_cast<char*>(DOT_TEXT_FILE.c_str()),
                    const_cast<char*>(o_arg.c_str()) };

    const int argc = sizeof(args)/sizeof(args[0]);

    cout << endl << o_arg<<"______________________________________________";

    Agraph_t * g, *prev = NULL;

    gvParseArgs(graphContext, argc, args);

    gvLayoutJobs(graphContext, agraph);
    gvRenderJobs(graphContext, agraph);

}

void Graph::AddResults(ResultTree resultTree) {

    if(agraph == nullptr) throw logic_error("Agraph_t doesn't exist!");

    agattr(agraph,AGNODE,"color","black");

    auto rootResult = resultTree.getFinalResult();

    for(auto i = rootResult.begin(); i != rootResult.end(); i++){
        char* color = (i->second? const_cast<char*>("green"): const_cast<char*>("red"));

        //moje dodano za potrebe testiranja
/*
        std::cout << "Ime: "<< std::endl <<(*(i->first)).getName()<<std::endl ;
        auto niz_pomocni_varijable = (*(i->first)).getVariables();
        for(int l =0;l< (*(i->first)).getVariables().size();l++)
            std::cout << "Ime varijabli i njihove vrijednosti: "  << niz_pomocni_varijable[l].getName() << "    " << niz_pomocni_varijable[l].getValue() << std::endl;
        //<< i->second;
        

        //kraj
*/


        agset(nodes[i->first],"color",color);
    }

    FILE * result = fopen("graph.dot","w+");

    gvLayout(graphContext, agraph, "dot");
    gvRender(gvContext(), agraph, "dot", result);
    fclose(result);

}

