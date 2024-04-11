
#Programa que lê arquivo com código e converte em arquivo com instruções em hexadecimal

#DEFINIÇÕES DE FUNÇÕES 

#As funções são responsáveis por receber os valores tratados e enviar para o arquivo

def nB(arquivo, x, y):
    arquivo.write(f"{x}{y}0\n")

def nAeBn(arquivo, x, y):
    arquivo.write(f"{x}{y}1\n")

def nAeB(arquivo, x, y):
    arquivo.write(f"{x}{y}2\n")

def Lzero(arquivo, x, y):
    arquivo.write(f"{x}{y}3\n")

def AeBn(arquivo, x, y):
    arquivo.write(f"{x}{y}4\n")

def nA(arquivo, x, y):
    arquivo.write(f"{x}{y}5\n")

def AXB(arquivo, x, y):
    arquivo.write(f"{x}{y}6\n")

def AenB(arquivo, x, y):
    arquivo.write(f"{x}{y}7\n")

def nAonB(arquivo, x, y):
    arquivo.write(f"{x}{y}8\n")

def nAXnB(arquivo, x, y):
    arquivo.write(f"{x}{y}9\n")

def Bcopia(arquivo, x, y):
    arquivo.write(f"{x}{y}A\n")

def AeB(arquivo, x, y):
    arquivo.write(f"{x}{y}B\n")

def Lum(arquivo, x, y):
    arquivo.write(f"{x}{y}C\n")

def AonB(arquivo, x, y):
    arquivo.write(f"{x}{y}D\n")

def AoB(arquivo, x, y):
    arquivo.write(f"{x}{y}E\n")

def Acopia(arquivo, x, y):
    arquivo.write(f"{x}{y}F\n")

#DEFINIÇÕES DE VARIÁVEL

instrucoes = {
    "nB": nB,
    "nAeBn": nAeBn,
    "nAeB": nAeB,
    "Lzero": Lzero,
    "AeBn": AeBn,
    "nA": nA,
    "AXB": AXB,
    "AenB": AenB,
    "nAonB": nAonB,
    "nAXnB": nAXnB,
    "Bcopia": Bcopia,
    "AeB": AeB,
    "Lum": Lum,
    "AonB": AonB,
    "AoB": AoB,
    "Acopia": Acopia
}

 
caminho_arquivo_ula = "testeula.txt"
caminho_arquivo_hexa = "testehexa.txt"

comandos = []

x = ""
y = ""

# Abre o arquivo em modo de leitura e armazena os comandos individualmetne em um vetor
with open(caminho_arquivo_ula, "r") as arquivo:
    for linha in arquivo:
        comandos.append(linha.strip())

#Este bloco itera por todos os comandos armazenados e verifica se é um comando de atribuição de valor à variável
#ou um comando de instrução e, em seguida, tratar a informação e enviar os dados para as funções de escrita no arquivo

#O bloco abre o arquivo em modo de escrita para transpor os dados ao arquivo testehexa.txt
       
with open(caminho_arquivo_hexa, "w") as arquivo:
    for comando in comandos:
        if comando[0] == 'W':
            escolha = comando[2:-1]
            instrucao_selecionada = instrucoes.get(escolha)
            instrucao_selecionada(arquivo, x, y)   
        elif comando[0] == 'X':
            x = comando[2]
        elif comando[0] == 'Y':
            y = comando[2]
        

            