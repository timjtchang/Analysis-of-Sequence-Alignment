#include<iostream>
#include<vector>
#include<fstream>
#include<unordered_map>
#include <sys/resource.h> 
#include <sys/time.h>
#include <errno.h> 
#include <limits.h>
#include <unordered_set>

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

void basic_alignment( int A_start, int A_end, int B_start, int B_end, unordered_map<int, vector<int> >& ArrowPath, const string& A, const string& B, unordered_map< char, unordered_map< char, int> >& mp, const int& gp  ){

    int m = A_end-A_start;
    int n = B_end-B_start;

    vector< vector<int> > memo( m+1, vector<int>(n+1,0) );

    memo[0][0] = 0;

    int i, j;

    for( j=1 ; j<=n ; ++j ) memo[0][j] = memo[0][j-1]+gp;

    for( i=1 ; i<=m ; ++i ) memo[i][0] = memo[i-1][0]+gp;

    for( i=1 ; i<=m ; ++i ){

        for( j=1 ; j<=n ; j++ ){

           memo[i][j] = min( memo[i-1][j-1]+mp[ A[A_start+i-1] ][ B[B_start+j-1]], min( memo[i-1][j]+gp, memo[i][j-1]+gp ) );

        }
    }

    int y=m;
    int x=n;



    while( y>0 && x>0 ){   

        ArrowPath[x+B_start].push_back(y+A_start);

        int dia = memo[y-1][x-1]+mp[ A[A_start+y-1] ][ B[B_start+x-1] ];
        int left = memo[y][x-1]+gp;
        int up = memo[y-1][x]+gp;

        if( dia<=left && dia<=up ){

            y--;
            x--;

        }else if( up<=left && up<=dia ) y--;
        else if( left<=up && left<=dia ) x--;
        else break;

    }

    while( y>0 ){

        ArrowPath[x+B_start].push_back(y+A_start);
        y--;
    } 
    while( x>0 ){

        ArrowPath[x+B_start].push_back(y+A_start);
        x--;
    } 

}

vector<int> getPrefix( int A_start, int A_end, int start, int end, string& A, string& B, unordered_map< char, unordered_map< char, int> >& mp, int& gp  ){

    int m = A_end-A_start;
    int n = end-start;

    vector<int> result;

    int memo[n+1];
    int row[n+1];

    int i, j;

    memo[0] = 0;
    for( j=1 ; j<=n ; ++j ) memo[j] = memo[j-1]+gp;

    for( i=1 ; i<=m ; ++i ){

        result.push_back(memo[n]);
        row[0]=memo[0]+gp; 

        for( j=1 ; j<=n ; j++ ){
            
            row[j] = min( memo[j-1]+mp[ A[A_start+i-1] ][ B[start+j-1] ], min( memo[j]+gp, row[j-1]+gp ) );
            memo[j-1] = row[j-1];

        }

        memo[n] = row[n];

    }

    result.push_back(memo[n]);

    return result;

}

vector<int> getSuffix( int A_start, int A_end, int start, int end, string& A, string& B, unordered_map< char, unordered_map< char, int> >& mp, int& gp  ){

    int m = A_end-A_start;
    int n = end-start;

    vector<int> result;

    int memo[n+1];
    int row[n+1];

    int i, j;

    memo[0] = 0;
    for( j=1 ; j<=n ; ++j ) memo[j] = memo[j-1]+gp;

    for( i=1; i<=m ; ++i ){

        result.push_back(memo[n]);
        row[0]=memo[0]+gp; 

        for( j=1 ; j<=n ; ++j ){
            
            row[j] = min( memo[j-1]+mp[ A[A_end-i] ][ B[end-j] ], min( memo[j]+gp, row[j-1]+gp ) );
            memo[j-1] = row[j-1];

        }

        memo[n] = row[n];

    }

    result.push_back(memo[n]);

    reverse( result.begin(), result.end() );

    return result;

}



