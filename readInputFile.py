import networkx as nx

# Nome do arquivo de entrada
nome_arquivo = "grafo.txt"

# Abrir o arquivo e pular a primeira linha
with open(nome_arquivo, 'r') as arquivo:
    next(arquivo)  # Pula a primeira linha
    print('aqui')
    # Lê o grafo a partir das linhas restantes
    G = nx.parse_adjlist(arquivo)
print(2)
# Encontrar todas as cliques maximais
cliques_maximais = list(nx.find_cliques(G))
print(3)
# Encontrar a clique máxima (a maior)
clique_maxima = max(cliques_maximais, key=len)
print(4)
print("Cliques maximais encontradas:")
for clique in cliques_maximais:
    print(clique)

print("Clique máxima encontrada:", clique_maxima)