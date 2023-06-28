#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

// Funcao para converter um endereco IP em um vetor de inteiros
vector<int> dividirIP(const string& ip) {
    vector<int> partes;
    size_t inicio = 0;
    size_t fim = ip.find('.');

    while (fim != string::npos) {
        partes.push_back(stoi(ip.substr(inicio, fim - inicio)));
        inicio = fim + 1;
        fim = ip.find('.', inicio);
    }

    partes.push_back(stoi(ip.substr(inicio, fim)));

    return partes;
}

// Funcao para converter um vetor de inteiros em um endereco IP
string juntarIP(const vector<int>& partes) {
    string ip;

    for (size_t i = 0; i < partes.size(); ++i) {
        ip += to_string(partes[i]);

        if (i != partes.size() - 1) {
            ip += ".";
        }
    }

    return ip;
}

// Funcao para calcular a mascara de sub-rede com base no prefixo
string calcularMascaraSubrede(int prefixo) {
    vector<int> partesMascara(4, 0);

    for (int i = 0; i < prefixo; ++i) {
        partesMascara[i / 8] |= (1 << (7 - (i % 8)));
    }

    return juntarIP(partesMascara);
}

// Funcao para calcular o endereco de rede com base no endereco IP e na mascara de sub-rede
string calcularEnderecoRede(const string& ip, const string& mascaraSubrede) {
    vector<int> partesIP = dividirIP(ip);
    vector<int> partesMascara = dividirIP(mascaraSubrede);
    vector<int> partesRede(4, 0);

    for (size_t i = 0; i < partesIP.size(); ++i) {
        partesRede[i] = partesIP[i] & partesMascara[i];
    }

    return juntarIP(partesRede);
}

// Funcao para calcular o numero de hosts disponiveis com base no prefixo
int calcularHostsDisponiveis(int prefixo) {
    return pow(2, 32 - prefixo) - 2;
}

int main() {
    string enderecoIP;
    int prefixo;

    // Solicita ao usuario o endereco IP e o prefixo
    cout << "Digite o endereco IP (xxx.xxx.xxx.xxx): ";
    cin >> enderecoIP;
    cout << "Digite o CIDR (0-32): ";
    cin >> prefixo;

    // Calcula a mascara de sub-rede
    string mascaraSubrede = calcularMascaraSubrede(prefixo);

    // Calcula o endereco de rede
    string enderecoRede = calcularEnderecoRede(enderecoIP, mascaraSubrede);

    // Calcula o numero de hosts disponiveis
    int hostsDisponiveis = calcularHostsDisponiveis(prefixo);

    // Imprime os resultados
    cout << "Mascara de Sub-rede: " << mascaraSubrede << endl;
    cout << "Endereco de Rede: " << enderecoRede << endl;
    cout << "Numero de Hosts Disponiveis: " << hostsDisponiveis << endl;

    return 0;
}
