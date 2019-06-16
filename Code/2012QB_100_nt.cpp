/*
ano: 2012
fase: qualificacao
problema: B
pontos: 100
autor: Nuno Teixeira
linguagem: c++
topicos: algoritmo de Rabin-Karp
url do problema: http://www.dcc.fc.up.pt/oni/problemas/2012/qualificacao/probB.html
url da solucao: 
*/

#include <iostream>
#include <stack>
#include <algorithm>
#include <cmath>
#include <vector>

using namespace std;

/*

Sendo T o comprimento de cada cadeia, existem T^2 sequências por cadeia.
Sendo S o comprimento de cada sequência, verificar se a sequência existe noutra cadeia demora T*S
Usando o algoritmo Rabin-Karp conseguimos verificar em T em vez de T*S, portanto para as N cadeias conseguimos verificar em N*T

Outras notas:
- Ordenar as cadeias por ordem crescente de tamanho permite ir descartanto as cadeias mais pequenas durante a procura
- Se já encontrámos uma sequência de tamanho S, devemos apenas procurar sequências maiores do que S
- A função de hash usada é o "segredo" do Rabin-Karp. Multiplicar cada elemento por uma potência de 3 reduz as colisões

*/

inline bool areEqual(string s1, string s2, int s1Hash, int s2Hash, int s1Start, int s2Start, int size) {
	if(s1Hash != s2Hash) return false;

	for(int i = 0; i < size; i++) {
		if(s1[s1Start + i] != s2[s2Start + i]) return false;
	}
	return true;
}

int maxCommon(vector<string> &lines, int k) {
	vector<int> indexCounter(lines.size());

	int maxSeq = 0;

	for(int i = 0; i < (int) lines.size() && i + k <= (int) lines.size(); i++) {
        if((int) lines[i].length() < maxSeq + 1) continue;

        fill(indexCounter.begin(), indexCounter.end(), 0);
		int iStart = 0;
		int iSize = maxSeq + 1;
		int previousHash = 0;
		int currentHash = 0;
        for(int j = 0; j < iSize; j++) {
            currentHash += lines[i][iStart + j] * pow(3, j);
        }

        while(true) {
        	int nrMatches = 1;

        	for(int j = i + 1; j < (int) lines.size(); j++) {
        		int currentIdx = indexCounter[j];
        		if(currentIdx == -1) continue;
        		if(currentIdx + iSize > (int) lines[j].length()) {
          			indexCounter[j] = -1;
          			continue; 			
        		}

        		string line = lines[j];
                int hash = previousHash;
                if(hash == 0) {
                    for(int k = 0; k < iSize; k++) {
                        hash += line[k] * pow(3, k);
                    }
                } else {
                    hash += line[currentIdx + iSize - 1] * pow(3, iSize - 1);
                }

        		while(!areEqual(lines[i], line, currentHash, hash, iStart, currentIdx, iSize) && currentIdx + iSize < (int) line.length()) {
        			hash -= line[currentIdx];
        			hash /= 3;
        			currentIdx++;
        			hash += line[currentIdx + iSize - 1] * pow(3, iSize - 1);
        		}

        		if(areEqual(lines[i], line, hash, currentHash, iStart, currentIdx, iSize)) {
        			indexCounter[j] = currentIdx;
        			nrMatches++;
        		} else {
        			indexCounter[j] = -1;
        		}
        	}

        	if(nrMatches >= k) {
				maxSeq = max(maxSeq, iSize);
        	}

        	if(iStart + iSize >= (int) lines[i].length()) break;

        	if(nrMatches < k) {
                currentHash -= lines[i][iStart];
                currentHash /= 3;                
        		iStart++;

                previousHash = 0;
        		fill(indexCounter.begin(), indexCounter.end(), 0);
        	} else {
        		previousHash = currentHash;
        		iSize++;
        	}
            currentHash += lines[i][iStart + iSize - 1] * pow(3, iSize - 1);
        }
	}
	return maxSeq;
}

struct compare {
    bool operator()(const std::string& first, const std::string& second) {
        return first.size() < second.size();
    }
};

int main() {

	int k, n;
	vector<string> lines;
	cin >> n;
	cin >> k;
	compare c;
	cin.ignore();

	for(int i = 0; i < n; i++) {
		string line;
		getline(cin, line);
		lines.push_back(line);
	}
	sort(lines.begin(), lines.end(), c);
	cout << maxCommon(lines, k) <<endl;
	return 0;
}
