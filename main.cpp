#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
//Area de definição de cabeçalhos de função
void menuInicial();
//Area das funções
void limpaTela(){
    system("CLS");
}

void iniciaTabuleiro(char tabuleiro[3][3]){
    //Navega por cada posição do tabuleiro e coloca o simbolo de '-'
    for(int lin=0;lin<3;lin++){
        for(int col=0;col<3;col++){
            tabuleiro[lin][col] = '-';
        }
    }
}

void exibeTabuleiro(char tabuleiro[3][3]){
    //Exibindo o tabuleiro com suas linhas e colunas quebrando a linha ao sair do for
    for(int lin = 0; lin < 3; lin++){
        for(int col = 0; col < 3; col++){
            cout << tabuleiro[lin][col];
        }
        cout << "\n";
    }
}

//1 = X Venceu; 2 = O Venceu; 0 = Empate
int confereTabuleiro(char tabuleiro[3][3]){

    int lin, col;
    //Confere se o jogo acabou e todas a linhas
    for(lin = 0; lin < 3; lin++){
        if(tabuleiro[lin][0] == 'X' && (tabuleiro[lin][0] == tabuleiro[lin][1] && tabuleiro[lin][1] == tabuleiro[lin][2])){
            return 1;
        }else if(tabuleiro[lin][0] == 'O' && (tabuleiro[lin][0] == tabuleiro[lin][1] && tabuleiro[lin][1] == tabuleiro[lin][2])){
            return 2;
        }
    }
    //Confere se o jogo acabou e todas as colunas
    for(col=0;col<3;col++){
        if(tabuleiro[0][col] == 'X' && (tabuleiro[0][col] == tabuleiro[1][col] && tabuleiro[1][col] == tabuleiro[2][col])){
            return 1;
        }else if(tabuleiro[lin][0] == 'O' && (tabuleiro[lin][0] == tabuleiro[lin][1] && tabuleiro[lin][1] == tabuleiro[lin][2])){
            return 2;
        }
    }
    //Conferindo a primeira diagonal
    if(tabuleiro[0][0] != '-' && (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2])){
        if(tabuleiro[0][0] == 'X'){
            return 1;
        }else{
            return 2;
        }
    }
    //Conferindo a segunda diagonal
    if(tabuleiro[0][2] != '-' && (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0])){
        if(tabuleiro[0][2] == 'X'){
            return 1;
        }else{
            return 2;
        }
    }

    return 0;

}

void exibeInstrucoes(){
    cout << "\nMapa das posicoes"<<endl;
    cout << " 7 | 8 | 9"<<endl;
    cout << " 4 | 5 | 6"<<endl;
    cout << " 1 | 2 | 3";
}

