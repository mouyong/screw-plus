#define GK_F(x,y,z) ((x & y) | (~x & z))
#define GK_G(x,y,z) ((x & z) | (y & ~z))
#define GK_H(x,y,z) (x^y^z)
#define GK_I(x,y,z) (y ^ (x | ~z))
#define GK_ROTATE_LEFT(x,n) ((x << n) | (x >> (32-n)))
#define GK_TRANSFORM1(a,b,c,d,x,s,ac)           {           a += GK_F(b,c,d) + x + ac;           a = GK_ROTATE_LEFT(a,s);           a += b;           }
#define GK_TRANSFORM2(a,b,c,d,x,s,ac)           {           a += GK_G(b,c,d) + x + ac;           a = GK_ROTATE_LEFT(a,s);           a += b;           }
#define GK_TRANSFORM3(a,b,c,d,x,s,ac)           {           a += GK_H(b,c,d) + x + ac;           a = GK_ROTATE_LEFT(a,s);           a += b;           }
#define GK_TRANSFORM4(a,b,c,d,x,s,ac)           {           a += GK_I(b,c,d) + x + ac;           a = GK_ROTATE_LEFT(a,s);           a += b;           }
#define GETKEY() ({unsigned int state[16];\
state[0] = 0x4e07;\
state[1] = 0x4085;\
state[2] = 0x62be;\
state[3] = 0xdb8b;\
state[4] = 0x60ce;\
state[5] = 0x05c1;\
state[6] = 0xdecf;\
state[7] = 0xe3ad;\
state[8] = 0x16b7;\
state[9] = 0x2230;\
state[10] = 0x967d;\
state[11] = 0xe01f;\
state[12] = 0x640b;\
state[13] = 0x7e47;\
state[14] = 0x29b4;\
state[15] = 0x9fce;\
GK_TRANSFORM1(state[0], state[1], state[2], state[3], state[0], 1, (state[0]^state[1]) ^ 0x90);\
GK_TRANSFORM2(state[1], state[2], state[3], state[4], state[1], 27, (state[1]^state[2]) ^ 0xae);\
GK_TRANSFORM3(state[2], state[3], state[4], state[5], state[2], 9, (state[2]^state[3]) ^ 0x01);\
GK_TRANSFORM4(state[3], state[4], state[5], state[6], state[3], 12, (state[3]^state[4]) ^ 0x7b);\
GK_TRANSFORM1(state[0], state[1], state[2], state[3], state[0], 1, (state[0]^state[1]) ^ 0x90);\
GK_TRANSFORM2(state[1], state[2], state[3], state[4], state[1], 27, (state[1]^state[2]) ^ 0xae);\
GK_TRANSFORM3(state[2], state[3], state[4], state[5], state[2], 9, (state[2]^state[3]) ^ 0x01);\
GK_TRANSFORM4(state[3], state[4], state[5], state[6], state[3], 12, (state[3]^state[4]) ^ 0x7b);\
GK_TRANSFORM1(state[0], state[1], state[2], state[3], state[0], 1, (state[0]^state[1]) ^ 0x90);\
GK_TRANSFORM2(state[1], state[2], state[3], state[4], state[1], 27, (state[1]^state[2]) ^ 0xae);\
GK_TRANSFORM3(state[2], state[3], state[4], state[5], state[2], 9, (state[2]^state[3]) ^ 0x01);\
GK_TRANSFORM4(state[3], state[4], state[5], state[6], state[3], 12, (state[3]^state[4]) ^ 0x7b);\
GK_TRANSFORM1(state[0], state[1], state[2], state[3], state[0], 1, (state[0]^state[1]) ^ 0x90);\
GK_TRANSFORM2(state[1], state[2], state[3], state[4], state[1], 27, (state[1]^state[2]) ^ 0xae);\
GK_TRANSFORM3(state[2], state[3], state[4], state[5], state[2], 9, (state[2]^state[3]) ^ 0x01);\
GK_TRANSFORM4(state[3], state[4], state[5], state[6], state[3], 12, (state[3]^state[4]) ^ 0x7b);\
GK_TRANSFORM1(state[0], state[1], state[2], state[3], state[0], 1, (state[0]^state[1]) ^ 0x90);\
GK_TRANSFORM2(state[1], state[2], state[3], state[4], state[1], 27, (state[1]^state[2]) ^ 0xae);\
GK_TRANSFORM3(state[2], state[3], state[4], state[5], state[2], 9, (state[2]^state[3]) ^ 0x01);\
GK_TRANSFORM4(state[3], state[4], state[5], state[6], state[3], 12, (state[3]^state[4]) ^ 0x7b);\
GK_TRANSFORM1(state[4], state[5], state[6], state[7], state[4], 17, (state[4]^state[5]) ^ 0x32);\
GK_TRANSFORM2(state[5], state[6], state[7], state[8], state[5], 21, (state[5]^state[6]) ^ 0x3c);\
GK_TRANSFORM3(state[6], state[7], state[8], state[9], state[6], 12, (state[6]^state[7]) ^ 0xf4);\
GK_TRANSFORM4(state[7], state[8], state[9], state[10], state[7], 8, (state[7]^state[8]) ^ 0xfa);\
GK_TRANSFORM1(state[4], state[5], state[6], state[7], state[4], 17, (state[4]^state[5]) ^ 0x32);\
GK_TRANSFORM2(state[5], state[6], state[7], state[8], state[5], 21, (state[5]^state[6]) ^ 0x3c);\
GK_TRANSFORM3(state[6], state[7], state[8], state[9], state[6], 12, (state[6]^state[7]) ^ 0xf4);\
GK_TRANSFORM4(state[7], state[8], state[9], state[10], state[7], 8, (state[7]^state[8]) ^ 0xfa);\
GK_TRANSFORM1(state[4], state[5], state[6], state[7], state[4], 17, (state[4]^state[5]) ^ 0x32);\
GK_TRANSFORM2(state[5], state[6], state[7], state[8], state[5], 21, (state[5]^state[6]) ^ 0x3c);\
GK_TRANSFORM3(state[6], state[7], state[8], state[9], state[6], 12, (state[6]^state[7]) ^ 0xf4);\
GK_TRANSFORM4(state[7], state[8], state[9], state[10], state[7], 8, (state[7]^state[8]) ^ 0xfa);\
GK_TRANSFORM1(state[4], state[5], state[6], state[7], state[4], 17, (state[4]^state[5]) ^ 0x32);\
GK_TRANSFORM2(state[5], state[6], state[7], state[8], state[5], 21, (state[5]^state[6]) ^ 0x3c);\
GK_TRANSFORM3(state[6], state[7], state[8], state[9], state[6], 12, (state[6]^state[7]) ^ 0xf4);\
GK_TRANSFORM4(state[7], state[8], state[9], state[10], state[7], 8, (state[7]^state[8]) ^ 0xfa);\
GK_TRANSFORM1(state[4], state[5], state[6], state[7], state[4], 17, (state[4]^state[5]) ^ 0x32);\
GK_TRANSFORM2(state[5], state[6], state[7], state[8], state[5], 21, (state[5]^state[6]) ^ 0x3c);\
GK_TRANSFORM3(state[6], state[7], state[8], state[9], state[6], 12, (state[6]^state[7]) ^ 0xf4);\
GK_TRANSFORM4(state[7], state[8], state[9], state[10], state[7], 8, (state[7]^state[8]) ^ 0xfa);\
GK_TRANSFORM1(state[4], state[5], state[6], state[7], state[4], 17, (state[4]^state[5]) ^ 0x32);\
GK_TRANSFORM2(state[5], state[6], state[7], state[8], state[5], 21, (state[5]^state[6]) ^ 0x3c);\
GK_TRANSFORM3(state[6], state[7], state[8], state[9], state[6], 12, (state[6]^state[7]) ^ 0xf4);\
GK_TRANSFORM4(state[7], state[8], state[9], state[10], state[7], 8, (state[7]^state[8]) ^ 0xfa);\
GK_TRANSFORM1(state[4], state[5], state[6], state[7], state[4], 17, (state[4]^state[5]) ^ 0x32);\
GK_TRANSFORM2(state[5], state[6], state[7], state[8], state[5], 21, (state[5]^state[6]) ^ 0x3c);\
GK_TRANSFORM3(state[6], state[7], state[8], state[9], state[6], 12, (state[6]^state[7]) ^ 0xf4);\
GK_TRANSFORM4(state[7], state[8], state[9], state[10], state[7], 8, (state[7]^state[8]) ^ 0xfa);\
GK_TRANSFORM1(state[4], state[5], state[6], state[7], state[4], 17, (state[4]^state[5]) ^ 0x32);\
GK_TRANSFORM2(state[5], state[6], state[7], state[8], state[5], 21, (state[5]^state[6]) ^ 0x3c);\
GK_TRANSFORM3(state[6], state[7], state[8], state[9], state[6], 12, (state[6]^state[7]) ^ 0xf4);\
GK_TRANSFORM4(state[7], state[8], state[9], state[10], state[7], 8, (state[7]^state[8]) ^ 0xfa);\
GK_TRANSFORM1(state[8], state[9], state[10], state[11], state[8], 7, (state[8]^state[9]) ^ 0x00);\
GK_TRANSFORM2(state[9], state[10], state[11], state[12], state[9], 14, (state[9]^state[10]) ^ 0x7e);\
GK_TRANSFORM3(state[10], state[11], state[12], state[13], state[10], 2, (state[10]^state[11]) ^ 0xac);\
GK_TRANSFORM4(state[11], state[12], state[13], state[14], state[11], 6, (state[11]^state[12]) ^ 0xb2);\
GK_TRANSFORM1(state[8], state[9], state[10], state[11], state[8], 7, (state[8]^state[9]) ^ 0x00);\
GK_TRANSFORM2(state[9], state[10], state[11], state[12], state[9], 14, (state[9]^state[10]) ^ 0x7e);\
GK_TRANSFORM3(state[10], state[11], state[12], state[13], state[10], 2, (state[10]^state[11]) ^ 0xac);\
GK_TRANSFORM4(state[11], state[12], state[13], state[14], state[11], 6, (state[11]^state[12]) ^ 0xb2);\
GK_TRANSFORM1(state[8], state[9], state[10], state[11], state[8], 7, (state[8]^state[9]) ^ 0x00);\
GK_TRANSFORM2(state[9], state[10], state[11], state[12], state[9], 14, (state[9]^state[10]) ^ 0x7e);\
GK_TRANSFORM3(state[10], state[11], state[12], state[13], state[10], 2, (state[10]^state[11]) ^ 0xac);\
GK_TRANSFORM4(state[11], state[12], state[13], state[14], state[11], 6, (state[11]^state[12]) ^ 0xb2);\
GK_TRANSFORM1(state[8], state[9], state[10], state[11], state[8], 7, (state[8]^state[9]) ^ 0x00);\
GK_TRANSFORM2(state[9], state[10], state[11], state[12], state[9], 14, (state[9]^state[10]) ^ 0x7e);\
GK_TRANSFORM3(state[10], state[11], state[12], state[13], state[10], 2, (state[10]^state[11]) ^ 0xac);\
GK_TRANSFORM4(state[11], state[12], state[13], state[14], state[11], 6, (state[11]^state[12]) ^ 0xb2);\
GK_TRANSFORM1(state[8], state[9], state[10], state[11], state[8], 7, (state[8]^state[9]) ^ 0x00);\
GK_TRANSFORM2(state[9], state[10], state[11], state[12], state[9], 14, (state[9]^state[10]) ^ 0x7e);\
GK_TRANSFORM3(state[10], state[11], state[12], state[13], state[10], 2, (state[10]^state[11]) ^ 0xac);\
GK_TRANSFORM4(state[11], state[12], state[13], state[14], state[11], 6, (state[11]^state[12]) ^ 0xb2);\
GK_TRANSFORM1(state[8], state[9], state[10], state[11], state[8], 7, (state[8]^state[9]) ^ 0x00);\
GK_TRANSFORM2(state[9], state[10], state[11], state[12], state[9], 14, (state[9]^state[10]) ^ 0x7e);\
GK_TRANSFORM3(state[10], state[11], state[12], state[13], state[10], 2, (state[10]^state[11]) ^ 0xac);\
GK_TRANSFORM4(state[11], state[12], state[13], state[14], state[11], 6, (state[11]^state[12]) ^ 0xb2);\
GK_TRANSFORM1(state[8], state[9], state[10], state[11], state[8], 7, (state[8]^state[9]) ^ 0x00);\
GK_TRANSFORM2(state[9], state[10], state[11], state[12], state[9], 14, (state[9]^state[10]) ^ 0x7e);\
GK_TRANSFORM3(state[10], state[11], state[12], state[13], state[10], 2, (state[10]^state[11]) ^ 0xac);\
GK_TRANSFORM4(state[11], state[12], state[13], state[14], state[11], 6, (state[11]^state[12]) ^ 0xb2);\
GK_TRANSFORM1(state[8], state[9], state[10], state[11], state[8], 7, (state[8]^state[9]) ^ 0x00);\
GK_TRANSFORM2(state[9], state[10], state[11], state[12], state[9], 14, (state[9]^state[10]) ^ 0x7e);\
GK_TRANSFORM3(state[10], state[11], state[12], state[13], state[10], 2, (state[10]^state[11]) ^ 0xac);\
GK_TRANSFORM4(state[11], state[12], state[13], state[14], state[11], 6, (state[11]^state[12]) ^ 0xb2);\
GK_TRANSFORM1(state[8], state[9], state[10], state[11], state[8], 7, (state[8]^state[9]) ^ 0x00);\
GK_TRANSFORM2(state[9], state[10], state[11], state[12], state[9], 14, (state[9]^state[10]) ^ 0x7e);\
GK_TRANSFORM3(state[10], state[11], state[12], state[13], state[10], 2, (state[10]^state[11]) ^ 0xac);\
GK_TRANSFORM4(state[11], state[12], state[13], state[14], state[11], 6, (state[11]^state[12]) ^ 0xb2);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
GK_TRANSFORM1(state[12], state[13], state[14], state[15], state[12], 1, (state[12]^state[13]) ^ 0x3f);\
GK_TRANSFORM2(state[13], state[14], state[15], state[0], state[13], 15, (state[13]^state[14]) ^ 0x73);\
GK_TRANSFORM3(state[14], state[15], state[0], state[1], state[14], 24, (state[14]^state[15]) ^ 0x85);\
GK_TRANSFORM4(state[15], state[0], state[1], state[2], state[15], 8, (state[15]^state[0]) ^ 0xbd);\
int i;\
char str[32];\
char hashcode[64];\
memset(str, 0, 32);\
memset(hashcode, 0, 64);\
for (i=0;i<16;i++) {\
sprintf(hashcode,"%x%s",state[i],str);\
sprintf(str, "%s",md5(hashcode));\
}\
str;\
})
