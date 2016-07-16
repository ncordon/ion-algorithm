def redistribute (ions, list_bests){
    for ion in ions{
        if rand(0,1) < prob_restart
            ion[j] = [random(-100,100) for j in {1...length(ion)}]
        else{
            if !list_bests.empty(){
                ions = lists_bests.pop()
            }
            else{
                ion[j] = [random(-100,100) for j in {1...length(ion)}]
            }
            for j in {1...length(ion)}{
                if(rand(0,1) < prob_mutation)
                    ion[j] = random(-100,100)
            }
        }
    }
}

redistribute(anions, best_cations)
redistribute(cations, best_anions)
