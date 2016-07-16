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
            position[j] = myrandom.randreal(lbound, ubound);

        ions[i] = Solution(position);
    }
}



void redistribute(vector<Solution> &ions, Solution ref, Solution ref_old){

    double phi;

    for (unsigned int i = 0; i < ions.size(); i++){
        // -1 < phi < 1
        phi = myrandom.randreal(-1,1);

        if (myrandom.randreal(0,1) > 0.5)
            for (unsigned int j = 0; j < ions[i].size(); j++){
                ions[i][j] = ions[i][j] + phi * ref_old[j];
                if(myrandom.randreal(0,1) < prob_mutation)
                    ions[i][j] = myrandom.randreal(lbound, ubound);
            }
        else
            for (unsigned int j = 0; j < ions[i].size(); j++){
                ions[i][j] = ions[i][j] + phi * ref[j];
                if(myrandom.randreal(0,1) < prob_mutation)
                    ions[i][j] = myrandom.randreal(lbound, ubound);
            }
        if(myrandom.randreal(0,1) < prob_restart){
            for (unsigned int j = 0; j < ions[i].size(); j++)
                ions[i][j] = myrandom.randreal(lbound, ubound);
        }
    }

    normalize(ions);
}

bool updateBestSolution(Solution &best_solution, Solution ref){
    bool best_updated = false;

    if (ref.getFitness() < best_solution.getFitness()){
        best_updated = true;
        best_solution = Solution(ref);
    }

    return best_updated;
}


vector<double> ionAlgorithm(){
    vector<Solution> cations(population_size/2);
    vector<Solution> anions(population_size/2);
    Solution best_solution(vector<double>(dimension), numeric_limits<double>::infinity());
    int eval = 0;
    bool liquid_phase = true;


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
            // Actualización de los mejores valores
            updateFitness(cations, eval);
            updateFitness(anions, eval);

            best_cation_old = best_cation;
            best_anion_old = best_anion;
            best_cation = *min_element(cations.begin(), cations.end(), ionOrder);
            best_anion = *min_element(anions.begin(), anions.end(), ionOrder);
            worst_cation = *max_element(cations.begin(), cations.end(), ionOrder);
            worst_anion = *max_element(anions.begin(), anions.end(), ionOrder);


            if (best_cation.getFitness() >= worst_cation.getFitness() &&
                best_anion.getFitness() >= worst_anion.getFitness()){

                // Salimos de la fase liquida, entramos en la sólida
                liquid_phase = false;
            }

            updateBestSolution(best_solution, best_cation);
            updateBestSolution(best_solution, best_anion);
        }
        // Fase sólida
        else{
            redistribute(cations, best_anion, best_anion_old);
            redistribute(anions, best_cation, best_cation_old);

            applyRealeaLS(best_solution, eval, dimension*1000);
            //applyLocalSearch(best_solution, eval, dimension*10);
            // Entramos en la siguiente iteración en fase líquida
            liquid_phase = true;
        }
    }

    return ((vector<double>) best_solution);
}



void updateLocations(vector<Solution> &anions, vector<Solution> cations){
    vector<vector <double>> v_anions(anions.size(), vector<double>(dimension,0));
    double factor, force;


    for(unsigned int i = 0; i < anions.size(); i++){

        for(unsigned int j = 0; j < anions.size(); j++){
            factor = (1.0/(1 + exp( anions[i].getFitness() -
                    anions[j].getFitness()) ))/2;

            if (j!=i){
                for(unsigned int k = 0; k < dimension; k++){
                    force = myrandom.randreal(0,1)*factor;//
                    // Repulsión
                    v_anions[i][k] += force*(anions[i][k] - anions[j][k]);
                }
            }
        }

        for(unsigned int j = 0; j < cations.size(); j++){
            factor = (1.0/(1 + exp( cations[j].getFitness() -
                    anions[i].getFitness()) ))/2;

            for(unsigned int k = 0; k < dimension; k++){
                force = myrandom.randreal(0,1)*factor;//
                // Atracción
                v_anions[i][k] += force*(cations[j][k] - anions[i][k]);
            }
        }
    }

    for(unsigned int i = 0; i < anions.size(); i++)
        for(unsigned int k = 0; k < dimension; k++)
            anions[i][k] += v_anions[i][k];

    normalize(anions);

}


