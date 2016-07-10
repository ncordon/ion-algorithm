for i=1 to length(cations){
    for j=1 to length(cation[i])
        if (cation[i][j] < -100) cation[i][j] = -100
        elsif (cation[i][j] > 100) cation[i][j] = 100
}

for i=1 to length(anions){
    for j=1 to length(anion[i])
        if (anion[i][j] < -100) anion[i][j] = -100
        elsif (anion[i][j] > 100) anion[i][j] = 100
}
