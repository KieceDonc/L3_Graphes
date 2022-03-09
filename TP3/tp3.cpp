#include <cstdlib>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

const int n=20; // nombre de sommets
int adj[n][n];  // matrice d'adjacence du graphe
int couleur1[n];  // couleurs des sommets pour l'agorithme exact
int couleur2[n];
int couleur3[n];
bool trouve=false; // permet de stopper l'algorithme exact, quand une coloration  a ete trouvee

bool convient1(int x, int c){
     for(int i=0;i<x;i++){
          if(adj[x][i] && (couleur1[i]==c)) return false;
     }
     return true;
}

bool convient2(int x, int c){
     for(int i=0;i<x;i++){
          if(adj[x][i] && (couleur2[i]==c)) return false;
     }
     return true;
}

bool convient3(int x, int c){
     for(int i=0;i<x;i++){
          if(adj[x][i] && (couleur3[i]==c)) return false;
     }
     return true;
}

void colorRR(int x, int k)
{ 
     if(x==n)
     { /*cout << "Coloration en " << k << " couleurs trouvee" << endl;
       for(int i=0;i<n;i++) cout << "couleur de " << i << " : " << couleur1[i] << endl; //int z;cin >> z;
       */trouve=true;
     }
     else
     for(int c=1;c<=k;c++)
      if(convient1(x,c)) 
	{couleur1[x]=c;
         colorRR(x+1,k);
	 if(trouve) return;}
}

void colorExact(int k)
{
    for(int i=0;i<n;i++)
     couleur1[i]=0;
     colorRR(0,k);
     if(!trouve) cout << "Pas de coloration en " << k <<" couleurs" << endl;
}

void genereGraphe(int p){
     for(int x = 0; x < n; x++){
          for(int y = 0; y < n; y++){
               if(x != y){
                    int proba = rand() % 100;
                    if(proba <= p){
                         adj[x][y] = 1;
                    }
               }
          }
     }
}

void afficheGraphe(){
     for(int x = 0; x < n; x++){
          cout << "sommet n°" << x << " : ";
          for(int y = 0; y < n; y++){
               if(adj[x][y] == 1){
                    cout << y << " ";
               }
          }
          cout << endl;
     }
}

int nbChromatique(){
     bool founded = false;
     int k = 1;
     while(!founded){
          colorExact(k);
          founded = trouve;
          k+=1;
     }
     return --k;
}

int colorGlouton(){

     for(int x = 0; x < n; x++){
          couleur2[x] = 0;
     }

     int max = 1;
     
     for(int x = 0; x < n; x++){
          bool founded = false;
          int c = 1;
          while(!founded){
               founded = convient2(x,c);
               c+=1;
          }
          couleur2[x]=--c;
          if(c > max){
               max = c;
          }
     }

     return max;
}

int DSATUR(){
     
     return;
}

int main(){
     genereGraphe(50);
     //afficheGraphe();
     int nbChro = nbChromatique();
     cout << "Nombre chromatique : " << nbChro << endl;
     int glouton = colorGlouton();
     cout << "Nombre chromatique : " << glouton << endl;
     return 0;
}