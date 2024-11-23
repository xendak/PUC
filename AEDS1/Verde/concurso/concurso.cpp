#include <iomanip>
#include <iostream>

#define MAX 100
int TAM = 0;

class Candidato {
    /*std::string nome;*/
    std::string nome;
    double nota;

    public:
        Candidato();
        ~Candidato();
        std::string get_nome();
        double get_nota();
        void set_nome(std::string nome);
        void set_nota(double nota);
};

Candidato::~Candidato() {
    delete this;
}

void Candidato::set_nome(std::string nome) {
    this->nome = nome;
}

void Candidato::set_nota(double nota) {
    this->nota = nota;
}

std::string Candidato::get_nome() {
    return this->nome;
}
double Candidato::get_nota() {
    return this->nota;
}


Candidato* registrar_candidatos();
double media_candidatos(Candidato* c);
void print_candidatos_media(Candidato* c, double media);

int main() {
    Candidato* candidatos = registrar_candidatos();
    double media = media_candidatos(candidatos);
    print_candidatos_media(candidatos, media);
    free(candidatos);
    return 0;
}

double media_candidatos(Candidato* c) {
    double media = 0.0f;
    for (int i = 0; i < TAM; i++)
        media += c[i].get_nota();
    return media / TAM;
}

void print_candidatos_media(Candidato* c, double media) {
    std::fflush(stdin);
    std::fflush(stdout);
    for (int i = 0; i < TAM; i++) {
        if (c[i].get_nota() >= media) {
            std::cout << c[i].get_nome() << " " << c[i].get_nota() << std::endl;
            /*std::cout << "\"" << c[i].get_nome() << "\"" << " " << c[i].get_nota();*/
            /*printf("\n");*/
        }
    }
}

Candidato* registrar_candidatos() {
        /* EU tive que tentar usar isso aqui pra fazer o site aceitar, deixei comentaado junto do outros, pois o programa funciona pra mim
         * mas nao quer validar no site.
         */
        /*int uselessgarbagefromsite;*/
        /*std::cin >> uselessgarbagefromsite;*/
        /*std::cin.ignore();*/
    std::cin >> TAM;
        /*std::cin.ignore();*/
        /*std::cin >> uselessgarbagefromsite;*/
        /*std::cin.ignore();*/

    Candidato* c = (Candidato *) std::malloc(sizeof(Candidato) * MAX);
    for (int i = 0; i < TAM; i++) {
        std::string nome;
        double nota;

        std::cin >> nome;
        std::cin >> nota;

        /*std::string linha;*/
        /*std::getline(std::cin, linha);*/
        /*std::cin.ignore();*/
        /*std::istringstream ss(linha);*/
        /*std::string nome;*/
        /*double nota;*/
        /**/
        /*ss >> std::quoted(nome) >> nota; */
        /**/

        c[i].set_nome(nome);
        c[i].set_nota(nota);
    }
    return c;
}
