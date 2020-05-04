#include <bits/stdc++.h>

using namespace std;

class Vector{
    int dim;
    int *a;

    void alocate(int dim)
    {
        try{
            this->a = new int [dim+1];
        }
        catch( bad_alloc& err){
            cout<<"Allocation Failure";
            exit(EXIT_FAILURE);
            }
    }
public:
    Vector(){
        alocate(100);
        dim = 100;}

    Vector( int dim )
    {
        alocate(dim);
        this->dim = dim;
    }

    Vector (const Vector& cpy)
    {
        this->dim = cpy.dim;
        alocate(this->dim);
        for(int i = 1; i<=dim; ++i)
            a[i] = cpy.a[i];
    }

    ~Vector()
    {
        delete[] a;
    }
    void setdim(int n)
    {
        dim=n;
    }

    int getdim()
    {
        return dim;
    }
    const int& operator()(int x) const
    {
        return this->a[x];
    }

    Vector& operator=(const Vector& cpy)
    {
        if (this != &cpy)
        {
            if (dim < cpy.dim)
            {
                delete[] a;
                alocate(cpy.dim);
             }
             dim=cpy.dim;
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Vector& v)
    {
        int m;
        cout<<"Enter number of elemetns: ";
        in>>m;
        if(v.dim < m){
            v=Vector(m);
        }
        v.a[0] = m;
        for(int i=1; i<=m; ++i)
        {
            cout<<i<<":";
            in>>v.a[i];
        }

        return in;

    }

    friend ostream& operator<<(ostream& out, const Vector& v)
    {
        for(int i=1; i<=v.a[0]; ++i)
        {
            out<<v.a[i]<<" ";
        }
        return out;
    }

};

class Matrice{
    Vector v;
    int nr_line;
public:
    Matrice(): v(){}
    Matrice(const Matrice& cpy)
    {
        v = cpy.v;
    }
    ~Matrice(){
        v.setdim(0);
    }
    int get_nr_line()
    {
        return nr_line;
    }
    Vector get_v()
    {
        return v;
    }
    int get_v_dim()
    {
        return get_v().getdim();
    }

    virtual Matrice& operator=(const Matrice& cpy)
    {
        if(this != &cpy)
        {
            v=cpy.v;
        }
        return *this;
    }
    virtual ostream& Matriceout(ostream& out)=0;
    virtual istream& Matricein(istream& in)=0;

    virtual istream& operator>>(istream& in){
        cout<<"Enter number of lines: ";
        in>>this->nr_line;
        for(int i=1;i<=this->nr_line;++i)
        {
            cout<<"l=";
            in>>v;
        }
        return in;
    }
    virtual ostream& operator<<(ostream& out){

        for(int i=1; i<=this->nr_line;++i)
        {
            out<<i<<": ";
            out<<v;
            out<<'\n';
        }
        return out;
    }
};

class Matrice_oarecare:virtual public Matrice{
    int lin;
public:
    Matrice_oarecare(): Matrice(),lin(){}
    Matrice_oarecare(const Matrice_oarecare& cpy): Matrice(cpy){
        this->lin=cpy.lin;
    }
    ~Matrice_oarecare(){
        lin=0;
    }

    istream& matriceIn(istream& in){
        cout<<"Enter number of lines: ";
        in>>lin;
        return in;
    }
    ostream& matriceOut(ostream& out){
        out<<"The matrix has "<<lin<<" lines\n";
        return out;
    }

    virtual bool verifmatriceoarecare (const Matrice& mat){
        for(int i=1; i<=get_nr_line(); ++i)
        {
            if(get_v_dim()!=get_nr_line())
                return 1;
        }
        return 0;
    }

     Matrice_oarecare& operator=(const Matrice_oarecare& cpy)
    {
        if(this!=&cpy){
                Matrice::operator=(cpy);
                lin=cpy.lin;
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Matrice_oarecare& cpy){
        cpy.Matrice::operator>>(in);
        return cpy.matriceIn(in);
    }
    friend ostream& operator<<(ostream& out, Matrice_oarecare& cpy){
        cpy.Matrice::operator<<(out);
        return cpy.matriceOut(out);
    }
};

class Matrice_patratica:virtual public Matrice{
    int dim;
public:
    Matrice_patratica(): Matrice(),dim(){}
    Matrice_patratica(const Matrice_patratica& cpy): Matrice(cpy){
        this->dim=cpy.dim;
    }
    ~Matrice_patratica(){
        dim=0;
    }

    virtual bool verifmatricepatratica (const Matrice& mat){
        for(int i=1; i<=get_nr_line(); ++i)
        {
            if(get_v_dim() == get_nr_line())
                return 1;
        }
        return 0;
    }
    istream& matriceIn(istream& in){
        cout<<"Enter number of lines: ";
        in>>dim;
        return in;
    }

    ostream& matriceOut(ostream& out){
        out<<"The matrix has "<<dim<<" lines\n";
        return out;
    }
    Matrice_patratica& operator=(const Matrice_patratica& cpy)
    {
        if(this!=&cpy){
                Matrice::operator=(cpy);
                dim=cpy.dim;
        }
        return *this;
    }

    friend istream& operator>>(istream& in, Matrice_patratica& cpy){
        cpy.Matrice::operator>>(in);
        return cpy.matriceIn(in);
    }
    friend ostream& operator<<(ostream& out, Matrice_patratica& cpy){
        cpy.Matrice::operator<<(out);
        return cpy.matriceOut(out);
    }

};

int main()
{
    int nr_line;
    cout<<"Nr lines: ";
    cin>>nr_line;
    Vector v(100);
    v.setdim(nr_line);
    for (int i=1; i<=nr_line ;++i)
    {
        cin>>v;
    }
    int ok1=1;
    int ok2=1;
    int ok3=1;
    int ok4=1;
    for (int i=1;i<=nr_line;++i)
    {
        for(int j=1; j<=v.getdim(); ++j)
        {
            if(i<j && v(j)!=0)
            {
                ok1=0;
            }
            if(i>j && v(j)!=0)
               {
                   ok2=0;
               }
            if(i<v.getdim()-j && v(j)!=0)
                {
                    ok3=0;
                }
            if(i>v.getdim()-j && v(j)!=0)
            {
                ok4=0;
            }
        }
    }
    if(ok1||ok2||ok3||ok4)
        cout<<"Matrice triunghiulara";

    return 0;
}
