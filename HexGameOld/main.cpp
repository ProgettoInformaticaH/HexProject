#include <iostream>
#include<vector>
#include<Tarta_CodeBlocks.h>

using namespace std;
class HexModel
{
public:
    HexModel()
    {
        m.resize(7);
        //resize
        for(int i=0; i<7; i++)
        {
            m[i].resize(7);
        }
        //inizializzo tutto a 0
        for(int i=0; i<m.size(); i++)
        {
            for(int j=0; j<m.size(); j++)
            {
                m[i][j]=0;
            }
        }
        //inizializzo i bordi
        for(int i=0; i<m.size(); i++)
        {
            m[0][i]=1;//rosso
            m[i][0]=2;//blu
            m[m.size()-1][i]=1;//rosso
            m[i][m.size()-1]=2;//blu
        }

    };      //costruttore;
    vector<vector<int> > m;

    int posr=3;
    int posc=3;

    void destra()
    {
        if(posc<m.size()-2&&posr>1)
        {
            posc++;
            posr--;
        }
        else{posr=3;posc=3;}
        //cout<<"posc: "<<posc<<endl;
        //cout<<"posr: "<<posr<<endl;

    }

    void sinistra()
    {
        if(posc>1&&posr<m.size()-2)
        {
            posc--;
            posr++;
        }
        else{posr=3;posc=3;}
        //cout<<"posc: "<<posc<<endl;
        //cout<<"posr: "<<posr<<endl;

    }

    void su()
    {
        if(posr>1&&posc>1)
        {
            posr--;
            posc--;
        }
        else{posr=3;posc=3;}
        //cout<<"posr: "<<posr<<endl;
        //cout<<"posc: "<<posc<<endl;

    }

    void giu()
    {
        if(posr<m.size()-2&&posc<m.size()-2)
        {
            posr++;
            posc++;
        }
        else{posr=3;posc=3;}
        //cout<<"posr: "<<posr<<endl;
        //cout<<"posc: "<<posc<<endl;

    }

    void set(int r,int c,int colore)
    {
        if(m[r][c]==0)      m[r][c]=colore;
    }


    void get(int & tempr,int & tempc,int & tempcolore)
    {
        tempr=posr;
        tempc=posc;
        tempcolore=m[posr][posc];
    }
    void stbit()
    {
        for(int i=0; i<m.size(); i++)
        {
            for(int j=0; j<m.size(); j++)
            {
                cout<<m[i][j]<<" ";
            }
            cout<<endl;
        }
    }
};



class Hexgraphic
{
public:
    Hexgraphic(HexModel c)
    {
        copM.resize(7);
        //resize
        for(int i=0; i<7; i++)
        {
            copM[i].resize(7);
        }
        //copio la matrice originale nella matrice della grafica
        for(int i=0; i<c.m.size(); i++)
            for(int j=0; j<c.m.size(); j++)
                copM[i][j]=c.m[i][j];
        //mi sposto in una posizione in cui la mappa è visibile
        t.Salta(-200,200);
        t.D(90);
        t.Nasconditi();
        t.TempoPasso(0);
        //stampo la mappa in anteprima
        for(int i=0; i<copM.size(); i++)
        {
            for(int j=0; j<copM.size(); j++)
            {
                if(copM[i][j]==0)    t.Color(Nero);
                if(copM[i][j]==1)    t.Color(Rosso);
                if(copM[i][j]==2)    t.Color(Blu);
                if(copM[i][j]==3)    t.Color(Bianco); //colore di selezione

                t.Cerchio(l);
                t.AlzaPennello();
                t.A(l*4);
                t.AbbassaPennello();
            }
            t.DoveSei(x,y);
            t.Salta(x-(l*4*copM.size()),y-(l*4));
        }
    }

        void stbit()
    {
        for(int i=0; i<copM.size(); i++)
        {
            for(int j=0; j<copM.size(); j++)
            {
                cout<<copM[i][j]<<" ";
            }
            cout<<endl;
        }
    }



    void set(int r,int c,int colore)
    {
        copM[r][c]=colore;
    }

    int get(int posr,int posc)
    {
        return copM[posr][posc];
    }

    void visMp()
    {
        t.PulisciSchermo();
        t.Salta(-200,200);
        for(int i=0; i<copM.size(); i++)
        {
            for(int j=0; j<copM.size(); j++)
            {
                if(copM[i][j]==0)    t.Color(Nero);
                if(copM[i][j]==1)    t.Color(Rosso);
                if(copM[i][j]==2)    t.Color(Blu);
                if(copM[i][j]==3)    t.Color(Bianco); //colore di selezione

                t.Cerchio(l);
                t.AlzaPennello();
                t.A(l*4);
                t.AbbassaPennello();
            }
            t.DoveSei(x,y);
            t.Salta(x-(l*4*copM.size()),y-(l*4));
        }
    }

    void cpMappa(HexModel c)
    {
        for(int i=0; i<copM.size(); i++)
            for(int j=0; j<copM.size(); j++)
                copM[i][j]=c.m[i][j];
    }

    vector < vector <int> > copM;
    Tartaruga t;
    double l=15;
    float x,y;
};


int main()
{
    Tartaruga mov;
    mov.Nasconditi();
    HexModel m;
    m.stbit();

    Hexgraphic g(m);

    while(true)
    {
        int tasto=KeyCode();
        //cout<<tasto<<"   "<<KEY_UP<<endl;
        if(tasto==18432) m.su();
        if(tasto==19200) m.sinistra();
        if(tasto==19712) m.destra();
        if(tasto==20480) m.giu();

        int realcol=g.get(m.posr,m.posc);
        g.set(m.posr,m.posc,3);
        g.stbit();
        g.visMp();
        cout<<"posr :"<<m.posr<<"  posc :"<<m.posc<<endl;
        g.set(m.posr,m.posc,realcol);
        g.stbit();
    }



    WaitESC();
}