void Align( int A_start, int A_end, int B_start, int B_end, unordered_map< int, vector<int> >& ArrowPath, string& A, string& B, unordered_map< char, unordered_map< char, int> >& mp, int& gp ){

    vector<int> col;

    int m = B_end-B_start;
    int n = A_end-A_start;

    if( B_end-B_start==1 || A_end-A_start<=2 ) basic_alignment( A_start, A_end , B_start, B_end, ArrowPath, A, B, mp, gp );
    else{

        vector<int> prefix = getPrefix( A_start, A_end, B_start, B_start+(m/2), A, B, mp, gp );
        vector<int> suffix = getSuffix( A_start, A_end, B_start+(m/2), B_end, A, B, mp, gp );

        int best_cost = INT_MAX;
        int bestq=0;
        int cost;

        for( int q=0 ; q<=A_end-A_start ; q++ ){

            cost = prefix[q]+suffix[q];

            if( cost<best_cost ){

                bestq = q;
                best_cost = cost;

            } 

        }

        ArrowPath[B_start+(m/2)].push_back( A_start+bestq );

        if( bestq==0 ) Align( A_start, A_end, B_start+(m/2), B_end,ArrowPath, A, B, mp, gp );
        else{

            Align( A_start, A_start+bestq, B_start, B_start+(m/2),ArrowPath, A, B, mp, gp );
            Align( A_start+bestq, A_end, B_start+(m/2), B_end,ArrowPath, A, B, mp, gp );
        }
   
    }


}

void solution( string input, FILE* outfp){

    string A="TCGGTCA";
    string B="ACGGA";

    generate(A, B, input);
    

    unordered_map< char, unordered_map< char, int> > mp;
    build_penalty_map(mp);

    int gp=30;

    vector<int> col;

    unordered_map< int, vector<int> > ArrowPath;

    struct timeval begin, end; 
    gettimeofday(&begin, 0);

    Align( 0, A.size(), 0, B.size(), ArrowPath, A, B, mp, gp );
    ArrowPath[0].push_back(0);

    int y=A.size();
    int x=B.size();

    int cur_x = x;
    int cur_y = y;
    int tmp_y = INT_MIN;

    int penalty=0;

    string a_alignment = "";
    string b_alignment = "";

    while( x>=0 ){

        sort( ArrowPath[x].begin(), ArrowPath[x].end() );

        while(1){

            if( ArrowPath[x].size() == 0 ) break;

            tmp_y = ArrowPath[x].back();
            ArrowPath[x].pop_back();

            if( cur_x==x && tmp_y == cur_y ) continue;
            else if( cur_x == x+1 && cur_y == tmp_y+1 ){
                
                a_alignment.push_back( A[cur_y-1] );
                b_alignment.push_back( B[cur_x-1] );

                penalty+=mp[A[cur_y-1]][B[cur_x-1]];

            }else if(cur_x == x+1 && cur_y == tmp_y ){

                a_alignment.push_back( '_' );
                b_alignment.push_back( B[cur_x-1] );
                penalty+=gp;

            }else{

                a_alignment.push_back( A[cur_y-1] );
                b_alignment.push_back('_');
                penalty+=gp;

            }

            cur_x = x;
            cur_y = tmp_y;

        }

        x--;

    }

    reverse( a_alignment.begin(), a_alignment.end() );
    reverse( b_alignment.begin(), b_alignment.end() );

    //selfCheck( a_alignment, b_alignment, mp, penalty );

    double totalmemory = getTotalMemory(); 
   
    gettimeofday(&end, 0); 
    long seconds = end.tv_sec - begin.tv_sec;
    long microseconds = end.tv_usec - begin.tv_usec; 
    double totaltime = seconds*1000 + microseconds*1e-3; 

    fprintf( outfp, "%d\n%s\n%s\n%f\n%f", penalty, a_alignment.c_str(), b_alignment.c_str(), totaltime, totalmemory );

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