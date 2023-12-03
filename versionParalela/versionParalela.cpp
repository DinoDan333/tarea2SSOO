#include <iostream>
#include <opencv2/opencv.hpp>
#include <omp.h>

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

    // Crear la imagen en escala de grises
    Mat imagenGrises(imagenColor.rows, imagenColor.cols, CV_8UC1);

    // Convertir la imagen a escala de grises de manera paralela
#pragma omp parallel for
    for (int i = 0; i < imagenColor.rows; ++i) {
        for (int j = 0; j < imagenColor.cols; ++j) {
            Vec3b pixel = imagenColor.at<Vec3b>(i, j);
            imagenGrises.at<uchar>(i, j) = static_cast<uchar>((pixel[0] + pixel[1] + pixel[2]) / 3);
        }
    }

    // Guardar la imagen en escala de grises
    imwrite(argv[2], imagenGrises);

    cout << "Conversión a escala de grises completada." << endl;

    return EXIT_SUCCESS;
}
