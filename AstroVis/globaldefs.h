#ifndef GLOBALDEFS_INCLUDED
#define GLOBALDEFS_INCLUDED

#define TF_TABLE_SIZE (256)

#ifndef M_PI
#define M_PI (3.14159)
#endif

#define EPSILON (0.000001)
#define START_EPSILON (0.01)
#define START_EPSILON1 (0.009)

#define RATIO

#define CONE

#ifdef RATIO
#define BLOB_FILE  (("/Desktop/data/blobID.txt"))

#define VOL1_SLIT1 (("/Desktop/data/ngc1068/ngc1068s1.bin"))
#define VOL1_SLIT2 (("/Desktop/data/ngc1068/ngc1068s2.bin"))
#define VOL1_SLIT3 (("/Desktop/data/ngc1068/ngc1068s3.bin"))
#define VOL1_SLIT4 (("/Desktop/data/ngc1068/ngc1068s4.bin"))
#define VOL1_SLIT5 (("/Desktop/data/ngc1068/ngc1068s5.bin"))
#define VOL1_SLIT6 (("/Desktop/data/ngc1068/ngc1068s6.bin"))

#define VOL2_SLIT1 (("/Desktop/data/cylv2/cylv2gridi0tf1.bin"))
#define VOL2_SLIT2 (("/Desktop/data/cylv2/cylv2gridi0tf2.bin"))
#define VOL2_SLIT3 (("/Desktop/data/cylv2/cylv2gridi0tf3.bin"))
#define VOL2_SLIT4 (("/Desktop/data/cylv2/cylv2gridi0tf4.bin"))
#define VOL2_SLIT5 (("/Desktop/data/cylv2/cylv2gridi0tf5.bin"))
#define VOL2_SLIT6 (("/Desktop/data/cylv2/cylv2gridi0tf6.bin"))

#define VOL3_SLIT1 (("/Desktop/data/cylv2/cylv2gridi30tf1.bin"))
#define VOL3_SLIT2 (("/Desktop/data/cylv2/cylv2gridi30tf2.bin"))
#define VOL3_SLIT3 (("/Desktop/data/cylv2/cylv2gridi30tf3.bin"))
#define VOL3_SLIT4 (("/Desktop/data/cylv2/cylv2gridi30tf4.bin"))
#define VOL3_SLIT5 (("/Desktop/data/cylv2/cylv2gridi30tf5.bin"))
#define VOL3_SLIT6 (("/Desktop/data/cylv2/cylv2gridi30tf6.bin"))

#define VOL4_SLIT1 (("/Desktop/data/cylv2/cylv2gridi60tf1.bin"))
#define VOL4_SLIT2 (("/Desktop/data/cylv2/cylv2gridi60tf2.bin"))
#define VOL4_SLIT3 (("/Desktop/data/cylv2/cylv2gridi60tf3.bin"))
#define VOL4_SLIT4 (("/Desktop/data/cylv2/cylv2gridi60tf4.bin"))
#define VOL4_SLIT5 (("/Desktop/data/cylv2/cylv2gridi60tf5.bin"))
#define VOL4_SLIT6 (("/Desktop/data/cylv2/cylv2gridi60tf6.bin"))

#define VOL5_SLIT1 (("/Desktop/data/cylv2/cylv2gridi90tf1.bin"))
#define VOL5_SLIT2 (("/Desktop/data/cylv2/cylv2gridi90tf2.bin"))
#define VOL5_SLIT3 (("/Desktop/data/cylv2/cylv2gridi90tf3.bin"))
#define VOL5_SLIT4 (("/Desktop/data/cylv2/cylv2gridi90tf4.bin"))
#define VOL5_SLIT5 (("/Desktop/data/cylv2/cylv2gridi90tf5.bin"))
#define VOL5_SLIT6 (("/Desktop/data/cylv2/cylv2gridi90tf6.bin"))