void jogo(string jogadorUm, string jogadorDois, int pJ1, int pJ2){          //pJ1 e pJ2 = Pontuacao dos jogadores

    ///Variaveis Gerais
    string jogadorAtual;                            //Nome dos jogadores
    char tabuleiro[3][3];                           //Tabuleiro do jogo
    int lin, col;                                   //Auxiliares para o tabuleiro (lin = linha, col = coluna)
    int linJogada, colJogada, posicaoJogada;        //Posicao em que o jogador direciona sua marca
    int estadoJogo = 1;                             //0 = Sem jogo, 1 = Em Jogo
    int turnoJogador;                               //1 = X, 2 = O
    int rodada=1;                                   //Quantas vezes os jogadores jogam no total
    int op;                                         //Opção de reinicio
    bool posicJogada;                       //Verifica se o jogador colocou um marcador no tabuleiro

    //Coloca os tracinhos no tabuleiro para indicar o vazio
    iniciaTabuleiro(tabuleiro);


    do{

        limpaTela();

        cout << "\nRodada: " << rodada <<endl;
        cout << "Placar: \n" << jogadorUm << " : "<< pJ1 << " X " << pJ2 << " : " << jogadorDois <<endl;

        //Exibe o tabuleiro na tela
        exibeTabuleiro(tabuleiro);

        //Exibe qual numero corresponde a qual posicao
        exibeInstrucoes();
        //Atualiza o nome do jogador atual
        if(turnoJogador == 1){
            jogadorAtual = jogadorUm;
        }else{
            jogadorAtual = jogadorDois;
        }

        posicJogada = false;

        //Matriz de posicoes possiveis;
        int posicoes[9][2] = {{2,0}, {2,1}, {2,2}, {1,0}, {1,1}, {1,2}, {0,0}, {0,1}, {0,2}};

        while(posicJogada == false){
            //Lê a jogada desejada
            cout << "\n\n" << jogadorAtual << ", Digite uma posicao conforme o mapa acima: ";
            cin >> posicaoJogada;
            //Passa a linha e coluna de acordo com a matriz de posicoes exibida no mapa
            linJogada = posicoes[posicaoJogada-1][0];
            colJogada = posicoes[posicaoJogada-1][1];

            //Verifica se a posição é vazia
            if(tabuleiro[linJogada][colJogada] == '-'){
                //Conseguiu posicionar um marcador
                posicJogada = true;
                //Verifica de quem é a vez para posicionar o marcador
                if(turnoJogador == 1){

                    tabuleiro[linJogada][colJogada] = 'X';

                    turnoJogador = 2;

                }else{

                    tabuleiro[linJogada][colJogada] = 'O';

                    turnoJogador = 1;

                }
           }

        }

        //Confere se o jogo acabou
        if(confereTabuleiro(tabuleiro) == 1){
            cout << "Jogador X venceu\n"<<endl;
            pJ1++;
            estadoJogo = 0;
        }else if(confereTabuleiro(tabuleiro) == 2){
            cout << "Jogador O venceu\n"<<endl;
            pJ2++;
            estadoJogo = 0;
        }else{
            cout << "Jogo empatado!!!\n"<<endl;
        }

        //Aumenta uma rodada
        rodada++;

    }
    while(rodada < 10 && estadoJogo == 1);

    exibeTabuleiro(tabuleiro);
    cout << "\nFim de jogo"<<endl;
    cout << "\nO que deseja fazer?"<<endl;
    cout << "1 - Continuar Jogando"<<endl;
    cout << "2 - Menu Inicial"<<endl;
    cout << "Qualquer Numero - Sair"<<endl;
    cout << ": ";
    cin >> op;
    if(op == 1){
        jogo(jogadorUm, jogadorDois, pJ1, pJ2);
    }else if(op == 2){
        menuInicial();
    }else{
        cout<<"Obrigado por jogar, ate a proxima :D"<<endl;
    }

}

void exibeSobre(){
    int op;
    ifstream input("Sobre.txt");            //Uma variavel que vai ler o arquivo .txt
    string sobre;                           //Vai receber o .txt e transformar numa variavel
    //Info do jogo
    for(string line; getline(input, line);){
        sobre += line;
    }
    cout << "\n" << sobre <<endl;
    //Um menu caso queira ir para o menu ou sair
    cout << "\nO que deseja fazer?"<<endl;
    cout << "1 - Menu Inicial"<<endl;
    cout << "Qualquer Numero - Sair"<<endl;
    cout << ": ";
    cin >> op;
    if(op == 1){
        menuInicial();
    }else{
        cout<<"Ate a proxima :D"<<endl;
    }

}

void menuInicial(){
    int op = 0;
    string jogadorUm, jogadorDois;          //Lendo dois jogadores
    //Enquanto o jogado não digita uma opção valida, mostra o menu novamente
    while(op < 1 || op > 3){
        limpaTela();
        cout << "=============== J O G O  D A  V E L H A ===============" << endl;
        cout << "1 - Jogar"<<endl;
        cout << "2 - Sobre"<<endl;
        cout << "3 - Sair"<<endl;
        cout << "Escolha uma opcao e tecle ENTER: ";
        //Faz a leitura da opcao
        cin >> op;
        //Faz algo de acordo com a opção escolhida
        switch(op){
            case 1:
                //Inicia o jogo
                //cout << "Jogo iniciado"<<endl;
                cout << "Digite o nome do primeiro jogador: ";
                cin >> jogadorUm;
                cout << "Digite o nome do segundo jogador: ";
                cin >> jogadorDois;
                jogo(jogadorUm, jogadorDois, 0,0);
                break;
            case 2:
                exibeSobre();
                break;
            case 3:
                //Sair do Jogo
                cout << "Ate Mais!!!";
                break;
        }

    }

}


int main()
{
    //A função que mostra o menu inicial
    menuInicial();
    return 0;
}
