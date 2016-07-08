#include "metaheuristic.h"

void updateFitness(vector<Ion> &population, int &eval){
    for (unsigned int i=0; i < population.size(); i++){
        population[i].updateFitness();
        eval++;
    }
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
    cout << "Normalizando" << endl;
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



void redistribute(vector<Ion> &ions, Ion ref, Ion ref_old,
                  double lbound, double ubound){

    double phi;

    for (unsigned int i = 0; i < ions.size(); i++){
        // -1 < phi < 1
        phi = -1 + 2*runif(generator);

        if (runif(generator) > 0.5)
            for (unsigned int j = 0; j < ions[i].size(); j++){
                //cout << "Antes " << ions[i][j] << endl;
                ions[i][j] = ions[i][j] + phi * ref_old[j];
                //cout << "Después: " << ions[i][j] << endl;
            }
        else
            for (unsigned int j = 0; j < ions[i].size(); j++){
                ions[i][j] = ions[i][j] + phi * ref[j];
            }
        if(runif(generator) < prob_restart)
            for (unsigned int j = 0; j < ions[i].size(); j++)
                ions[i][j] = lbound + (ubound-lbound)*runif(generator);
    }
}

void updateBestSolution(double &best_fvalue, vector<double> &best_solution, Ion ref){
    if (ref.getFitness() < best_fvalue){
        best_fvalue = ref.getFitness();
        best_solution = (vector<double>) ref;
        cout << best_fvalue << endl;
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
    initialize(anions, lbound, ubound);
    updateFitness(cations, eval);
    updateFitness(anions, eval);
    auto best_cation = *min_element(cations.begin(), cations.end(), ionOrder);
    auto best_anion = *min_element(anions.begin(), anions.end(), ionOrder);
    auto worst_cation = *max_element(cations.begin(), cations.end(), ionOrder);
    auto worst_anion = *max_element(anions.begin(), anions.end(), ionOrder);
    auto best_cation_old = best_cation;
    auto best_anion_old = best_anion;


    while (eval < max_eval){
        // Fase líquida
        if (liquid_phase){
            updateLocations(anions, best_cation);
            updateLocations(cations, best_anion);

            if (best_cation.getFitness() >= worst_cation.getFitness()/2 &&
                best_anion.getFitness() >= worst_anion.getFitness()/2){
                // Salimos de la fase liquida, entramos en la sólida
                //cout << "Tras " << eval << " evaluaciones " << " salimos de fase líquida" << endl;
                //cout << "best_cation: " << best_cation.getFitness() << endl;
                //cout << "worst_cation: " <<worst_cation.getFitness() << endl;
                //cout << "best_anion: " <<best_anion.getFitness() << endl;
                //cout << "worst_anion: " <<worst_anion.getFitness() << endl;
                cout << "Esto sirve de algo" << endl;
                liquid_phase = false;
            }
            eval++;
        }
        // Fase sólida
        else{
            redistribute(cations, best_anion, best_anion_old, lbound, ubound);
            redistribute(anions, best_cation, best_cation_old, lbound, ubound);
            //normalize(cations, lbound, ubound);
            //normalize(anions, lbound, ubound);
            // Entramos en la siguiente iteración en fase líquida
            liquid_phase = true;
        }

        // Actualización de los mejores valores
        updateFitness(cations, eval);
        updateFitness(anions, eval);

        //cout << "worst_cation: " <<worst_cation.getFitness() << endl;
        //cout << "best_anion: " <<best_anion.getFitness() << endl;
        //cout << "worst_anion: " <<worst_anion.getFitness() << endl;
        best_cation_old = best_cation;
        best_anion_old = best_anion;
        best_cation = *min_element(cations.begin(), cations.end(), ionOrder);
        best_anion = *min_element(anions.begin(), anions.end(), ionOrder);
        worst_cation = *max_element(cations.begin(), cations.end(), ionOrder);
        worst_anion = *max_element(anions.begin(), anions.end(), ionOrder);
        cout << "best_cation: " << best_cation.getFitness() << endl;
        for (int i=0; i<best_cation.size(); i++){
            cout << best_cation[i] << " ";
        }
        cout << endl;
        cout << "old best_cation: " << best_cation.getFitness() << endl;
        for (int i=0; i<best_cation.size(); i++){
            cout << best_cation_old[i] << " ";
        }
        cout << endl;
        updateBestSolution(best_fvalue, best_solution, best_cation);
        updateBestSolution(best_fvalue, best_solution, best_anion);
    }

    return best_solution;
}
