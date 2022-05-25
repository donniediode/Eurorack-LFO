
#include <xc.h>

    
    
__attribute__((space(psv)))  unsigned int potValuesL[] = {

0xCCCC,0x5900,0xE94C,0x7D8A,0x1597,0xB150,0x5095,0xF345,0x9940,0x426B,0xEEA6,0x9DD8,0x4FE4,0x04B2,0xBC28,0x762E,
0x32AE,0xF190,0xB2BF,0x7626,0x3BB1,0x034E,0xCCE8,0x986F,0x65D0,0x34FB,0x05E0,0xD870,0xAC9A,0x8251,0x5986,0x322C,
0x0C37,0xE798,0xC445,0xA232,0x8153,0x619D,0x4306,0x2584,0x090D,0xED97,0xD31A,0xB98C,0xA0E6,0x891E,0x722E,0x5C0D,
0x46B4,0x321D,0x1E40,0x0B16,0xF89A,0xE6C5,0xD591,0xC4F9,0xB4F7,0xA586,0x96A1,0x8842,0x7A66,0x6D06,0x6020,0x53AF,
0x47AE,0x3C19,0x30EE,0x2627,0x1BC2,0x11BB,0x080E,0xFEBA,0xF5B9,0xED0A,0xE4AA,0xDC95,0xD4CA,0xCD45,0xC604,0xBF04,
0xB844,0xB1C1,0xAB79,0xA56A,0x9F91,0x99EE,0x947D,0x8F3E,0x8A2E,0x854C,0x8096,0x7C0B,0x77A9,0x736E,0x6F5A,0x6B6A,
0x679F,0x63F5,0x606D,0x5D05,0x59BB,0x568F,0x5380,0x508D,0x4DB4,0x4AF5,0x484F,0x45C1,0x434A,0x40E9,0x3E9E,0x3C67,
0x3A45,0x3836,0x3639,0x344F,0x3275,0x30AD,0x2EF4,0x2D4C,0x2BB2,0x2A27,0x28A9,0x2739,0x25D7,0x2480,0x2336,0x21F7,
0x20C4,0x1F9C,0x1E7E,0x1D6A,0x1C60,0x1B5F,0x1A67,0x1979,0x1892,0x17B4,0x16DD,0x160E,0x1547,0x1486,0x13CD,0x131A,
0x126D,0x11C6,0x1125,0x108A,0x0FF4,0x0F64,0x0ED9,0x0E53,0x0DD1,0x0D54,0x0CDB,0x0C67,0x0BF7,0x0B8B,0x0B22,0x0ABD,
0x0A5C,0x09FE,0x09A4,0x094D,0x08F9,0x08A7,0x0859,0x080E,0x07C5,0x077E,0x073B,0x06F9,0x06BA,0x067D,0x0643,0x060A,
0x05D3,0x059F,0x056C,0x053B,0x050B,0x04DE,0x04B2,0x0487,0x045E,0x0437,0x0410,0x03EC,0x03C8,0x03A6,0x0385,0x0365,
0x0346,0x0329,0x030C,0x02F1,0x02D6,0x02BC,0x02A3,0x028C,0x0275,0x025E,0x0249,0x0234,0x0220,0x020D,0x01FA,0x01E9,
0x01D7,0x01C7,0x01B6,0x01A7,0x0198,0x018A,0x017C,0x016E,0x0161,0x0155,0x0149,0x013D,0x0132,0x0127,0x011D,0x0112,
0x0109,0x00FF,0x00F6,0x00EE,0x00E5,0x00DD,0x00D5,0x00CE,0x00C6,0x00BF,0x00B9,0x00B2,0x00AC,0x00A6,0x00A0,0x009A,
0x0095,0x008F,0x008A,0x0085,0x0081,0x007C,0x0078,0x0073,0x006F,0x006B,0x0068,0x0064,0x0060,0x005D,0x005A,0x0056,
};


__attribute__((space(psv)))  unsigned int potValuesH[] = {
12,12,11,11,11,10,10,9,9,9,8,8,8,8,7,7,
7,6,6,6,6,6,5,5,5,5,5,4,4,4,4,4,
4,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,
2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,
1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
};

unsigned int sineLUT[] = {

    127, 130, 133, 136, 139, 142, 145, 148, 151, 154, 157, 160, 163, 166, 169, 172, 
    175, 178, 181, 184, 186, 189, 192, 194, 197, 200, 202, 205, 207, 209, 212, 214, 
    216, 218, 221, 223, 225, 227, 229, 230, 232, 234, 235, 237, 239, 240, 241, 243, 
    244, 245, 246, 247, 248, 249, 250, 250, 251, 252, 252, 253, 253, 253, 253, 253, 
    254, 253, 253, 253, 253, 253, 252, 252, 251, 250, 250, 249, 248, 247, 246, 245, 
    244, 243, 241, 240, 239, 237, 235, 234, 232, 230, 229, 227, 225, 223, 221, 218, 
    216, 214, 212, 209, 207, 205, 202, 200, 197, 194, 192, 189, 186, 184, 181, 178, 
    175, 172, 169, 166, 163, 160, 157, 154, 151, 148, 145, 142, 139, 136, 133, 130, 
    127, 123, 120, 117, 114, 111, 108, 105, 102, 99, 96, 93, 90, 87, 84, 81, 
    78, 75, 72, 69, 67, 64, 61, 59, 56, 53, 51, 48, 46, 44, 41, 39, 
    37, 35, 32, 30, 28, 26, 24, 23, 21, 19, 18, 16, 14, 13, 12, 10, 
    9, 8, 7, 6, 5, 4, 3, 3, 2, 1, 1, 0, 0, 0, 0, 0, 
    0, 0, 0, 0, 0, 0, 1, 1, 2, 3, 3, 4, 5, 6, 7, 8, 
    9, 10, 12, 13, 14, 16, 18, 19, 21, 23, 24, 26, 28, 30, 32, 35, 
    37, 39, 41, 44, 46, 48, 51, 53, 56, 59, 61, 64, 67, 69, 72, 75, 
    78, 81, 84, 87, 90, 93, 96, 99, 102, 105, 108, 111, 114, 117, 120, 123
            
};