#define VOL6_SLIT1 (("/Desktop/data/cylv2/cylv2randi0tf1.bin"))
#define VOL6_SLIT2 (("/Desktop/data/cylv2/cylv2randi0tf2.bin"))
#define VOL6_SLIT3 (("/Desktop/data/cylv2/cylv2randi0tf3.bin"))
#define VOL6_SLIT4 (("/Desktop/data/cylv2/cylv2randi0tf4.bin"))
#define VOL6_SLIT5 (("/Desktop/data/cylv2/cylv2randi0tf5.bin"))
#define VOL6_SLIT6 (("/Desktop/data/cylv2/cylv2randi0tf6.bin"))

#define VOL7_SLIT1 (("/Desktop/data/cylv2/cylv2randi30tf1.bin"))
#define VOL7_SLIT2 (("/Desktop/data/cylv2/cylv2randi30tf2.bin"))
#define VOL7_SLIT3 (("/Desktop/data/cylv2/cylv2randi30tf3.bin"))
#define VOL7_SLIT4 (("/Desktop/data/cylv2/cylv2randi30tf4.bin"))
#define VOL7_SLIT5 (("/Desktop/data/cylv2/cylv2randi30tf5.bin"))
#define VOL7_SLIT6 (("/Desktop/data/cylv2/cylv2randi30tf6.bin"))

#define VOL8_SLIT1 (("/Desktop/data/cylv2/cylv2randi60tf1.bin"))
#define VOL8_SLIT2 (("/Desktop/data/cylv2/cylv2randi60tf2.bin"))
#define VOL8_SLIT3 (("/Desktop/data/cylv2/cylv2randi60tf3.bin"))
#define VOL8_SLIT4 (("/Desktop/data/cylv2/cylv2randi60tf4.bin"))
#define VOL8_SLIT5 (("/Desktop/data/cylv2/cylv2randi60tf5.bin"))
#define VOL8_SLIT6 (("/Desktop/data/cylv2/cylv2randi60tf6.bin"))

#define VOL9_SLIT1 (("/Desktop/data/cylv2/cylv2randi90tf1.bin"))
#define VOL9_SLIT2 (("/Desktop/data/cylv2/cylv2randi90tf2.bin"))
#define VOL9_SLIT3 (("/Desktop/data/cylv2/cylv2randi90tf3.bin"))
#define VOL9_SLIT4 (("/Desktop/data/cylv2/cylv2randi90tf4.bin"))
#define VOL9_SLIT5 (("/Desktop/data/cylv2/cylv2randi90tf5.bin"))
#define VOL9_SLIT6 (("/Desktop/data/cylv2/cylv2randi90tf6.bin"))

#define VOL10_SLIT1 (("/Desktop/data/grid/cylgridi0tf1.bin"))
#define VOL10_SLIT2 (("/Desktop/data/grid/cylgridi0tf2.bin"))
#define VOL10_SLIT3 (("/Desktop/data/grid/cylgridi0tf3.bin"))
#define VOL10_SLIT4 (("/Desktop/data/grid/cylgridi0tf4.bin"))
#define VOL10_SLIT5 (("/Desktop/data/grid/cylgridi0tf5.bin"))
#define VOL10_SLIT6 (("/Desktop/data/grid/cylgridi0tf6.bin"))

#define VOL11_SLIT1 (("/Desktop/data/grid/cylgridi30tf1.bin"))
#define VOL11_SLIT2 (("/Desktop/data/grid/cylgridi30tf2.bin"))
#define VOL11_SLIT3 (("/Desktop/data/grid/cylgridi30tf3.bin"))
#define VOL11_SLIT4 (("/Desktop/data/grid/cylgridi30tf4.bin"))
#define VOL11_SLIT5 (("/Desktop/data/grid/cylgridi30tf5.bin"))
#define VOL11_SLIT6 (("/Desktop/data/grid/cylgridi30tf6.bin"))

#define VOL12_SLIT1 (("/Desktop/data/grid/cylgridi60tf1.bin"))
#define VOL12_SLIT2 (("/Desktop/data/grid/cylgridi60tf2.bin"))
#define VOL12_SLIT3 (("/Desktop/data/grid/cylgridi60tf3.bin"))
#define VOL12_SLIT4 (("/Desktop/data/grid/cylgridi60tf4.bin"))
#define VOL12_SLIT5 (("/Desktop/data/grid/cylgridi60tf5.bin"))
#define VOL12_SLIT6 (("/Desktop/data/grid/cylgridi60tf6.bin"))

