#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>

static int rotations[64] =
  {7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22, 7, 12, 17, 22,
   5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20, 5,  9, 14, 20,
   4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23, 4, 11, 16, 23,
   6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21, 6, 10, 15, 21};

static uint32_t sinus[64] = 
  {0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee ,
   0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501 ,
   0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be ,
   0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821 ,
   0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa ,
   0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8 ,
   0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed ,
   0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a ,
   0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c ,
   0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70 ,
   0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05 ,
   0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665 ,
   0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039 ,
   0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1 ,
   0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1 ,
   0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391 };

uint32_t f(int turn, uint32_t b, uint32_t c, uint32_t d) {
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

size_t g(int i) {
  switch(i / 16) {
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

uint32_t rotleft(uint32_t value, int shift) {
  return (value << shift) | (value >> (32 - shift));
}

void md5(void *input, size_t inlength, void* output) {
  
  // Making the working buffer
  size_t mlength = inlength % 64 == 55 ? inlength + 9 : (inlength / 64)*64 + 64; //?
  char* message = calloc(mlength, 1);
  memcpy(message, input, inlength);
  message[inlength] = 0x80;
  memcpy(message + mlength - 8, &inlength, 8);
  
  // Initliasing
  uint32_t hash[4] = {0x67452301, 0xefcdab89, 0x98badcfe, 0x10325476};
  
  //Hashing 
  for(size_t cursor = 0; cursor < mlength; cursor += 64) {
    uint32_t *chunk = (uint32_t *) message + cursor;
    uint32_t a = hash[0], b = hash[1], c = hash[2], d = hash[3];

    //Performing a round
    for(int i = 0; i < 64; i++) {
      uint32_t x = a + f(i, b, c, d) + sinus[i] + chunk[g(i)];
      uint32_t temp = b + rotleft(x, rotations[i]);
      a = d, d = c, c = b, b = temp;
    }

    hash[0] += a, hash[1] += b, hash[2] += c, hash[3] += d;
  }

  //Finalization
  for(int i = 0; i < 4; i++)
    ((uint32_t*) output)[i] = hash[i];
  free(message);
}

int main(int argc, char** argv) {
  uint32_t digest[4];
  md5(argv[1], strlen(argv[1]), digest);
  for(int i = 0; i < 4; i++)
    printf("%08x", digest[i]);
  puts("\n");
}
