#include "SimpleSlicerWindow.h"
#include "ArcBall.h"
#include "TransferFunction.h"
#include "gluiVars.h"
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <GLUT/glut.h>
#include <GLUI/glui.h>
#include <assert.h>
#include <string>
#include <fstream>
#include "LoadConfig.cpp"

using namespace std;

//global variables
int m_bDisplayTF = 3;
int vol_data1 = 0;
int vol_data2 = 1;

int vol_data1C = 0;
int vol_data2C = 1;

int col_data1 = 0;
int col_data2 = 0;
int showVol1 = 1;
int showVol2 = 0;
int m_nMode = 0;
int scaleColorMap = 1;
int scaleColorMapC = 1;
int filter[12] = {1,1,1,1,1,1,1,1,1,1,1,1};
int filterC[12] = {1,1,1,1,1,1,1,1,1,1,1,1};
int generateFile = 0;

int Vol1Slit[6] = {1,1,1,1,1,1};
int Vol2Slit[6] = {1,1,1,1,1,1};
int Vol1Img[8] = {1,1,1,1,1,1,1,1};
int Vol2Img[8] = {1,1,1,1,1,1,1,1};
int blobCheckBox[14] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1};
int blobCheckBoxC[14] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1};


//checks for changes, to reload 3D texture
int Vol1SlitC[6] = {1,1,1,1,1,1};
int Vol2SlitC[6] = {1,1,1,1,1,1};
int Vol1ImgC[8] = 	{1,1,1,1,1,1,1,1};
int Vol2ImgC[8] = 	{1,1,1,1,1,1,1,1};

int boundBox = 1;

double min1 = 255.0, max1 = 0.0, temp1 = 0.0;
double min2 = 255.0, max2 = 0.0, temp2 = 0.0;
double min3 = 255.0, max3 = 0.0, temp3 = 0.0;
double min4 = 255.0, max4 = 0.0, temp4 = 0.0;

bool initialLoad1 = true;
bool initialLoad2 = true;
bool initialLoad3 = true;
bool initialLoad4 = true;
bool initialLoad5 = true;
unsigned char *pVolTemp  = NULL;
unsigned char *pVolTemp1 = NULL;
unsigned char *pVolTemp2 = NULL;
unsigned char *pVolTemp3 = NULL;
unsigned char *pVolTemp4 = NULL;
int *input[6];
int blobID[6][8][256];
int *pMask;
int *pMask1;
int *pMask2;
int *pMask3;
int *pMask4;
int *pMask5;
int *pMask6;
int *pMask7;
int *pMask8;
int *pMask9;
int *pMask10;
int *pMask11;
int *pMask12;
int maskCount[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };


CSimpleSlicerWindow::CSimpleSlicerWindow()
{
	//initialize starting position of cone model
	xCent = 0.5;
	yCent = 0.825;
	zCent = 0.65;
	r_div_h = 220;
    
	m_pVertices[0] = CVector(-1.0,-1.0,-1.0, 1.0,  0.0, 0.0, 0.0);
	m_pVertices[1] = CVector( 1.0,-1.0,-1.0, 1.0,  1.0, 0.0, 0.0);
	m_pVertices[2] = CVector( 1.0, 1.0,-1.0, 1.0,  1.0, 1.0, 0.0);
	m_pVertices[3] = CVector(-1.0, 1.0,-1.0, 1.0,  0.0, 1.0, 0.0);
    
	m_pVertices[4] = CVector(-1.0,-1.0, 1.0, 1.0,  0.0, 0.0, 1.0);
	m_pVertices[5] = CVector( 1.0,-1.0, 1.0, 1.0,  1.0, 0.0, 1.0);
	m_pVertices[6] = CVector( 1.0, 1.0, 1.0, 1.0,  1.0, 1.0, 1.0);
	m_pVertices[7] = CVector(-1.0, 1.0, 1.0, 1.0,  0.0, 1.0, 1.0);
    
	m_pEdges[0]  = Edge(0,1);
	m_pEdges[1]  = Edge(1,2);
	m_pEdges[2]  = Edge(2,3);
	m_pEdges[3]  = Edge(3,0);
	m_pEdges[4]  = Edge(0,4);
	m_pEdges[5]  = Edge(1,5);
	m_pEdges[6]  = Edge(2,6);
	m_pEdges[7]  = Edge(3,7);
	m_pEdges[8]  = Edge(4,5);
	m_pEdges[9]  = Edge(5,6);
	m_pEdges[10] = Edge(6,7);
	m_pEdges[11] = Edge(7,4);
    
	m_nNumSlices = 512;
	m_nWidth = 0;
	m_nHeight = 0;
    
	//initialize transfer functions with color map and trapazoid position
	m_pTransferFunction   = new CTransferFunction(getRoot("/Desktop/data/ColorMap1D_12.ppm"),5,120,255,255,60);
    m_pTransferFunction1  = new CTransferFunction(getRoot("/Desktop/data/ColorMap1D_11.ppm"),50,120,255,255,20);
    readMask();
    
}

CSimpleSlicerWindow::~CSimpleSlicerWindow(void)
{
    
}

