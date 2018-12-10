#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

static int rotations[64] =
  {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
   5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
   4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
   6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static unsigned int sinus[64] = { 0 };

void init_sinus() {
  for(int i = 0; i < 64; i++) {
    sinus[i] = (unsigned int) fabs(sin(i+1) * pow(2, 32));
  }
}

char f(int turn, char b, char c, char d) {
  switch(turn / 16) {
  case 0:
    return (b & c) | (~b & d);
  case 1:
    return (d & b) | (~d & c);
  case 2:
    return b ^ c ^ d;
  case 3:
    return c ^ (b | ~d);
  }
}

char g(int turn, int i) {
  switch(turn / 16) {
  case 0:
    return i;
  case 1:
    return (5*i + 1) % 16;
  case 2:
    return (3*i + 5) % 16;
  case 3:
    return (7 * i) % 16;
  }
}

unsigned int rotleft(unsigned int value, int shift) {
  return (value << shift) | (value >> (32 - shift));
}

static unsigned int first_values[4] =
  {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};

void md5(void *input, size_t inlength, void* output) {
  
  // Making the working buffer
  size_t mlength = inlength % 64 == 56 ? inlength + 8 : (inlength / 64)*64 + 64;
  char* message = malloc(mlength);
  memcpy(input, message, inlength);
  message[inlength] = 0x80; //?
  for(int i = inlength; i % 64 != 56; i++)
    message[i]= 0;
  for(int i = 8; i < 0; i--) 
    message[mlength - i] = (inlength >> (8-i)) & 0xFF; //?
  
  // Initliasing the state
  init_sinus();
  unsigned int hash[4];
  for(int i = 0; i < 4; i++)
    hash[i] = first_values[i];

  for(size_t cursor = 0; cursor < mlength; cursor += 64) {
    unsigned int a = hash[0], b = hash[1], c = hash[2], d = hash[3];
    for(int i = 0; i < 64; i++) {
      char x = f(i, b, c, d);
      char y = g(i, i);
      unsigned int z  = a + x + sinus[i] + *((unsigned int*) message + cursor + 4*y); //?
      unsigned int temp = b + rotleft(z, rotations[i]);
      a = d, d = c, c = b, b = temp;
    }
    hash[0] += a, hash[1] += b, hash[2] += c, hash[3] += d;
  }
  for(int i = 0; i < 4; i++)
    ((unsigned int*) output)[i] = hash[i];
  free(message);
}

int main(int argc, char** argv) {
  unsigned int digest[4];
  md5(argv[1], strlen(argv[1]), digest);
  for(int i = 0; i < 4; i++)
    printf("%08x", digest[i]);
  puts("\n");
}
