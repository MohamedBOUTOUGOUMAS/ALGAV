#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>
#include <algorithm>
#include "cle.h"
using namespace std;

using uint1b_t = unsigned char;  // 8bits (1 Byte)
using uint4b_t = unsigned int;	// 32bits (4 Byte)

/**
 * No-linear functions
 */

/**
 * F := (B and C) or ((not B) and D)
 */
uint4b_t F_f(uint4b_t b, uint4b_t c, uint4b_t d) {
  return (b & c) | ((~b) & d);
}

/*
 * F := (D and B) or ((not D) and C)
 */
uint4b_t G_f(uint4b_t b, uint4b_t c, uint4b_t d) {
  return (d & b) | ((~d) & c);
}

/**
 * F := B xor C xor D
 */
uint4b_t H_f(uint4b_t b, uint4b_t c, uint4b_t d) {
  return b ^ c ^ d;;
}

/**
 * F := C xor (B or (not D))
 */
uint4b_t I_f(uint4b_t b, uint4b_t c, uint4b_t d) {
  return c ^ (b | (~d));;
}

/**
 * leftrotate rotates x left n bits.
 */
uint4b_t leftrotate(uint4b_t x, int n) {
  return (x << n) | (x >> (32-n));
}

/**
* integer h0 := 0x67452301
* integer h1 := 0xEFCDAB89
* integer h2 := 0x98BADCFE
* integer h3 := 0x10325476
*/



static unsigned* md5(string msg) {
	uint4b_t h0 = 0x67452301;
	uint4b_t h1 = 0xEFCDAB89;
	uint4b_t h2 = 0x98BADCFE;
	uint4b_t h3 = 0x10325476;

	int msglen = msg.length(); // size in digit of my msg
	uint1b_t *nmsg = NULL;
	static const uint4b_t r[] = {7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,  7, 12, 17, 22,
	                			5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,  5,  9, 14, 20,
								4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,  4, 11, 16, 23,
								6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21,  6, 10, 15, 21};

	/**
	 * k[i] := floor(abs(sin(i + 1)) * 2^32) // 1lu <==> (uint4_t) 1
	 */
	uint4b_t k[64];
	for (int i = 0; i < 64; i++) {
		k[i] = (uint4b_t) (fabs(sin(i + 1.0)) * (1lu << 32));
	}

	/**
	 * Padding of the message :
	 * - adding the bit '1' to the message
	 * - adding the bit '0' to the message until the size of the message in bits is 448 (mod 512)
	 */

	int nmsglen;
	for(nmsglen = msglen * 8 + 1; nmsglen % 512 != 448; nmsglen++); // calculating the new length in bits
	nmsglen /= 8;

	nmsg = (uint1b_t*)calloc(nmsglen + 8, 1); // adding '0' to the message
	memcpy(nmsg, msg.c_str(), msglen);
	nmsg[msglen] = (uint1b_t) 0x80; // adding '1' to the message

	uint4b_t msglenb = 8 * msglen; // message length in bits
	memcpy(nmsg + nmsglen, &msglenb, 4); // adding original length in bits mod 2^64 to the message

	/**
	 * Process the message in 512-bit blocks:
	 */

	int offset;
	for(offset=0; offset<nmsglen; offset += (512/8)) {

		/**
		 *  break blocks into sixteen 32-bit words M[j], 0 <= i <= 15
		 */

		uint4b_t *w = (uint4b_t *) (nmsg + offset);

		uint4b_t a = h0;
		uint4b_t b = h1;
		uint4b_t c = h2;
		uint4b_t d = h3;

		/**
		 * Main loop
		 */

		for (int i = 0; i < 64; i++) {

			uint4b_t F, g;

			if (0 <= i and i <= 15)
			{
				F = F_f(b,c,d);
				g = i;
			}
			else if(16 <= i and i <= 31)
			{
				F = G_f(b,c,d);
				g = (5*i + 1) % 16;
			}
			else if (32 <= i and i <= 47)
			{
				F = H_f(b,c,d);
				g = (3*i + 5) % 16;
			}
			else if (48 <= i and i <= 64)
			{
				F = I_f(b,c,d);
				g = (7*i) % 16;
			}

			F = F + a + k[i] + w[g];
			a = d;
			d = c;
			c = b;
			b = b + leftrotate(F, r[i]);
		}


	/*
	 * var char digest[16] := a0 append b0 append c0 append d0
	 */

		h0 += a;
		h1 += b;
		h2 += c;
		h3 += d;

	}

	// clean the memory
	free(nmsg);

	// create un array of hashes
	//uint4b_t hashed[4] = {h0,h1,h2,h3};
	uint4b_t * hashed = (uint4b_t *)malloc(16);
	hashed[0] = h0;
	hashed[1] = h1;
	hashed[2] = h2;
	hashed[3] = h3;
	return std::move(hashed);
}

static string md5toString(string msg) {
	string str;
	int i;
	uint4b_t *d = md5(msg);
	for (i = 0; i<4; i++){
		char s[9];
		uint1b_t *h;
		h=(uint1b_t *)&d[i];
		sprintf(s, "%02x%02x%02x%02x", h[0], h[1], h[2], h[3]); // @suppress("Function cannot be resolved")
		str += s;
	}

	return str;
}


int main(){

	int tailleFichier = 1;
	string path = ("/home/moumouh/workspace_c++/FilesBinomiales/src/Shakespeare/");
	string extension = to_string(tailleFichier) + "henryiv.txt";
	path = path + extension;

	FILE* fp = fopen(path.c_str(), "r");

	if(!fp){
		return 0;
	}


	vector<cle *> keys;

	char temp[36] = {0};

	while(fgets (temp, 35, fp) !=NULL) {
		cout<<temp<<endl;
		string k = md5toString(temp);
		cle * cl = parse_cle(k.c_str());
		print(cl);
		cout<<k<<endl;
		keys.push_back(cl);
	}
	fclose(fp);

	/*for(auto i:keys){
		print(i);
	}*/


	/*string msg = "salut les gens comment allez vous";
	string msg1 = "ALGAV";
	string msg2 = "salut khbc gens comment allez vous";
	string msg3 = "salut N gens comment allez vous";
	string msg4 = "salut X gens comment allez vous";
	string value = md5toString(msg);
	string value1 = md5toString(msg1);
	string value2 = md5toString(msg2);
	string value3 = md5toString(msg3);
	string value4 = md5toString(msg4);
	cout << "The md5 hash of \"" << msg << "\" is :"<<value << endl;
	cout << "The md5 hash of \"" << msg1 << "\" is :"<<value1 << endl;
	cout << "The md5 hash of \"" << msg2 << "\" is :"<<value2 << endl;
	cout << "The md5 hash of \"" << msg3 << "\" is :"<<value3 << endl;
	cout << "The md5 hash of \"" << msg4 << "\" is :"<<value4 << endl;
*/
return 0;
}
