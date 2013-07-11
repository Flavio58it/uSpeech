#include "uspeech.h"
/**
* The recognizer function
*/
char signal::getPhoneme(){
	sample();
	if(power()>SILENCE){
		//Low pass filter for noise removal
		int k = complexity(power()); 
		overview[6] = overview[5];
		overview[5] = overview[4];
		overview[4] = overview[3];
		overview[3] = overview[2];
		overview[2] = overview[1];
		overview[1] = overview[0];
		overview[0] = k;
		int coeff = 0;
		char f = 0;
		while(f<6){
			coeff += overview[f];
			f++;
		}
		coeff /= 7;
		//Serial.println(coeff); //Use this for debugging
#if F_DETECTION > 0
        micPower = 0.05 * maxPower() + (1 - 0.05) * micPower;
        //Serial.println(micPower)//If you are having trouble with fs
        
        if (micPower > F_CONSTANT/*Use the header file to change this*/) {
            return 'f';
        }
#endif
	//Twiddle with the numbers here if your getting false triggers
	//This is the main recognizer part
	//Todo: use move values to header file
		if(coeff<30 && coeff>20){
			return 'u';
		}
		else {
			if(coeff<33){
				return 'e';
			}
			else{
				if(coeff<46){
					return 'o';
				}
				else{
					if(coeff<60){
						return 'v';
					}
					else{
						if(coeff<80){
							return 'h';
						}
						else{
							if(coeff>80){
								return 's';
							}
							else{
								return 'm';
							}
						}
					}
				}
			}
		}
	}
	else{
		return ' ';
	}
}
void signal::formantAnal(){
	int i = 0;
	int k = 0;
	while(i<18){
		if((long)(filters[i]-filters[i-1]) > 0 & (long)(filters[i]-filters[i+1]) < 0){
			if(k < 3){
				formants[k] = i;
			}
		}
		i++;
	}
}
