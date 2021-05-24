package trabalho;
import java.util.Random;
import java.util.Scanner;
/* Disciplina: Computacao Concorrente */
/* Prof.: Silvana Rossetto */
/* Codigo: Leitores e escritores usando monitores em Java */
/* -------------------------------------------------------------------*/

// Monitor que implementa a logica do padrao leitores/escritores
class LE {
    private int leit, escr,  escresp;

    // Construtor
    LE() {
        this.leit = 0; //leitores lendo (0 ou mais)
        this.escr = 0; //escritor escrevendo (0 ou 1)
        this.escresp = 0; //numero de escritores esperando
    }

    // Entrada para leitores
    public synchronized void EntraLeitor (int id) {
        try {
            while (this.escr > 0 || this.escresp > 0) {
                //System.out.println ("le.leitorBloqueado("+id+")");
                wait();  //bloqueia pela condicao logica da aplicacao
            }
            this.leit++;  //registra que ha mais um leitor lendo
            //System.out.println ("le.leitorLendo("+id+")");
        } catch (InterruptedException e) { }
    }

    // Saida para leitores
    public synchronized void SaiLeitor (int id) {
        this.leit--; //registra que um leitor saiu
        if (this.leit == 0)
            this.notify(); //libera escritor (caso exista escritor bloqueado)
        //System.out.println ("le.leitorSaindo("+id+")");
    }

    // Entrada para escritores
    public synchronized void EntraEscritor (int id) {
        try {
            this.escresp++;
            while ((this.leit > 0) || (this.escr > 0)) {
                // System.out.println ("le.escritorBloqueado("+id+")");
                wait();  //bloqueia pela condicao logica da aplicacao
            }
            this.escresp--;
            this.escr++; //registra que ha um escritor escrevendo
            //System.out.println ("le.escritorEscrevendo("+id+")");
        } catch (InterruptedException e) { }
    }

    // Saida para escritores
    public synchronized void SaiEscritor (int id) {
        this.escr--; //registra que o escritor saiu
        notifyAll(); //libera leitores e escritores (caso existam leitores ou escritores bloqueados)
        //System.out.println ("le.escritorSaindo("+id+")");
    }
}
class Fila {
    int temperatura;
    int identificador_sensor;
    int identificador_atuador;
    Fila(int temperatura, int identificador_sensor, int identificador_atuador){
        this.temperatura =temperatura;
        this.identificador_sensor =identificador_sensor;
        this.identificador_atuador =identificador_atuador;
    }
}
class Buffer{
    Fila[] vetor; //Vetor que armazenará dados do buffer
    int tamanho;
    int proximoIndex; //Variável que guarda a posição onde será inserido o próximo elemento
    public Buffer(int tamanho) { //Construtor que inicializa o vetor do buffer e a variável de controle
        this.tamanho=tamanho;
        this.vetor = new Fila[this.tamanho];
        for(int i = 0; i < tamanho; i++ ) {
            this.vetor[i] = new Fila(0,0,0);
        }
        this.proximoIndex = 0;
    }
    public  void insereTemperatura(int temperatura, int id, int identificador) {
        this.vetor[proximoIndex] =  new Fila(temperatura,(id),identificador);
        this.proximoIndex++;
        if(proximoIndex == vetor.length) {
            proximoIndex=0;
        }
    }
    public void imprimeBuffer() {
        String saida_buffer = "Bf-[";
        for (int i = 0; i < this.vetor.length; i++) {
            saida_buffer = saida_buffer + this.vetor[i].temperatura;
            if(i != this.vetor.length - 1)
                saida_buffer = saida_buffer + ", ";
        }
        saida_buffer = saida_buffer + "]";
        System.out.println(saida_buffer);

        String saida_IS = "IS-[";
        for (int i = 0; i < this.vetor.length; i++) {
            saida_IS = saida_IS + this.vetor[i].identificador_sensor;
            if(i != this.vetor.length - 1)
                saida_IS = saida_IS + ",  ";
        }
        saida_IS = saida_IS + "]";
        System.out.println(saida_IS);

        String saida_IA = "IA-[";
        for (int i = 0; i < this.vetor.length; i++) {
            saida_IA = saida_IA + this.vetor[i].identificador_atuador;
            if(i != this.vetor.length - 1)
                saida_IA = saida_IA + ",  ";
        }
        saida_IA = saida_IA + "]";
        System.out.println(saida_IA);
    }
}

