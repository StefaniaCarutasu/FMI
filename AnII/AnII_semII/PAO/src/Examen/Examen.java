package Examen;

class Fir extends Thread{
    int nivel;
    static int numar = 0;
    public Fir(int n){nivel=n;}
    public void run(){
        System.out.print(nivel+" ");
        if (nivel<2){
            Fir fir = new Fir(nivel+1);
            fir.start();
        }
        if (nivel<2){
            Fir fir = new Fir(nivel+1);
            fir.start();
        }
        if (nivel<10000000){
            Fir fir = new Fir(nivel+1);
            fir.start();
        }
    }
}
public class Examen {
    public static void main(String[] args) {
        Fir fir = new Fir(0);
        fir.start();
    }
}