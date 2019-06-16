/*
ano: 2015
fase: qualificacao
problema: B
pontos: 100
autor: David Nassauer
linguagem: c++
topicos:
url do problema: http://www.dcc.fc.up.pt/oni/problemas/2015/qualificacao/probB.html
url da solucao: 

Para saber se um par de partículas é estável ou não, basta-nos conhecer o valor máximo e mínimo das partículas
que estão entre eles. Ex:
D = 5
4 1 2 3 5 6 7 8 9 4
Para saber se os dois 4 que aparecem são estáveis, só precisamos de saber o mínimo (neste caso 1) e o máximo (neste caso 11) entre os dois 4:
Como 1 está a distância <= D do 4, então sabemos que o 2 e o 3 também vão estar a distância <= D do 4.
Como 9 está a distância <= D do 4, então sabemos que o 5, 6, 7, e 8 também vão estar a distância <= D do 4.

Dava-nos muito jeito conseguir descobrir se duas partículas são estáveis em O(1). Será que conseguimos fazer isso?
A resposta é sim - usando uma estrutura de dados chamada "sparse table" (podem ler sobre ela na pg. 85 deste livro: https://cses.fi/book.pdf . Já agora, recomendo vivamente este livro para quem quer treinar informática - acho que explica melhor do que o CP3)
Com a sparse table conseguimos, depois de O(Nlog N) de preprocessamento, obter o valor mínimo e o valor máximo entre quaisquer dois números em O(1)
Por isso já conseguimos dizer se um par é estável ou não em O(1)

Agora é fácil: penso que há outras maneiras de fazer isto, mas o que eu fiz foi:
Para cada número (literalmente para todos os números de 1 até 1000000) guardo em que posições é que esse número aparece no input (no exemplo acima guardaria as posições 0 e 9 para o número 4)
Isto faz-se em O(N) percorrendo a lista do input uma vez
Depois vejo se para cada par de posições ADJACENTES (adjacente significa que não há outro número igual a esses dois entre esses os dois) esse par é estável ou não.
Basta ver os adjacentes: por exemplo se o input for este:
D = 5
4 1 2 3 4 5 6 7 4
se eu sei que os dois primeiros 4 são estáveis e os dois últimos também, então sei que o primeiro e o último também o são.
Usando esta propriedade simpática, conseguimos calcular, para cada número k, quantos pares de partículas estáveis de valor = k existem,
rapidamente: em O(número de vezes que esse número aparece no input), porque percorremos a lista de posições desse número exatamente uma vez
No total, a complexidade é
O(C(Nlog N + max{p_i}))
*/
#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;

int n, d;
int val[60005];
int st_min[18][60005];
int st_max[18][60005];
vector<int> pos[1000010];

int range_min(int a, int b){
    int len = b-a+1;
    int k = log2(len);
    return min(st_min[k][a], st_min[k][b-((int)pow(2,k))+1]);
}

int range_max(int a, int b){
    int len = b-a+1;
    int k = log2(len);
    return max(st_max[k][a], st_max[k][b-((int)pow(2,k))+1]);
}

bool is_stable(int v,int a, int b){
    if(b!=a+1){
        int mx = range_max(a+1,b-1);
        int mn = range_min(a+1,b-1);
        return (((int) fabs(mx-v))<=d)&&(((int) fabs(mn-v))<=d);
    }else{
        return true;
    }
}

int main(){
	int c; scanf("%d", &c);
	while(c--){ //C casos de teste
        //Clean last case
        memset(val, -1, sizeof(val[0])*60005);
        for(int i=0;i<1000010;i++){
            if(!pos[i].empty()) pos[i].clear();
        }
        //Input
        scanf("%d %d", &n, &d);
        for(int i=0;i<n;i++){
            scanf("%d", &val[i]);
        }
        //Sparse table for min and max
        int lgn = log2(n);
        for(int i=0;i<n;i++){
            st_min[0][i] = val[i];
            st_max[0][i] = val[i];
        }
        for(int j=1;j<=lgn;j++){
            int power = pow(2,j);
            for(int i=0;i+power-1<n;i++){
                st_min[j][i] = min(st_min[j-1][i], st_min[j-1][i+power/2]);
                st_max[j][i] = max(st_max[j-1][i], st_max[j-1][i+power/2]);
            }
        }
        //ALG
        for(int i=0;i<n;i++){
            pos[val[i]].push_back(i);
        }
        long long int ans = 0;
        for(int i=1;i<=1000000;i++){
            long long int de_seguida = 1;
            for(unsigned int j=1;j<pos[i].size();j++){
                if(is_stable(i, pos[i][j-1], pos[i][j])){
                    //printf("O par nas pos %d e %d é estável.\n", );
                    ans += de_seguida;
                    de_seguida++;
                }else{
                    de_seguida = 1;
                }
            }
        }
        printf("%lld\n", ans);
	}
	return 0;
}
