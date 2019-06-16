import os

def sortf(a, b):
	for i in range(6):
		if i == 0 and a[i] != b[i]:
			return a[i] > b[i]
		if a[i] != b[i]:
			return a[i] < b[i]

BITS = [2, 5, 1000, 6, 1000, 10, 1000, 8, 1000, 7, 1000, 11, 1000, 9, 1000]
progs = os.listdir("Code/")
values = []
i = 0
for prog in progs:
    values.append([])
    iFile = open("Code/" + prog, "r")
    for j in range(15):
        if BITS[j] == 1000:
            value = iFile.readline()
            values[i].append(value)
        else:
            value = iFile.read(BITS[j])
    iFile.close()
    i += 1
links = open("Links.txt", "r")
for i in range(len(progs)):
    f = links.readline()
    for prog in progs:
        if f == prog:
            for j in range(3):
                values[i].append(links.readline())
            links.readline()
links.close()
values.sort(values, cmp = sortf)
lines = []
lines.append('|Ano|Fase|Problema|Solucao|Pontos|Autor|Linguagem|Topicos|)')
lines.append('|---|----|--------|-------|------|-----|---------|-------|)')
for i in range(len(values)):
    lines.append('|' + str(values[i][0]) + '|' + values[i][1] + '|' + '[' + values[i][2] + '](' + values[i][7] + ')' + '|' + '[Oficial](' + values[i][8] + ')' + '|' + '[' + str(values[i][3]) + '](' + values[i][9] + ')|' + values[i][4] + '|' + values[i][5] + '|' + values[i][6] + '|')
wFile = open("README.md", "w")
wFile.writelines(lines)
wFile.close()
			