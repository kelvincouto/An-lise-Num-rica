import matplotlib.pyplot as plt

arq = open('ERRO.txt', 'r')

M = arq.readlines()
x = []
y = []

for line in M:
    s = line.split(',')
    x.append(float (s[0]))
    y.append(float (s[1]))
plt.plot(x,y, label='f(n) = Erro(n)') 
plt.title('Gráfico do erro cometido em I_4 ', color='black') 
plt.xlabel('Eixo X - valores de n')
plt.ylabel('Eixo Y ')

plt.legend(loc='best')

plt.show()
