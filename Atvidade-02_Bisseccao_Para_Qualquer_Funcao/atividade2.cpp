#include <thread>
#include <iostream>
#include <conio.h>
#include <bits/stdc++.h>

using namespace std;

//Bissecção: ponto, dentro de um intervalo [a, b], aonde uma função f(x) = 0
    //Ex:   f(x) = X^2 - 17,   [a, b] = [4, 5]
    //      Precisao E = 10^(-8), N° max de iterações N* = 1000.
        //Aqui fazemos um loop calculando o ponto médio entre a e b...
            //vamos calculando os pontos médios ate chegar na intersecção entre a função e o eixo y.
            //Como descobrimos quando chegamos nessaintersecção? Simples! 
                //Nós temos A precisão E, que é um numero tipo 0,0000...01
                //No ponto de intersecção, y = 0.
                //Quando mais os pontos médios se aproximarem do resultado esperado, mais nós nos aproximaremos de 0.
                    //Por consequência, mais nós nos aproximaremos de E (a precisão)!
                //Calculamos os pontos medios como p = (a+b)/2
                    //Mas, aparentemente, p = a + (b-a)/2 vai gastar menos processamento.
                //Se |f(p)| < E // Se o modulo do ponto medio for menor que a precisao //, então nós chegamos na solução!!!
                //Se não, então substituiremos 'a' ou 'b' por 'p'. Por que? Para diminuirmos o intervalo sendo analisado.
                    //Como sabemos qual dos dois substituir por 'p'? (em outras palavras, se o novo intervalo será [a, p] ou [p, b])
                        //Para isso, basta multiplicar f(a) * f(p)!
                            //Se f(a) * f(p) > 0,   então, a = p
                            //                      senao, b = p
                            //Tambem daria pra fazer isso com f(b) * f(p), a logica seria a mesma.
                                //Caso nao tenha entendido, se f(x) * f(p) for < 0, entao eles tem sinais opostos, e a intersecção vai necessariamente entar contida num intervalo [a, b] onde f(a) e f(b) possuem sinais opostos.
                        //Agora repetimos o processo N* vezes! (ou ate chegarmos na precisão desejada!)

    //Nota: primeiro calculamos f(a) e f(b). Fazemos isso para:
        //Saber se a intersecção está exatamente em 'a' ou 'b'.
        //Saber se eles possuem sinais iguais.
            //Se eles possuírem sinais iguais, então a intersecção não está nesse intervalo!

    //Nota2: Podemos usar isso para calcular a raiz quadrada de qualquer numero! 

float fx(float a, int b, float c, float x){ //Essa função apenas calcula o valor de f(x), aonde f(X) = aX^b + c
    float resultado = 1.0; //Para o caso de b == c == 0
    for(int i = 0; i < b; i++){//Multiplicações sucessivas, vai calcular o x^b
        resultado = resultado * x;
    }
    resultado = resultado * a;
    resultado = resultado + c;

    //cout << "\nResulta em " << resultado << endl;
    return resultado;
}

int analiseintervalo(float aIntervalo,float bIntervalo,float aFunc, int bFunc, float cFunc){ 
//    f(X) = aX^b + c                   [a, b]
//      ^    ^  ^   ^                    ^  ^
//   a/bInt  aF bF  cF                  aI  bI

//Essa função vai calcular o valor de y das extremidades do intervalo, multiplicá-los, e retornar:
//                                                0 caso o resultado for positivo
//                                                caso o resultado for negativo: (normalmente esperamos esse resultado)
//                                                1 caso 'a' < 0 e 'b' > 0;
//                                                2 caso 'a' > 0 e 'b' < 0
//                                                3 caso 'a' for a raiz
//                                                4 caso 'b' for a raiz
float a, b;
    a = fx(aFunc, bFunc, cFunc, aIntervalo);
    if(a == 0.0){
        return 3;
    }
    b = fx(aFunc, bFunc, cFunc, bIntervalo);
    if(b == 0.0){
        return 4;
    }

    if(a < 0 && b > 0){
        return 1;
    }else if(a > 0 && b < 0){
        return 2;
    }
    
    return 0;
}