//19.5khz electric druid lfo - phase acc is 24 bit!

unsigned int incsH_lfo [] = {
  
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1,
    0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1, 0x1,
    0x1, 0x1, 0x1, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x2,
    0x2, 0x2, 0x2, 0x2, 0x2, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3,
    0x3, 0x3, 0x3, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x4, 0x5, 0x5, 0x5,
    0x5, 0x5, 0x5, 0x5, 0x5, 0x5, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x6, 0x7, 0x7, 0x7,
    0x7, 0x7, 0x7, 0x8, 0x8, 0x8, 0x8, 0x8, 0x9, 0x9, 0x9, 0x9, 0x9, 0xa, 0xa, 0xa,
    0xa, 0xa, 0xb, 0xb, 0xb, 0xb, 0xc, 0xc, 0xc, 0xd, 0xd, 0xd, 0xd, 0xe, 0xe, 0xe,
    0xf, 0xf, 0xf, 0x10, 0x10, 0x10, 0x11, 0x11, 0x12, 0x12, 0x12, 0x13, 0x13, 0x14, 0x14, 0x15,
    0x15, 0x15, 0x16, 0x16, 0x17, 0x17, 0x18, 0x19, 0x19, 0x1a, 0x1a, 0x1b, 0x1b, 0x1c, 0x1d, 0x1d,
    0x1e, 0x1f, 0x1f, 0x20, 0x21, 0x21, 0x22, 0x23, 0x24, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a
    
};

unsigned int incsL_lfo [] = {
  
    0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x37, 0x38, 0x39, 0x3a, 0x3c,
    0x3d, 0x3e, 0x40, 0x41, 0x42, 0x44, 0x45, 0x47, 0x48, 0x4a, 0x4c, 0x4d, 0x4f, 0x51, 0x52, 0x54,
    0x56, 0x58, 0x5a, 0x5c, 0x5e, 0x60, 0x62, 0x64, 0x66, 0x69, 0x6b, 0x6d, 0x70, 0x72, 0x75, 0x77,
    0x7a, 0x7c, 0x7f, 0x82, 0x85, 0x88, 0x8b, 0x8e, 0x91, 0x94, 0x97, 0x9a, 0x9e, 0xa1, 0xa5, 0xa8,
    0xac, 0xb0, 0xb4, 0xb8, 0xbc, 0xc0, 0xc4, 0xc8, 0xcd, 0xd1, 0xd6, 0xda, 0xdf, 0xe4, 0xe9, 0xee,
    0xf3, 0xf9, 0xfe, 0x4, 0x9, 0xf, 0x15, 0x1b, 0x21, 0x28, 0x2e, 0x35, 0x3c, 0x42, 0x4a, 0x51,
    0x58, 0x60, 0x67, 0x6f, 0x77, 0x80, 0x88, 0x90, 0x99, 0xa2, 0xab, 0xb5, 0xbe, 0xc8, 0xd2, 0xdc,
    0xe7, 0xf1, 0xfc, 0x7, 0x13, 0x1e, 0x2a, 0x36, 0x43, 0x4f, 0x5c, 0x6a, 0x77, 0x85, 0x93, 0xa2,
    0xb0, 0xbf, 0xcf, 0xdf, 0xef, 0xff, 0x10, 0x21, 0x33, 0x44, 0x57, 0x69, 0x7d, 0x90, 0xa4, 0xb9,
    0xcd, 0xe3, 0xf8, 0xf, 0x25, 0x3d, 0x54, 0x6d, 0x86, 0x9f, 0xb9, 0xd3, 0xee, 0xa, 0x26, 0x43,
    0x61, 0x7f, 0x9e, 0xbd, 0xdd, 0xfe, 0x20, 0x42, 0x65, 0x89, 0xae, 0xd3, 0xf9, 0x20, 0x48, 0x71,
    0x9b, 0xc5, 0xf1, 0x1e, 0x4b, 0x79, 0xa9, 0xda, 0xb, 0x3e, 0x72, 0xa7, 0xdd, 0x14, 0x4c, 0x86,
    0xc1, 0xfd, 0x3b, 0x7a, 0xba, 0xfc, 0x3f, 0x84, 0xca, 0x12, 0x5b, 0xa6, 0xf2, 0x41, 0x91, 0xe2,
    0x36, 0x8b, 0xe2, 0x3b, 0x96, 0xf3, 0x52, 0xb3, 0x16, 0x7c, 0xe3, 0x4d, 0xb9, 0x28, 0x99, 0xc,
    0x82, 0xfb, 0x76, 0xf4, 0x75, 0xf8, 0x7f, 0x8, 0x94, 0x24, 0xb6, 0x4c, 0xe5, 0x81, 0x21, 0xc4,
    0x6b, 0x16, 0xc4, 0x76, 0x2c, 0xe6, 0xa4, 0x66, 0x2d, 0xf7, 0xc7, 0x9a, 0x73, 0x50, 0x32, 0x19
    
};