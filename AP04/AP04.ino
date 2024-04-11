const int BUFFER_SIZE = 500; // Tamanho do buffer de leitura
char buffer[BUFFER_SIZE];    // Buffer para armazenar a entrada
String comandos[3];          // Vetor para armazenar os comandos

int led10 = 10;
int led11 = 11;
int led12 = 12;
int led13 = 13;

void setup()
{
    Serial.begin(115200);
    pinMode(led10, OUTPUT);
    pinMode(led11, OUTPUT);
    pinMode(led12, OUTPUT);
    pinMode(led13, OUTPUT);
}

void loop()
{
    if (Serial.available() > 0)
    {

        String memoriaInteira = Serial.readString();

        memoriaInteira += " ";

        char temp[memoriaInteira.length()];
        memoriaInteira.toCharArray(temp, memoriaInteira.length());

        int instrucoesQuant = 0;

        for (int i = 0; i < strlen(temp); i++)
        {
            if (temp[i] == ' ')
            {
                instrucoesQuant++;
            }
        }
        instrucoesQuant++;

        String vetorInstrucoes[instrucoesQuant];
        String vI[4];

        char *ptr = strtok(temp, " ");
        int j = 0;

        while (ptr != NULL)
        {
            vetorInstrucoes[j++] = String(ptr);
            ptr = strtok(NULL, " ");
        }


        vI[0] = "4";
        vI[1] = "";
        vI[2] = "";
        vI[3] = "";

        Serial.println("Programa comecando...");

        for (int k = 0; k < instrucoesQuant; k++)
        {   

            printValores(vI, memoriaInteira);
            vI[0] = String(k + 5);

            String X = conversorBinario(vetorInstrucoes[k].charAt(0));
            String Y = conversorBinario(vetorInstrucoes[k].charAt(1));
            String Z = conversorBinario(vetorInstrucoes[k].charAt(2));
            String resp;

            
            controleLed(conversorBinario(vI[1].charAt(0)));

            switch (vetorInstrucoes[k].charAt(2))
            {
            // B'
            case '0':
                resp = portaNot(Y);

                resp = binarioParaHexadecimal(resp);
                vI[1] = resp;
                break;
            // (A'.B)'
            case '1':
                X = portaNot(X);
                resp = portaAnd(X, Y);
                resp = portaNot(resp);
                resp = binarioParaHexadecimal(resp);
                vI[1] = resp;
                break;
            // A'.B
            case '2':
                X = portaNot(X);
                resp = portaAnd(X, Y);
                resp = binarioParaHexadecimal(resp);
                vI[1] = resp;
                break;
            // 0 Logico
            case '3':
                resp = zeroLogico(X);
                resp = binarioParaHexadecimal(resp);
                vI[1] = resp;
                break;
            // (A.B)'
            case '4':
                resp = portaAnd(X, Y);
                resp = portaNot(resp);
                resp = binarioParaHexadecimal(resp);
                vI[1] = resp;
                break;
            // A'
            case '5':
                resp = portaNot(X);
                resp = binarioParaHexadecimal(resp);
                vI[1] = resp;
                break;
            // (A XOR B)
            case '6':
                resp = portaXor(X, Y);
                resp = binarioParaHexadecimal(resp);
                vI[1] = resp;
                break;
            // A.B'
            case '7':
                Y = portaNot(Y);
                resp = portaAnd(X, Y);
                resp = binarioParaHexadecimal(resp);
                vI[1] = resp;
                break;
            // A' + B'
            case '8':
                X = portaNot(X);
                Y = portaNot(Y);
                resp = portaOr(X, Y);
                resp = binarioParaHexadecimal(resp);
                vI[1] = resp;
                break;
            // A' XOR B'
            case '9':
                X = portaNot(X);
                Y = portaNot(Y);
                resp = portaXor(X, Y);
                resp = binarioParaHexadecimal(resp);
                vI[1] = resp;
                break;
            // B
            case 'A':
                controleLed(Y);
                vI[1] = vetorInstrucoes[k][0];
                break;
            // A.B
            case 'B':
                resp = portaAnd(X, Y);

                resp = binarioParaHexadecimal(resp);
                vI[1] = resp;
                break;
            // 1 LOGICO
            case 'C':
                resp = umLogico(X);
                resp = binarioParaHexadecimal(resp);
                vI[1] = resp;
                break;
            // A+B'
            case 'D':
                Y = portaNot(Y);
                resp = portaOr(X, Y);
                resp = binarioParaHexadecimal(resp);
                vI[1] = resp;
                break;
            // A+B
            case 'E':
                resp = portaOr(X, Y);
                resp = binarioParaHexadecimal(resp);

                vI[1] = resp;
                break;
            // A
            case 'F':
                controleLed(X);
                vI[1] = vetorInstrucoes[k].charAt(0);
                break;
            default:
                Serial.print("ERROR");
                break;
            }

            vI[2] = vetorInstrucoes[k].charAt(0);
            vI[3] = vetorInstrucoes[k].charAt(1);
            delay(4000);
        }
        
        printValores(vI, memoriaInteira);
    }
}

