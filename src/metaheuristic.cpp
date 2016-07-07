#include "metaheuristic.h"

void updateFitness(vector<Ion> &population){
    for (unsigned int i=0; i < population.size(); i++)
        population[i].updateFitness();
}


bool ionOrder(Ion i, Ion j){
    return i.getFitness() < j.getFitness();
}


void updateLocations(vector<Ion> &ions, Ion ref){
    double force;

    for(unsigned int i = 0; i < ions.size(); i++){
        for(unsigned int j = 0; j < ions[i].size(); j++){
            force = (1.0/(1 + exp(-0.1/abs(ions[i][j] - ref[j]))));
            ions[i][j] = ions[i][j] + force*(ref[j] - ions[i][j]);
        }
    }
}



void normalize(vector<Ion> &ions, double lbound, double ubound){
    for (unsigned int i=0; i < ions.size(); i++){
        for(unsigned int j=0; j < ions[i].size(); j++){
            if(ions[i][j] < lbound)
                ions[i][j] = lbound;
            else if(ions[i][j] > ubound)
                ions[i][j] = ubound;
        }
    }
}



void initialize(vector<Ion> &ions, int lbound, int ubound){
    vector<double> position(dimension);

    for (unsigned int i=0; i < ions.size(); i++){
        for (unsigned int j=0; j < dimension; j++)
            position[j] = lbound + (ubound-lbound)*runif(generator);

        ions[i] = Ion(position);
    }
}



void redistribute(vector<Ion> &ions, Ion ref,
                  double lbound, double ubound){

    double phi;

    for (unsigned int i = 0; i < ions.size(); i++){
        // -1 < phi < 1
        phi = -1 + 2*runif(generator);

        if (runif(generator) > 0.5)
            for (unsigned int j = 0; j < ions[i].size(); j++)
                ions[i][j] = ions[i][j] + phi * (ref[j]-1);
        else
            for (unsigned int j = 0; j < ions[i].size(); j++)
                ions[i][j] = ions[i][j] + phi * ref[j];

        if(runif(generator) < prob_restart)
            for (unsigned int j = 0; j < ions[i].size(); j++)
                ions[i][j] = lbound + (ubound-lbound)*runif(generator);
    }
}



vector<double> ion_algorithm(){
    vector<Ion> cations(population_size/2);
    vector<Ion> anions(population_size/2);
    vector<double> position(dimension);
    vector<double> best_solution(dimension);
    double best_fvalue=numeric_limits<double>::infinity();
    int lbound = -100, ubound = 100, eval = 0, liquid_phase = false;


    // Inicialización
    initialize(cations, lbound, ubound);
    cout << cations[0].size();
    cout << anions[0].size();
    initialize(anions, lbound, ubound);
    updateFitness(cations);
    updateFitness(anions);
    auto best_cation = min_element(cations.begin(), cations.end(), ionOrder);
    auto best_anion = min_element(anions.begin(), anions.end(), ionOrder);
    auto worst_cation = max_element(cations.begin(), cations.end(), ionOrder);
    auto worst_anion = max_element(anions.begin(), anions.end(), ionOrder);


    while (eval < max_eval){
        // Fase líquida
        if (liquid_phase){
            updateLocations(anions, (*best_cation));
            updateLocations(cations, (*best_anion));

            if ((*best_cation).getFitness() >= (*worst_cation).getFitness()/2 &&
                (*best_anion).getFitness() >= (*worst_anion).getFitness()/2){
                // Salimos de la fase liquida, entramos en la sólida
                liquid_phase = false;
            }
            eval++;
        }
        // Fase sólida
        else{
            redistribute(cations, (*best_anion), lbound, ubound);
            redistribute(anions, (*best_cation), lbound, ubound);
            normalize(cations, lbound, ubound);
            normalize(anions, lbound, ubound);
            // Entramos en la siguiente iteración en fase líquida
            liquid_phase = true;
        }

        // Actualización de los mejores valores
        updateFitness(cations);
        updateFitness(anions);


        auto best_cation = min_element(cations.begin(), cations.end(), ionOrder);
        auto best_anion = min_element(anions.begin(), anions.end(), ionOrder);
        auto worst_cation = max_element(cations.begin(), cations.end(), ionOrder);
        auto worst_anion = max_element(anions.begin(), anions.end(), ionOrder);


        if ((*best_cation).getFitness() < best_fvalue){
            best_fvalue = (*best_cation).getFitness();
            best_solution = (vector<double>) (*best_cation);
            cout << best_fvalue << endl;
        }
        if ((*best_anion).getFitness() < best_fvalue){
            best_fvalue = (*best_anion).getFitness();
            best_solution = (vector<double>) (*best_anion);
            cout << best_fvalue << endl;
        }
    }

    return best_solution;
}
