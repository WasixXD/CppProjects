#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <string>


#define verde "\033[32m"
#define vermelho "\033[31m"
#define reset "\033[0m"


void sleep(int second) {
    std::this_thread::sleep_for(std::chrono::seconds(second)); 
}

int logar() {
    std::string nome, senha, registroNome, registroSenha;

    std::cout << "Nome >> "; std::cin >> nome;
    std::cout << "Senha >> "; std::cin >> senha;

    std::ifstream arquivo;

    arquivo.open(nome + ".txt");
    if(arquivo.is_open()) {
        std::getline(arquivo, registroNome);
        std::getline(arquivo, registroSenha);
        
        if(registroNome == nome && registroSenha == senha) {
            std::cout << verde <<"Este usuario existe e esta logado como " << nome << reset << "\n";
            sleep(3);
        }

    } else {
        std::cout << vermelho <<"Login nao encontrado, crie um registro antes de logar" << reset << "\n";
        sleep(2);
        return 0;
    }
    return 0;

    
}


int registrar() {
    std::string nome, senha;

    //Pegando o nome e senha
    std::cout << "Nome >> "; std::cin >> nome;
    std::cout << "Senha >> "; std::cin >> senha;

    //abrindo e colocando as informações dentro dele
    std::ofstream login;
    login.open(nome + ".txt");
    login << nome <<std::endl << senha;
    login.close();


    std::cout << verde << "Registro Realizado!" << reset << "\n";
    sleep(2);
    return 0;

}


int menu() {
    int choice;
    while(true) {
        std::cout << "1 - Registrar | 2 - Logar | 3 - Sair\n>> ";
        std::cin >> choice;
        if(choice == 1 || choice == 2 || choice == 3) {
            return choice;
        } 
        std::cout << vermelho <<"Comando nao identificado" << reset << "\n";
    }
    return 0;
}

int main() {
    
    while(true) {
        std::system("clear");
        int choice = menu();
        if(choice == 1) {
            registrar();
        } else if(choice == 2) {
            logar();
        } else if(choice == 3) {
            break;
        } 
    }
    
    
    
}