// RATIO DATA
void CSimpleSlicerWindow::loadTex1() {
    
    
    cout << "inside LoadTex1" << endl;
	int size = XMAX*YMAX*ZMAX;
    
	//FIST PASS
	if(initialLoad1) {
		pVolTemp = new unsigned char[size];
		memset(pVolTemp,0,size*sizeof(unsigned char));
		unsigned char *pVolume = new unsigned char[size];
		memset(pVolume,0,size*sizeof(unsigned char));
		int i, j, k;
		short c;
        
		ifstream file_in[6];
        
        switch (vol_data1) {
            case 0:
                file_in[0].open(getRoot(VOL1_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL1_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL1_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL1_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL1_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL1_SLIT6), ios::in | ios::binary);
                break;
            case 1:
                cout << "opening another tex1" << endl;
                file_in[0].open(getRoot(VOL2_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL2_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL2_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL2_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL2_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL2_SLIT6), ios::in | ios::binary);
                break;
            case 2:
                file_in[0].open(getRoot(VOL3_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL3_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL3_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL3_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL3_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL3_SLIT6), ios::in | ios::binary);
                break;
            case 3:
                file_in[0].open(getRoot(VOL4_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL4_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL4_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL4_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL4_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL4_SLIT6), ios::in | ios::binary);
                break;
            case 4:
                file_in[0].open(getRoot(VOL5_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL5_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL5_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL5_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL5_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL5_SLIT6), ios::in | ios::binary);
                break;
            case 5:
                file_in[0].open(getRoot(VOL6_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL6_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL6_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL6_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL6_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL6_SLIT6), ios::in | ios::binary);
                break;
            case 6:
                file_in[0].open(getRoot(VOL7_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL7_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL7_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL7_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL7_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL7_SLIT6), ios::in | ios::binary);
                break;
            case 7:
                file_in[0].open(getRoot(VOL8_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL8_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL8_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL8_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL8_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL8_SLIT6), ios::in | ios::binary);
                break;
            case 8:
                file_in[0].open(getRoot(VOL9_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL9_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL9_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL9_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL9_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL9_SLIT6), ios::in | ios::binary);
                break;
            case 9:
                file_in[0].open(getRoot(VOL10_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL10_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL10_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL10_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL10_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL10_SLIT6), ios::in | ios::binary);
                break;                
            case 10:
                file_in[0].open(getRoot(VOL11_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL11_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL11_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL11_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL11_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL11_SLIT6), ios::in | ios::binary);
                break;                
            case 11:
                file_in[0].open(getRoot(VOL12_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL12_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL12_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL12_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL12_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL12_SLIT6), ios::in | ios::binary);
                break;     
            case 12:
                file_in[0].open(getRoot(VOL13_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL13_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL13_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL13_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL13_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL13_SLIT6), ios::in | ios::binary);
                break;     
            case 13:
                file_in[0].open(getRoot(VOL14_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL14_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL14_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL14_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL14_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL14_SLIT6), ios::in | ios::binary);
                break;     
            case 14:
                file_in[0].open(getRoot(VOL15_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL15_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL15_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL15_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL15_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL15_SLIT6), ios::in | ios::binary);
                break;     
            case 15:
                file_in[0].open(getRoot(VOL16_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL16_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL16_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL16_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL16_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL16_SLIT6), ios::in | ios::binary);
                break;     
            case 16:
                file_in[0].open(getRoot(VOL17_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL17_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL17_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL17_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL17_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL17_SLIT6), ios::in | ios::binary);
                break;     
            case 17:
                file_in[0].open(getRoot(VOL18_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL18_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL18_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL18_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL18_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL18_SLIT6), ios::in | ios::binary);
                break;     
            case 18:
                file_in[0].open(getRoot(VOL19_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL19_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL19_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL19_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL19_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL19_SLIT6), ios::in | ios::binary);
                break;     
            case 19:
                file_in[0].open(getRoot(VOL20_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL20_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL20_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL20_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL20_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL20_SLIT6), ios::in | ios::binary);
                break;     
            case 20:
                file_in[0].open(getRoot(VOL21_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL21_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL21_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL21_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL21_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL21_SLIT6), ios::in | ios::binary);
                break;     
            case 21:
                file_in[0].open(getRoot(VOL22_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL22_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL22_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL22_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL22_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL22_SLIT6), ios::in | ios::binary);
                break;     
            case 22:
                file_in[0].open(getRoot(VOL23_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL23_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL23_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL23_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL23_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL23_SLIT6), ios::in | ios::binary);
                break;     
            case 23:
                file_in[0].open(getRoot(VOL24_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL24_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL24_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL24_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL24_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL24_SLIT6), ios::in | ios::binary);
                break;     
            case 24:
                file_in[0].open(getRoot(VOL25_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL25_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL25_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL25_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL25_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL25_SLIT6), ios::in | ios::binary);
                break;     
            default:
                break;
        }
        
		input[0] = new int[512*512];
		input[1] = new int[512*512];
		input[2] = new int[512*512];
		input[3] = new int[512*512];
		input[4] = new int[512*512];
		input[5] = new int[512*512];
        
		file_in[0].read(reinterpret_cast<char*>(input[0]),512*512*sizeof(int));
		file_in[1].read(reinterpret_cast<char*>(input[1]),512*512*sizeof(int));
		file_in[2].read(reinterpret_cast<char*>(input[2]),512*512*sizeof(int));
		file_in[3].read(reinterpret_cast<char*>(input[3]),512*512*sizeof(int));
		file_in[4].read(reinterpret_cast<char*>(input[4]),512*512*sizeof(int));
		file_in[5].read(reinterpret_cast<char*>(input[5]),512*512*sizeof(int));
		int ndx=0;
        
		//Create Volume
		for(i=0; i<ZMAX; i++){
			ndx = 0;
			for(j=0; j<YMAX; j++){
				for(k=0; k<XMAX; k++){
					if(i>8 && i<=56){
						if (i %8 == 1) {
							c = input[(i-9)/8][ndx];
                            pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char)(c);
							ndx++;
						}
                        else {
							pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = pVolume[(((((i-1)/8)*8) +1)*YMAX*XMAX)+(j*XMAX)+k];
						}
					}
					else {
						pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char) 0;
                    }
                    if (k == 0) {
                        pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char) 0;
                        
                    }
                    
				}
			}
		}
		for(k=0; k<6; k++)
			file_in[k].close();
        
        if (!initialLoad1) {
            filterData1(pVolume);
        }
        
		glGenTextures(2,m_pTextureids);
		glBindTexture(GL_TEXTURE_3D,m_pTextureids[0]);
        
		//======================== FILE READ IN =============================
        
        
		// set the texture parameters
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
		glTexImage3D(GL_TEXTURE_3D,0,GL_INTENSITY,XMAX,YMAX,ZMAX,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,pVolume);
        
		for(i=0; i<ZMAX; i++){
			for(j=0; j<YMAX; j++){
				for(k=0; k<XMAX; k++){
					pVolTemp[(i*YMAX*XMAX)+(j*XMAX)+k] = pVolume[(i*YMAX*XMAX)+(j*XMAX)+k];
				}
			}
		}
        
		delete [] pVolume;
        generateMask();
	}
	//ANY OTHER PASS
	if(! initialLoad1){
		unsigned char *pVolume = new unsigned char[size];
		memset(pVolume,0,size*sizeof(unsigned char));
		int i, j, k;
        
		for(i=0; i<ZMAX; i++){
			for(j=0; j<YMAX; j++){
				for(k=0; k<XMAX; k++){
					pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = pVolTemp[(i*YMAX*XMAX)+(j*XMAX)+k];
                    
					if(i>8 && i<=56) {
                        
						//EDIT VIEWABLE SLICES
						if(i>8  && i<=16 && Vol1Slit[0] == 0) {
							pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char) 0;
							continue;
						}
						if(i>16 && i<=24 && Vol1Slit[1] == 0) {
							pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char) 0;
							continue;
						}
						if(i>24 && i<=32 && Vol1Slit[2] == 0) {
							pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char) 0;
							continue;
						}
						if(i>32 && i<=40 && Vol1Slit[3] == 0) {
							pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char) 0;
							continue;
						}
						if(i>40 && i<=48 && Vol1Slit[4] == 0) {
							pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char) 0;
							continue;
						}
						if(i>48 && i<=56 && Vol1Slit[5] == 0) {
							pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char) 0;
							continue;
						}
					}
				}
			}
		}
        
        filterData1(pVolume);
        
        for (int i = 0; i < (XMAX*YMAX*ZMAX); i++) {
            if (pVolume[i] < 3 && pVolume[i] > 0) {
                //cout << i << endl;
                //pVolume[i] = 0;
            }
        }
        
		glBindTexture(GL_TEXTURE_3D,m_pTextureids[0]);
        
		//======================== FILE READ IN =============================
        
        
		// set the texture parameters
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
		glTexImage3D(GL_TEXTURE_3D,0,GL_INTENSITY,XMAX,YMAX,ZMAX,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,pVolume);
        
        delete [] pVolume;
	}
    
    
    initialLoad1 = false;
    
    
}



