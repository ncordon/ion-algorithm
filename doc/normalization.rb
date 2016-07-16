for i in {1,...length(cations)} {
    for j in {1,...length(cation[i]}{
        if (cation[i][j] < -100) cation[i][j] = -100
        elsif (cation[i][j] > 100) cation[i][j] = 100
}

for i in {1,...length(anions)} {
    for j in {1,...length(anion[i]}{
        if (anion[i][j] < -100) anion[i][j] = -100
        elsif (anion[i][j] > 100) anion[i][j] = 100
    }
}
