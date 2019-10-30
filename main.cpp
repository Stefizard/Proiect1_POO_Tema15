#include <iostream>
using namespace std;
class Nod
{
    int info;
    Nod *st, *dr;
public:
    Nod(int x, Nod * st, Nod * dr)
    {
        info=x;
        this->st=st;
        this->dr=dr;
    }
    Nod(int x=0)
    {
        info=x;
        st=NULL;
        dr=NULL;
    }
    ~Nod()
    {

    }
    int getinfo(){ return info;}
    Nod* getst(){ return st;}
    Nod* getdr(){ return dr;}
    void setinfo(int info){ this->info=info;}
    void setst(Nod *st){ this->st=st;}
    void setdr(Nod *dr){ this->dr=dr;}
};
class ABC
{
    Nod *rad;
public:
    Nod* getrad(){ return rad;}
    void setrad(Nod *rad){ this->rad=rad;}
    ABC()
    {
        rad=NULL;
    }
    void dezalocare(Nod * parc)
    {
        if (parc->getst()!=NULL) dezalocare(parc->getst());
        if (parc->getdr()!=NULL) dezalocare(parc->getdr());
        delete parc;
    }
    ~ABC()
    {
        dezalocare(rad);
    }
    int operator+(int val)
    {
        if (rad==NULL)
        {
            Nod *a;
            a=new Nod(val);
            rad=a;
        }
        else
        {
            Nod * parc;
            parc=rad;
            while ((parc->getst()!=NULL && val<parc->getinfo()) || (parc->getdr()!=NULL && val>parc->getinfo()))
            {
                if (val<parc->getinfo()) parc=parc->getst();
                else if (val>parc->getinfo()) parc=parc->getdr();
            }
            if (val==parc->getinfo())
            {
                cout<<"Valoare deja introdusa!"<<endl;
                return 1;
            }
            Nod *a;
            a=new Nod(val);
            if (val<parc->getinfo()) parc->setst(a);
            else parc->setdr(a);
        }
        return 0;
    }
    friend istream& operator>>(istream& in, ABC& copac)
    {
        int x,n;
        cout<<"Numarul nodurilor de adaugat in arbore: ";
        cin>>n;
        for (int i=1;i<=n;i++)
        {
            cout<<"Nodul "<<i<<": ";
            cin>>x;
            if(copac+x) i--;
        }
        return in;
    }
    void preordine(Nod * parc)
    {
        cout<<parc->getinfo()<<" ";
        if (parc->getst()!=NULL) preordine(parc->getst());
        if (parc->getdr()!=NULL) preordine(parc->getdr());
    }
    void inordine(Nod * parc)
    {
        if (parc->getst()!=NULL) inordine(parc->getst());
        cout<<parc->getinfo()<<" ";
        if (parc->getdr()!=NULL) inordine(parc->getdr());
    }
    void postordine(Nod * parc)
    {
        if (parc->getst()!=NULL) postordine(parc->getst());
        if (parc->getdr()!=NULL) postordine(parc->getdr());
        cout<<parc->getinfo()<<" ";
    }
    friend ostream& operator<<(ostream& out, ABC& copac)
    {
        if (copac.getrad()!=NULL)
        {
            cout<<"Parcurgerea in preordine:"<<endl;
            copac.preordine(copac.getrad());
            cout<<endl<<"Parcurgerea in inordine:"<<endl;
            copac.inordine(copac.getrad());
            cout<<endl<<"Parcurgerea in postordine:"<<endl;
            copac.postordine(copac.getrad());
            cout<<endl;
        }
        else cout<<"Copac vid!";
        return out;
    }
    void stergereFrunza(Nod * tata, Nod * frunza)
    {
        if (tata==getrad() && frunza==getrad()) setrad(NULL);
        else if (tata->getst()==frunza) tata->setst(NULL);
        else if (tata->getdr()==frunza) tata->setdr(NULL);
        delete frunza;
    }
    void stergereFiu(Nod * tata, Nod * fiu)
    {
        if (tata==getrad() && fiu==getrad())
        {
            if (fiu->getst()!=NULL) this->setrad(fiu->getst());
            else this->setrad(fiu->getdr());
        }
        else if (tata->getst()==fiu)
        {
            if (fiu->getst()!=NULL) tata->setst(fiu->getst());
            else tata->setst(fiu->getdr());
        }
        else if (tata->getdr()==fiu)
        {
            if (fiu->getst()!=NULL) tata->setdr(fiu->getst());
            else tata->setdr(fiu->getdr());
        }
        delete fiu;
    }
    void stergereFii(Nod * tata, Nod * fiu)
    {
        Nod * parc, *tataParc, *a, *b, *aux;
        parc=fiu->getst();
        tataParc=fiu;
        while (parc->getdr()!=NULL)
        {
            tataParc=parc;
            parc=parc->getdr();
        }
        a=new Nod(fiu->getinfo(),parc->getst(),parc->getdr());
        b=new Nod(parc->getinfo(),fiu->getst(),fiu->getdr());
        if (fiu==tataParc)
        {
            b->setst(a);
            tataParc=b;
        }
        if (tata==getrad() && fiu==getrad()) this->setrad(b);
        else if (tata->getst()==fiu) tata->setst(b);
        else if (tata->getdr()==fiu) tata->setdr(b);
        if (tataParc->getst()==parc) tataParc->setst(a);
        else if (tataParc->getdr()==parc) tataParc->setdr(a);
        delete fiu;
        delete parc;
        if (a->getst()!=NULL) stergereFiu(tataParc,a);
        else stergereFrunza(tataParc,a);
    }
    void stergere(int val)
    {
        if (val==getrad()->getinfo())
        {
            if (getrad()->getst()!=NULL && getrad()->getdr()!=NULL) stergereFii(getrad(),getrad());
            else if (getrad()->getst()!=NULL || getrad()->getdr()!=NULL) stergereFiu(getrad(),getrad());
            else stergereFrunza(getrad(),getrad());
            return;
        }
        Nod * parc, *tataParc;
        tataParc=getrad();
        if (val<getrad()->getinfo())
        {
            if (getrad()->getst()!=NULL) parc=getrad()->getst();
            else
            {
                cout<<"Nu exista valoarea in acest arbore!"<<endl;
                return;
            }
        }
        else if (val>getrad()->getinfo())
        {
            if (getrad()->getdr()!=NULL) parc=getrad()->getdr();
            else
            {
                cout<<"Nu exista valoarea in acest arbore!"<<endl;
                return;
            }
        }
        while (val!=parc->getinfo())
        {
            if (val<parc->getinfo())
            {
                if (parc->getst()!=NULL)
                {
                    tataParc=parc;
                    parc=parc->getst();
                }
                else
                {
                    cout<<"Nu exista valoarea in acest arbore!"<<endl;
                    return;
                }
            }
            else if (val>parc->getinfo())
            {
                if (parc->getdr()!=NULL)
                {
                    tataParc=parc;
                    parc=parc->getdr();
                }
                else
                {
                    cout<<"Nu exista valoarea in acest arbore!"<<endl;
                    return;
                }
            }
        }
        if (parc->getst()!=NULL && parc->getdr()!=NULL) stergereFii(tataParc,parc);
        else if (parc->getst()!=NULL || parc->getdr()!=NULL) stergereFiu(tataParc,parc);
        else stergereFrunza(tataParc,parc);
        cout<<"Elementul a fost sters cu succes!"<<endl;
    }
    int inaltime(Nod * parc)
    {
        if (parc->getst()==NULL && parc->getdr()==NULL) return 0;
        int s,d;
        if (parc->getst()!=NULL) s=inaltime(parc->getst());
        else s=-1;
        if (parc->getdr()!=NULL) d=inaltime(parc->getdr());
        else d=-1;
        if (s>d) return s+1;
        else return d+1;
    }
    void frunze(Nod * parc)
    {
        if (parc->getst()!=NULL) frunze(parc->getst());
        if (parc->getst()==NULL && parc->getdr()==NULL) cout<<parc->getinfo()<<" ";
        if (parc->getdr()!=NULL) frunze(parc->getdr());
    }
};
class Nr_ABC
{
    int n;
    ABC *v;
public:
    int getn(){ return n;}
    ABC* getv(){ return v;}
    void citire()
    {
        cout<<"Numarul de arbori: ";
        cin>>n;
        v=new ABC[n];
        for (int i=0;i<n;i++)
        {
            cout<<"Arborele "<<i+1<<":"<<endl;
            cin>>v[i];
        }
    }
    ~Nr_ABC()
    {
        delete v;
    }
};
int main()
{
/*    ABC arbore;
    cin>>arbore;
    cout<<arbore;
    cout<<"Inaltimea arborelui este "<<arbore.inaltime(arbore.getrad())<<endl;
    cout<<"Frunzele arborelui sunt:"<<endl;
    arbore.frunze(arbore.getrad());
    cout<<endl;
    int n,x;
    cin>>n;
    for (int i=1;i<=n;i++)
    {
        cin>>x;
        arbore.stergere(x);
    }
    cout<<arbore;
*/
    Nr_ABC vec;
    vec.citire();
    int o,i,x;
    while (1)
    {
        cout<<"[1-afisarea arborelui in toate cele 3 metode; 2-inserare elemente; 3-stergere element; 4-inaltimea arborelui; 5-lista frunzelor; 6-exit]"<<endl<<"Optiunea ";
        cin>>o;
        if (o==6) break;
        cout<<"Carui arbore doriti sa ii aplicati optiunea? (indicele incepe de la 1)"<<endl<<"Arborele ";
        cin>>i;
        if (i>vec.getn() || i<1)
        {
            cout<<"Nu exista acest arbore!"<<endl;
            continue;
        }
        i--;
        switch (o)
        {
            case 1:
            {
                cout<<vec.getv()[i];
                break;
            }
            case 2:
            {
                cin>>vec.getv()[i];
                break;
            }
            case 3:
            {
                cout<<"Ce element doriti sa stergeti?"<<endl<<"Elementul ";
                cin>>x;
                vec.getv()[i].stergere(x);
                break;
            }
            case 4:
            {
                cout<<"Inaltimea arborelui este "<<vec.getv()[i].inaltime(vec.getv()[i].getrad())<<endl;
                break;
            }
            case 5:
            {
                cout<<"Frunzele arborelui sunt:"<<endl;
                vec.getv()[i].frunze(vec.getv()[i].getrad());
                cout<<endl;
                break;
            }
            default: cout<<"Optiune invalida!"<<endl;
        }
    }
    return 0;
}
