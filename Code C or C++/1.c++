#include <iostream>
#include <string>
#include <vector>
#include <cctype> // Para usar toupper()
using namespace std;

class Pessoa {
public:
    float altura;
    int idade;
    string nome;
    string cor_do_cabelo;

    Pessoa(float a, int b, string c, string d) {
        altura = a;
        idade = b;
        nome = c;
        cor_do_cabelo = d;
    }

    void exibir() const {
        cout << "Nome: " << nome << ", Idade: " << idade 
             << ", Altura: " << altura << "m, Cabelo: " << cor_do_cabelo << endl;
    }
};


void Cadastrar(vector<Pessoa>& lista) { 
    float altura;
    int idade;
    string nome;
    string cor_do_cabelo;

    cout << "Nome: ";
    cin.ignore();  // Ignorar buffer do enter anterior
    getline(cin, nome);
    cout << "Altura: ";
    cin >> altura;
    cout << "Idade: ";
    cin >> idade;
    cout << "Cor do cabelo: ";
    cin.ignore();
    getline(cin, cor_do_cabelo);

    lista.push_back(Pessoa(altura, idade, nome, cor_do_cabelo));
    cout << "Cadastro bem-sucedido!\n";
}

// Função para exibir os cadastrados
void exibir(const vector<Pessoa>& lista) {
    cout << "\nLista de Pessoas Cadastradas:\n";
    if (lista.empty()) {
        cout << "Nenhuma pessoa cadastrada.\n";
    } else {
        for (const auto& p : lista) {
            p.exibir();
        }
    }
}

// Função para gerenciar cadastro
void menu_cadastrar(vector<Pessoa>& lista) {
    char resposta;
    do {
        cout << "\nGostaria de se cadastrar? (S/N): ";
        cin >> resposta;
        resposta = toupper(resposta);

        while (resposta != 'S' && resposta != 'N') {
            cout << "Resposta invalida. Digite S ou N: ";
            cin >> resposta;
            resposta = toupper(resposta);
        }

        if (resposta == 'S') {
            Cadastrar(lista);
        }

        cout << "Cadastrar mais alguem? (S/N): ";
        cin >> resposta;
        resposta = toupper(resposta);

    } while (resposta == 'S');
    cout << "Voltando ao menu...";
}

// Função principal do menu
void Menu(vector<Pessoa>& lista) {
    int opcao;
    do {
        cout << "\n=== MENU ===\n";
        cout << "0 - Sair\n";
        cout << "1 - Cadastrar\n";
        cout << "2 - Exibir\n";
        cout << "Escolha uma opcao: ";
        cin >> opcao;

        switch (opcao) {
        case 0:
            cout << "Saindo...\n";
            return;
        case 1:
            menu_cadastrar(lista);
            break;
        case 2:
            exibir(lista);
            break;
        default:
            cout << "Opção invalida! Tente novamente.\n";
        }
    } while (opcao != 0);
}

// Função principal
int main() {
    vector<Pessoa> lista;
    Menu(lista);
    return 0;
}
