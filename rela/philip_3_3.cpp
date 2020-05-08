#include <iostream>
#include <math.h>

using namespace std;

void impmat(int n,int A[]);
int prodint(int n,int A[],int B[]);
void conm(int n,int A[],int B[]);
int det(int n,int A[]);
void inv(int n,int A[]);



int main (){

int Jx[16]={0,0,0,0,0,0,0,0,0,0,0,1,0,0,-1,0};
int Jy[16]={0,0,0,0,0,0,0,-1,0,0,0,0,0,1,0,0};
int Jz[16]={0,0,0,0,0,0,1,0,0,-1,0,0,0,0,0,0};
int Kx[16]={0,-1,0,0,-1,0,0,0,0,0,0,0,0,0,0,0};
int Ky[16]={0,0,-1,0,0,0,0,0,-1,0,0,0,0,0,0,0};
int Kz[16]={0,0,0,-1,0,0,0,0,0,0,0,0,-1,0,0,0};
int K[36]={};
int A[16]={};
int B[16]={};
int i,j,l,m;

for(i=0;i<36;i++){

l=i/6;
m=i%6;

switch(l){

case 0:
for(j=0;j<16;j++){
A[j]=Jx[j];
}

break;

case 1:
for(j=0;j<16;j++){
A[j]=Jy[j];
}

break;

case 2:
for(j=0;j<16;j++){
A[j]=Jz[j];
}
break;

case 3:
for(j=0;j<16;j++){
A[j]=Kx[j];
}
break;

case 4:
for(j=0;j<16;j++){
A[j]=Ky[j];
}
break;

case 5:
for(j=0;j<16;j++){
A[j]=Kz[j];
}
break;

default:
j=0;
}

switch(m){
  
case 0:
for(j=0;j<16;j++){
B[j]=Jx[j];
}

break;

case 1:
for(j=0;j<16;j++){
B[j]=Jy[j];
}
break;

case 2:
for(j=0;j<16;j++){
B[j]=Jz[j];
}
break;

case 3:
for(j=0;j<16;j++){
B[j]=Kx[j];
}
break;

case 4:
for(j=0;j<16;j++){
B[j]=Ky[j];
}
break;

case 5:
for(j=0;j<16;j++){
B[j]=Kz[j];
}
break;

default:

j=0;

}

K[i]=prodint(4,A,B);
}

cout<<"Indice 1 -> Jx"<<endl;
cout<<"Indice 2 -> Jy"<<endl;
cout<<"Indice 3 -> Jz"<<endl;
cout<<"Indice 4 -> Kx"<<endl;
cout<<"Indice 5 -> Ky"<<endl;
cout<<"Indice 6 -> Kz"<<endl;
cout<<"Metrica de Killing:"<<endl<<endl;

impmat(6,K);

cout<<"Metrica de Killing Inversa:"<<endl<<endl;
inv(6,K);

for(i=0;i<36;i++){

l=i/6;

m=i%6;

switch(l){

case 0:
for(j=0;j<16;j++){
A[j]=Jx[j];
}
break;

case 1:
for(j=0;j<16;j++){
A[j]=Jy[j];
}
break;

case 2:
for(j=0;j<16;j++){
A[j]=Jz[j];
}
break;

case 3:
for(j=0;j<16;j++){
A[j]=Kx[j];
}
break;

case 4:
for(j=0;j<16;j++){
A[j]=Ky[j];
}
break;

case 5:
for(j=0;j<16;j++){
A[j]=Kz[j];
}
break;

default:

j=0;

}

switch(m){

case 0:
for(j=0;j<16;j++){
B[j]=Jx[j];
}
break;

case 1:
for(j=0;j<16;j++){
B[j]=Jy[j];
}
break;

case 2:
for(j=0;j<16;j++){
B[j]=Jz[j];
}
break;

case 3:
for(j=0;j<16;j++){
B[j]=Kx[j];
}
break;

case 4:
for(j=0;j<16;j++){
B[j]=Ky[j];
}
break;

case 5:
for(j=0;j<16;j++){
B[j]=Kz[j];
}

break;

default:

j=0;

}

cout<<"["<<l+1<<","<<m+1<<"]="<<endl<<endl;

conm(4,A,B);

}

return 0;

}



void impmat(int n, int A[]){

int i;

for(i=0;i<(n*n);i++){

cout<<A[i]<<"   ";

if(((i+1)%n)==0) cout<<endl<<endl;

}

return;

}



int prodint(int n, int A[], int B[]){

int i,j,l,m,P=0;

int AB[36]={};

for(i=0;i<(n*n);i++){

l=i/n;

m=i%n;

for(j=0;j<n;j++){

AB[i]+=A[n*l+j]*B[m+j*n];

}

}

for(i=0;i<n;i++){

P+=AB[i*(n+1)];

}

P/=2;

return P;

}



void conm(int n, int A[], int B[]){

int i,j;
int C[36]={};
for(i=0;i<(n*n);i++){
for(j=0;j<n;j++){

C[i]+=A[n*(i/n)+j]B[i%n+j*n]-B[n(i/n)+j]*A[i%n+j*n];

}

}

impmat(n,C);

return;

}



int det(int n,int A[]){

int D;

if(n==1){

D=A[0];

}

else{

int i,j,k;

int B[36]={};

D=0;

for(i=0;i<n;i++){

k=0;

for(j=0;j<(n*n);j++){

if((j/n!=i/n)&&(j%n!=i%n)){

B[k]=A[j];

k++;

}

}

D+=pow(-1,i/n+i%n+2)*A[i]*det((n-1),B);

}

}

return D;

}



void inv(int n,int A[]){

int i,j,k,d;

d=det(n,A);

int B[36]={};

int C[36]={};

int D[36]={};

for(i=0;i<(n*n);i++){

k=0;

for(j=0;j<(n*n);j++){

if((j/n!=i/n)&&(j%n!=i%n)){

B[k]=A[j];

k++;

}

}

C[i]=pow(-1,i/n+i%n+2)*det(n-1,B);

}

for(i=0;i<(n*n);i++){

j=n*(i%n)+i/n;

D[i]=C[j]/d;

}

impmat(n,D);

return;

}

