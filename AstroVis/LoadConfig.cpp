//
//  LoadConfig.cpp
//  AstroVis
//
//  Created by Joseph Snee on 9/24/12.
//  Copyright (c) 2012 Drake University. All rights reserved.
//
//  Loads the necessary data files

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void Config() {
    //Check for config file
    ifstream inf("astrovis.ini");
    
    //If file does not exist
    if (!inf) {
        cerr << "Configuration File Does Not Exist, Generating Default Configuration File" << endl;
        
        inf.close();
        ofstream outf("astrovis.ini");
        /*
        outf << "/Users/000617123/Desktop/data/Engine256.raw" << endl;
        outf << "/Users/000617123/Desktop/data/CTA.raw" << endl;
        outf << "/Users/000617123/Desktop/data/1068s1g.txt" << endl;
        outf << "/Users/000617123/Desktop/data/1068s2g.txt" << endl;
        outf << "/Users/000617123/Desktop/data/1068s3g.txt" << endl;
        outf << "/Users/000617123/Desktop/data/1068s4g.txt" << endl;
        outf << "/Users/000617123/Desktop/data/1068s5g.txt" << endl;
        outf << "/Users/000617123/Desktop/data/1068s6g.txt" << endl;
        outf << "/Users/000617123/Desktop/data/1068s1a.txt" << endl;
        outf << "/Users/000617123/Desktop/data/1068s2a.txt" << endl;
        outf << "/Users/000617123/Desktop/data/1068s3a.txt" << endl;
        outf << "/Users/000617123/Desktop/data/1068s4a.txt" << endl;
        outf << "/Users/000617123/Desktop/data/1068s5a.txt" << endl;
        outf << "/Users/000617123/Desktop/data/1068s6a.txt" << endl;
        outf << "/Users/000617123/Desktop/data/1068gAllNNx.txt" << endl;
        outf << "/Users/000617123/Desktop/data/1068gAllNNy.txt" << endl;
        outf << "/Users/000617123/Desktop/data/blobID.txt")
        outf << "/Users/000617123/Desktop/data/ngc1068/ngc1068s1.bin")
        outf << "/Users/000617123/Desktop/data/ngc1068/ngc1068s2.bin")
        outf << "/Users/000617123/Desktop/data/ngc1068/ngc1068s3.bin")
        outf << "/Users/000617123/Desktop/data/ngc1068/ngc1068s4.bin")
        outf << "/Users/000617123/Desktop/data/ngc1068/ngc1068s5.bin")
        outf << "/Users/000617123/Desktop/data/ngc1068/ngc1068s6.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi0tf1.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi0tf2.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi0tf3.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi0tf4.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi0tf5.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi0tf6.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi30tf1.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi30tf2.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi30tf3.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi30tf4.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi30tf5.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi30tf6.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi60tf1.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi60tf2.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi60tf3.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi60tf4.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi60tf5.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi60tf6.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi90tf1.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi90tf2.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi90tf3.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi90tf4.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi90tf5.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2gridi90tf6.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi0tf1.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi0tf2.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi0tf3.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi0tf4.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi0tf5.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi0tf6.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi30tf1.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi30tf2.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi30tf3.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi30tf4.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi30tf5.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi30tf6.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi60tf1.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi60tf2.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi60tf3.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi60tf4.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi60tf5.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi60tf6.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi90tf1.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi90tf2.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi90tf3.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi90tf4.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi90tf5.bin")
        outf << "/Users/000617123/Desktop/data/cylv2/cylv2randi90tf6.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi0tf1.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi0tf2.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi0tf3.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi0tf4.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi0tf5.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi0tf6.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi30tf1.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi30tf2.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi30tf3.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi30tf4.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi30tf5.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi30tf6.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi60tf1.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi60tf2.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi60tf3.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi60tf4.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi60tf5.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi60tf6.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi90tf1.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi90tf2.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi90tf3.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi90tf4.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi90tf5.bin")
        outf << "/Users/000617123/Desktop/data/grid/cylgridi90tf6.bin")
        outf << "/Users/000617123/Desktop/data/grid/radgridi0tf1.bin")
        outf << "/Users/000617123/Desktop/data/grid/radgridi0tf2.bin")
        outf << "/Users/000617123/Desktop/data/grid/radgridi0tf3.bin")
        outf << "/Users/000617123/Desktop/data/grid/radgridi0tf4.bin")
        outf << "/Users/000617123/Desktop/data/grid/radgridi0tf5.bin")
        outf << "/Users/000617123/Desktop/data/grid/radgridi0tf6.bin")
        outf << "/Users/000617123/Desktop/data/grid/radgridi30tf1.bin")
#define VOL15_SLIT2 ("/Users/000617123/Desktop/data/grid/radgridi30tf2.bin")
#define VOL15_SLIT3 ("/Users/000617123/Desktop/data/grid/radgridi30tf3.bin")
#define VOL15_SLIT4 ("/Users/000617123/Desktop/data/grid/radgridi30tf4.bin")
#define VOL15_SLIT5 ("/Users/000617123/Desktop/data/grid/radgridi30tf5.bin")
#define VOL15_SLIT6 ("/Users/000617123/Desktop/data/grid/radgridi30tf6.bin")
        
#define VOL16_SLIT1 ("/Users/000617123/Desktop/data/grid/radgridi60tf1.bin")
#define VOL16_SLIT2 ("/Users/000617123/Desktop/data/grid/radgridi60tf2.bin")
#define VOL16_SLIT3 ("/Users/000617123/Desktop/data/grid/radgridi60tf3.bin")
#define VOL16_SLIT4 ("/Users/000617123/Desktop/data/grid/radgridi60tf4.bin")
#define VOL16_SLIT5 ("/Users/000617123/Desktop/data/grid/radgridi60tf5.bin")
#define VOL16_SLIT6 ("/Users/000617123/Desktop/data/grid/radgridi60tf6.bin")
        
#define VOL17_SLIT1 ("/Users/000617123/Desktop/data/grid/radgridi90tf1.bin")
#define VOL17_SLIT2 ("/Users/000617123/Desktop/data/grid/radgridi90tf2.bin")
#define VOL17_SLIT3 ("/Users/000617123/Desktop/data/grid/radgridi90tf3.bin")
#define VOL17_SLIT4 ("/Users/000617123/Desktop/data/grid/radgridi90tf4.bin")
#define VOL17_SLIT5 ("/Users/000617123/Desktop/data/grid/radgridi90tf5.bin")
#define VOL17_SLIT6 ("/Users/000617123/Desktop/data/grid/radgridi90tf6.bin")
        
#define VOL18_SLIT1 ("/Users/000617123/Desktop/data/rand/cylrandi0tf1.bin")
#define VOL18_SLIT2 ("/Users/000617123/Desktop/data/rand/cylrandi0tf2.bin")
#define VOL18_SLIT3 ("/Users/000617123/Desktop/data/rand/cylrandi0tf3.bin")
#define VOL18_SLIT4 ("/Users/000617123/Desktop/data/rand/cylrandi0tf4.bin")
#define VOL18_SLIT5 ("/Users/000617123/Desktop/data/rand/cylrandi0tf5.bin")
#define VOL18_SLIT6 ("/Users/000617123/Desktop/data/rand/cylrandi0tf6.bin")
        
#define VOL19_SLIT1 ("/Users/000617123/Desktop/data/rand/cylrandi30tf1.bin")
#define VOL19_SLIT2 ("/Users/000617123/Desktop/data/rand/cylrandi30tf2.bin")
#define VOL19_SLIT3 ("/Users/000617123/Desktop/data/rand/cylrandi30tf3.bin")
#define VOL19_SLIT4 ("/Users/000617123/Desktop/data/rand/cylrandi30tf4.bin")
#define VOL19_SLIT5 ("/Users/000617123/Desktop/data/rand/cylrandi30tf5.bin")
#define VOL19_SLIT6 ("/Users/000617123/Desktop/data/rand/cylrandi30tf6.bin")
        
#define VOL20_SLIT1 ("/Users/000617123/Desktop/data/rand/cylrandi60tf1.bin")
#define VOL20_SLIT2 ("/Users/000617123/Desktop/data/rand/cylrandi60tf2.bin")
#define VOL20_SLIT3 ("/Users/000617123/Desktop/data/rand/cylrandi60tf3.bin")
#define VOL20_SLIT4 ("/Users/000617123/Desktop/data/rand/cylrandi60tf4.bin")
#define VOL20_SLIT5 ("/Users/000617123/Desktop/data/rand/cylrandi60tf5.bin")
#define VOL20_SLIT6 ("/Users/000617123/Desktop/data/rand/cylrandi60tf6.bin")
        
#define VOL21_SLIT1 ("/Users/000617123/Desktop/data/rand/cylrandi90tf1.bin")
#define VOL21_SLIT2 ("/Users/000617123/Desktop/data/rand/cylrandi90tf2.bin")
#define VOL21_SLIT3 ("/Users/000617123/Desktop/data/rand/cylrandi90tf3.bin")
#define VOL21_SLIT4 ("/Users/000617123/Desktop/data/rand/cylrandi90tf4.bin")
#define VOL21_SLIT5 ("/Users/000617123/Desktop/data/rand/cylrandi90tf5.bin")
#define VOL21_SLIT6 ("/Users/000617123/Desktop/data/rand/cylrandi90tf6.bin")
        
#define VOL22_SLIT1 ("/Users/000617123/Desktop/data/rand/radrandi0tf1.bin")
#define VOL22_SLIT2 ("/Users/000617123/Desktop/data/rand/radrandi0tf2.bin")
#define VOL22_SLIT3 ("/Users/000617123/Desktop/data/rand/radrandi0tf3.bin")
#define VOL22_SLIT4 ("/Users/000617123/Desktop/data/rand/radrandi0tf4.bin")
#define VOL22_SLIT5 ("/Users/000617123/Desktop/data/rand/radrandi0tf5.bin")
#define VOL22_SLIT6 ("/Users/000617123/Desktop/data/rand/radrandi0tf6.bin")
        
#define VOL23_SLIT1 ("/Users/000617123/Desktop/data/rand/radrandi30tf1.bin")
#define VOL23_SLIT2 ("/Users/000617123/Desktop/data/rand/radrandi30tf2.bin")
#define VOL23_SLIT3 ("/Users/000617123/Desktop/data/rand/radrandi30tf3.bin")
#define VOL23_SLIT4 ("/Users/000617123/Desktop/data/rand/radrandi30tf4.bin")
#define VOL23_SLIT5 ("/Users/000617123/Desktop/data/rand/radrandi30tf5.bin")
#define VOL23_SLIT6 ("/Users/000617123/Desktop/data/rand/radrandi30tf6.bin")
        
#define VOL24_SLIT1 ("/Users/000617123/Desktop/data/rand/radrandi60tf1.bin")
#define VOL24_SLIT2 ("/Users/000617123/Desktop/data/rand/radrandi60tf2.bin")
#define VOL24_SLIT3 ("/Users/000617123/Desktop/data/rand/radrandi60tf3.bin")
#define VOL24_SLIT4 ("/Users/000617123/Desktop/data/rand/radrandi60tf4.bin")
#define VOL24_SLIT5 ("/Users/000617123/Desktop/data/rand/radrandi60tf5.bin")
#define VOL24_SLIT6 ("/Users/000617123/Desktop/data/rand/radrandi60tf6.bin")
        
#define VOL25_SLIT1 ("/Users/000617123/Desktop/data/rand/radrandi90tf1.bin")
#define VOL25_SLIT2 ("/Users/000617123/Desktop/data/rand/radrandi90tf2.bin")
#define VOL25_SLIT3 ("/Users/000617123/Desktop/data/rand/radrandi90tf3.bin")
#define VOL25_SLIT4 ("/Users/000617123/Desktop/data/rand/radrandi90tf4.bin")
#define VOL25_SLIT5 ("/Users/000617123/Desktop/data/rand/radrandi90tf5.bin")
#define VOL25_SLIT6 ("/Users/000617123/Desktop/data/rand/radrandi90tf6.bin")
         */
    } else {
        
        while (inf) {
            
        }
    }
    
}