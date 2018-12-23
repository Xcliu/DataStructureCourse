#include<iostream>
using namespace std;


class BMI{
      public:
	      int human_character[3];
	      BMI(int height_foot,int height_inch , int weight_ponds){
	      human_character[0]=height_foot;
	      human_character[1]=height_inch;
              human_character[2]=weight_ponds;
	      }
      
             double character_num[2];

	     void Trans(){
	          character_num[0]=(12*double(human_character[0])+double(human_character[1]))*0.0254;
	          //cout << double(human_character[2]) << endl;
		  character_num[1]=double(human_character[2])/2.2; 	  
	          //cout << character_num[0] << "," << character_num[1] << endl;
	     }
		
	     double BMI_value;

	     void cal_BMI(){
	          BMI_value=character_num[1]/(character_num[0]*character_num[0] );  
	          cout << "your BMI is " << BMI_value << endl; 
	    
	    
	     }

};

int main(){
    cout << "Please input your height and weight(For example , foot inch ponds) : ";
    int a,b,c;
    cin >> a >> b >> c;
    //cout << a << "," << b << "," << c << endl; 
    BMI character(a,b,c);
    character.Trans();
    character.cal_BMI();  
    return 0;

}
