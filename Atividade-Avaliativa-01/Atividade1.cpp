#include <chrono>
#include <thread>
#include <vector>
#include <iostream>
#include <conio.h>
#include <bits/stdc++.h>
#include <string>

using namespace std;
using namespace std::this_thread;     // Para o comando sleep_for
using namespace std::chrono_literals; // ns, us, ms, s, h, etc.
using std::chrono::system_clock;

char stringficador(int num){//Essa função converte numeros inteiros em caracteres.
    if (num < 10){
            return static_cast<char>('0' + num); 
            //a funcao acima converte um inteiro para o seu caractere equivalente, seguindo a tabela ASCII...
            //Digamos que num == 3. O 3° elemento da tabela ASCII é um caractere chamado 'STX'. Então, como que fazemos para
            //que a função solte o caractere '3', que é o 48° elemento da tabela? Para isso, nós somamos 3 ao caractere '0'.
            //Na tabela ASCII, os numeros estao posicionados de forma consecutiva, e '0' está na posição 48.
            //Logo, o caractere '3' está na posição 48 + 3 = 51. Ao somar '0' + num (lembrando que num == 3),
            //o resultado é 51, e a função static_cast<char> retorna o caractere '3'.
        }
    switch (num){ //Aqui vai pegar numeros maiores que 10 e retornar suas letras equivalentes
        case 10:
            return 'A';
            break;
        case 11:
            return 'B';
            break;
        case 12:
            return 'C';
            break;
        case 13:
            return 'D';
            break;
        case 14:
            return 'E';
            break;
        case 15:
            return 'F';
            break;
        default:
        cout << "\nERRO ERRO\n";
        abort();
    }
}

string ex01(int N, int B){
    int r;//r - resto; N - numero convertido; B - nova base; 

    int q, signal = 0; //q - quociente; signal - indica o sinal do numero convertido. Interferindo na função 'convertido.insert();'

    string convertido; //Resultado final da conversao

    if(N < 0){
        N = -N;
        convertido += '-'; //Se o numero for negativo, isso adiciona um '-' no começo pra ficar boonitinho
        cout << "Olha aolla " << convertido << endl;
        signal = 1;
    }
    //o loop abaixo fará as divisões sucessivas, e calculará o resto para definir a conversao de bases.
    do{
        r = N % B; //calcula o resto da divisao
        cout << "Olha o resto " << r << endl; 
        q = N / B; //divide as partes inteiras de N e B
        cout << "Olha o quociente " << q << endl;
        convertido.insert(signal, 1, stringficador(r)); //Converte inteiro pra caractere, e joga ele no resultado final
        //Se o numero for positivo, signal será == 0, então os caracteres novos serão posicionados na primeira casa da string
        //Se forem negativos, signal == 1, e novos caracteres serão posicionados na segunda casas da string
        //Mas por quê? É que nesse caso, a primeira casa estará ocupada pelo símbolo de negativo, - 
        N = q; //Numero a ser dividido recebe o quociente da ultima divisao;
        cout << "Olha o convertido " << convertido << endl << endl;
    }while(N != 0);

    return convertido;
}

string ex02(double N, int B){
    double r, q = 0;//r - resultado; q - contador (while); N - numero convertido; 

    string convertido; //Resultado final da conversao

    if(N < 0){
        N = -N;
        convertido += '-'; //Se o numero for negativo, isso adiciona um '-' no começo pra ficar bonitinho
        cout << "Olha aolla " << convertido << endl;
    }
        convertido += "0.";

    //o loop abaixo fará as multiplicações sucessivas.
    do{
        q++;
        r = N * B; //calcula o resultado da multiplicacao
        cout << "Olha o resultado A " << r << endl; 
        convertido += stringficador(static_cast<int>(r)); //Converte inteiro pra caractere, e joga ele no resultado final 
        N = r - static_cast<int>(r);
        cout << "Olha o resultado B " << r << endl; 

        cout << "Olha o convertido " << convertido << endl << endl;
    }while(N != 0.0 && q < 50); //calcula ate 50 casas decimais
    
    return convertido;
}

string ex03(){
    double num = 374.526; // numero a ser convertido
    string sint, sfloat, convertido;
    sint = ex01(static_cast<int>(num), 5); // obtem a parte inteira
    sfloat = ex02(num - static_cast<int>(num), 5); // obtem a parte "decimal"
    sfloat = sfloat.substr(1); //faz uma gambiarra pra tirar o 0 à esquerda da parte "decimal"
    convertido = sint + sfloat; // Concatena as duas
    return convertido; //retorna o resultado
}

//minhaString.insert(0, 1, meuCaractere);
//0 - Posição, 1 - Quantas vezes, meucaractere - o que vai ser inerido
//usaremos convertido.insert(signal, 1, var);
//Se for positivo, signal sera 0.
//Se for negativo, signal sera 1, pois haverá um '-' na posicao 0.

int main(){
    int Ni, B = 0, op = 0;
    float Nf = 18;
    string convertido;
    while(op <= 0 || op >= 4){
        system("cls");
        cout << "==-==---=-=---==-== Super Conversor de Bases ==-==---=-=---==-==" << endl;
        cout << "==--== Qual exercicio voce deseja executar?\n1 - ExA\n2 - ExB\n3 - ExC\nR: ";
        cin >> op;
        switch(op){
            case 1:
                //abaixo, o usuário irá inserir os valores a serem convertidos
                system("cls");
                cout << "==-==---=-=---==-== Super Conversor de Bases ==-==---=-=---==-==" << endl;
                cout << "==--== Insira o numero inteiro em base 10 que voce deseja converter:\nR: ";
                cin >> Ni;
                while(B > 16 || B < 1){
                    cout << "\n==--== Insira a base a qual o numero sera convertido (de 1 a 16):\nR: ";
                    cin >> B;        
                }
                convertido = ex01(Ni, B); //Chama a funcao de computa a conversao
                cout << endl << "Resultado final:: " << convertido << endl; //Joga o resultado na tela
            break;
            case 2:
                //abaixo, o usuário irá inserir os valores a serem convertidos
                system("cls");
                while(Nf > 1.0 || Nf < -1.0){
                    system("cls");
                    cout << "==-==---=-=---==-== Super Conversor de Bases ==-==---=-=---==-==" << endl;
                    cout << "==--== Insira um numero real, entre -1 e 1, que voce deseja converter:\nR: ";
                    cin >> Nf;
                }
                while(B > 16 || B < 1){
                    system("cls");
                    cout << "\n==--== Insira a base a qual o numero sera convertido (de 1 a 16):\nR: ";
                    cin >> B;
                }
                convertido = ex02(Nf, B); //Chama a funcao que computa a conversao
                cout << endl << "Resultado final:: " << convertido << endl; // escreve o resultado na tela
            break;
            case 3:
                convertido = ex03(); // Chama a função ex03
                cout << endl << "Resultado final:: " << convertido << endl; // Escreve o resultado
            break;
            default:
            cout << endl << "-=-=- Opcao invalida!!!" << endl;
            sleep_for(2s);
        }    
    }
}