//Aplicacao de exemplo--------------------------------------------------------
// Atuador
class Atuador extends Thread {
    int[] amarelo;
    int[] vermelho;
    int id; //Identificador da thread
    LE monitor;//Objeto monitor para coordenar a lógica de execução das threads
    Buffer buffer;
    // Construtor
    Atuador (int id, LE m, Buffer buffer) {
        this.id = id;
        this.monitor = m;
        this.buffer = buffer;
        this.amarelo = new int[15];
        this.vermelho = new int[5];
        for(int k = 0; k<15; k++)
            this.amarelo[k]=0;
        for(int p = 0; p<5;p++)
            this.vermelho[p]=0;

    }
    // Método executado pela thread
    public void run () {
        int b = 0;
        int count=1;
        int c = 0;
        int l =0;
        int u = 0;
        int sinal_amarelo=0;
        int sinal_vermelho=0;
        int soma=0;
        double media=0;
        try {
            for (;;) {
                this.monitor.EntraLeitor(this.id);
                for(int a = 0; a<this.buffer.vetor.length;a++) {
                    if(this.id == this.buffer.vetor[a].identificador_sensor) {
                        //System.out.printf("id da thread leitor %d.\n",  this.id);
                        //System.out.printf("id da thread escritor %d.\n",  this.buffer.vetor[a].identificador_escritor);
                        b=(this.buffer.vetor[a].identificador_atuador -1)-(15*l);
                        c=(this.buffer.vetor[a].identificador_atuador -1)-(5*u);
                        //System.out.printf("%d - b: %d\n",this.buffer.vetor[a].identificador_escritor,b);
                        soma+=this.buffer.vetor[a].temperatura;
                        if(soma>40)
                            count+=1;
                        media=(double)soma/(double)count;
                        //System.out.printf("%d - soma: %d\n",this.id,soma);
                        //System.out.printf("\n ");
                        if(b>=0 && b<15)
                            this.amarelo[b]=this.buffer.vetor[a].temperatura;
                        if(b == 14)
                            l+=1;
                        if(c>=0 && c<5)
                            this.vermelho[c]=this.buffer.vetor[a].temperatura;
                        if(c == 4)
                            u+=1;
                    }
                }
	        /*
	        System.out.printf("%d - [",this.id);
	        for(int d =0; d<5;d++)
	        	System.out.printf("%d  ", vermelho[d]);
	        System.out.printf("]");
	        System.out.printf("\n");
    	   System.out.printf("%d - [",this.id);
    	        for(int d =0; d<15;d++)
    	        	System.out.printf("%d  ", amarelo[d]);
    	   System.out.printf("]");
    	   System.out.printf("\n");*/
                for(int q =0; q<15;q++)
                    if(this.amarelo[q]>35)
                        sinal_amarelo+=1;
                for(int q =0; q<5;q++)
                    if(this.vermelho[q]>35)
                        sinal_vermelho+=1;
                if(sinal_amarelo>=5)
                    System.out.printf("%d - Sinal amarelo\n",this.id);
                else
                    System.out.printf("%d - Condição normal\n",this.id);
                if(sinal_vermelho==5)
                    System.out.printf("%d - Sinal vermelho\n",this.id);
                else
                    System.out.printf("%d - Condição normal\n",this.id);

                sinal_amarelo=0;
                sinal_vermelho=0;
                soma=0;
                count=1;
                System.out.printf("%d - Media: %.5f \n", this.id, media);
                this.monitor.SaiLeitor(this.id);
                Thread.sleep(2000);// Atraso para simbolizar a leitura
            }
        } catch (InterruptedException e) { return; }
    }
}
//--------------------------------------------------------
// Sensor
class Sensor extends Thread {
    int id; //Identificador da thread
    LE monitor; //Objeto monitor para coordenar a lógica de execução das threads
    Buffer buffer;
    // Construtor
    Sensor (int id, LE m, Buffer buffer) {
        this.id = id;
        this.monitor = m;
        this.buffer = buffer;
    }

    // Método executado pela thread
    public void run () {
        Random rand = new Random();
        int inserido;
        int identificador=0;
        try {
            for (;;) {
                this.monitor.EntraEscritor(this.id);
                inserido = rand.nextInt(16) + 25;
                System.out.printf("Thread sensor %d indicou a temperatura %d.\n", id , inserido);
                if(inserido>30) {
                    identificador+=1;
                    this.buffer.insereTemperatura(inserido, this.id, identificador);
                }
                this.monitor.SaiEscritor(this.id);
                Thread.sleep(1000); // Atraso para simbolizar a escrita
                //synchronized (this) {buffer.imprimeBuffer();}
            }
        } catch (InterruptedException e) { return; }
    }
}

//--------------------------------------------------------
// Classe principal
class LeitorEscritor {
    public static void main (String[] args) {
        System.out.printf("Digite o numeros de sensores: ");
        Scanner ler = new Scanner(System.in);
        int n = ler.nextInt();
        LE monitor = new LE();          // Monitor (objeto compartilhado entre leitores e escritores)
        Atuador[] l = new Atuador[n];   // Threads leitores
        Sensor[] e = new Sensor[n];     // Threads escritores
        Buffer b = new Buffer(60);
        //inicia o log de saida

        for (int i=0; i<n; i++) {
            l[i] = new Atuador(i+1, monitor,b);
            l[i].start();
        }
        for (int i=0; i<n; i++) {
            e[i] = new Sensor(i+1, monitor,b);
            e[i].start();
        }
    }
}
