#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <cstdio>
#include <vector>
#include <chrono>
#include <thread>

#define verde "\033[32m"
#define vermelho "\033[31m"
#define reset "\033[0m"



void sleep(int second) {
    std::this_thread::sleep_for(std::chrono::seconds(second)); 
}

std::string dateNow() {
    std::time_t now = std::time(0);
    std::string date = std::ctime(&now);
    return date;
}

int menu() {
    int action;
    while(true) {
        std::cout << "Qual ação você deseja realizar?\n1 - Adicionar cliente | 2 - Atualizar cliente | 3 - Deletar cliente | 4 - Mostrar clientes\n5 - Sair\n>> "; 
        std::cin >> action;

        if(action == 1 || action == 2 || action == 3 || action == 4 || action == 5) {
            return action;
        }

        std::cout << vermelho<< "Opção desconhecida\n"<< reset;

    }
    return 0;

}

int add() {
    std::string nome;
    float deve;

    std::cout << "Qual o nome da pessoa >> ";std::cin >> nome;
    std::cout << "Quanto ela deve >> ";std::cin >> deve;


    std::ofstream arquivo;
    arquivo.open(nome + ".txt");

    //pegar a data atual
    
    std::string date = dateNow();

    //adicionar no arquivo
    arquivo << date << nome << "\n" << deve << "\n" << "false";

    arquivo.close();


    arquivo.open("nome.txt", std::ios::app);
    arquivo << nome << "\n";
    arquivo.close();
    sleep(1);
    std::cout << verde << "Cliente adicionado\n" << reset;
    sleep(1);
    std::system("clear");
    return 0;
}

int update() {
    std::string nome;
    std::ifstream arquivo;
    bool trocar = false;

    std::cout << "Qual o nome da pessoa? >> "; std::cin >> nome;
    arquivo.open(nome + ".txt");
    if(arquivo.is_open()) {

        std::ofstream update;
        std::string newName;
        std::cout << "Digite o novo nome >> ";std::cin >> newName;

        int newValor;
        std::cout << "Digite o novo valor >> ";std::cin >> newValor;

        std::string choice;
        std::string trocar = "false";
        std::cout << "Foi pago?[s/n] >> ";std::cin >> choice;
        if(choice == "s") {
            trocar = "true";
        } else {
            trocar= "false";
        }
        update.open(nome + ".txt");
        std::string date= dateNow();
        update << date << newName << "\n" << newValor << "\n" << trocar;
        update.close();

        std::cout << verde <<"Cliente atualizado com sucesso\n" << reset;
    
       
    } else {
        std::cout <<vermelho << "Arquivo não encontrado\n" << reset;
    
       
    }
    arquivo.close();
    sleep(2);
    std::system("clear");
    return 0;
}

int Delete() {
    char nome[30];
    std::vector<std::string> newNames;
    std::cout << "Diga o nome do Cliente + .txt a ser deletado >> "; std::cin >> nome;
    
    
    //deletar o nome da lista
    std::ifstream arquivo;
    std::string name(nome);
    std::string compare = name.substr(0, name.size() - 4);
    arquivo.open("nome.txt");
    //olha no arquivo nomes.txt pelo nome da pessoa que quer se deletada
    if(arquivo.is_open()) {
        std::string linhas;
        while(std::getline(arquivo, linhas)) {
            //se nao for a pessoa adiciona nas outras que ainda estao
            if(linhas != compare) {
                newNames.push_back(linhas);
            }
        }
        
        std::ofstream add;
        //atualiza a lista
        add.open("nome.txt");
        for(int i =0; i < newNames.size(); i++) {
            add << newNames[i] << "\n";
        }
        add.close();
        std::remove(nome);

        std::cout << verde << "Cliente removido\n" << reset;
        
    } else {
        std::cout << vermelho << "Cliente não encontrado\n" << reset; 
    }

    sleep(2);
    std::system("clear");

    return 0;
}

int show() {
    //pegar o nome de todos os arquivos
    std::ifstream arquivo;
    std::string line;
    std::vector<std::string> nomes;
    std::vector<std::string> labels = {"Data", "Nome", "Valor a pagar", "Já pagou"};
    int x = 0;
    //passa pela lista de nomes
    arquivo.open("nome.txt");
    if(arquivo.is_open()) {
        //adiciona a pessoa pra ser mostrada
        while(std::getline(arquivo, line)) {
            nomes.push_back(line);
        }

        std::ifstream cliente;
        //pra cada pessoa no vetor nomes
        for(int i = 0; i < nomes.size(); i++) {
            //abre o arquivo com nome dela
            cliente.open(nomes[i] + ".txt");
            
            if(cliente.is_open()) {
                std::string cont;
                //mostra as informações
                while(std::getline(cliente, cont)) {
                    std::cout <<  labels[x] << ": " << cont << "\n";
                    x++;
                }
            }
            std::cout << "\n";
            x = 0;
            cliente.close();
            sleep(1);
        }
    }

    return 0;
}


int main() {

    while(true) {

        int action = menu();
    
        switch(action) {
        
            case 1:
                add();
                break;
            case 2:
                update();
                break;
            case 3:
                Delete();
                break;
            case 4:
                show();
                break;
            case 5:
                std::cout << "Adeus...";
                sleep(2);
                return 0;
            default:
                std::cout << "saindo";
                return 0;
        }

       
    }
    


}