void CSimpleSlicerWindow::loadTex2() {
    
	int size = XMAX*YMAX*ZMAX;
    
	//FIST PASS
	if(initialLoad2) {
        pVolTemp1 = new unsigned char[size];
		memset(pVolTemp1,0,size*sizeof(unsigned char));
		unsigned char *pVolume3 = new unsigned char[size];
		memset(pVolume3,0,size*sizeof(unsigned char));
		int i, j, k;
		short c;
        
        
		ifstream file_in[6];
        switch (vol_data2) {
            case 0:
                file_in[0].open(getRoot(VOL1_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL1_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL1_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL1_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL1_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL1_SLIT6), ios::in | ios::binary);
                break;
            case 1:
                cout << "opening another tex2" << endl;
                file_in[0].open(getRoot(VOL2_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL2_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL2_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL2_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL2_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL2_SLIT6), ios::in | ios::binary);
                break;
            case 2:
                file_in[0].open(getRoot(VOL3_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL3_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL3_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL3_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL3_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL3_SLIT6), ios::in | ios::binary);
                break;
            case 3:
                file_in[0].open(getRoot(VOL4_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL4_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL4_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL4_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL4_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL4_SLIT6), ios::in | ios::binary);
                break;
            case 4:
                file_in[0].open(getRoot(VOL5_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL5_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL5_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL5_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL5_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL5_SLIT6), ios::in | ios::binary);
                break;
            case 5:
                file_in[0].open(getRoot(VOL6_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL6_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL6_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL6_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL6_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL6_SLIT6), ios::in | ios::binary);
                break;
            case 6:
                file_in[0].open(getRoot(VOL7_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL7_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL7_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL7_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL7_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL7_SLIT6), ios::in | ios::binary);
                break;
            case 7:
                file_in[0].open(getRoot(VOL8_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL8_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL8_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL8_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL8_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL8_SLIT6), ios::in | ios::binary);
                break;
            case 8:
                file_in[0].open(getRoot(VOL9_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL9_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL9_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL9_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL9_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL9_SLIT6), ios::in | ios::binary);
                break;
            case 9:
                file_in[0].open(getRoot(VOL10_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL10_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL10_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL10_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL10_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL10_SLIT6), ios::in | ios::binary);
                break;                
            case 10:
                file_in[0].open(getRoot(VOL11_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL11_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL11_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL11_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL11_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL11_SLIT6), ios::in | ios::binary);
                break;                
            case 11:
                file_in[0].open(getRoot(VOL12_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL12_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL12_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL12_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL12_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL12_SLIT6), ios::in | ios::binary);
                break;     
            case 12:
                file_in[0].open(getRoot(VOL13_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL13_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL13_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL13_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL13_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL13_SLIT6), ios::in | ios::binary);
                break;     
            case 13:
                file_in[0].open(getRoot(VOL14_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL14_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL14_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL14_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL14_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL14_SLIT6), ios::in | ios::binary);
                break;     
            case 14:
                file_in[0].open(getRoot(VOL15_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL15_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL15_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL15_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL15_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL15_SLIT6), ios::in | ios::binary);
                break;     
            case 15:
                file_in[0].open(getRoot(VOL16_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL16_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL16_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL16_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL16_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL16_SLIT6), ios::in | ios::binary);
                break;     
            case 16:
                file_in[0].open(getRoot(VOL17_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL17_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL17_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL17_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL17_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL17_SLIT6), ios::in | ios::binary);
                break;     
            case 17:
                file_in[0].open(getRoot(VOL18_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL18_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL18_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL18_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL18_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL18_SLIT6), ios::in | ios::binary);
                break;     
            case 18:
                file_in[0].open(getRoot(VOL19_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL19_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL19_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL19_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL19_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL19_SLIT6), ios::in | ios::binary);
                break;     
            case 19:
                file_in[0].open(getRoot(VOL20_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL20_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL20_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL20_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL20_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL20_SLIT6), ios::in | ios::binary);
                break;     
            case 20:
                file_in[0].open(getRoot(VOL21_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL21_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL21_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL21_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL21_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL21_SLIT6), ios::in | ios::binary);
                break;     
            case 21:
                file_in[0].open(getRoot(VOL22_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL22_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL22_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL22_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL22_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL22_SLIT6), ios::in | ios::binary);
                break;     
            case 22:
                file_in[0].open(getRoot(VOL23_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL23_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL23_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL23_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL23_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL23_SLIT6), ios::in | ios::binary);
                break;     
            case 23:
                file_in[0].open(getRoot(VOL24_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL24_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL24_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL24_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL24_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL24_SLIT6), ios::in | ios::binary);
                break;     
            case 24:
                file_in[0].open(getRoot(VOL25_SLIT1), ios::in | ios::binary);
                file_in[1].open(getRoot(VOL25_SLIT2), ios::in | ios::binary);
                file_in[2].open(getRoot(VOL25_SLIT3), ios::in | ios::binary);
                file_in[3].open(getRoot(VOL25_SLIT4), ios::in | ios::binary);
                file_in[4].open(getRoot(VOL25_SLIT5), ios::in | ios::binary);
                file_in[5].open(getRoot(VOL25_SLIT6), ios::in | ios::binary);
                break;     
            default:
                break;
        }
        
        
		input[0] = new int[512*512];
		input[1] = new int[512*512];
		input[2] = new int[512*512];
		input[3] = new int[512*512];
		input[4] = new int[512*512];
		input[5] = new int[512*512];
        
		file_in[0].read(reinterpret_cast<char*>(input[0]),512*512*sizeof(int));
		file_in[1].read(reinterpret_cast<char*>(input[1]),512*512*sizeof(int));
		file_in[2].read(reinterpret_cast<char*>(input[2]),512*512*sizeof(int));
		file_in[3].read(reinterpret_cast<char*>(input[3]),512*512*sizeof(int));
		file_in[4].read(reinterpret_cast<char*>(input[4]),512*512*sizeof(int));
		file_in[5].read(reinterpret_cast<char*>(input[5]),512*512*sizeof(int));
		int ndx=0;
        
		//Create Volume
		for(i=0; i<ZMAX; i++){
			ndx = 0;
			for(j=0; j<YMAX; j++){
				for(k=0; k<XMAX; k++){
					if(i>8 && i<=56){
						if (i %8 == 1) {
							
							c = input[(i-9)/8][ndx];
                            pVolume3[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char)(c);
							ndx++;
						}
						else {
							pVolume3[(i*YMAX*XMAX)+(j*XMAX)+k] = pVolume3[(((((i-1)/8)*8) +1)*YMAX*XMAX)+(j*XMAX)+k];
						}
					}
					else
						pVolume3[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char) 0;
				}
			}
		}
		for(k=0; k<6; k++)
			file_in[k].close();
        
		glBindTexture(GL_TEXTURE_3D,m_pTextureids[1]);
        
		//======================== FILE READ IN =============================
        
        
		// set the texture parameters
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
		glTexImage3D(GL_TEXTURE_3D,0,GL_INTENSITY,XMAX,YMAX,ZMAX,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,pVolume3);
        
		for(i=0; i<ZMAX; i++){
			for(j=0; j<YMAX; j++){
				for(k=0; k<XMAX; k++){
					pVolTemp1[(i*YMAX*XMAX)+(j*XMAX)+k] = pVolume3[(i*YMAX*XMAX)+(j*XMAX)+k];
				}
			}
		}
		delete [] pVolume3;
	}
	//ANY OTHER PASS
	if(! initialLoad2){
		unsigned char *pVolume = new unsigned char[size];
		memset(pVolume,0,size*sizeof(unsigned char));
		int i, j, k;
        
		for(i=0; i<ZMAX; i++){
			for(j=0; j<YMAX; j++){
				for(k=0; k<XMAX; k++){
					pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = pVolTemp1[(i*YMAX*XMAX)+(j*XMAX)+k];
                    
					if(i>8 && i<=56) {
                        
						//EDIT VIEWABLE SLICES
						if(i>8  && i<=16 && Vol2Slit[0] == 0) {
							pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char) 0;
							continue;
						}
						if(i>16 && i<=24 && Vol2Slit[1] == 0) {
							pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char) 0;
							continue;
						}
						if(i>24 && i<=32 && Vol2Slit[2] == 0) {
							pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char) 0;
							continue;
						}
						if(i>32 && i<=40 && Vol2Slit[3] == 0) {
							pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char) 0;
							continue;
						}
						if(i>40 && i<=48 && Vol2Slit[4] == 0) {
							pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char) 0;
							continue;
						}
						if(i>48 && i<=56 && Vol2Slit[5] == 0) {
							pVolume[(i*YMAX*XMAX)+(j*XMAX)+k] = (unsigned char) 0;
							continue;
						}
					}
				}
			}
		}
        
        
		glBindTexture(GL_TEXTURE_3D,m_pTextureids[1]);
        
		//======================== FILE READ IN =============================
        
        
		// set the texture parameters
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        
		glTexImage3D(GL_TEXTURE_3D,0,GL_INTENSITY,XMAX,YMAX,ZMAX,0,GL_LUMINANCE,GL_UNSIGNED_BYTE,pVolume);
        delete [] pVolume;
	}
    
	initialLoad2 = false;
    
}

bool CSimpleSlicerWindow::loadTextures() {
	loadTex1();
	loadTex2();
	return true;
}


void CSimpleSlicerWindow::drawString(char *s) {
	int i;
	for(i=0; i<strlen(s); i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, s[i]);
    }
}

void CSimpleSlicerWindow::drawStrings(string s) {
    char* inputString = (char*) s.c_str();
    drawString(inputString);
}

