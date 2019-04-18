/*
(david n)

Para saber se um par de part�culas � est�vel ou n�o, basta-nos conhecer o valor m�ximo e m�nimo das part�culas
que est�o entre eles. Ex:
D = 5
4 1 2 3 5 6 7 8 9 4
Para saber se os dois 4 que aparecem s�o est�veis, s� precisamos de saber o m�nimo (neste caso 1) e o m�ximo (neste caso 11) entre os dois 4:
Como 1 est� a dist�ncia <= D do 4, ent�o sabemos que o 2 e o 3 tamb�m v�o estar a dist�ncia <= D do 4.
Como 9 est� a dist�ncia <= D do 4, ent�o sabemos que o 5, 6, 7, e 8 tamb�m v�o estar a dist�ncia <= D do 4.

Dava-nos muito jeito conseguir descobrir se duas part�culas s�o est�veis em O(1). Ser� que conseguimos fazer isso?
A resposta � sim - usando uma estrutura de dados chamada "sparse table" (podem ler sobre ela na pg. 85 deste livro: https://cses.fi/book.pdf . J� agora, recomendo vivamente este livro para quem quer treinar inform�tica - acho que explica melhor do que o CP3)
Com a sparse table conseguimos, depois de O(Nlog N) de preprocessamento, obter o valor m�nimo e o valor m�ximo entre quaisquer dois n�meros em O(1)
Por isso j� conseguimos dizer se um par � est�vel ou n�o em O(1)

Agora � f�cil: penso que h� outras maneiras de fazer isto, mas o que eu fiz foi:
Para cada n�mero (literalmente para todos os n�meros de 1 at� 1000000) guardo em que posi��es � que esse n�mero aparece no input (no exemplo acima guardaria as posi��es 0 e 9 para o n�mero 4)
Isto faz-se em O(N) percorrendo a lista do input uma vez
Depois vejo se para cada par de posi��es ADJACENTES (adjacente significa que n�o h� outro n�mero igual a esses dois entre esses os dois) esse par � est�vel ou n�o.
Basta ver os adjacentes: por exemplo se o input for este:
D = 5
4 1 2 3 4 5 6 7 4
se eu sei que os dois primeiros 4 s�o est�veis e os dois �ltimos tamb�m, ent�o sei que o primeiro e o �ltimo tamb�m o s�o.
Usando esta propriedade simp�tica, conseguimos calcular, para cada n�mero k, quantos pares de part�culas est�veis de valor = k existem,
rapidamente: em O(n�mero de vezes que esse n�mero aparece no input), porque percorremos a lista de posi��es desse n�mero exatamente uma vez
No total, a complexidade �
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
                    //printf("O par nas pos %d e %d � est�vel.\n", );
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
