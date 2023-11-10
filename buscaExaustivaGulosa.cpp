#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::vector<int> EncontrarCliqueMaxima(std::vector<std::vector<int>> grafo, int numVertices) {
    std::vector<int> cliqueMaxima;

    while (!grafo.empty()) {
        // Encontrar o vértice com mais arestas para a clique existente
        int verticeEscolhido = -1;
        int maxArestasConectadas = -1;

        for (int i = 0; i < numVertices; ++i) {
            if (std::find(cliqueMaxima.begin(), cliqueMaxima.end(), i) == cliqueMaxima.end()) {
                int arestasConectadas = 0;

                for (int v : cliqueMaxima) {
                    if (grafo[i][v] == 1) {
                        ++arestasConectadas;
                    }
                }

                if (arestasConectadas > maxArestasConectadas) {
                    maxArestasConectadas = arestasConectadas;
                    verticeEscolhido = i;
                }
            }
        }

        if (verticeEscolhido == -1) {
            break;  // Não há mais vértices para adicionar à clique
        }

        // Adicionar vértice à clique máxima
        cliqueMaxima.push_back(verticeEscolhido);

        // Remover vértice e seus vizinhos do grafo
        grafo.erase(grafo.begin() + verticeEscolhido);
        for (int i = 0; i < numVertices; ++i) {
            grafo[i].erase(grafo[i].begin() + verticeEscolhido);
        }

        --numVertices;
    }

    return cliqueMaxima;
}

int main() {
    std::string nomeArquivo;
    std::cout << "Digite o nome do arquivo contendo o grafo: ";
    std::cin >> nomeArquivo;

    std::ifstream arquivo(nomeArquivo);

    if (!arquivo.is_open()) {
        std::cerr << "Erro ao abrir o arquivo." << std::endl;
        return 1;
    }

    int numVertices;
    arquivo >> numVertices;

    std::vector<std::vector<int>> grafo(numVertices, std::vector<int>(numVertices, 0));

    for (int i = 0; i < numVertices; ++i) {
        for (int j = 0; j < numVertices; ++j) {
            arquivo >> grafo[i][j];
        }
    }

    arquivo.close();

    std::vector<int> maxClique = EncontrarCliqueMaxima(grafo, numVertices);

    std::cout << "Clique Máxima: ";
    for (int node : maxClique) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    return 0;
}