void
CSimpleSlicerWindow::cgRenderGeometry() {
    //Begin Rendering
	int pViewport[4];
	glGetIntegerv(GL_VIEWPORT,pViewport);
    
	m_nWidth = pViewport[2];
	m_nHeight = pViewport[3];
    
	static bool bInit = false;
    
	if (false == bInit) {
		bInit = loadTextures();
		bInit &= createPrograms();
	}
    
    //RELOAD TEXTURES ONLY IF SOMETHING HAS CHANGED
    if (vol_data1 != vol_data1C) {
        initialLoad1 = true;
        vol_data1C = vol_data1;
        loadTextures();
    }
	
	if( Vol1Slit[0] != Vol1SlitC[0] || Vol1Slit[1] != Vol1SlitC[1] || Vol1Slit[2] != Vol1SlitC[2] ||
       Vol1Slit[3] != Vol1SlitC[3] || Vol1Slit[4] != Vol1SlitC[4] || Vol1Slit[5] != Vol1SlitC[5]) {
        
        loadTextures();
        for (int i=0; i<6; i++) {
            Vol1SlitC[i] = Vol1Slit[i];
        }
        
        
	}
    
	//RELOAD TEXTURES ONLY IF SOMETHING HAS CHANGED
    if (vol_data2 != vol_data2C) {
        initialLoad2 = true;
        vol_data2C = vol_data2;
        loadTextures();
    }
    
    
	if( Vol2Slit[0] != Vol2SlitC[0] || Vol2Slit[1] != Vol2SlitC[1] || Vol2Slit[2] != Vol2SlitC[2] ||
       Vol2Slit[3] != Vol2SlitC[3] || Vol2Slit[4] != Vol2SlitC[4] || Vol2Slit[5] != Vol2SlitC[5] ) {
        loadTextures();
        for (int i=0; i<6; i++) {
            Vol2SlitC[i] = Vol2Slit[i];
        }
        
	}
    
    //RELOAD TEXTURES ONLY IF SOMETHING HAS CHANGED
    if (scaleColorMap != scaleColorMapC) {
        scaleColorMapC = scaleColorMap;
        m_pTransferFunction->updateColor();
    }
    
    if (filter[0] != filterC[0] || filter[1] != filterC[1] || filter[2] != filterC[2] || filter[3] != filterC[3] || filter[4] != filterC[4]) {
        for (int i = 0; i < 6; i++) {
            filterC[i] = filter[i];
        }
        loadTextures();
    }
    
    
	//ASSIGN MIN AND MAX VALUES BASED ON CURRENT VOLUMES
	if(vol_data1 == 0){
		vol1min = min1;
		vol1max = max1;
	}
	if(vol_data2 == 0){
		vol2min = min1;
		vol2max = max1;
	}
	if(vol_data1 == 1){
		vol1min = min2;
		vol1max = max2;
	}
	if(vol_data2 == 1){
		vol2min = min2;
		vol2max = max2;
	}
	if(vol_data1 == 2){
		vol1min = min3;
		vol1max = max3;
	}
	if(vol_data2 == 2){
		vol2min = min3;
		vol2max = max3;
	}
	if(vol_data1 == 3){
		vol1min = 0.0;
		vol1max = 255.0;
	}
	if(vol_data2 == 3){
		vol2min = 0.0;
		vol2max = 255.0;
	}
	if(vol_data1 == 4){
		vol1min = min4;
		vol1max = max4;
	}
	if(vol_data2 == 4){
		vol2min = min4;
		vol2max = max4;
	}
	if(vol_data1 == 5){
		vol1min = min1;
		vol1max = max1;
	}
	if(vol_data2 == 5){
		vol2min = min1;
		vol2max = max1;
	}
    
	int i;
    
	const int m_pEdgeList[8][12] = {
		{ 0,1,5,6,   4,8,11,9,  3,7,2,10 }, // v0 is front
		{ 0,4,3,11,  1,2,6,7,   5,9,8,10 }, // v1 is front
		{ 1,5,0,8,   2,3,7,4,   6,10,9,11}, // v2 is front
		{ 7,11,10,8, 2,6,1,9,   3,0,4,5  }, // v3 is front
		{ 8,5,9,1,   11,10,7,6, 4,3,0,2  }, // v4 is front
		{ 9,6,10,2,  8,11,4,7,  5,0,1,3  }, // v5 is front
		{ 9,8,5,4,   6,1,2,0,   10,7,11,3}, // v6 is front
		{ 10,9,6,5,  7,2,3,1,   11,4,8,0 }  // v7 is front
	}; 
    
#ifdef COLOR_CODE_EDGES
	double colors[12][3] = {
		{1.0,0.0,0.0},{1.0,0.0,0.0},{1.0,1.0,0.0},{1.0,0.0,0.0},
		{0.0,1.0,0.0},{0.0,1.0,0.0},{0.0,1.0,1.0},{0.0,1.0,0.0},
		{0.0,0.0,1.0},{0.0,0.0,1.0},{1.0,0.0,1.0},{0.0,0.0,1.0}
	};
#endif
    
	float pMatrix[16];
    
	glGetFloatv(GL_MODELVIEW_MATRIX,pMatrix);
    
    
    
	glDisable(GL_LIGHTING);
    
	CVector colKeyLight(0.8,0.8,0.8,0.0);
	CVector colFillLight(0.6,0.6,0.5,0.0);
	CVector colBackLight(0.3,0.3,0.2,0.0);
    
	CMatrix matLight = m_pLightArcball->getRotatonMatrix();
	CVector vecKeyLight  = matLight * CVector(1.0,1.0,1.0,0.0);
	CVector vecFillLight = matLight * CVector(-1.0,1.0,1.0,0.0);
	CVector vecBackLight = matLight * CVector(0.0,1.0,-1.0,0.0);
    
    
	CVector viewVec(-pMatrix[2],-pMatrix[6],-pMatrix[10],0.0);
    
	double dMaxDist = viewVec * m_pVertices[0];
	double dMinDist = dMaxDist;
	int nMaxIdx = 0;
	for(int i = 1; i < 8; ++i) {
		double dist = viewVec * m_pVertices[i];
		if ( dist > dMaxDist) {
			dMaxDist = dist;
			nMaxIdx = i;
		}
		if ( dist < dMinDist) {
			dMinDist = dist;
		}
        
	}
    
	glEnd();
    
	//CREATE BOUNDING BOX
	CVector m_pVerticesT[8];
    
	m_pVerticesT[0] = CVector(-XSCALE,-YSCALE,-ZSCALE, 1.0,  0.0, 0.0, 0.0);
	m_pVerticesT[1] = CVector( XSCALE,-YSCALE,-ZSCALE, 1.0,  1.0, 0.0, 0.0);
	m_pVerticesT[2] = CVector( XSCALE, YSCALE,-ZSCALE, 1.0,  1.0, 1.0, 0.0);
	m_pVerticesT[3] = CVector(-XSCALE, YSCALE,-ZSCALE, 1.0,  0.0, 1.0, 0.0);
    
	m_pVerticesT[4] = CVector(-XSCALE,-YSCALE, ZSCALE, 1.0,  0.0, 0.0, 1.0);
	m_pVerticesT[5] = CVector( XSCALE,-YSCALE, ZSCALE, 1.0,  1.0, 0.0, 1.0);
	m_pVerticesT[6] = CVector( XSCALE, YSCALE, ZSCALE, 1.0,  1.0, 1.0, 1.0);
	m_pVerticesT[7] = CVector(-XSCALE, YSCALE, ZSCALE, 1.0,  0.0, 1.0, 1.0);
    
	if(boundBox == 1){
		glLineWidth(2.0);
		glBegin(GL_LINES);
		{
#ifndef COLOR_CODE_EDGES
			glColor3f(1.0,1.0,1.0);
#endif
            
			for(int i = 0; i < 12; i++) {
#ifdef COLOR_CODE_EDGES
				glColor3dv(colors[i]);
#endif
				glVertex4dv(&(m_pVerticesT[m_pEdges[m_pEdgeList[nMaxIdx][i]].nV1])[0]);
				glVertex4dv(&(m_pVerticesT[m_pEdges[m_pEdgeList[nMaxIdx][i]].nV2])[0]);
			}
            
		}
		glEnd();
	}
    
	glScaled(XSIZE,YSIZE,ZSIZE);
    
	CVector xLine  = CVector(  0.0,         -YSCALE-0.05,  ZSCALE+0.05, 1.0,  0.0,0.0,0.0);
	CVector yLine  = CVector( -XSCALE,      0.0,           ZSCALE+0.05, 1.0,  0.0,0.0,0.0);
	CVector zLine  = CVector( -XSCALE,      -YSCALE-0.05,  0.0,         1.0,  0.0,0.0,0.0);
    
	//NAME AXES
	if(boundBox == 1){
		glRasterPos4dv(&xLine[0]);
		drawStrings("Velocity");
		glRasterPos4dv(&yLine[0]);
		drawStrings("Distance");
		glRasterPos4dv(&zLine[0]);
		drawStrings("Slit");
	}
    
	CVector SlitStartB  = CVector(XSCALE,  -YSCALE-0.05,  1.00000*(48./64.),1.0,  0.0,0.0,0.0);
	CVector Slit1B  = CVector(    XSCALE,  -YSCALE-0.05,  0.66667*(48./64.),1.0,  0.0,0.0,0.0);
	CVector Slit2B  = CVector(    XSCALE,  -YSCALE-0.05,  0.33333*(48./64.),1.0,  0.0,0.0,0.0);
	CVector Slit3B  = CVector(    XSCALE,  -YSCALE-0.05,  0.00000*(48./64.),1.0,  0.0,0.0,0.0);
	CVector Slit4B  = CVector(    XSCALE,  -YSCALE-0.05, -0.33333*(48./64.),1.0,  0.0,0.0,0.0);
	CVector Slit5B  = CVector(    XSCALE,  -YSCALE-0.05, -0.66667*(48./64.),1.0,  0.0,0.0,0.0);
	CVector Slit6B  = CVector(    XSCALE,  -YSCALE-0.05, -1.00000*(48./64.),1.0,  0.0,0.0,0.0);
	CVector SlitStartT  = CVector(XSCALE,  -YSCALE,       1.00000*(48./64.),1.0,  0.0,0.0,0.0);
	CVector Slit1T  = CVector(    XSCALE,  -YSCALE,       0.66667*(48./64.),1.0,  0.0,0.0,0.0);
	CVector Slit2T  = CVector(    XSCALE,  -YSCALE,       0.33333*(48./64.),1.0,  0.0,0.0,0.0);
	CVector Slit3T  = CVector(    XSCALE,  -YSCALE,       0.00000*(48./64.),1.0,  0.0,0.0,0.0);
	CVector Slit4T  = CVector(    XSCALE,  -YSCALE,      -0.33333*(48./64.),1.0,  0.0,0.0,0.0);
	CVector Slit5T  = CVector(    XSCALE,  -YSCALE,      -0.66667*(48./64.),1.0,  0.0,0.0,0.0);
	CVector Slit6T  = CVector(    XSCALE,  -YSCALE,      -1.00000*(48./64.),1.0,  0.0,0.0,0.0);
    
	if(boundBox == 1){
		glLineWidth(2.0);
		glBegin(GL_LINES);
		{
			glVertex4dv(&(SlitStartB)[0]);
			glVertex4dv(&(Slit6B)[0]);
			glVertex4dv(&(SlitStartB)[0]);
			glVertex4dv(&(SlitStartT)[0]);
			glVertex4dv(&(Slit1B)[0]);
			glVertex4dv(&(Slit1T)[0]);
			glVertex4dv(&(Slit2B)[0]);
			glVertex4dv(&(Slit2T)[0]);
			glVertex4dv(&(Slit3B)[0]);
			glVertex4dv(&(Slit3T)[0]);
			glVertex4dv(&(Slit4B)[0]);
			glVertex4dv(&(Slit4T)[0]);
			glVertex4dv(&(Slit5B)[0]);
			glVertex4dv(&(Slit5T)[0]);
			glVertex4dv(&(Slit6B)[0]);
			glVertex4dv(&(Slit6T)[0]);
		}
		glEnd();
	}
    
	CGprofile vertProfile = CGlutCgWindow::vertProfile();
	CGprofile fragProfile = CGlutCgWindow::fragProfile();
    
    
	CGprogram vertProg; 
	CGprogram fragProg; 
    
	//SWITCH BETWEEN 3 DIFFERENT FRAGMENT SHADERS
	switch(m_nMode) {
            
		default:
		case 0:
			vertProg = m_pVertexPrograms[0];
			fragProg = m_pFragmentPrograms[0];
			break;
            
		case 1:
			vertProg = m_pVertexPrograms[0];
			fragProg = m_pFragmentPrograms[1];
			cgGLSetParameter3dv(cgGetNamedParameter(fragProg,"viewVec"),&(viewVec[0]));
			cgGLSetParameter3dv(cgGetNamedParameter(fragProg,"vecKeyLight"),&(vecKeyLight[0]));
			cgGLSetParameter3dv(cgGetNamedParameter(fragProg,"vecFillLight"),&(vecFillLight[0]));
			cgGLSetParameter3dv(cgGetNamedParameter(fragProg,"vecBackLight"),&(vecBackLight[0]));
			cgGLSetParameter3dv(cgGetNamedParameter(fragProg,"colKeyLight"),&(colKeyLight[0]));
			cgGLSetParameter3dv(cgGetNamedParameter(fragProg,"colFillLight"),&(colFillLight[0]));
			cgGLSetParameter3dv(cgGetNamedParameter(fragProg,"colBackLight"),&(colBackLight[0]));
			cgGLSetParameter3d(cgGetNamedParameter(fragProg,"k_diff"),0.4,0.2,0.3);
			cgGLSetParameter3d(cgGetNamedParameter(fragProg,"k_spec"),0.4,0.4,0.4);
			cgGLSetParameter3d(cgGetNamedParameter(fragProg,"k_emit"),0.3,0.3,0.3);
			cgGLSetParameter1d(cgGetNamedParameter(fragProg,"shininess"),300.0);
			break;
		case 2:
			vertProg = m_pVertexPrograms[0];
			fragProg = m_pFragmentPrograms[2];
			cgGLSetParameter3dv(cgGetNamedParameter(fragProg,"viewVec"),&(viewVec[0]));
			break;
            
	}
    
	// Bind uniform parameters to vertex shader
	cgGLSetStateMatrixParameter(cgGetNamedParameter(vertProg, "ModelViewProj"),
                                CG_GL_MODELVIEW_PROJECTION_MATRIX,
                                CG_GL_MATRIX_IDENTITY);
    
    
	//========== START PLANE BOUNDING-BOX INTERSECTION AND SLICE GENERATOR ==========
	CVector vecStart[12];
	CVector vecDir[12];
	float lambda[12];
	float lambda_inc[12];
	double denom;
    
	dMinDist += EPSILON;
	dMaxDist -= EPSILON;
	double dPlaneDist    =  dMinDist;   
	double dPlaneDistInc =  (dMaxDist-dMinDist)/double(m_nNumSlices);
    
	float dVertices[12*3];
	float dEdges[12*3];
    
	for(i = 0; i < 12; i++) {
		vecStart[i] = m_pVertices[m_pEdges[m_pEdgeList[nMaxIdx][i]].nV1];
		vecDir[i]   = m_pVertices[m_pEdges[m_pEdgeList[nMaxIdx][i]].nV2] - m_pVertices[m_pEdges[m_pEdgeList[nMaxIdx][i]].nV1];
        
		denom = vecDir[i] * viewVec;
        
		if (1.0 + denom != 1.0) {
			lambda_inc[i] =  dPlaneDistInc/denom;
			lambda[i]     = (dPlaneDist - vecStart[i] *viewVec)/denom;
		} else {
			lambda[i]     = -1.0;
			lambda_inc[i] =  0.0;	
		}
        
		dVertices[3*i]   = vecStart[i][0];
		dVertices[3*i+1] = vecStart[i][1];
		dVertices[3*i+2] = vecStart[i][2];
		dEdges[3*i]      = vecDir[i][0];
		dEdges[3*i+1]    = vecDir[i][1];
		dEdges[3*i+2]    = vecDir[i][2];
	};
    
    
	CVector intersection[6];
	float lmb[12];
    
	for(int n = m_nNumSlices-1; n >= 0; --n) {
        
        //ONLY ONE VOLUME
        if(showVol2 == 0) {
            cgGLSetParameter1d(cgGetNamedParameter(fragProg,"showVol"),showVol1);
			// ===================== Opacity Values ===================
            cgGLSetTextureParameter(   cgGetNamedParameter(fragProg,"volume"),m_pTextureids[0]);
			cgGLEnableTextureParameter(cgGetNamedParameter(fragProg,"volume"));
            
			// ===================== Color Values ===================
            cgGLSetTextureParameter(   cgGetNamedParameter(fragProg,"ScalarValues"),m_pTextureids[0]);
			cgGLEnableTextureParameter(cgGetNamedParameter(fragProg,"ScalarValues"));
			m_pTransferFunction->activate(fragProg, 0);
        }
        
		//FIRST VOLUME
		else if(showVol2 == 1 && n%2 == 0){
			cgGLSetParameter1d(cgGetNamedParameter(fragProg,"showVol"),showVol1);
			// ===================== Opacity Values ===================
			
            cgGLSetTextureParameter(   cgGetNamedParameter(fragProg,"volume"),m_pTextureids[0]);
			cgGLEnableTextureParameter(cgGetNamedParameter(fragProg,"volume"));
            
			// ===================== Color Values ===================
            cgGLSetTextureParameter(   cgGetNamedParameter(fragProg,"ScalarValues"),m_pTextureids[0]);
			cgGLEnableTextureParameter(cgGetNamedParameter(fragProg,"ScalarValues"));
			m_pTransferFunction->activate(fragProg, 0);
		}
		//SECOND VOLUME
		else if(showVol2 == 1 && n%2 == 1 ){
			cgGLSetParameter1d(cgGetNamedParameter(fragProg,"showVol"),showVol2);
			// ===================== Opacity Value ===================
			
            cgGLSetTextureParameter(   cgGetNamedParameter(fragProg,"volume"),m_pTextureids[1]);
			cgGLEnableTextureParameter(cgGetNamedParameter(fragProg,"volume"));
            
			// ===================== Color Values ===================
            cgGLSetTextureParameter(   cgGetNamedParameter(fragProg,"ScalarValues"),m_pTextureids[1]);
			cgGLEnableTextureParameter(cgGetNamedParameter(fragProg,"ScalarValues"));
			m_pTransferFunction1->activate(fragProg, 1);
		}
        
        
		cgGLEnableProfile(vertProfile);
		cgGLEnableProfile(fragProfile);
		cgGLBindProgram(vertProg);
		cgGLBindProgram(fragProg);
        
		for(int e = 0; e < 12; e++) {
			lmb[e] = lambda[e] + n*lambda_inc[e];
		}
        
		if      ((lmb[0] >= 0.0) && (lmb[0] < 1.0)) intersection[0] = vecStart[0] + lmb[0] * vecDir[0];
		else if ((lmb[1] >= 0.0) && (lmb[1] < 1.0)) intersection[0] = vecStart[1] + lmb[1] * vecDir[1];
		else if ((lmb[3] >= 0.0) && (lmb[3] < 1.0)) intersection[0] = vecStart[3] + lmb[3] * vecDir[3];
		else continue;
        
		if	    ((lmb[2] >= 0.0) && (lmb[2] < 1.0)) intersection[1] = vecStart[2] + lmb[2] * vecDir[2];
		else if ((lmb[0] >= 0.0) && (lmb[0] < 1.0)) intersection[1] = vecStart[0] + lmb[0] * vecDir[0];
		else if ((lmb[1] >= 0.0) && (lmb[1] < 1.0)) intersection[1] = vecStart[1] + lmb[1] * vecDir[1];
		else intersection[1] = vecStart[3] + lmb[3] * vecDir[3];
        
		if      ((lmb[4] >= 0.0) && (lmb[4] < 1.0)) intersection[2] = vecStart[4] + lmb[4] * vecDir[4];
		else if ((lmb[5] >= 0.0) && (lmb[5] < 1.0)) intersection[2] = vecStart[5] + lmb[5] * vecDir[5];
		else intersection[2] = vecStart[7] + lmb[7] * vecDir[7];
        
		if	    ((lmb[6] >= 0.0) && (lmb[6] < 1.0)) intersection[3] = vecStart[6] + lmb[6] * vecDir[6];
		else if ((lmb[4] >= 0.0) && (lmb[4] < 1.0)) intersection[3] = vecStart[4] + lmb[4] * vecDir[4];
		else if ((lmb[5] >= 0.0) && (lmb[5] < 1.0)) intersection[3] = vecStart[5] + lmb[5] * vecDir[5];
		else intersection[3] = vecStart[7] + lmb[7] * vecDir[7];
        
		if	    ((lmb[8] >= 0.0) && (lmb[8] < 1.0)) intersection[4] = vecStart[8] + lmb[8] * vecDir[8] ;
		else if ((lmb[9] >= 0.0) && (lmb[9] < 1.0)) intersection[4] = vecStart[9] + lmb[9] * vecDir[9] ;
		else intersection[4] = vecStart[11]+ lmb[11]* vecDir[11];
        
		if	    ((lmb[10]>= 0.0) && (lmb[10]< 1.0)) intersection[5] = vecStart[10]+ lmb[10]* vecDir[10];
		else if ((lmb[8] >= 0.0) && (lmb[8] < 1.0)) intersection[5] = vecStart[8] + lmb[8] * vecDir[8] ;
		else if ((lmb[9] >= 0.0) && (lmb[9] < 1.0)) intersection[5] = vecStart[9] + lmb[9] * vecDir[9] ;
		else intersection[5] = vecStart[11]+ lmb[11]* vecDir[11];
        
        
		//======================== END INTERSECTION AND SLICES =======================

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
        
		float c = 1.0f-float(n)/float(m_nNumSlices);
		glColor3f(c,c,c);
		glBegin(GL_TRIANGLE_FAN);
		for(int i = 0; i < 6; ++i) {
			intersection[i].glVertex(false,true);
		}
		glEnd();
        
		glDisable(GL_BLEND);
		glDisable(GL_TEXTURE_3D);
	}
    
	cgGLDisableProfile(vertProfile);
	cgGLDisableProfile(fragProfile);
}

