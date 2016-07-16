if  fitness(best(cations)) >= fitness(worst(cations)) and
    fitness(best(anions)) >= fitness(worst(anions))

    if (rand < prob_restart){
        random_restart(anions)
    }
    else{
        for i in {1,...length(anions)}{
            if (rand(0,1) > 0.5)
                anion[i] = anion[i] + rand(-1,1)*(best_old_cation)
            else
                anion[i] = anion[i] + rand(-1,1)*(best_cation)
        }
    }
    if (rand < prob_restart){
        random_restart(cations)
    }
    else{
        for i in {1,...length(cations)}{
            if (rand(0,1) > 0.5)
                cation[i] = cation[i] + rand(-1,1)*(best_old_anion)
            else
                cation[i] = cation[i] + rand(-1,1)*(best_anion)
        }
    }
