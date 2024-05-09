#include<iostream>
#include<vector>
#include<fstream>
#include<unordered_map>
#include <sys/resource.h> 
#include <sys/time.h>
#include <errno.h> 

extern int errno;

using namespace std;

long getTotalMemory() { 
    
    struct rusage usage;
    int returnCode = getrusage(RUSAGE_SELF, &usage); 

    if(returnCode == 0) return usage.ru_maxrss;
    else printf("error %d", errno); return -1;

}


void selfCheck( string& A, string& B, unordered_map< char, unordered_map< char, int> >& mp, int penalty ){

    int p = 0;
    for( int i=0 ; i<A.size() ; i++ ){

        if( A[i]==B[i] ) continue;
        else if( A[i]=='_' && B[i]=='_' ) continue;
        else if( A[i]=='_' || B[i]=='_' ) p+=30;
        else{

            p+=mp[A[i]][B[i]];
        }

    }

    if( penalty == p ) cout<<"Correct"<<endl;
    else{

        cout<<"The answer should be: "<< p <<endl;
        cout<<"My answer is: "<< penalty <<endl;
    }
    
}

void build_penalty_map( unordered_map< char, unordered_map< char, int> >& mp ){
    
    mp['_']['_']=0;

    mp['A']['A']=0;
    mp['A']['C']=110;
    mp['A']['G']=48;
    mp['A']['T']=94;

    mp['C']['A']=110;
    mp['C']['C']=0;
    mp['C']['G']=118;
    mp['C']['T']=48;

    mp['G']['A']=48;
    mp['G']['C']=118;
    mp['G']['G']=0;
    mp['G']['T']=110;

    mp['T']['A']=94;
    mp['T']['C']=48;
    mp['T']['G']=110;
    mp['T']['T']=0;
    
    
}

void generate( string& A, string& B, const string& input ){

    ifstream file(input);

    A="";
    B="";

    if( file.is_open() ){

        string line;
        getline(file,line);

        while( line.back()<'A' || line.back()>'Z' ) line.pop_back();
        A=line;

        while( getline(file,line)){

            if( line[0]>='0' && line[0]<='9' ){

                string tmp=A;
                int number = stoi(line);

                A="";

                A.append( tmp.begin(), tmp.begin()+number+1 );
                A.append(tmp);
                A.append( tmp.begin()+number+1, tmp.end() );


            }else{

                while( line.back()<'A' || line.back()>'Z' ) line.pop_back();
                B=line;
                break;
            }

        }

        while( getline(file,line)){

            if( line[0]>='0' && line[0]<='9' ){

                string tmp=B;
                int number=stoi(line);

                B="";
                B.append( tmp.begin(), tmp.begin()+number+1 );
                B.append(tmp);
                B.append( tmp.begin()+number+1, tmp.end() );



            }else break;

        }

        file.close();

    }else cout<<"File cannot open!"<<endl;

}

void solution( string input, FILE* outfp ){

    string A="GACT";
    string B="TAGT";

    generate(A, B, input);

    unordered_map< char, unordered_map< char, int> > mp;
    build_penalty_map(mp);

    int m = A.size();
    int n = B.size();
    int gp = 30; // gap panelty

    struct timeval begin, end; 
    gettimeofday(&begin, 0);

    vector< vector<int> > memo( m+1, vector<int>(n+1,0) );

    memo[0][0] = 0;

    int i, j;

    for( j=1 ; j<=n ; ++j ) memo[0][j] = memo[0][j-1]+gp;

    for( i=1 ; i<=m ; ++i ) memo[i][0] = memo[i-1][0]+gp;

    for( i=1 ; i<=m ; ++i ){

        for( j=1 ; j<=n ; j++ ){

           memo[i][j] = min( memo[i-1][j-1]+mp[ A[i-1] ][ B[j-1]], min( memo[i-1][j]+gp, memo[i][j-1]+gp ) );

        }
    }

    string a_alignment="";
    string b_alignment="";

    int y=m;
    int x=n;

    while( y>0 && x>0 ){   

        int dia = memo[y-1][x-1]+mp[ A[y-1] ][ B[x-1] ];
        int left = memo[y][x-1]+gp;
        int up = memo[y-1][x]+gp;

        if( dia<=left && dia<=up ){

            a_alignment+=A[y-1];
            b_alignment+=B[x-1];

            y--;
            x--;

        }else if( up<=left && up<=dia ){

            a_alignment+=A[y-1];
            b_alignment+="_";

            y--;

            
        }else{

            a_alignment+="_";
            b_alignment+=B[x-1];

            x--;

        }

    }

    while( y>0 ){

        a_alignment+=A[y-1];
        b_alignment+="_";

        y--;

    }

    while( x>0 ){

        a_alignment+="_";
        b_alignment+=B[x-1];

        x--;

    }

    
    reverse( a_alignment.begin(), a_alignment.end() );
    reverse( b_alignment.begin(), b_alignment.end() );

    double totalmemory = getTotalMemory(); 
   
    gettimeofday(&end, 0); 
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec; 
    double totaltime = seconds*1000 + microseconds*1e-3; 

    //selfCheck( a_alignment, b_alignment, mp, memo[m][n] );

    fprintf( outfp, "%d\n%s\n%s\n%f\n%f", memo[m][n], a_alignment.c_str(), b_alignment.c_str(), totaltime, totalmemory );


}

int main( int argc, char *argv[] ){

    string input = argv[1];
    string output = argv[2];

    FILE *outfp;
    outfp = fopen( output.c_str(), "w+");

    solution( input, outfp);
    
}

/*

A-A = 0
C-C = 0
G-G = 0
T-T = 0
A-C = 110
A-G = 48
A-T = 94
C-G = 118
C-T = 48
G-T = 110

AC_TTG
AGGC_G
48+30+48+30 = 150

*/