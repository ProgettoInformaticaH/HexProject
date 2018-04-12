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
        ///Resize mSelection
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

        ///Resize mReal
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



        ///Resize Matrice win
        matriceWin.resize(d);
        for(int i=0; i<d; i++)  matriceWin[i].resize(d);
        //Inizializzazione a 0 matriceWin
        for(int i=0; i<d; i++)
            for(int j=0; j<d; j++)
                matriceWin[i][j]=0;
        //inizializzo i bordi
        for(int i=0; i<d-1; i++)
        {
            matriceWin[0][i]=1; //Rosso
            matriceWin[i][d-1]=2; //Blu
            matriceWin[d-1][d-(1+i)]=1; //Rosso
            matriceWin[d-(1+i)][0]=2; //Blu
        }
    }

    vector < vector <int> > mSelection;
    vector < vector <int> > mReal;
    vector < vector <int> > matriceWin;


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
        void printmMWin()
    {
        for(int i=0; i<matriceWin.size(); i++)
        {
            for(int j=0; j<matriceWin.size(); j++)
            {
                cout<<matriceWin[i][j]<<" ";
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
        bool rit;
        int colcontr=1,p=1;
        for (int i=1; i<d-2; i++)
        {
            if (DbModel.matriceWin[i][p]==1)
            {
                rit=false;
                if (Arriva(i,p,colcontr,rit))
                    {
                       return colcontr;
                    }

                else SincWin();
            }
        }
        colcontr=2;
        for (int i=1; i<d-2; i++)
        {
            if (DbModel.matriceWin[p][i]==2)
            {
                rit=false;
                if (Arriva(p,i,colcontr,rit))
                {
                    return colcontr;
                }

                else SincWin();
            }
        }
        return 0;

    }
    bool Arriva(int r, int c,int & colcontr,bool & rit )
    {
        DbModel.matriceWin[r][c]=-1;
        if (colcontr==1) ///orizzontale
        {

            if (c==d-2    &&    DbModel.matriceWin[r][d-2]==-1) rit= true;
            if(r>1   &&    DbModel.matriceWin[r-1][c]==colcontr) Arriva(r-1,c,colcontr,rit);
            if(c<d-1 &&    DbModel.matriceWin[r][c+1]==colcontr)  Arriva(r,c+1,colcontr,rit);
            if(r<d-1 &&    c<d-1   &&    DbModel.matriceWin[r+1][c+1]==colcontr) Arriva(r+1,c+1,colcontr,rit);
            if(r<d-1 &&    DbModel.matriceWin[r+1][c]==colcontr)  Arriva(r+1,c,colcontr,rit);
            if(c>1 &&    DbModel.matriceWin[r][c-1]==colcontr)  Arriva(r,c-1,colcontr,rit);
            if(r>1 && c>1 &&   DbModel.matriceWin[r-1][c-1]==colcontr)  Arriva(r-1,c-1,colcontr,rit);

            //
        }

        if (colcontr==2) ///verticale
        {
            if (r==d-2    &&    DbModel.matriceWin[d-2][c]==-1) rit= true;
            if(c>1   &&    DbModel.matriceWin[r][c-1]==colcontr)  Arriva(r,c-1,colcontr,rit);
            if(r<d-1 &&    DbModel.matriceWin[r+1][c]==colcontr)  Arriva(r+1,c,colcontr,rit);
            if(r<d-1 &&    c<d-1   &&    DbModel.matriceWin[r+1][c+1]==colcontr)  Arriva(r+1,c+1,colcontr,rit);
            if(c<d-1 &&    DbModel.matriceWin[r][c+1]==colcontr)  Arriva(r,c+1,colcontr,rit);
            //
            if(r>1 &&    DbModel.matriceWin[r-1][c]==colcontr)  Arriva(r-1,c,colcontr,rit);
            if(r>1 && c>1 &&   DbModel.matriceWin[r-1][c-1]==colcontr)  Arriva(r-1,c-1,colcontr,rit);
        }
        return rit;
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
        if(posC<d-2&&posR>=1)   posC++;
    }

    void sinistra()
    {
        if(posC>1&&posR<d-1)    posC--;
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
            if(tcor==18432) {su(); vcol=getvalTemp();}
            else if(tcor==19200) {sinistra(); vcol=getvalTemp();}
            else if(tcor==19712) {destra(); vcol=getvalTemp();}
            else if(tcor==20480) {giu(); vcol=getvalTemp();}
            else if(tcor==32)    {if(spazio(nGioc)) return true;}
            return false;

    }



    void Reset();

    void SincronizzaMatrice()
    {
        for(int i=0;i<d;i++)
            for(int j=0;j<d;j++)
                DbModel.mSelection[i][j]=DbModel.mReal[i][j];
    }
       void SincWin()
    {
        for(int i=0;i<d;i++)
            for(int j=0;j<d;j++)
                DbModel.matriceWin[i][j]=DbModel.mReal[i][j];
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
        //Presentazione();
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
        //t.Cerchio((l*2)/3);
        if(col==0)        t.RiempiColore(Grigio,Bianco);
        if(col==1)        t.RiempiColore(Rosso,Bianco);
        if(col==2)        t.RiempiColore(Blu,Bianco);
        if(col==3)        t.RiempiColore(RossoChiaro,Bianco);
        if(col==4)        t.RiempiColore(BluChiaro,Bianco);
    }




    void VisualeWin(int nGioc)
    {
        t.ClearScreen(Bianco);
        t.Home();
        if (nGioc==1)    t.CambiaColorePennello(Rosso);
        if (nGioc==2)    t.CambiaColorePennello(Blu);
        t.Cerchio(200);
        t.Salta(-40,-300);
        t<<"Hai Vinto!!!";

    }
    void Pareggio()
        {
        t.ClearScreen(Bianco);
        t.Home();
        t.CambiaColorePennello(Nero);
        t.Cerchio(200);
        t.Salta(-40,-300);
        t.CambiaColorePennello(Verde);
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
            int vitt=a.HaiVinto();
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
            a.SincWin();
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
