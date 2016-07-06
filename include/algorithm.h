#include<algorithm>
using namespace std;


void updateFitness(&vector<Ion> population);


bool ionOrder(Ion i, Ion j);


void updateLocations(&vector<Ion> current, &Ion reference);


double ion_algorithm(int population_size, int dimension, int max_eval);