//DISPLAYS TRANSFER FUNCTION BOXES
void CSimpleSlicerWindow::cgDisplayTF() {
    
	if (m_bDisplayTF == 1) {
		m_pTransferFunction->render(0, 0);
	}
	else if(m_bDisplayTF == 2) {
		m_pTransferFunction1->render(glutGet(GLUT_WINDOW_WIDTH) - 284, 1);	
	}
	else if(m_bDisplayTF == 3) {
		m_pTransferFunction->render(0, 0);
		m_pTransferFunction1->render(glutGet(GLUT_WINDOW_WIDTH) - 284, 1);	
	}
}


bool CSimpleSlicerWindow::handleButtonEvent(int button, int state, int x, int y) {
    
	int x_offset = glutGet(GLUT_WINDOW_WIDTH) - 284;
	bool a = false, b = false;
	if (m_bDisplayTF == 1) {
		if(x < 18+TF_TABLE_SIZE && x > 8 && m_nHeight-1-y < 306)
			a =   m_pTransferFunction->handleButtonEvent(button, state, x, m_nHeight-1-y);
	}
	else if (m_bDisplayTF == 2){
		if(x < 18+TF_TABLE_SIZE + (x_offset) && x > 8 + (x_offset) && m_nHeight-1-y < 306)
			b =   m_pTransferFunction1->handleButtonEvent(button, state, x-(x_offset), m_nHeight-1-y);
	}
	else if (m_bDisplayTF == 3) {
		if(x < 18+TF_TABLE_SIZE && x > 8 && m_nHeight-1-y < 306)
			a =   m_pTransferFunction->handleButtonEvent(button, state, x, m_nHeight-1-y);
		if(x < 18+TF_TABLE_SIZE + (x_offset) && x > 8 + (x_offset) && m_nHeight-1-y < 306)
			b =   m_pTransferFunction1->handleButtonEvent(button, state, x-(x_offset), m_nHeight-1-y);
	}
    
	if (a || b) glutPostRedisplay();
	return (a || b);
    
	return false;
}