#define VOL13_SLIT1 (("/Desktop/data/grid/cylgridi90tf1.bin"))
#define VOL13_SLIT2 (("/Desktop/data/grid/cylgridi90tf2.bin"))
#define VOL13_SLIT3 (("/Desktop/data/grid/cylgridi90tf3.bin"))
#define VOL13_SLIT4 (("/Desktop/data/grid/cylgridi90tf4.bin"))
#define VOL13_SLIT5 (("/Desktop/data/grid/cylgridi90tf5.bin"))
#define VOL13_SLIT6 (("/Desktop/data/grid/cylgridi90tf6.bin"))

#define VOL14_SLIT1 (("/Desktop/data/grid/radgridi0tf1.bin"))
#define VOL14_SLIT2 (("/Desktop/data/grid/radgridi0tf2.bin"))
#define VOL14_SLIT3 (("/Desktop/data/grid/radgridi0tf3.bin"))
#define VOL14_SLIT4 (("/Desktop/data/grid/radgridi0tf4.bin"))
#define VOL14_SLIT5 (("/Desktop/data/grid/radgridi0tf5.bin"))
#define VOL14_SLIT6 (("/Desktop/data/grid/radgridi0tf6.bin"))

#define VOL15_SLIT1 (("/Desktop/data/grid/radgridi30tf1.bin"))
#define VOL15_SLIT2 (("/Desktop/data/grid/radgridi30tf2.bin"))
#define VOL15_SLIT3 (("/Desktop/data/grid/radgridi30tf3.bin"))
#define VOL15_SLIT4 (("/Desktop/data/grid/radgridi30tf4.bin"))
#define VOL15_SLIT5 (("/Desktop/data/grid/radgridi30tf5.bin"))
#define VOL15_SLIT6 (("/Desktop/data/grid/radgridi30tf6.bin"))

#define VOL16_SLIT1 (("/Desktop/data/grid/radgridi60tf1.bin"))
#define VOL16_SLIT2 (("/Desktop/data/grid/radgridi60tf2.bin"))
#define VOL16_SLIT3 (("/Desktop/data/grid/radgridi60tf3.bin"))
#define VOL16_SLIT4 (("/Desktop/data/grid/radgridi60tf4.bin"))
#define VOL16_SLIT5 (("/Desktop/data/grid/radgridi60tf5.bin"))
#define VOL16_SLIT6 (("/Desktop/data/grid/radgridi60tf6.bin"))

#define VOL17_SLIT1 (("/Desktop/data/grid/radgridi90tf1.bin"))
#define VOL17_SLIT2 (("/Desktop/data/grid/radgridi90tf2.bin"))
#define VOL17_SLIT3 (("/Desktop/data/grid/radgridi90tf3.bin"))
#define VOL17_SLIT4 (("/Desktop/data/grid/radgridi90tf4.bin"))
#define VOL17_SLIT5 (("/Desktop/data/grid/radgridi90tf5.bin"))
#define VOL17_SLIT6 (("/Desktop/data/grid/radgridi90tf6.bin"))

#define VOL18_SLIT1 (("/Desktop/data/rand/cylrandi0tf1.bin"))
#define VOL18_SLIT2 (("/Desktop/data/rand/cylrandi0tf2.bin"))
#define VOL18_SLIT3 (("/Desktop/data/rand/cylrandi0tf3.bin"))
#define VOL18_SLIT4 (("/Desktop/data/rand/cylrandi0tf4.bin"))
#define VOL18_SLIT5 (("/Desktop/data/rand/cylrandi0tf5.bin"))
#define VOL18_SLIT6 (("/Desktop/data/rand/cylrandi0tf6.bin"))

#define VOL19_SLIT1 (("/Desktop/data/rand/cylrandi30tf1.bin"))
#define VOL19_SLIT2 (("/Desktop/data/rand/cylrandi30tf2.bin"))
#define VOL19_SLIT3 (("/Desktop/data/rand/cylrandi30tf3.bin"))
#define VOL19_SLIT4 (("/Desktop/data/rand/cylrandi30tf4.bin"))
#define VOL19_SLIT5 (("/Desktop/data/rand/cylrandi30tf5.bin"))
#define VOL19_SLIT6 (("/Desktop/data/rand/cylrandi30tf6.bin"))

