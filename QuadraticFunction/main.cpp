#include <iostream>
#include <math.h>
#include "pbPlots.hpp"
#include "supportLib.hpp"
#include <vector>

using namespace std;

float a, b, c;

float calcDelta(float a, float b, float c) {
    float delta = pow(b, 2) -4 * a * c;
    return delta; 
}

void graphPlot(float c, float xl, float xll, float vertice1, float vertice2, float delta) {
    RGBABitmapImageReference *imageReference = CreateRGBABitmapImageReference();

    vector<double> x;
    vector<double> y;
    //parabola pra baixo
    if(a < 0) {
        x = {xl};
        y = {0};
        //gerando ponto entre x' e vertice1 para dar um arredondamento
        //entre x' e vertice1 pois x' sempre vai ser menor que vertice1
        for(float i = xl; i < vertice1; i += 0.01) {
            float firstPart = a * pow(i, 2);
            float middle = b * i;
            float newPointY = firstPart + middle + c;

            x.push_back(i);
            y.push_back(newPointY);
        }
        
        
        x.push_back(vertice1);
        y.push_back(vertice2);

        //Gerando mais pontos, so que agora entre vertice1(começando lá em cima) e xll(xll sendo o sempre o ultimo numero de uma parabola com a < 0)
        for(float i = vertice1; i < xll; i += 0.01) {
            float firstPart = a * pow(i, 2);
            float middle = b * i;
            float newPointY = firstPart + middle + c;

            x.push_back(i);
            y.push_back(newPointY);
            
        }

        x.push_back(xll);
        y.push_back(0);

    } else { // parabola pra cima
        //entre o grafico passar pelo eixo x e nao passar, muda o codigo
        if(xl <= 0 && xll <= 0) {
            //ja  que nao temos o xl e xll pra ajudar tem que usar os pontos x da vertice
            for(float i = vertice1 - 3; i < vertice1 ; i+= 0.01 ) {
                
                float firstPart = a * pow(i, 2);
                float middle = b * i;
                float newPointY = firstPart + middle + c;

                x.push_back(i);
                y.push_back(newPointY);
            }

            
            x.push_back(vertice1);
            y.push_back(vertice2);
           
            
            for(float i = vertice1; i < vertice1 + 3; i+= 0.01) {
                

                float firstPart = a * pow(i, 2);
                float middle = b * i;
                float newPointY = firstPart + middle + c;

                x.push_back(i);
                y.push_back(newPointY);
            }


        } else {
            
            for(float i = -2;i < vertice1; i+= 0.01) {
                float firstPart = a * pow(i, 2);
                float middle = b * i;
                float newPointY = firstPart + middle + c;

                x.push_back(i);
                y.push_back(newPointY);
            }

            x.push_back(vertice1);
            y.push_back(vertice2);

            //provavelmente nao deveria deixar tanta coisa repetida assim, mas ok
            for(float i = vertice1; i < xl + 2; i+= 0.01) {
                float firstPart = a * pow(i, 2);
                float middle = b * i;
                float newPointY = firstPart + middle + c;

                x.push_back(i);
                y.push_back(newPointY);
            }

           

        
        }
        
    }
    
    //algum codigo que eu nao sei oq faz
    DrawScatterPlot(imageReference, 1000, 1000,&x, &y);
    vector<double> *pngData = ConvertToPNG(imageReference->image);
    WriteToFile(pngData, "plot.png");
    DeleteImage(imageReference->image);

    cout << "Plot.png generated\n";
}


int main() {
    cout << "A >> "; cin >> a;
    cout << "B >> "; cin >> b;
    cout << "C >> "; cin >> c;
    cout << "-=-=-=-=-=-=-=-=-=-=-=-\n";

    float delta = calcDelta(a, b, c);
    float xl = 0, xll = 0;
    
    if(a < 0) {
        cout << "The Parabola will open downward\n";
    } else {
        cout << "The Parabola will open upward\n";
    }
    cout << "Delta: "<<delta << endl;
    
        
    if(delta < 0) {
        cout << "X-intercepts: None\n";
        
    } else {
        xl = (-b + sqrt(delta)) / (2 * a);
        xll = (-b - sqrt(delta)) / (2 * a);
    }
    cout << "X' and X'': (" << xl << ",0) (" << xll<< ",0)"<< endl; 


    float vertice1 = -b / (2*a);
    float vertice2 = -delta /(4 * a);
    cout << "Vertex: (" << vertice1 << "," << vertice2 << ")"<< endl;
    graphPlot(c, xl, xll, vertice1, vertice2, delta);

    return 0;
    

}