bool CSimpleSlicerWindow::handleMoveEvent(int x, int y) {
	int x_offset = glutGet(GLUT_WINDOW_WIDTH) - 284;
	bool a = false, b = false;
	if (m_bDisplayTF == 1) {
		a =  m_pTransferFunction->handleMoveEvent(x,m_nHeight-1-y);
	}
	else if (m_bDisplayTF == 2) {
		b =  m_pTransferFunction1->handleMoveEvent(x-(x_offset),m_nHeight-1-y);
	}
	else if (m_bDisplayTF == 3) {
		a =  m_pTransferFunction->handleMoveEvent(x,m_nHeight-1-y);
		b =  m_pTransferFunction1->handleMoveEvent(x-(x_offset),m_nHeight-1-y);
	}
    
    
	if (a || b) glutPostRedisplay();
    
	return (a || b);
    
	return false;
}
void 
CSimpleSlicerWindow::keyEvent(unsigned char key,int x,int y){
	glutPostRedisplay();
}

#define NUM_FRAGPROGS 3
#define NUM_VERTPROGS 1

bool CSimpleSlicerWindow::createPrograms()
{
	CGcontext context = CGlutCgWindow::context();
	CGprofile vertProfile = CGlutCgWindow::vertProfile();
	CGprofile fragProfile = CGlutCgWindow::fragProfile();
	assert(cgIsContext(context));
    
	m_pVertexPrograms   = new CGprogram[NUM_VERTPROGS];
	m_pFragmentPrograms = new CGprogram[NUM_FRAGPROGS];
    
	const char *strVertProgFiles[NUM_VERTPROGS] = {getRoot("/Desktop/data/shaders/vp_simple.cg")};
	const char *strFragProgFiles[NUM_FRAGPROGS] = {
		getRoot("/Desktop/data/shaders/fp_emission_absorption.cg"), 
		getRoot("/Desktop/data/shaders/fp_emis_abs_gradlightPhong.cg"),
		getRoot("/Desktop/data/shaders/fp_showGradient.cg")};
    
    cgGLEnableProfile(vertProfile);
    cgGLEnableProfile(fragProfile);
    
    bool bOK = true;
    for(int i = 0; i < NUM_VERTPROGS; ++i) {
        m_pVertexPrograms[i] = cgCreateProgramFromFile(context, CG_SOURCE, strVertProgFiles[i], vertProfile, NULL, NULL);
        if (NULL == m_pVertexPrograms[i]) {
            bOK = false;
        }
        
        if (!cgIsProgramCompiled(m_pVertexPrograms[i])){
            cgCompileProgram(m_pVertexPrograms[i]);
        }
        
        cgGLLoadProgram(m_pVertexPrograms[i]);
    }  
    
    for(int i = 0; i < NUM_FRAGPROGS; ++i) {
        m_pFragmentPrograms[i] = cgCreateProgramFromFile(context, CG_SOURCE, strFragProgFiles[i], fragProfile, NULL, NULL);
        if (NULL == m_pFragmentPrograms[i]) {
            bOK = false;
        }
        
        if (!cgIsProgramCompiled(m_pFragmentPrograms[i])){
            cgCompileProgram(m_pFragmentPrograms[i]);
        }
        
        cgGLLoadProgram(m_pFragmentPrograms[i]);
    }  
    
    return bOK;
}

