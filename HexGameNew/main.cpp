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
class GraficHex;

///Classe gestione funzionamento del gioco
class ModelHex
{

public:
    int d;
    //Rosso=1       Blu=2       Vuoto=0     Selezione=3

    DatabaseHex DbModel;
    ModelHex(int d1)
    {
        DbModel.resM(d1);
        d=d1;

    }
    ///Funzioni da implementare
    int HaiVinto() //Controlla se uno dei due giocatori ha vinto e ne restituisce il numero, altrimenti torna 0
        {
            return 0;

        }
    bool Arriva()
    {

    }

    bool pareggio()
    {
        for(int i=0;i<d;i++)
            for(int j=0;j<d;j++)
                if(DbModel.mReal[i][j]==0) return false;
            return true;
    }


        void destra()
    {

        if(posC<d-2&&posR>=1)
        {
            posC++;
            //posR--;
        }


    }

    void sinistra()
    {
        if(posC>1&&posR<d-1)
        {
            posC--;
            //posR++;
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

    bool spazio(int nGioc)
    {
        if(getvalReal()==0)
            selposTemp(nGioc);
    }

    bool SelezioneTemp(int nGioc,int & vcol)
    {
        ///valori tasti
            int tcor=KeyCode();
            //grf.setptemp(posR,posC,0);
            if(tcor==18432) {su(); vcol=getvalTemp();}
            else if(tcor==19200) {sinistra(); vcol=getvalTemp();}
            else if(tcor==19712) {destra(); vcol=getvalTemp();}
            else if(tcor==20480) {giu(); vcol=getvalTemp();}
            else if(tcor==32)    {if(spazio(nGioc)) return true;}
            //grf.setptemp(posR,posC,getvalTemp());
            return false;

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
        DbModel.mSelection[posR][posC]=(nGioc+2);
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
    float l=25;
    GraficHex(int d)
    {
        t.Nasconditi();
        t.TempoPasso(0);
        Presentazione();
        t.ClearScreen(Nero);
        t.Salta(-250,-200);     ///Da sistemare le posizioni
        GrigliaEsagono(t,l,d);

    }


    void Presentazione()
    {
        t.ClearScreen(Nero);
        string s="Hex \n\n\n", a="By:    Samuele Stefanello";
        t.Jump(-300,200);
        delay(300);
        for(int i=0; i<s.size(); i++)
        {
            t<<s[i];
            if(s[i]!=' '&&s[i]!='\n')
                delay(150);
        }
        t.Jump(-300,150);
        for(int i=0; i<a.size(); i++)
        {
            t<<a[i];
            if(a[i]!=' '&&s[i]!='\n')
                delay(150);
        }
        delay(1000);
    }

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

    void setpallina(ModelHex p)
    {
        float xc,xy;
        t.DoveSei(xc,xy);
        setposColore(p.posR,p.posC,p.DbModel.mSelection[p.posR][p.posC]);
        t.Salta(xc,xy);
        t.D(60);
    }

       void setptemp(int posR,int posC,int col)
    {
        float xc,xy;
        t.DoveSei(xc,xy);
        setposColore( posR, posC, col);
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
        t.Cerchio((l*2)/3);
    }




    void VisualeWin(int nGioc)
    {
        delay(2000);
        t.ClearScreen(Bianco);
        t.Home();
        if (nGioc=1)    t.CambiaColorePennello(Rosso);
        if (nGioc=2)    t.CambiaColorePennello(Blu);
        t.Cerchio(200);
        t.AlzaPennello();
        t.Salta(-40,0);
        t.AbbassaPennello();
        t.CambiaColorePennello(Nero);
        t<<"HAI VINTO!!!";
    }
    void Pareggio()
        {
        t.ClearScreen();
        t.Home();
        t.CambiaColorePennello(Bianco);
        t.Cerchio(200);
        t.AlzaPennello();
        t.Salta(-40,0);
        t.AbbassaPennello();
        t.CambiaColorePennello(Nero);
        t<<"PAREGGIO!!!";
        }


    void EsagonoBase(Tartaruga & t,float l)
    {

        for (int i=0;i<6;i++)
        {
            t.A(l);
            t.S(60);
        }
    }

    void GrigliaEsagono(Tartaruga & t,float l,int d)       //Lasciata in secondo piano sempre
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
    Game()
    {
        int d=10;
        ///Usata come classe debug adesso successivamente come unica classe da usare nel main
        ModelHex a(d);
        GraficHex b(d);
        b.DisegnaM(d,a);
        bool settato;
        int nGioc=1,nMossa=1,vr=a.posR,vc=a.posC;
        while(a.HaiVinto()==0&&!a.pareggio())    ///pareggio torna falso
        {
            settato=false;
            int vcol;
            while(!settato)
            {
                settato=a.SelezioneTemp(nGioc,vcol);

                b.setptemp(vr,vc,a.DbModel.mSelection[vr][vc]);
                a.selposTemp(nGioc);

                vr=a.posR;
                vc=a.posC;
                b.setptemp(a.posR,a.posC,a.DbModel.mSelection[a.posR][a.posC]);
                a.selposTemp(vcol-2);
             }

            a.setposReal(nGioc);
            b.setpallina(a);
            a.SincronizzaMatrice();
            nMossa++;

            if(nMossa%2==0) nGioc=2;
            else    nGioc=1;

        }

        if(a.pareggio())
            b.Pareggio();
        else
            b.VisualeWin(a.HaiVinto());
            WaitESC();
    }


};

int main()
{
    Game Gioco;
    return 0;
}