void redistribute(vector<Solution> &ions, vector<Solution> &bests){
    bool bests_left = true;

    for (unsigned int i = 0; i < ions.size(); i++){
        if(bests.size()>0){
            ions[i] = Solution(bests.back());

            for (unsigned int j = 0; j < ions[i].size(); j++)
                if(myrandom.randreal(0,1) < prob_mutation)
                    ions[i][j] = myrandom.randreal(lbound, ubound);

            bests.pop_back();
        }
        else
            bests_left = false;

        if(myrandom.randreal(0,1) < prob_restart || !bests_left){
            for (unsigned int j = 0; j < ions[i].size(); j++)
                ions[i][j] = myrandom.randreal(lbound, ubound);
        }
    }

    normalize(ions);
}


vector<double> ionAlgorithm_v2(){
    vector<Solution> cations(population_size/2);
    vector<Solution> anions(population_size/2);
    Solution best_solution(vector<double>(dimension), numeric_limits<double>::infinity());
    vector<Solution> best_cations;
    vector<Solution> best_anions;
    Solution best_cation, best_anion;
    int eval = 0;
    bool liquid_phase = true;
    bool best_achieved = false;
    bool best_updated = false;
    double delta = 1;
    int not_mejora = 0;
    int tope_not_mejora = 10;
    int tope_eval = 100 * dimension;

    // Inicialización
    initialize(cations);
    initialize(anions);
    updateFitness(cations, eval);
    updateFitness(anions, eval);


    while (eval < max_eval && !best_achieved){
        // Fase líquida
        if (liquid_phase){
            vector<Solution> anions_aux(anions);
            updateLocations(anions, cations);
            updateLocations(cations, anions_aux);
            vector<Solution> cations_aux(anions);
            anions = cations;
            cations = cations_aux;

            // Actualización de los mejores valores
            updateFitness(cations, eval);
            updateFitness(anions, eval);

            best_cation = *min_element(cations.begin(), cations.end(), ionOrder);
            best_anion = *min_element(anions.begin(), anions.end(), ionOrder);
            best_cations.push_back(best_cation);
            best_anions.push_back(best_anion);

            best_updated = (updateBestSolution(best_solution, best_cation)||
                            updateBestSolution(best_solution, best_anion) ||
                            best_updated);

            // Salimos de la fase liquida, entramos en la sólida

            if (eval%tope_eval == 0){
                liquid_phase = false;
                //not_mejora=0;
            }
            if (best_solution.getFitness()==0)
                best_achieved = true;
        }
        // Fase sólida
        else{
            if (best_updated){
                applyRealeaLS(best_solution, eval, dimension*1000);
                best_cations.push_back(best_solution);
                best_anions.push_back(best_solution);
            }
            redistribute(anions, best_anions);
            redistribute(cations, best_cations);
            // Entramos en la siguiente iteración en fase líquida
            best_updated = false;
            liquid_phase = true;
        }
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

void applyRealeaLS(Solution &solution, int &eval, int evals_ls){
    tChromosomeReal sol(solution);
    ProblemCEC2014 cec2014(dimension);
    ProblemPtr problem = cec2014.get(func_num);
    ILocalSearch *ls;
    ILSParameters *ls_options;

    if (type_ls == "sw") {
        // Get the Solis Wets problem
        SolisWets *sw = new SolisWets();
        // Set the delta values
        sw->setDelta(0.2);
        ls = sw;
    }
    else if (type_ls == "simplex") {
        ls = new SimplexDim();
    }
    else if (type_ls == "cmaes") {
        CMAESHansen *cmaes = new CMAESHansen("cmaesinit.par");
        cmaes->searchRange(0.1);
        ls = cmaes;
    }

    ls -> setProblem(problem.get());
    ls -> setRandom(&myrandom);
    ls_options = ls -> getInitOptions(sol);

    // Apply the local search
    tFitness fitness = solution.getFitness();
    unsigned evals = ls->apply(ls_options, sol, fitness, evals_ls);

    eval += evals;
    solution = Solution(sol, fitness);
}


void applyLocalSearch(Solution &solution, int &eval, int evals_ls){
    int i=0;
    double norma;
    vector<double> direccion(solution.size());
    Solution current(solution);
    bool mejora = false;

    while(i < evals_ls){
        for (int j=0; j<direccion.size(); j++){
            direccion[j] = myrandom.randreal(-1,1);
        }

        norma = computeNorm(direccion);

        for (int j=0; j<direccion.size(); j++){
            current[j] += myrandom.randreal(0, epsilon)*(direccion[j] / norma);
        }

        normalize(current);

        current.updateFitness();

        if (current.getFitness() <= solution.getFitness()){
            mejora = true;
            solution = Solution(current);
        }
        else{
            mejora = false;
            current = Solution(solution);
        }
        eval++;
        i++;
    }
}
