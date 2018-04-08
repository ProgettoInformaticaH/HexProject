#include <iostream>
#include<vector>
#include<Tarta_CodeBlocks.h>

using namespace std;

///Classe gestione Dati di gioco
class DatabaseHex
{
public:
    DatabaseHex(int d)
    {
        //Resize mSelection
        mSelection.resize(d);
        for(int i=0; i<d; i++)  mSelection[i].resize(d);
        //Inizializzazione a 0 mSelection
        for(int i=0; i<d; i++)
            for(int j=0; j<d; j++)
                mSelection[i][j]=0;
        //Inizializzazione bordi
        //inizializzo i bordi
        for(int i=0; i<d-1; i++)
        {
            mSelection[0][i]=1; //Rosso
            mSelection[i][d-1]=2; //Blu
            mSelection[d-1][d-(1+i)]=1; //Rosso
            mSelection[d-(1+i)][0]=2; //Blu
        }

        //Resize mReal
        mReal.resize(d);
        for(int i=0; i<d; i++)  mReal[i].resize(d);
        //Inizializzazione a 0 mReal
        for(int i=0; i<d; i++)
            for(int j=0; j<d; j++)
                mReal[i][j]=0;
        //inizializzo i bordi
        for(int i=0; i<d-1; i++)
        {
            mReal[0][i]=1; //Rosso
            mReal[i][d-1]=2; //Blu
            mReal[d-1][d-(1+i)]=1; //Rosso
            mReal[d-(1+i)][0]=2; //Blu
        }
    }

    vector < vector <int> > mSelection;
    vector < vector <int> > mReal;

    void printmReal()
    {
        for(int i=0; i<mReal.size(); i++)
        {
            for(int j=0; j<mReal.size(); j++)
            {
                cout<<mReal[i][j]<<" ";
            }
            cout<<endl;
        }
    }
    void printmSelection()
    {
        for(int i=0; i<mSelection.size(); i++)
        {
            for(int j=0; j<mSelection.size(); j++)
            {
                cout<<mSelection[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};


///Classe gestione funzionamento del gioco
class ModelHex
{
public:
//Rosso=1       Blu=2       Vuoto=0     Selezione=3
    ModelHex(int d)
    {
        DatabaseHex DbModel(d);
        DbModel.printmSelection();
    }
    ///Funzioni da implementare
    int HaiVinto(); //Controlla se uno dei due giocatori ha vinto e ne restituisce il numero, altrimenti torna 0
    void giu();
    void su();
    void destra();
    void sinistra();
    void Reset();
    void SincronizzaMatrice();
    void getpos(int & posR,int & posC);
    void setpos(int posR,int posC,int nGioc);

    int posR, posC;

};


///Classe gestione output grafico di gioco
class GraficHex
{
public:

    GraficHex(int d)
    {
        Tartaruga t;
        t.Nasconditi();
        t.TempoPasso(0);
        t.Salta(-250,-200);     ///Da sistemare
        int l=22;               ///Da sistemare
        GrigliaEsagono(t,l,d);
    }


    void Presentazione();
    void DisegnaM();            //Disegna i pallini dentro la griglia
    void setposColore(int posR,int posC);       //Data la posizione in matrice in base al colore riscontrato lo disegna in base alla posizione degli indici
    void VisualeWin();
    void Pareggio();
    void NomeGioc();
    void EsagonoBase(Tartaruga & t,int l)
    {

        for (int i=0;i<6;i++)
        {
            t.A(l);
            t.S(60);
        }
    }
    void GrigliaEsagono(Tartaruga & t,int l,int d)       //Lasciata in secondo piano sempre
    {
        t.D(120);
        for (int j=0;j<d;j++)
        {
            for (int i=0;i<d;i++)
            {
                EsagonoBase(t,l);
                //t.CambiaColorePennello(Rosso);
                t.A(l);
                t.S(60);
                t.A(l);
                t.D(60);
                //t.CambiaColorePennello(Bianco);
            }
            t.S(120);
            t.A(l);
            t.S(60);
            for (int p=0;p<d-1;p++)
            {
                t.A(l);
                t.S(60);
                t.A(l);
                t.D(60);
            }
            t.A(l);
            t.D(180);
        }

            WaitESC();
    }
    void Menu();

};


class Game
{
public:
    Game(int d)
    {
        ///Usata come classe debug adesso successivamente come unica classe da usare nel main
        ModelHex a(d);
        GraficHex b(d);
    }

};

int main()
{
    int d=11;
    Game Gioco(d);
    return 0;
}
