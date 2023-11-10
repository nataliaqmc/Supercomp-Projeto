#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

std::vector<int> EncontrarCliqueMaxima(std::vector<std::vector<int>> grafo, int numVertices) {
    std::vector<int> cliqueMaxima;

    while (!grafo.empty()) {
        // Encontrar o vértice de maior grau
        int verticeMaiorGrau = -1;
        int grauMaior = -1;

        for (int i = 0; i < numVertices; ++i) {
            int grau = std::count(grafo[i].begin(), grafo[i].end(), 1);
            if (grau > grauMaior) {
                grauMaior = grau;
                verticeMaiorGrau = i;
            }
        }

        if (verticeMaiorGrau == -1) {
            break;  // Não há mais vértices para adicionar à clique
        }

        // Adicionar vértice à clique máxima
        cliqueMaxima.push_back(verticeMaiorGrau);

        // Remover vértice e seus vizinhos do grafo
        grafo.erase(grafo.begin() + verticeMaiorGrau);
        for (int i = 0; i < numVertices; ++i) {
            grafo[i].erase(grafo[i].begin() + verticeMaiorGrau);
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