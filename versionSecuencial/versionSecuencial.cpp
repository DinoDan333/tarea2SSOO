#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void convertirEscalaDeGrises(Mat& imagenColor, Mat& imagenGrises) {
    cvtColor(imagenColor, imagenGrises, COLOR_BGR2GRAY);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cerr << "Uso: " << argv[0] << " <imagen_entrada> <imagen_salida>" << endl;
        return EXIT_FAILURE;
    }

    // Cargar la imagen a color
    Mat imagenColor = imread(argv[1], IMREAD_COLOR);
    if (imagenColor.empty()) {
        cerr << "Error al cargar la imagen de entrada." << endl;
        return EXIT_FAILURE;
    }

    // Convertir la imagen a escala de grises
    Mat imagenGrises;
    convertirEscalaDeGrises(imagenColor, imagenGrises);

    // Guardar la imagen en escala de grises
    imwrite(argv[2], imagenGrises);

    cout << "Conversión a escala de grises completada." << endl;

    return EXIT_SUCCESS;
}
