CODE_FOLDER = "Code/"
OUTPUT_FILE = "README.md"
CODE_URL = "https://github.com/LikeScience/Repositorio_ONI/blob/master/Code/"

import os

def sortf(a, b):
    for i in range(6):
        if i == 0 and a[i] != b[i]:
            return a[i] > b[i]
        if a[i] != b[i]:
            return a[i] < b[i]
        
files = os.listdir(CODE_FOLDER)
values = []

for file in files:
    if file.endswith(".cpp") or file.endswith(".java") or file.endswith(".c") or file.endswith(".pas"):
        attributes = []
        lines = open(CODE_FOLDER + file, encoding='utf-8').read().splitlines()
        for i in range(1,10):
            line = lines[i]
            x, y = line.split(":",1)
            attributes.append(y)
        attributes.append(CODE_URL + file)
        if attributes[8] == " ":
            attributes.append("Em falta")
        else:
            attributes.append("[Oficial](" + attributes[8] + ")")
        values.append(attributes)


lines = []
lines.append('|Ano|Fase|Problema|Solucao|Pontos|Autor|Linguagem|Topicos|')
lines.append('|---|----|--------|-------|------|-----|---------|-------|')
for i in range(len(values)):
    lines.append('|' + str(values[i][0]) + '|' + values[i][1] + '|' + '[' + values[i][2] + '](' + values[i][7] + ')' + '|' + values[i][10] + '|' + '[' + str(values[i][3]) + '](' + values[i][9] + ')|' + values[i][4] + '|' + values[i][5] + '|' + values[i][6] + '|')
wFile = open(OUTPUT_FILE, "w")
wFile.write('\n'.join(lines) + '\n')
wFile.close()