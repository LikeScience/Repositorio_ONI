/*
(joao rico)

A solucao de pesquisa completa e demasiado lenta, de complexidade exponencial O(2**n)

Podemos usar programacao dinamica, atraves de uma relacao de recorrencia.

Imaginemos que sabemos F[k] que e o numero maximo de potes para uma solucao
em que o ultimo pote esta exatamente na posicao k.
Entao a solucao pretendida e max{F[k]} para k de 1 a N.
Atencao que F[k] NAO representa o numero maximo de potes para uma solucao com as k primeiras malas 
(se fosse esse o caso, a solucao seria F[N]). Em particular F[k] nao e necessariamente crescente.

Por exemplo para 
N 1 2 3 4 5 
A 1 1 1 1 6 
F 1 2 3 4 1 (nao e crescente, so existe uma solucao com o ultimo pote em n=5 (o caso em que e o unico))

Ou por exemplo para 
N 1 2 3 4 5 6 7
A 1 7 2 7 2 3 1
F 1 1 2 1 3 3 4

Sabemos certamente que F[k] >= 1. Qualquer que seja o alcance, tem pelo menos o proprio pote.
Basta-nos ver qual e o maior F[i] (com i < k) que e compativel em termos de alcance, e somar.

Complexidade:
Isto demora O(N) para um certo F[k], caso usemos uma lista de memoria.
Como ha N casos, temos O(N*N)

A relacao de recorrencia e:
F[k] =  1, se k - A[k] < 1 
     =  1 + max{F[i] se i + A[i] <= k} em que i vai de 1 a k-A[k], se k - A[k] >= 1
(com k de 1 a N)


Atencao que se comeca a contar de 1, e nao 0, ao longo deste problema
*/


#include<iostream>

using namespace std;

int main(){

        int N;
        int max; 
        int A[10010]; // alcances
        int F[10010]; // potes, p[i] potes ate a posicao i

        cin >> N;
        for (int i = 1; i <= N; i++){
                cin >> A[i];
        }

        // bottom-up DP
        F[1] = 1;

        for(int k = 2; k <= N; k++){ // comecar em k=2       
                if (k - A[k] < 1) {
                        F[k] = 1;
                        continue;
                }           
                max = 0;              
                for(int i = 1; i <= k-A[k]; i++){
                        if( i+A[i] <= k){
                                if (F[i] > max){
                                        max = F[i];
                                } 
                        }
                }
                F[k] = 1 + max;
        }
        max = 0;
        for(int i = 1; i <= N; i++){
                if (F[i] > max){
                        max = F[i];
                }
        }
        cout << max << endl;
}
