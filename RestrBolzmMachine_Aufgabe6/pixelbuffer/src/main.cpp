//cover up bad practise coding
#define _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4244)
#pragma warning( disable : 4018)

#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "hwFunctions.h"
#include "MnistReader.h"
#include <chrono>
#include <iostream>

// graphical output_size
#define width 900
#define height 350

// --- Deep Net
#define NEURONS 28*28+10
#define OUTNEURONS 10
static double LERNRATE = 2;
static int lernCycle = 2000;

#define GREEN 0,1,0
#define BLUE 0,0,1

static unsigned int m_z=12345,m_w=45678;

MnistReader letters;


unsigned int randomGen()
{
    m_z = 36969 * (m_z & 65535) + (m_z >> 16);
    m_w = 18000 * (m_w & 65535) + (m_w >> 16);
    return (m_z << 16) + m_w;
}
void init(double weights[NEURONS][NEURONS]){
	for (int t=0;t<NEURONS;t++){
		for (int neuron=0; neuron<NEURONS; neuron++){
			weights[neuron][t]=randomGen()%2000/1000.0-1.0;
		}
	}
}
void activateForward(double input[], double weights[NEURONS][NEURONS],double output[]){

	// insert code here
	for (int i = 0; i < NEURONS; i++) {
		output[i] = 0;
		for (int j = 0; j < NEURONS - OUTNEURONS; j++) {
			output[i] += weights[i][j] * input[j];
		}
		if (output[i] > 1) {
			output[i] = 1;
		}
		else if (output[i] < 0) {
			output[i] = 0;
		}
	}

}
void activateReconstruction(double input[], double weights[NEURONS][NEURONS],double output[]){
	
	// insert code here
	for (int i = 0; i < NEURONS; i++) {
		input[i] = 0;
		for (int j = 0; j < NEURONS; j++) {
			input[i] += weights[j][i] * output[j];
		}
		if (input[i] > 1) {
			input[i] = 1;
		}
		else if (input[i] < 0) {
			input[i] = 0;
		}
	}

}

void contrastiveDivergence(double input[], double output[], double reconstructed_input[], double weights[NEURONS][NEURONS])
{
	
	double deltaW = 0;
	// insert code here
	for (int i = 0; i < NEURONS; i++) {
		for (int j = 0; j < NEURONS; j++) {
			deltaW = LERNRATE * output[i] * (input[j] - reconstructed_input[j]);
			weights[i][j] += deltaW;
		}
	}

}


void drawActivity(int xx, int yy, double neuron[],float red, float green, float blue){
	int i=0;
	for (int y=0;y<28;y++){
		for (int x=0;x<28;x++){
			setColor(red*neuron[i],green*neuron[i],blue*neuron[i]);
			drawBox(x*10+xx,y*10+yy,x*10+8+xx,y*10+8+yy);
			i++;
		}
	}
	int y=29;
	for (int x=0;x<10;x++){
		setColor(red*neuron[i],green*neuron[i],blue*neuron[i]);
		drawBox(x*10+xx,y*10+yy,x*10+8+xx,y*10+8+yy);
		i++;
	}

}

void trainOrTestNet(bool train, int maxCount,float red,float green,float blue){
	static double weights[NEURONS][NEURONS];
	static double output[NEURONS];
	static double input[NEURONS];
	static double reconstructed_input[NEURONS];
	int correct = 0;

	char text[1000];

	FILE *outFile;
	outFile = fopen("result.txt","wb");
	
	if (train){
		init(weights);
	}
	int pattern=0;
    for (int count=1; count<maxCount; count++){
		// --- training phase

		for (int t=0;t<NEURONS-10;t++){
			input[t]=letters.trainImage[pattern%100][t]; // initialize original pattern
		}
		for (int t=NEURONS-10;t<NEURONS;t++){
			input[t]=0;
		}
		if (train){
			// --- use the label also as input!
			if (letters.trainLabel[pattern%100]>=0 && letters.trainLabel[pattern%100]<10){
				input[NEURONS-10+letters.trainLabel[pattern%100]] = 1.0;
			}
		}

		drawActivity(0,0,input,red,green,blue);

		// --- Contrastive divergence
		// Activation
		input[0] = 1;					// bias neuron!
		activateForward(input,weights,output); // positive Phase
		output[0] = 1;					// bias neuron!

		drawActivity(300,0,output,red,green,blue);

		activateReconstruction(reconstructed_input,weights,output); // negative phase/ reconstruction

		drawActivity(600,0,reconstructed_input,red,green,blue);
		if (train){
			contrastiveDivergence(input,output,reconstructed_input,weights);
		}

		if (count%51==0){
			sprintf(text,"Zahl:%d",letters.trainLabel[pattern%100]);
			setColor(1,0,0);
			glPrint(10,340,text);

			sprintf(text,"Trainingsmuster:%d                 Erkennungsrate:%f %%",count,(float)(correct)/(float)(count)*100);
			setColor(1,0,0);
			glPrint(10,320,text);
			for (int t=0;t<10;t++){
				display();
				glutMainLoopEvent();
			}
		}

		if (!train){
			int number = 0;
			for (int t=NEURONS-10;t<NEURONS;t++){
				if (reconstructed_input[t]>reconstructed_input[NEURONS-10+number]){
					number = t-(NEURONS-10);
				}
			}
			if (letters.trainLabel[pattern%100]==number){
				fprintf(outFile,"Muster: %d, Erkannt: %d KORREKT!!!\n",letters.trainLabel[pattern%100],number);
				correct++;
			}
			else{
				fprintf(outFile,"Muster: %d, Erkannt: %d \n",letters.trainLabel[pattern%100],number);
			}
		}

		pattern++;
	}

	fclose(outFile);

}

int main(int argc, char** argv){

	initWindow(argc,argv,width,height,"Restricted Bolzmann Machine");
	std::chrono::time_point<std::chrono::system_clock> t1, t2, t3;
	t1 = std::chrono::system_clock::now();
	
	trainOrTestNet(true,lernCycle,BLUE);
	
	t2 = std::chrono::system_clock::now();
	
	trainOrTestNet(false,1000,GREEN);
	
	t3 = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = t2 - t1;
	std::cout << elapsed_seconds.count() << std::endl;
	elapsed_seconds = t3 - t2;
	std::cout << elapsed_seconds.count() << std::endl;
	char a;
	std::cin >> a;
}