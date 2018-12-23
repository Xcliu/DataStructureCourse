#include<iostream>
using namespace std;
int queen_node[8][8]={{0}};
bool queen_check(int i,int j,int queen_num);
void Queen_solu(int row,int queen_num);
void dispaly(int queen_num);

void Queen_solu(int row,int queen_num){
	int column;
     for(column=0;column<queen_num;column++){
         if(queen_check(row,column,queen_num)==true){
             queen_node[row][column]=1;
             if(row==queen_num-1){
                dispaly(queen_num);
		cout << "###########" << endl;
             }
            Queen_solu(row+1,queen_num);
	    queen_node[row][column]=0;
         }
     } 
}

bool queen_check(int i ,int j,int queen_num){
     	int k;
	for(k=0;k<queen_num;k++){
         if(queen_node[i][k]==1){return false;}
         if(queen_node[k][j]==1){return false;}   
         if(i-k>=0&&j-k>=0){if(queen_node[i-k][j-k]==1){return false;}}
         if(i-k>=0&&j+k<queen_num){if(queen_node[i-k][j+k]==1){return false;}}
         if(i+k<queen_num&&j+k<queen_num){if(queen_node[i+k][j+k]==1){return false;}}
         if(i+k<queen_num&&j-k>=0){if(queen_node[i+k][j-k]==1){return false;}} 
	 }
    	//cout << "fucking" << endl;
	return true;   
}

void dispaly(int queen_num){
	int i;int j;
    for(i=0;i<queen_num;i++){
        for(j=0;j<queen_num;j++){
            if(j==queen_num-1){cout << queen_node[i][j] << endl;}
            else{cout << queen_node[i][j];}
        }
    }
}

int main(){
    Queen_solu(0,8);
    return 0;
}
