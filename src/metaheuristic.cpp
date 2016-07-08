#include "metaheuristic.h"

void updateFitness(vector<Solution> &population, int &eval){
    for (unsigned int i=0; i < population.size(); i++){
        population[i].updateFitness();
        eval++;
    }
}


bool ionOrder(Solution i, Solution j){
    return i.getFitness() < j.getFitness();
}


void updateLocations(vector<Solution> &ions, Solution ref){
    double force;

    for(unsigned int i = 0; i < ions.size(); i++){
        for(unsigned int j = 0; j < ions[i].size(); j++){
            force = (1.0/(1 + exp(-0.1/abs(ions[i][j] - ref[j]))));
            ions[i][j] = ions[i][j] + force*(ref[j] - ions[i][j]);
        }
    }
}

void normalize(Solution &ion){
    for(unsigned int j=0; j < ion.size(); j++){
        if(ion[j] < lbound)
            ion[j] = lbound;
        else if(ion[j] > ubound)
            ion[j] = ubound;
    }
}

void normalize(vector<Solution> &ions){

    for (unsigned int i=0; i < ions.size(); i++){
        normalize(ions[i]);
    }
}



void initialize(vector<Solution> &ions){
    vector<double> position(dimension);

    for (unsigned int i=0; i < ions.size(); i++){
        for (unsigned int j=0; j < dimension; j++)
            position[j] = lbound + (ubound-lbound)*runif(generator);

        ions[i] = Solution(position);
    }
}



void redistribute(vector<Solution> &ions, Solution ref, Solution ref_old){

    double phi;

    for (unsigned int i = 0; i < ions.size(); i++){
        // -1 < phi < 1
        phi = -1 + 2*runif(generator);

        if (runif(generator) > 0.5)
            for (unsigned int j = 0; j < ions[i].size(); j++){
                ions[i][j] = ions[i][j] + phi * ref_old[j];
                if(runif(generator) < prob_mutation)
                    ions[i][j] = lbound + (ubound-lbound)*runif(generator);
            }
        else
            for (unsigned int j = 0; j < ions[i].size(); j++){
                ions[i][j] = ions[i][j] + phi * ref[j];
                if(runif(generator) < prob_mutation)
                    ions[i][j] = lbound + (ubound-lbound)*runif(generator);
            }
        if(runif(generator) < prob_restart)
            for (unsigned int j = 0; j < ions[i].size(); j++)
                ions[i][j] = lbound + (ubound-lbound)*runif(generator);
    }
}

void updateBestSolution(Solution &best_solution, Solution ref){
    if (ref.getFitness() < best_solution.getFitness()){
        best_solution = Solution(ref);
    }
}


vector<double> ion_algorithm(){
    vector<Solution> cations(population_size/2);
    vector<Solution> anions(population_size/2);
    Solution best_solution(vector<double> dimension, numeric_limits<double>::infinity());
    int eval = 0;
    bool liquid_phase = false;

    // Inicialización
    initialize(cations);
    initialize(anions);
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
                liquid_phase = false;
            }
            eval++;
        }
        // Fase sólida
        else{
            redistribute(cations, best_anion, best_anion_old);
            redistribute(anions, best_cation, best_cation_old);
            normalize(cations);
            normalize(anions);
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

        updateBestSolution(best_solution, best_cation);
        updateBestSolution(best_solution, best_anion);

        applyLocalSearch(best_solution, eval);
    }

    return ((vector<double>) best_solution);
}



double computeNorm(vector<double> v){
    double suma=0;

    for(int i=0; i<v.size(); i++){
        suma += v[i]*v[i];
    }

    return sqrt(suma);
}



void applyLocalSearch(Solution &solution, int &eval){
    int i=0;
    int tope=solution.size();
    double epsilon = local_epsilon;
    double norma;
    vector<double> direccion(solution.size());
    Solution current(solution);


    while(i < tope){
        for (int j=0; j<direccion.size(); j++){
            direccion[j] = -1 + 2*runif(generator);
        }

        norma = computeNorm(direccion);

        for (int j=0; j<direccion.size(); j++){
            current[j] += epsilon*(direccion[j] / norma);
        }

        normalize(current);

        current.updateFitness();

        if (current.getFitness() < solution.getFitness()){
            solution = Solution(current);
            epsilon/=2;
        }
        else{
            current = Solution(solution);
            epsilon = min(epsilon*2, 1.0);
        }
        eval++;
    }
}