double calculaprecisao(int Eprecisao){ //retorno == 10^(-Eprecisao)
//Esta função simplesmente converte o valor de precisao inserido pelo usuario [10^(-x)] em um numero real [0,000...01]
    double d = 1.0;

    for(int i = 0; i < Eprecisao; i++){
        d = d * 1/10;
    }
    return d;
}

float fy(){
    return 0;
}


int main(){
   float aFunc, cFunc, aIntervalo, bIntervalo, mIntervalo;
   double precisao, resultado = 0;
   int Eprecisao, No, op = 0, bFunc;
    
    // Abaixo, o usuário será capaz de inserir os valores de 'a', 'b' e 'c' para a função genérica f(X) = aX^b + c
    do{
        cout << "\n=--=--= Dada a Funcao:\n\tf(x) = aX^b + c\n\n=-= Insira 'a', 'b' e 'c'." << endl;
        cout << "Insira 'a' (numero real)\n-R: ";
        cin  >> aFunc;
        cout << "Insira 'b' (numero inteiro)\n-R: ";
        cin  >> bFunc;
        cout << "Insira 'c' (numero real)\n-R: ";
        cin  >> cFunc;

        do{
            cout << "\n=-= A funcao a ser avaliada eh\n\tf(x) = " << aFunc << "X^(" << bFunc << ") + " << cFunc << endl;
            cout << "=- Isso esta correto?\n[1] Sim\n[0] Nao\n-R: ";
            cin  >> op;
            if(op != 1 && op != 0){
                cout << endl << "Opcao invalida! Tente de novo" << endl;
            }
        }while(op != 1 && op != 0);
    }while(op != 1);

    // Abaixo, o usuário irá definir a precisão e o número máximo de iterações a serem calculados
    do{
        cout << endl << "=--=--= O valor de precisao eh notado como E = 10^(-x);" << endl;
        cout << "=-= Insira o valor de x (numero inteiro, menor que 318)\n-R: "; 
        //REVISAR ESSE LIMITE DEPOIS
        cin  >> Eprecisao;

        No = 1000;
        do{
            cout << "\n=--= Agora, insira o numero maximo de iteracoes que serao calculadas, caso a interseccao exata nao seja encontrada (numero inteiro positivo diferente de 0)\n-R: ";
            cin  >>  No;
            if(No < 0){
                cout << endl << "-=- O numero que voce inseriu eh menor que 1! Tente de novo." << endl;
            }
        }while(No < 1);
        precisao = calculaprecisao(Eprecisao);
        do{

            cout << "\n\n=-= A precisao eh E = 10^(-" << Eprecisao << "), ou " << precisao << endl;
            //printf("\n %lf \n", (precisao * 100000000));
            cout << "=-= Serao calculadas " << No << " iteracoes" << endl;
            cout << "\n=- Isso esta certo?\n[1] Sim\n[0] Nao\n-R: ";
            cin  >> op;
            if(op != 1 && op != 0){
                cout << endl << "\t-- Opcao invalida! Tente de novo --" << endl;
            }
        }while(op != 1 && op != 0);
    }while(op != 1);

    // Por fim, o usuário vai decidir o intervalo a ser analisado! Caso o algoritmo identifique
    // que o intervalo é inválido, ele vai pedir ao usuário se ele realmente deseja continuar
    do{
        do{
            cout << "\n\n\n=--=--= Por fim, Faremos nosso calculo a partir de um intervalo [a, b];" << endl;
            cout << "\n=--= Insira o valor de 'a' (numero real)\n-R: ";
            cin  >> aIntervalo;
            cout << "=--= Insira o valor de 'b' (numero real)\n-R: ";
            cin  >> bIntervalo;

            do{
                cout << "\n\n=-= O intervalo eh [a, b] = [" << aIntervalo << ", " << bIntervalo << "]" << endl;
                cout << "\n=- Isso esta certo?\n[1] Sim\n[0] Nao\n-R: ";
                cin  >> op;
                if(op != 1 && op != 0){
                    cout << endl << "\t-- Opcao invalida! Tente de novo --" << endl;
                }
            }while(op != 1 && op != 0);
        }while(op != 1);
        
        cout << "analiseintervalo inicial " << analiseintervalo(aIntervalo, bIntervalo, aFunc, bFunc, cFunc) << endl;
        
        if(analiseintervalo(aIntervalo, bIntervalo, aFunc, bFunc, cFunc) == 0){ 
            // Aqui ele vai tentar prever se y=0 está contido no intervalo
            // Porém, ele pode resultar num falso positivo.
            //      Isso acontece quando o intervalo inserido é muito amplo
            
            do{
                cout << endl << "-=--=- Foi detectado que o y = 0 pode nao estar contido dentro do intervalo!\n=--- Deseja continuar mesmo assim?\n=--- (lembrete: isso pode ser um falso positivo)\n[1] Sim\n[0] Nao\n-R: " << endl;
                cin  >> op;
                if(op != 1 && op != 0){
                    cout << endl << "\t-- Opcao invalida! Tente de novo --" << endl;
                }
            }while(op != 1 && op != 0);
        }
        
    }while(op != 1);
    
    if(aIntervalo > bIntervalo){ //Isso aqui serve para garantir que B seja maior que A
        mIntervalo = bIntervalo;
        bIntervalo = aIntervalo;
        aIntervalo = mIntervalo;
    }
    
//precisao
//fx(float a, int b, float c, float x)
//analiseintervalo(float aIntervalo,float bIntervalo,float aFunc, int bFunc, float cFunc)
//cout << "Comecouu" << endl;
int i;
    for(i = 0; i < No; i++){ //op = numero de iterações, escolhido pelo usuário

    //cout << "2" << endl;
        //Primeiro, vamos ver se um dos limites é a raiz
        op = analiseintervalo(aIntervalo, bIntervalo, aFunc, bFunc, cFunc);

        mIntervalo = aIntervalo + (bIntervalo - aIntervalo)/2;
        resultado = fx(aFunc, bFunc, cFunc, mIntervalo);

        //cout << "3" << endl;



        //cout << "6" << endl;
        switch(op){
            case 0: //Resultado positivo

            break;
            case 1: //a = negativo; b = positivo (fazemos o ponto medio)
            //p = a + (b-a)/2
            //cout << "10" << endl;
                if(resultado > 0){
                   // cout << "11" << endl;
                    bIntervalo = mIntervalo;
                }else{
                    //cout << "12" << endl;
                    aIntervalo = mIntervalo;
                }
            break;
            case 2: //a = positivo; b = negativo (fazemos o ponto medio)
            //p = a + (b-a)/2
                //cout << "20" << endl;
                if(resultado < 0){
                    //cout << "21" << endl;
                    bIntervalo = mIntervalo;
                }else{
                    //cout << "22" << endl;
                    aIntervalo = mIntervalo;
                }
            break;
            case 3: //'a' é a raiz
            //cout << "30" << endl;
                mIntervalo = aIntervalo;
                i = No + 2;
            break;
            case 4: //'b' é a raiz
            //cout << "40" << endl;
                mIntervalo = bIntervalo;
                i = No + 2;
            break;
            default: //Caso 'op' nao tenha nenhum dos valores acima. Isso nunca deve acontecer...
                cout << endl << endl << "ATENCAO! Um erro desconhecido aconteceu!" << endl;
                exit(1);
            break;
        }

        ////////////////
                if(resultado < 0){ //Tiramos modulo
            resultado = resultado * (-1);

            //cout << "4" << endl;

        }
        if(resultado <= precisao){
            cout << "\n\n==-=-=-== Resultado calculado!" << endl;
            cout << "==-=-- f(" << mIntervalo << ") = " << resultado << endl;
            cout << "==-=-- Valores dentro da precisao inserida!";
            op = 0;
            i = No + 2;

            //cout << "5" << endl;
        }
        /////////////////
        //cout << "100" << endl;
    }
    if(i == No){
        cout << "\n\n==-=-=-== Numero maximo de iteracoes alcancado!" << endl;
            cout << "==-=-- f(" << mIntervalo << ") = " << resultado << endl;
            cout << "==-=-- Valores fora da precisao inserida!";
    }
}
