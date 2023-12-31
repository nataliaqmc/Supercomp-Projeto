#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>

std::vector<std::vector<int>> LerGrafo(const std::string& nomeArquivo, int& numVertices) {
    std::ifstream arquivo(nomeArquivo);
    int numArestas = 0;
    arquivo >> numVertices >> numArestas;

    std::vector<std::vector<int>> grafo(numVertices, std::vector<int>(numVertices, 0));

    for (int i = 0; i < numArestas; ++i) {
        int u, v;
        arquivo >> u >> v;
        grafo[u - 1][v - 1] = 1;
        grafo[v - 1][u - 1] = 1;  // O grafo é não direcionado
    }

    arquivo.close();
    std::cout << "aqui" << std::endl;

    return grafo;
}
std::list<int> EncontrarCliqueMaxima(std::vector<std::vector<int>>& grafo, int numVertices) {
    std::list<int> cliqueMaxima;
    std::list<int> candidatos;

    // Inicialmente, todos os nós são candidatos
    for (int i = 0; i < numVertices; ++i) {
        candidatos.push_back(i);
    }

    while (!candidatos.empty()) {
        int v = candidatos.back();
        candidatos.pop_back();

        bool podeAdicionar = true;

        for (int u : cliqueMaxima) {
            if (grafo[u][v] == 0) {
                podeAdicionar = false;
                break;
            }
        }

        if (podeAdicionar) {
            cliqueMaxima.push_back(v);

            std::list<int> novosCandidatos;

            for (int u : candidatos) {
                bool adjacenteATodos = true;

                for (int c : cliqueMaxima) {
                    if (grafo[u][c] == 0) {
                        adjacenteATodos = false;
                        break;
                    }
                }

                if (adjacenteATodos) {
                    novosCandidatos.push_back(u);
                }
            }

            candidatos = novosCandidatos;
        }
    }

    return cliqueMaxima;
}


int main() {
    std::string nomeArquivo = "grafo.txt";
    int numVertices = 1000;
    std::vector<std::vector<int>> grafo =  LerGrafo(nomeArquivo,numVertices);
    std::list<int> maxClique = EncontrarCliqueMaxima(grafo, numVertices);

    std::cout << "Clique Máxima: ";
    for (int node : maxClique) {
        std::cout << node << " ";
    }
    std::cout << std::endl;

    return 0;
}