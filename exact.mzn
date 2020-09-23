% Use this editor as a MiniZinc scratch book
include "large3.dzn";
int :row;
int :col;
int :maxi;
 array[1..row,1..col] of int:arr;
array [1..maxi] of var 0..1:x;

constraint  sum(i in 1..maxi)(x[i])>0;
/*constraint sum(i in 1..n)(m[i,n+1-i])=n*(n*n+1)/2;*/
constraint forall (i in 1..row)( (sum(j in 1..col where arr[i,j]>0)(x[arr[i,j]] )) mod 2=0);
/*constraint forall (j in 1..n)( (sum(i in 1..n)(m[i,j]))=n*(n*n+1)/2);*/
var int :count=sum(i in 1..maxi)(x[i]);
solve minimize count;
output[show(count),"\n"];
output[show(x[i])| i in 1..maxi];