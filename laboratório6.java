package labativ;

/* Disciplina Computação Concorrente
 * Prof.: Silvana Rossetto
 * Módulo 2 - Laboratório 6
 * Código: Programa concorrente em Java para incrementar de 1 todos os elementos de um vetor.*/

class Vetor {

    //Atributos Vetor
    private int [] vetor;
    private int tamanho;

    public Vetor(int tamanho) { //Construtor da classe
        this.tamanho = tamanho;
        this.vetor = new int [tamanho];
        for(int i = 0; i < tamanho; i++) {
            this.vetor[i] = i*5;
        }
    }
    //Métodos
    public int getTamanho() {
        return this.tamanho;
    }

    public int getElemento(int posicao) {
        return this.vetor[posicao];
    }

    public void imprimeVetor() {
        String saida = "[";
        for (int i = 0; i < this.vetor.length; i++) {
            saida = saida + this.vetor[i];
            if(i != this.vetor.length - 1) {
                saida = saida + ", ";
            }
        }
        
        saida = saida + "]";
        System.out.println(saida);
    }

    public void setElemento(int elemento, int posicao) {
        this.vetor[posicao] = elemento;
    }
}
class Somador implements Runnable {

    //Atributos da classe Somador
    Vetor a; //Vetor que sera somado
    int id; //Identificador da thread
    int nthreads; //Armazena o número de threads sendo utilizada para saber quais elementos esta thread irá calcular

    public Somador(Vetor a, int id, int nthreads) { //Construtor da thread
        this.a = a;
        this.id = id;
        this.nthreads = nthreads;
    }

    public void run() { //Método main da thread
        for(int i = this.id; i < this.a.getTamanho(); i += this.nthreads) {
            int resultado = this.a.getElemento(i) + 1;
            this.a.setElemento(resultado, i);
        }
    }
}
public class labativ {

    public static void main(String [] args) {
        int tamanho=20; //Variável que armazenará o tamanho dos vetores
        Vetor a = new Vetor(tamanho);
        int nthreads=2; //Variável que armazenará o número de threads

        //Imprime o vetor inicial
        System.out.print("Vetor inicial: "); a.imprimeVetor();

        Thread [] threads = new Thread[nthreads]; //Vetor de Threads instanciado

        //Cria as threads da aplicação
        for(int i = 0; i < nthreads; i++) {
            threads[i] = new Thread(new Somador(a, i, nthreads));
        }

        //Inicia as threads
        for(int i = 0; i < nthreads; i++) {
            threads[i].start();
        }
        
        //Espera o término de todas as threads
        for(int i = 0; i < nthreads; i++) {
            try { threads[i].join(); } catch (InterruptedException e) { return; }
        }
        //Imprime o vetor resultante e termina a execução da main
        System.out.print("Vetor final:   "); a.imprimeVetor();
    }
}