// Funcao que recebe um caracter de uma entrada Hexadecimal e transforma em um Inteiro na base 10
int charToInt(char numero)
{
    int num;

    if (numero >= '0' && numero <= '9')
    {
        num = numero - '0'; // Converte '0'-'9' para 0-9
    }
    else if (numero >= 'A' && numero <= 'F')
    {
        num = numero - 'A' + 10; // Converte 'A'-'F' para 10-15
    }
    else
    {
        return -1;
    }
    return num;
}

// Funcao que pega a instrucao em um array de char, chama a instrucao de converter caracter por caracter em inteiro,
// pega  inteiro  e usa ele como entrada de uma funcao que converte inteiro pra binario e armazena em uma string
String conversorBinario(char valor)
{
    int Entrada = charToInt(valor);             // pegando a instrucao em Hexadecimal e tranformando em int
    String respostaTemp = String(Entrada, BIN); // enviando a instrucao int e convertendo para binario e salvando em uma string
    String resposta = "";
    if (respostaTemp.length() == 1)
    {
        resposta += "000";
        resposta += respostaTemp;
    }
    else if (respostaTemp.length() == 2)
    {
        resposta += "00";
        resposta += respostaTemp;
    }
    else if (respostaTemp.length() == 3)
    {
        resposta += "0";
        resposta += respostaTemp;
    }
    else
    {
        resposta += respostaTemp;
    }
    return resposta;
}

// Funcao que recebe o ARRAY BINARIO e nega seus valores, tudo que é 1 vira 0 e vice versa.
String portaNot(String numB)
{
    String resp = "";
    for (int i = 0; i < 4; i++)
    {
        if (numB.charAt(i) == '0')
        {
            resp += '1';
        }
        else
        {
            resp += '0';
        }
    }
    return resp;
}

// Funcao que simula uma porta AND a partir de 2 strings de numeros binarios.
String portaAnd(String X, String Y)
{
    String resp = "";
    for (int i = 0; i < 4; i++)
    {
        if (X.charAt(i) == '1' && Y.charAt(i) == '1')
        {
            resp += '1';
        }
        else
        {
            resp += '0';
        }
    }
    return resp;
}

// Funcao que simula uma porta OR a partir de 2 strings de numeros binarios
String portaOr(String X, String Y)
{
    String resp = "";
    for (int i = 0; i < 4; i++)
    {
        if (X.charAt(i) == '1' || Y.charAt(i) == '1')
        {
            resp += '1';
        }
        else
        {
            resp += '0';
        }
    }
    return resp;
}

// Funcao que simula uma porta XOR a partir de 2 strings de numeros binarios
String portaXor(String X, String Y)
{
    String resp = "";
    for (int i = 0; i < 4; i++)
    {
        if ((X.charAt(i) == '1' && Y.charAt(i) == '0') || (X.charAt(i) == '0' && Y.charAt(i) == '1'))
        {
            resp += '1';
        }
        else
        {
            resp += '0';
        }
    }
    return resp;
}

// Converter toda os valores da String binaria para 0
String zeroLogico(String numB)
{
    String resp = "";
    for (int i = 0; i < 4; i++)
    {
        resp += '0';
    }
    return resp;
}

// Converte todos os valores da String para 1.
String umLogico(String numB)
{
    String resp = "";
    for (int i = 0; i < 4; i++)
    {
        resp += '1';
    }
    return resp;
}

// Controla as led a partir do valor que receber em Binario.
void controleLed(String numB)
{
    if (numB.charAt(0) == '1')
    {
        digitalWrite(led13, HIGH);
    }
    else
    {
        digitalWrite(led13, LOW);
    }

    if (numB.charAt(1) == '1')
    {
        digitalWrite(led12, HIGH);
    }
    else
    {
        digitalWrite(led12, LOW);
    }

    if (numB.charAt(2) == '1')
    {
        digitalWrite(led11, HIGH);
    }
    else
    {
        digitalWrite(led11, LOW);
    }

    if (numB.charAt(3) == '1')
    {
        digitalWrite(led10, HIGH);
    }
    else
    {
        digitalWrite(led10, LOW);
    }
}
String binarioParaHexadecimal(String binario)
{
    long decimal = 0;
    for (int i = 0; i < binario.length(); i++)
    {
        decimal = decimal * 2 + (binario.charAt(i) - '0');
    }
    String hexadecimal = String(decimal, HEX);
    return hexadecimal;
}


void printValores(String* memoriaDados, String memoria){

    for (int j = 0; j < 4; j++)
        {

            Serial.print(memoriaDados[j]);
            Serial.print("|");
        }
        Serial.println(memoria);
        Serial.println();

}
