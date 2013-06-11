#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define BER 3
#define LENGTH_OF_READ 1
#define IF_ERROR_OCCURS_WITH_PROBABILITY(BER)  if( ((rand()%100)+1)<=BER )

void bit_error_generator(unsigned char *buffer_data_ptr, int length)
{
  int i;
  for (i = 0; i < length; ++i)  //for each byte
  {
    int j;
    for (j = 1; j <= 8; ++j)  //for bit 1 to bit 8
    {
      IF_ERROR_OCCURS_WITH_PROBABILITY(BER)
      {
        int XORmask = (int)pow(2,j-1);  //using XOR mask
        buffer_data_ptr[i] = buffer_data_ptr[i]^XORmask;  //masking
      }
    }
  }
}

void processing(FILE *ifp, FILE *ofp);

void main(int argc, char *argv[])
{
  FILE *ifp;
  FILE *ofp;
  if (argc != 3) 
    printf("Usage: beg inputfile outputfile\n");
  if ((ifp = fopen(argv[1], "rb")) == NULL) {
        printf("can't open input file %s\n", argv[1]);
          return ;
  }
  if ((ofp = fopen(argv[2], "w")) == NULL) {
        printf("can't open output file %s\n", argv[2]);
          return ;
  }
  processing(ifp, ofp);
  return ;
}

void processing(FILE *ifp, FILE *ofp)
{
  unsigned char *c = malloc(LENGTH_OF_READ*sizeof(unsigned char));
  int iresult, oresult;
  while(1)
  {
    iresult = fread (c,1,LENGTH_OF_READ,ifp);
    if (iresult!=LENGTH_OF_READ)
      break;
    bit_error_generator(c, LENGTH_OF_READ);
    oresult = fwrite (c,1,iresult,ofp);
  }
}