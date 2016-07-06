#include <algorithm>
#include "ion.h"

using namespace std;


void updateFitness(&vector<Ion> population){
    for (int i=0; i < population.size, i++)
        population[i].updateFitness();
}


bool ionOrder(Ion i, Ion j){
    return i.getFitness() < j.getFitness();
}


void updateLocations(&vector<Ion> current, &Ion reference){
    double force;

    for(int i = 0; i < ions.size(), i++){
        for(int j = 0; j < current[i].size(); j++){
            force = (1.0/(1 + exp(-0.1/abs(current[i][j] - reference[j])));
            current[i][j] = current[i][j] + force*(reference[j] - current[i][j]);
        }
    }
}


double ion_algorithm(int population_size, int dimension, int max_eval){
    vector<Ion> cations;
    vector<Ion> anions;
    cations.reserve(population_size/2);
    anions.reserve(population_size/2);
    vector<double> position(dimension);
    vector<double> best_solution(dimension);
    double best_fvalue=numeric_limits<double>::infinity();
    int lbound = -100, ubound = 100, index, eval = 0, liquid_phase = true;

    // Generador aleatorio
    default_random_engine seed(12345678);
    uniform_real_distribution<double> runif(0.0, 1.0);


    // Inicialización
    for (int i=0; i < population_size; i++){
        index = i/2;

        for (int j=0; j < dimension; j++)
            position[j] = lbound + (ubound-lbound)*runif(seed);

        // Inicializamos los pares a cationes, los impares a aniones
        if (i%2==0)
            cations[index] = Ion(position, true);
        else
            anions[index] = Ion(position, false);
    }


    while (eval < max_eval){
        auto best_cation = max_element(anions.begin(), anions.end(), ionOrder);
        auto best_anion = max_element(cations.begin(), cations.end(), ionOrder);

        if (liquid_phase){
            updateLocations(anions, best_cation);
            updateLocations(cations, best_anion);

            updateFitness(anions);
            updateFitness(cations);

            auto best_cation = min_element(anions.begin(), anions.end(), ionOrder);
            auto best_anion = min_element(cations.begin(), cations.end(), ionOrder);
            auto worst_cation = max_element(anions.begin(), anions.end(), ionOrder);
            auto worst_anion = max_element(cations.begin(), cations.end(), ionOrder);


            // Actualización de los mejores valores
            if (*best_cation.getFitness() < best_fvalue){
                best_fvalue = *best_cation.getFitness();
                best_solution = (vector<double>) best_cation;
            }
            if (*best_anion.getFitness() < best_fvalue){
                best_fvalue = *best_anion.getFitness();
                best_solution = (vector<double>) best_anion;
            }
        }

        eval++;
    }

}
