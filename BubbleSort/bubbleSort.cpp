#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <math.h>


using namespace std;
vector<int> list(10);


void displayArray(vector<int> list) {
    cout << "[ ";
    for(int i = 0; i < list.size(); i++) {
        cout << list[i] << " " ;
    }
    cout << "]" << flush << "\n";
}

void sleep(int second) {
    this_thread::sleep_for(chrono::seconds(second)); 
}
   

vector<int> bubble(vector<int> list, bool flu) {
    for(int i = 0; i < list.size(); i++) {
        for(int j = 0; j < list.size() - i - 1;j++) {
            int temp = list[j];
            if(list[j] > list[j + 1]) {
                
                list[j] = list[j + 1];
                list[j + 1] = temp;
                if(flu) {
                    displayArray(list);
                    sleep(1);
                }      
            }
            
        }
               
    }
    if(!flu) {
        displayArray(list);
    }    
    return list;
} 


int main() {
    int n;
    cout << "Quantos itens você quer colocar no array? >> ";
    cin >> n;
    list.resize(n);

    for(int i = 0; i < n; i++) {
        cout << "Array[" << i << "] >> ";
        cin >> list[i]; 
        
    }
    string esc;
    bool flu = true;
    
    
    cout << "Você deseja ver o processo?[s/n] >> " ;
    cin >> esc;
    if(esc == "s") {
        flu = true;
    } else {
        flu = false;
    }

    sleep(1);
    cout << "Usando o método Bubble no array >> ";
    displayArray(list);
    sleep(1);
    cout << "------------------\n";
    sleep(1);
    cout << "Utilizando o algoritmo\n";
    bubble(list, flu);
    cout << "\nNúmero de iterações " << pow(list.size(), 2);

}