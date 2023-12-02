#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>

class Punto {
public:
    double x, y;
    
    Punto(double x, double y) : x(x), y(y) {}
    
    double calcularDistancia(const Punto& otroPunto) const {
        return std::sqrt(std::pow(x - otroPunto.x, 2) + std::pow(y - otroPunto.y, 2));
    }
};

class KMeans {
private:
    int k; 
    std::vector<Punto> centros;
    std::vector<std::vector<Punto>> clusters;

public:
    KMeans(int k) : k(k) {}

    void ajustar(std::vector<Punto>& datos, int iteracionesMaximas = 100) {
        inicializarCentros(datos);

        for (int iteracion = 0; iteracion < iteracionesMaximas; ++iteracion) {
            asignarClusters(datos);

            calcularNuevosCentros();
        }
    }

    void mostrarClusters() const {
        for (size_t i = 0; i < clusters.size(); ++i) {
            std::cout << "Cluster " << i + 1 << ": ";
            for (const auto& punto : clusters[i]) {
                std::cout << "(" << punto.x << ", " << punto.y << ") ";
            }
            std::cout << std::endl;
        }
    }

private:
    void inicializarCentros(const std::vector<Punto>& datos) {
        centros.clear();
        clusters.clear();

        std::srand(std::time(0));
        std::vector<int> indices;
        for (int i = 0; i < k; ++i) {
            int indice = std::rand() % datos.size();
            centros.push_back(datos[indice]);
            indices.push_back(indice);
        }

        clusters.resize(k);
    }

    void asignarClusters(const std::vector<Punto>& datos) {
        for (auto& cluster : clusters) {
            cluster.clear();
        }

        for (const auto& punto : datos) {
            double distanciaMinima = std::numeric_limits<double>::max();
            int indiceCluster = 0;

            for (size_t i = 0; i < centros.size(); ++i) {
                double distancia = punto.calcularDistancia(centros[i]);
                if (distancia < distanciaMinima) {
                    distanciaMinima = distancia;
                    indiceCluster = i;
                }
            }

            clusters[indiceCluster].push_back(punto);
        }
    }

    void calcularNuevosCentros() {
        for (size_t i = 0; i < clusters.size(); ++i) {
            if (!clusters[i].empty()) {
                double sumaX = 0.0, sumaY = 0.0;
                for (const auto& punto : clusters[i]) {
                    sumaX += punto.x;
                    sumaY += punto.y;
                }

                centros[i].x = sumaX / clusters[i].size();
                centros[i].y = sumaY / clusters[i].size();
            }
        }
    }
};

int main() {
    std::vector<Punto> datos = {
        {1.0, 2.0},
        {2.0, 3.0},
        {3.0, 4.0},
        {10.0, 11.0},
        {11.0, 12.0},
        {12.0, 13.0}
    };

    int k = 2;
    KMeans kmeans(k);
    kmeans.ajustar(datos);

    std::cout << "Clusters finales:" << std::endl;
    kmeans.mostrarClusters();

    return 0;
}