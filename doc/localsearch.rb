applyLocalSearch(best_solution){
    current = best_solution

    for i in {1,2,...evals_ls} {
        direccion = [random(0,1) for i in {1...dimension}]
        norma = || direccion ||

        for j in {1...dimension} {
            current[j] += random(0, epsilon)*(direccion[j] / norma);
        }

        normalize(current);
        current.updateFitness();

        if (current.getFitness() <= best_solution.getFitness()){
            best_solution = current
        }
        else{
            current = best_solution
        }
    }
}
