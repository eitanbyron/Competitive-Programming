
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int siz = 2 ;

struct Mat{
    ll mat[siz][siz];
};
Mat matMul(Mat mat1, Mat mat2)
{
    Mat out{};
    for(int i = 0 ; i < siz ; i++)
        for(int j = 0 ; j < siz ; j++)
        {
            out.mat[i][j] = 0;
            for(int k = 0; k < siz ; k++){
                out.mat[i][j]= out.mat[i][j] + mat1.mat[i][k] * mat2.mat[k][j] ;
            }
        }
    return out;
}

Mat matExpo(Mat base, ll p)
{
    if(p == 1) {
        return base;
    }
    Mat out = matExpo(base, p / 2 );
    out = matMul(out, out);
    if(p&1) {
        out = matMul(out, base);
    }
    return out;
}

int main()
{
    Mat Base{} ;
    ll p , q , n ;
    while( cin >> p >> q >> n )
    {

        if( n == 0 ){
            cout << "2" << '\n';
            continue;
        }
        Base.mat[0][0] = p ;
        Base.mat[0][1] = -q ;
        Base.mat[1][0] = 1 ;
        Base.mat[1][1] = 0 ;

        Mat ret = matExpo(Base, n);
        ll ans =  ret.mat[1][0] * p  + ret.mat[1][1] * 2;
        cout << ans << '\n';
    }
}