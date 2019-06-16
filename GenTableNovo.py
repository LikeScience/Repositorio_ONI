CODE_FOLDER = "Code/"
OUTPUT_FILE = "README_test.md"

import os

def sortf(a, b):
    for i in range(6):
        if i == 0 and a[i] != b[i]:
            return a[i] > b[i]
        if a[i] != b[i]:
            return a[i] < b[i]
        
BITS = [2, 5, 1000, 6, 1000, 10, 1000, 8, 1000, 7, 1000, 11, 1000, 9, 1000]
files = os.listdir(CODE_FOLDER)
values = []

for file in files:
    if file.endswith(".cpp"): # .java
        attributes = []
        lines = open(CODE_FOLDER + file, encoding='utf-8').read().splitlines()
        for i in range(1,10):
            line = lines[i]
            x, y = line.split(":",1)
            attributes.append(y)
        values.append(attributes)


lines = []
lines.append('|Ano|Fase|Problema|Solucao|Pontos|Autor|Linguagem|Topicos|')
lines.append('|---|----|--------|-------|------|-----|---------|-------|')
for i in range(len(values)):
    lines.append('|' + str(values[i][0]) + '|' + values[i][1] + '|' + '[' + values[i][2] + '](' + values[i][7] + ')' + '|' + '[Oficial](' + values[i][8] + ')' + '|' + '[' + str(values[i][3]) + '](' + values[i][6] + ')|' + values[i][4] + '|' + values[i][5] + '|' + values[i][6] + '|')
wFile = open(OUTPUT_FILE, "w")
wFile.write('\n'.join(lines) + '\n')
wFile.close()