void CSimpleSlicerWindow::filterData1(unsigned char * ptr) {
    int i, j, k;
    int num[12] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    bool done = false;
    //cout << "testing..... " << mask[0] << endl;
    
    for(i=0; i<ZMAX; i++){
        for(j=0; j<YMAX; j++){
            for(k=0; k<XMAX; k++){
                int value = ptrVal(i, j, k);
                if (value == 0) continue;
                
                int masks[12] = { pMask[num[0]], pMask1[num[1]], pMask2[num[2]], pMask3[num[3]], pMask4[num[4]], pMask5[num[5]], pMask6[num[6]], pMask7[num[7]], pMask8[num[8]], pMask9[num[9]], pMask10[num[10]], pMask11[num[11]] };
                done = true;
                
                for (int h = 0; h < 12; h++) {
                    
                    if (value == masks[h] && filter[h] != 1) {
                        ptr[value] = (unsigned char) 0;
                        if (num[h] < (maskCount[h] - 1)) {
                            num[h]++;
                        }
                    }
                    if (done && masks[h] != 0 && num[h] < (maskCount[h] - 1)) {
                        done = false;
                    }
                }
            }
            if (done) {
                break;
            }
        }
        if (done) {
            break;
        }
    }
    
}

bool CSimpleSlicerWindow::filterBotTail(int pValue) {
    bool result = true;
    double radius = sqrt(((pow((double)getCoordinate(pValue)[0] - 250.0, 2) + pow((double)getCoordinate(pValue)[1] - 256.0, 2))));
    
    if (radius <= 50 || getCoordinate(pValue)[1] < 200) {
        result = false;
    }
    return result;
}

int CSimpleSlicerWindow::ptrVal(int z, int y, int x) {
    int result = ((z * YMAX * XMAX) + (y * XMAX) + x);
    return result;
}

int CSimpleSlicerWindow::slitNum(int ptrID) {
    int result = -1;
    int zVal = (YMAX * XMAX);
    
    if (ptrID >= (9 * zVal)  && ptrID < (17 * zVal)) {
        result = 0;
    } else if (ptrID >= (17 * zVal) && ptrID < (25 * zVal)) {
        result = 1;
    } else if (ptrID >= (25 * zVal) && ptrID < (33 * zVal)) {
        result = 2;
    } else if (ptrID >= (33 * zVal) && ptrID < (41 * zVal)) {
        result = 3;
    } else if (ptrID >= (41 * zVal) && ptrID < (49 * zVal)) {
        result = 4;
    } else if (ptrID >= (49 * zVal) && ptrID < (57 * zVal)) {
        result = 5;
    }
    
    return result;
}

int* CSimpleSlicerWindow::getCoordinate(int pValue) {
    int *result = new int[3];
    memset(result, 0, sizeof(int) * 3);
    int array[3];
    array[0] = (pValue % (YMAX * XMAX)) % XMAX;
    array[1] = ((pValue % (YMAX * XMAX)) - array[0]) / XMAX;
    array[2] = pValue - array[1] - array[0];
    result = array;
    return result;
}

void CSimpleSlicerWindow::generateMask() {
    return;
    ofstream tempFile (getRoot("/Desktop/temp.txt"), ios::out);
    cout << "writing mask file" << endl;
    int count = 0;
    while (tempFile.is_open()) {
        cout << "here" << endl;
        for(int i=0; i<ZMAX; i++){
            for(int j=0; j<YMAX; j++){
                for(int k=0; k<XMAX; k++){
                    if (slitNum(ptrVal(i, j, k)) != -1 && (int)pVolTemp[(i*YMAX*XMAX)+(j*XMAX)+k] != 0 && filterBotTail(ptrVal(i, j, k))) {
                        long toAdd = ptrVal(i, j, k);
                        tempFile << toAdd << "\n";
                        count++;
                    }
                }
            }
        }
        tempFile.close();
    }
    cout << "Wrote temp file, generating mask now" << endl;
        
       
    ifstream readTemp (getRoot("/Desktop/temp.txt"), ios::in);
    ofstream maskFile (getRoot("/Desktop/data/masks/mask3.txt"), ios::out);
        string line;
    maskFile << count << "\n";
    while (maskFile.is_open()) {
        for (int i = 0; i < count; i++) {
            readTemp >> line;
            maskFile << line << "\n";
        }
        maskFile.close();
        readTemp.close();
    }
    remove(getRoot("/Desktop/temp.txt"));
    cout << "done!" << endl;
    
}

