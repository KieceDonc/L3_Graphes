#include <vector>
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

// On définit un type pour les tableaux 1D et 2D
typedef std::vector<int> iVector;
typedef std::vector<iVector> iVector2D;

// Fonction affichant un tableau d'arêtes
void printGraphe(iVector2D in){
    for(int x = 0 ; x < in.size() ; x++){
        cout << "Arête " << x << " : " ;
        for(int y = 0 ; y < in[x].size() ; y++)
            cout << in[x][y] << " ";
        cout << endl;
    }
}

void printVec1D(iVector in){
    for(int x = 0 ; x < in.size() ; x++)
        cout << in[x] << " ";
    cout << endl;
}

// EXERCICE 1 : Fonction de génération d'arêtes aléatoires 
iVector2D genegraphe(int n, int m){
    iVector2D out;
    
    for(int x = 0 ; x < m ; x++){
        out.push_back( iVector{rand()%n,rand()%n} );
    }

    return out;
}

// EXERCICE 2 : Recherche de composantes connexes
iVector compConn(iVector2D in, int n, int m){
    iVector comp;

    for(int x = 0 ; x < n ; x++)
        comp.push_back(x);
    
    for(int x = 0 ; x < m ; x++)
        if(comp[in[x][1 ]] != comp[in[x][0]])
            for(int z = 0 ; z < n ; z++)
                if(comp[z] == comp[ in[x][1] ])
                    comp[z] = comp[ in[x][0] ];
    
    
    return comp;
}

// EXERCICE 3 : Calcul des tailles des composantes connexes
iVector tailleComp(iVector2D in, int n, int m){
    iVector sizes;
    iVector comp = compConn(in,n,m);

    for(int x = 0 ; x < n ; x++){
        int occ = count(comp.begin(),comp.end(),x);
        sizes.push_back(occ);
    }

    return sizes;
}

// Calcul les occurences des composantes de taille n
void nombreComp(iVector in){
    int max = *max_element(in.begin(), in.end());
    
    for(int x = 0 ; x <= max ; x++){
        int occ = count(in.begin(),in.end(),x);
        if(occ != 0)
            cout << "Il y a " << occ << " composantes de taille " << x << endl;
    }
}

// Main
int main(int argc, const char * argv[])
{
    srand(time(NULL));

    int n = 10000;
    int m = 5000;

    iVector2D arete = genegraphe(n,m);
    iVector comp = tailleComp(arete,n,m);
    nombreComp(comp);
    return 0;
}
