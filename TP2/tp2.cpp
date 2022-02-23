#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <math.h>
using namespace std;

const int n=40;               // Le nombre de points.
const int dmax=20;		// La distance jusqu'a laquelle on relie deux points.
vector<int> voisin[n];          // Les listes de voisins.                    
int point[n][2];                // Les coordonnees des points.
int arbre[n-1][2];              // Les aretes de l'arbre de Dijkstra .
int pere[n];    		// La relation de filiation de l'arbre de Dijkstra.

void afficheGraphe(int n,int d, int sommet[][2]){
    // Cree le fichier Graphe.ps qui affiche le graphe.
    
    ofstream output;
    output.open("Graphe.ps",ios::out);
    output << "%!PS-Adobe-3.0" << endl;
    output << endl;  

    for(int i=0;i<n;i++){
        output << sommet[i][0] << " " << sommet[i][1] << " 1 0 360 arc" <<endl;
        output << "0 setgray" <<endl;
        output << "fill" <<endl;
        output << "stroke"<<endl;
        output << endl;
    }
    
    output << endl;
    
    for(int i=0;i<n-1;i++){
        for (int j=i+1 ;j<n;j++)
            if ((sommet[i][0]-sommet[j][0])*(sommet[i][0]-sommet[j][0])+(sommet[i][1]-sommet[j][1])*(sommet[i][1]-sommet[j][1])<d*d){
                output << sommet[i][0] << " " << sommet[i][1] << " moveto" << endl;
                output << sommet[j][0] << " " << sommet[j][1] << " lineto" << endl;
                output << "stroke" << endl;
                output << endl;
            
            }
        
    }
  }

void afficheArbre(int n, int k, int point[][2], int arbre[][2]){
    // Cree le fichier Arbre.ps qui affiche l'arbre.
    ofstream output;                           
    output.open("Arbre.ps",ios::out);
    output << "%!PS-Adobe-3.0" << endl;
    output << "%%BoundingBox: 0 0 612 792" << endl;
    output << endl;  
    
    for(int i=0;i<n;i++){
        output << point[i][0] << " " << point[i][1] << " 1 0 360 arc" <<endl;
        output << "0 setgray" <<endl;
        output << "fill" <<endl;
        output << "stroke"<<endl;
        output << endl;
    }

    output << endl;
    
    for(int i=0;i<k;i++){
    
        output << point[arbre[i][0]][0] << " " << point[arbre[i][0]][1] << " moveto" << endl;
        output << point[arbre[i][1]][0] << " " << point[arbre[i][1]][1] << " lineto" << endl;
        output << "stroke" << endl;
        output << endl;
    }
    
    output.close();
}

void generegraphe(int n, int point[][2]){
    for(int x = 0; x < n; x++){
        point[x][0]=rand()%611;
        point[x][1]=rand()%791;
    }
}

void voisins(){
    for(int x = 0; x < n; x++){
        vector<int> voisinx;
        for(int y = 0; y < n; y++){
            if(x != y){
                int euclide_distance = sqrt(pow((point[x][0]-point[y][0]),2)+pow((point[x][1]-point[y][1]),2));
                if(euclide_distance == dmax){
                    voisinx.push_back(y);
                }
            }
        }
        voisin[x]=voisinx;
    }
}

void printVoisins(){
    for(int x = 0; x< n ;x++){
        cout << "voisin de " << x << " : ";
        if(voisin[x].size() == 0){
            cout << "aucun voisin";
        }else{
            for(int y = 0 ; y < voisin[x].size() ; y++)
            cout << voisin[x][y] << " ";
        }
        cout << endl;
    }
}

int nb_m=0; // nombre de sommet marqué
int l[n]; // Distance de la source 
int m[n]; // Sommet marqué, si 0 pas marqué, si 1 marqué
int p[n]; // Prédécesseur dans l'arbre des plus courts

void Dijkstra_init_distance(int s){
    for(int x = 0; x < n; x++){
        // On initialise la distance depuis la source
        if(x!=s){
            l[x]=1000000000;
        }
    }
}

int Dijkstra_choisir_sommet(int s){
    int minimun_index=-1;
    int minimun_distance=-1;
    for(int x = 0; x < n ; x++){
        if(m[x]==0 && (minimun_distance==-1 || l[x]<minimun_distance)){
            minimun_index = x;
            minimun_distance = l[x]; 
        }
    }

    if(minimun_index!=-1){
        m[minimun_index]=1;
        nb_m+=1;
        return minimun_index;
    }else{
        cout << "minimun index = -1" << endl;
        return -1;
    }
}

vector<int> Dijkstra_sommet_non_marquer(int sommet){
    vector<int> nonmarquer;
    for(int x = 0; x < n ; x++){
        if(x!=sommet && m[x]==0){
            nonmarquer.push_back(x);
        }
    }
    return nonmarquer;
}

void Dijkstra(int s){
    // s = source
    p[s]=-1;
    Dijkstra_init_distance(s);
    l[s]=0;
    m[s]=1;
    nb_m+=1;
    while(nb_m < n){
        int sommet = Dijkstra_choisir_sommet(s);
        vector<int> sommet_non_marquer = Dijkstra_sommet_non_marquer(sommet);
        for(int index = 0; index < sommet_non_marquer.size(); index++){
            int y = sommet_non_marquer[index];
            int euclide_distance = sqrt(pow((point[sommet][0]-point[y][0]),2)+pow((point[sommet][1]-point[y][1]),2));
            if(l[y] > l[sommet] + euclide_distance){
                p[y] = sommet;
                l[y] = l[sommet] + euclide_distance;
            }
        }
    }
}

void printResultatDijkstra(){
    for(int x = 0; x < n; x++){
        cout << "Distance du sommet " << x << " depuis la source : " << l[x] << endl;
    }
}

int main(){
    generegraphe(n,point);
    afficheGraphe(n,dmax,point);
    voisins();
    printVoisins();
    int source = 1;
    Dijkstra(source);
    printResultatDijkstra();
    cout << point[0][0] << " " << point[0][1] << endl; 
    cout << point[1][0] << " " << point[1][1] << endl;
    return 0;
}