#define VOL20_SLIT1 (("/Desktop/data/rand/cylrandi60tf1.bin"))
#define VOL20_SLIT2 (("/Desktop/data/rand/cylrandi60tf2.bin"))
#define VOL20_SLIT3 (("/Desktop/data/rand/cylrandi60tf3.bin"))
#define VOL20_SLIT4 (("/Desktop/data/rand/cylrandi60tf4.bin"))
#define VOL20_SLIT5 (("/Desktop/data/rand/cylrandi60tf5.bin"))
#define VOL20_SLIT6 (("/Desktop/data/rand/cylrandi60tf6.bin"))

#define VOL21_SLIT1 (("/Desktop/data/rand/cylrandi90tf1.bin"))
#define VOL21_SLIT2 (("/Desktop/data/rand/cylrandi90tf2.bin"))
#define VOL21_SLIT3 (("/Desktop/data/rand/cylrandi90tf3.bin"))
#define VOL21_SLIT4 (("/Desktop/data/rand/cylrandi90tf4.bin"))
#define VOL21_SLIT5 (("/Desktop/data/rand/cylrandi90tf5.bin"))
#define VOL21_SLIT6 (("/Desktop/data/rand/cylrandi90tf6.bin"))

#define VOL22_SLIT1 (("/Desktop/data/rand/radrandi0tf1.bin"))
#define VOL22_SLIT2 (("/Desktop/data/rand/radrandi0tf2.bin"))
#define VOL22_SLIT3 (("/Desktop/data/rand/radrandi0tf3.bin"))
#define VOL22_SLIT4 (("/Desktop/data/rand/radrandi0tf4.bin"))
#define VOL22_SLIT5 (("/Desktop/data/rand/radrandi0tf5.bin"))
#define VOL22_SLIT6 (("/Desktop/data/rand/radrandi0tf6.bin"))

#define VOL23_SLIT1 (("/Desktop/data/rand/radrandi30tf1.bin"))
#define VOL23_SLIT2 (("/Desktop/data/rand/radrandi30tf2.bin"))
#define VOL23_SLIT3 (("/Desktop/data/rand/radrandi30tf3.bin"))
#define VOL23_SLIT4 (("/Desktop/data/rand/radrandi30tf4.bin"))
#define VOL23_SLIT5 (("/Desktop/data/rand/radrandi30tf5.bin"))
#define VOL23_SLIT6 (("/Desktop/data/rand/radrandi30tf6.bin"))

#define VOL24_SLIT1 (("/Desktop/data/rand/radrandi60tf1.bin"))
#define VOL24_SLIT2 (("/Desktop/data/rand/radrandi60tf2.bin"))
#define VOL24_SLIT3 (("/Desktop/data/rand/radrandi60tf3.bin"))
#define VOL24_SLIT4 (("/Desktop/data/rand/radrandi60tf4.bin"))
#define VOL24_SLIT5 (("/Desktop/data/rand/radrandi60tf5.bin"))
#define VOL24_SLIT6 (("/Desktop/data/rand/radrandi60tf6.bin"))

#define VOL25_SLIT1 (("/Desktop/data/rand/radrandi90tf1.bin"))
#define VOL25_SLIT2 (("/Desktop/data/rand/radrandi90tf2.bin"))
#define VOL25_SLIT3 (("/Desktop/data/rand/radrandi90tf3.bin"))
#define VOL25_SLIT4 (("/Desktop/data/rand/radrandi90tf4.bin"))
#define VOL25_SLIT5 (("/Desktop/data/rand/radrandi90tf5.bin"))
#define VOL25_SLIT6 (("/Desktop/data/rand/radrandi90tf6.bin"))

#define XMAX (512)
#define YMAX (512)
#define ZMAX (64)

#define XSIZE 1.0  
#define YSIZE 1.0
#define ZSIZE 0.25 

#define XSCALE 1.000000
#define YSCALE 1.000000
#define ZSCALE 0.187500
#endif

#define CLAMP(a,b,c) { b = ((b) < (a))? (a) : (((b) > (c))? (c): (b));}

#endif