#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <mpi.h>

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
    return grafo;
}

std::list<int> EncontrarCliqueMaxima(std::vector<std::vector<int>>& grafo, int numVertices, int inicio, int fim) {
    std::list<int> cliqueMaxima;
    std::list<int> melhorClique;

    int melhorTamanho = 0;

    for (int i = inicio; i <= fim; ++i) {
        std::list<int> candidatos;

        for (int j = 0; j < numVertices; ++j) {
            if (i & (1 << j)) {
                candidatos.push_back(j);
            }
        }

        // Verifica se é uma clique válida
        bool cliqueValida = true;
        for (int u : candidatos) {
            for (int v : candidatos) {
                if (u != v && grafo[u][v] == 0) {
                    cliqueValida = false;
                    break;
                }
            }
            if (!cliqueValida) break;
        }

        // Atualiza a melhor clique encontrada até agora
        if (cliqueValida && candidatos.size() > melhorTamanho) {
            melhorTamanho = candidatos.size();
            melhorClique = candidatos;
        }
    }

    cliqueMaxima.assign(melhorClique.begin(), melhorClique.end());
    return cliqueMaxima;
}

int main(int argc, char* argv[]) {
    MPI_Init(&argc, &argv);

    int numProcessos;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcessos);

    int processoRank;
    MPI_Comm_rank(MPI_COMM_WORLD, &processoRank);

    std::string nomeArquivo = "grafo.txt";
    int numVertices;
    std::vector<std::vector<int>> grafo;

    if (processoRank == 0) {
        grafo = LerGrafo(nomeArquivo, numVertices);
    }

    MPI_Bcast(&numVertices, 1, MPI_INT, 0, MPI_COMM_WORLD);

    int particaoTamanho = (1 << numVertices) / numProcessos;
    int inicio = processoRank * particaoTamanho;
    int fim = (processoRank == numProcessos - 1) ? (1 << numVertices) - 1 : (processoRank + 1) * particaoTamanho - 1;

    std::list<int> maxCliqueLocal = EncontrarCliqueMaxima(grafo, numVertices, inicio, fim);

    std::list<int> maxCliqueGlobal;

    if (processoRank == 0) {
        maxCliqueGlobal = maxCliqueLocal;
        for (int i = 1; i < numProcessos; ++i) {
            std::list<int> cliqueParcial;
            MPI_Recv(&cliqueParcial, numVertices, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
            if (cliqueParcial.size() > maxCliqueGlobal.size()) {
                maxCliqueGlobal = cliqueParcial;
            }
        }
    } else {
        MPI_Send(&maxCliqueLocal, numVertices, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    if (processoRank == 0) {
        std::cout << "Clique Máxima: ";
        for (int node : maxCliqueGlobal) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }

    MPI_Finalize();
    return 0;
}