void CSimpleSlicerWindow::readMask() {
    int n;
    string line;
    int readNum;
    ifstream maskFile (getRoot("/Desktop/data/masks/mask0.txt"), ios::in);
    cout << "reading mask" << endl;
    if (maskFile.is_open()) {
        getline(maskFile, line);
        maskCount[0] = atoi(line.c_str());
        pMask = new int[maskCount[0]];
        n = 0;
        while (maskFile.good()) {
            getline(maskFile, line);
            readNum = atoi(line.c_str());
            pMask[n] = readNum;
            n++;
            
        }
    } else {
        pMask = new int[1];
        pMask[0] = 0;
        maskCount[0] = 1;
    }
    maskFile.close();
    
    n = 0;
    ifstream maskFile1 (getRoot("/Desktop/data/masks/mask1.txt"), ios::in);
    if (maskFile1.is_open()) {
        getline(maskFile1, line);
        maskCount[1] = atoi(line.c_str());
        pMask1 = new int[maskCount[1]];
        n = 0;
        while (maskFile1.good()) {
            getline(maskFile1, line);
            readNum = atoi(line.c_str());
            pMask1[n] = readNum;
            n++;
            
        }
    } else {
        pMask1 = new int[1];
        pMask1[0] = 0;
        maskCount[1] = 1;
    }
    maskFile1.close();
    
    n = 0;
    ifstream maskFile2 (getRoot("/Desktop/data/masks/mask2.txt"), ios::in);
    if (maskFile2.is_open()) {
        getline(maskFile2, line);
        maskCount[2] = atoi(line.c_str());
        pMask2 = new int[maskCount[2]];
        n = 0;
        while (maskFile2.good()) {
            getline(maskFile2, line);
            readNum = atoi(line.c_str());
            pMask2[n] = readNum;
            n++;
            
        }
    } else {
        pMask2 = new int[1];
        pMask2[0] = 0;
        maskCount[2] = 1;
    }
    maskFile2.close();
    
    
    n = 0;
    ifstream maskFile3 (getRoot("/Desktop/data/masks/mask3.txt"), ios::in);
    if (maskFile3.is_open()) {
        getline(maskFile3, line);
        maskCount[3] = atoi(line.c_str());
        pMask3 = new int[maskCount[3]];
        n = 0;
        while (maskFile3.good()) {
            getline(maskFile3, line);
            readNum = atoi(line.c_str());
            pMask3[n] = readNum;
            n++;
            
        }
    } else {
        pMask3 = new int[1];
        pMask3[0] = 0;
        maskCount[3] = 1;
     }
    maskFile3.close();
    
    n = 0;
    ifstream maskFile4 (getRoot("/Desktop/data/masks/mask4.txt"), ios::in);
    if (maskFile4.is_open()) {
        getline(maskFile4, line);
        maskCount[4] = atoi(line.c_str());
        pMask4 = new int[maskCount[4]];
        n = 0;
        while (maskFile4.good()) {
            getline(maskFile4, line);
            readNum = atoi(line.c_str());
            pMask4[n] = readNum;
            n++;
            
        }
    } else {
        pMask4 = new int[1];
        pMask4[0] = 0;
        maskCount[4] = 1;
     }
    maskFile4.close();
    
    n = 0;
    ifstream maskFile5 (getRoot("/Desktop/data/masks/mask5.txt"), ios::in);
    if (maskFile5.is_open()) {
        getline(maskFile5, line);
        maskCount[5] = atoi(line.c_str());
        pMask5 = new int[maskCount[5]];
        n = 0;
        while (maskFile5.good()) {
            getline(maskFile5, line);
            readNum = atoi(line.c_str());
            pMask5[n] = readNum;
            n++;
            
        }
    } else {
        pMask5 = new int[1];
        pMask5[0] = 0;
        maskCount[5] = 1;
     }
    maskFile5.close();
    
    n = 0;
    ifstream maskFile6 (getRoot("/Desktop/data/masks/mask6.txt"), ios::in);
    if (maskFile6.is_open()) {
        getline(maskFile6, line);
        maskCount[6] = atoi(line.c_str());
        pMask6 = new int[maskCount[6]];
        n = 0;
        while (maskFile6.good()) {
            getline(maskFile6, line);
            readNum = atoi(line.c_str());
            pMask6[n] = readNum;
            n++;
            
        }
    } else {
        pMask6 = new int[1];
        pMask6[0] = 0;
        maskCount[6] = 1;
     }
    maskFile6.close();
    
    n = 0;
    ifstream maskFile7 (getRoot("/Desktop/data/masks/mask7.txt"), ios::in);
    if (maskFile7.is_open()) {
        getline(maskFile7, line);
        maskCount[7] = atoi(line.c_str());
        pMask7 = new int[maskCount[7]];
        n = 0;
        while (maskFile7.good()) {
            getline(maskFile7, line);
            readNum = atoi(line.c_str());
            pMask7[n] = readNum;
            n++;
            
        }
    } else {
        pMask7 = new int[1];
        pMask7[0] = 0;
        maskCount[7] = 1;
     }
    maskFile7.close();
    
    n = 0;
    ifstream maskFile8 (getRoot("/Desktop/data/masks/mask8.txt"), ios::in);
    if (maskFile8.is_open()) {
        getline(maskFile8, line);
        maskCount[8] = atoi(line.c_str());
        pMask8 = new int[maskCount[8]];
        n = 0;
        while (maskFile8.good()) {
            getline(maskFile8, line);
            readNum = atoi(line.c_str());
            pMask8[n] = readNum;
            n++;
            
        }
    } else {
        pMask8 = new int[1];
        pMask8[0] = 0;
        maskCount[8] = 1;
     }
    maskFile8.close();
    
    n = 0;
    ifstream maskFile9 (getRoot("/Desktop/data/masks/mask9.txt"), ios::in);
    if (maskFile9.is_open()) {
        getline(maskFile9, line);
        maskCount[9] = atoi(line.c_str());
        pMask9 = new int[maskCount[9]];
        n = 0;
        while (maskFile9.good()) {
            getline(maskFile9, line);
            readNum = atoi(line.c_str());
            pMask9[n] = readNum;
            n++;
            
        }
    } else {
        pMask9 = new int[1];
        pMask9[0] = 0;
        maskCount[9] = 1;
     }
    maskFile2.close();
    
    n = 0;
    ifstream maskFile10 (getRoot("/Desktop/data/masks/mask10.txt"), ios::in);
    if (maskFile10.is_open()) {
        getline(maskFile10, line);
        maskCount[10] = atoi(line.c_str());
        pMask10 = new int[maskCount[10]];
        n = 0;
        while (maskFile10.good()) {
            getline(maskFile10, line);
            readNum = atoi(line.c_str());
            pMask10[n] = readNum;
            n++;
            
        }
    } else {
        pMask10 = new int[1];
        pMask10[0] = 0;
        maskCount[10] = 1;
     }
    maskFile10.close();
    
    n = 0;
    ifstream maskFile11 (getRoot("/Desktop/data/masks/mask11.txt"), ios::in);
    if (maskFile11.is_open()) {
        getline(maskFile11, line);
        maskCount[11] = atoi(line.c_str());
        pMask11 = new int[maskCount[11]];
        n = 0;
        while (maskFile11.good()) {
            getline(maskFile11, line);
            readNum = atoi(line.c_str());
            pMask11[n] = readNum;
            n++;
            
        }
    } else {
        pMask11 = new int[1];
        pMask11[0] = 0;
        maskCount[11] = 1;
     }
    maskFile11.close();
     
}
