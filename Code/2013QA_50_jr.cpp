/*
ano: 2013
fase: qualificação
problema: A
pontos: 50
autor: João Rico
linguafem: c++
tópicos: pesquisa completa

Pesquisa completa simples.

Para cada intervalo [A, B], percorrer cada numero e adicionar a frequencia dos digitos encontrados a um vector.

Complexidade:

O(N*B)



*/


#include <iostream>
#include <vector>
#include <cstdio>

using namespace std;

int main(){
        int count[10];
        int N, A, B, n, max;

        cin >> N;

        while(N--){
                
                scanf("%d %d", &A, &B);

                // reset count
                for(int i = 0; i < 10; i++){
                         count[i] = 0;
                }
                // for each number count digits
                for(int i = A; i <= B; i++){
                        n = i;
                        while(n){
                                count[n%10]++;
                                n = n/10;
                        }

                }

                // find and print max
                max = 0;
                for(int i = 0; i < 10; i++){

                        if (count[i] > max){
                                max = count[i]; 
                        }
                }                
                cout << max;

                // print every digit that has max counts
                for(int i = 0; i < 10; i++){
                        if(count[i]==max){
                                cout << " " << i;
                        }
                }
                cout << endl;
        }
}
