#include <iostream>
#include<vector>
#include<Tarta_CodeBlocks.h>

using namespace std;

///Classe gestione Dati di gioco
class DatabaseHex
{
public:
    void resM(int d)
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
    int d;
    DatabaseHex DbModel;
    ModelHex(int d)
    {
        DbModel.resM(d);
        d=d;
    }
    ///Funzioni da implementare
    int HaiVinto(); //Controlla se uno dei due giocatori ha vinto e ne restituisce il numero, altrimenti torna 0





        void destra()
    {
        if(posC<d-2&&posR>1)
        {
            posC++;
            posR--;
        }


    }

    void sinistra()
    {
        if(posC>1&&posR<d-2)
        {
            posC--;
            posR++;
        }


    }

    void su()
    {
        if(posR>1&&posC>1)
        {
            posR--;
            posC--;
        }


    }

    void giu()
    {
        if(posR<d-2&&posC<d-2)
        {
            posR++;
            posC++;
        }

    }


    int SelezioneTemp(int nGioc)
    {
        ///valori tasti

            int tcor=KeyCode();
            if(tcor==18432) su();
            if(tcor==19200) sinistra();
            if(tcor==19712) destra();
            if(tcor==20480) giu();
    }



    void Reset();

    void SincronizzaMatrice()
    {
        for(int i=0;i<d;i++)
            for(int j=0;j<d;j++)
                DbModel.mSelection[i][j]=DbModel.mReal[i][j];

    }

    int getvalReal()
    {
        return DbModel.mReal[posR][posC];
    }

    int getvalTemp()
    {
        return DbModel.mSelection[posR][posC];
    }

    void setposReal(int nGioc)
    {
        DbModel.mReal[posR][posC]=nGioc;
        SincronizzaMatrice();
    }
    void selposTemp(int nGioc)
    {
        DbModel.mSelection[posR][posC]=nGioc+2;
    }

    int gtvalmGraf(int pc, int pr)
    {
        return DbModel.mSelection[pr][pc];
    }
    int posR=1;
    int posC=1;

};


///Classe gestione output grafico di gioco
class GraficHex
{
public:

    Tartaruga t;
    int l=22;
    GraficHex(int d)
    {
        t.Nasconditi();
        t.TempoPasso(0);
        t.Salta(-250,-200);     ///Da sistemare le posizioni
        GrigliaEsagono(t,l,d);
    }


    void Presentazione();

    void DisegnaM(int d,ModelHex m)            //Disegna i pallini dentro la griglia di standard
    {
        float xc,xy;
        t.DoveSei(xc,xy);
        for(int i=0;i<d;i++)
            for(int j=0;j<d;j++)
        {
            t.Salta(xc,xy);
            setposColore(i,j,m.gtvalmGraf(i,j));
            t.D(60);
        }
        t.Salta(xc,xy);
    }

    void setpallina(int posR,int posC,ModelHex p)
    {
        float xc,xy;
        t.DoveSei(xc,xy);
        setposColore(posR,posC,p.DbModel.mSelection[posR][posC]);
        t.Salta(xc,xy);
        t.D(60);
    }


    void setposColore(int posR,int posC,int col)       //Data il colore e la posizione degli indici lo colora
    {
        t.AlzaPennello();
        for(int i=0;i<=posC;i++)
        {
            t.A(l);
            t.D(60);
            t.A(l);
            t.S(60);
        }
        t.D(120);
        for(int i=0;i<=posR;i++)
        {
            t.A(l);
            t.D(60);
            t.A(l);
            t.S(60);
        }
        t.S(180);
        t.A(l);
        if(col==0)        t.CambiaColorePennello(Bianco);
        if(col==1)        t.CambiaColorePennello(Rosso);
        if(col==2)        t.CambiaColorePennello(Blu);
        if(col==3)        t.CambiaColorePennello(RossoChiaro);
        if(col==4)        t.CambiaColorePennello(BluChiaro);
        t.AbbassaPennello();
        t.Cerchio(15);
    }




    void VisualeWin();
    void Pareggio();
    void NomeGioc();        //opzionale


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
        t.S(60);
        t.A(-l);

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
        b.DisegnaM(d,a);





        WaitESC();

    }

};

int main()
{
    int d=11;
    Game Gioco(d);
    return 0;
}
