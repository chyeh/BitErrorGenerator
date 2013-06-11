#include <stdio.h>
#include <time.h>
#include <math.h>
#define BER 3
void bit_error_generator(unsigned char *buffer_data_ptr, int size)
{
  //srand(time(NULL));  move to main
  int i;
  for (i = 0; i < size; ++i)//for each byte
  {
    int j;
    for (j = 1; j <= 8; ++j)//for bit 1 to bit 8
    {
      int randnum;
      randnum = (rand()%100)+1;
      //printf("randnum %d!!\n", randnum);
      if (randnum<=BER) //probability of BER%
      {
        //printf("got %d!!\n", ++gotcnt);
        int XORmask = (int)pow(2,j-1);//using XOR mask
        buffer_data_ptr[i] = buffer_data_ptr[i]^XORmask;//masking
      }
    }
  }
}

void processing(FILE *ifp, FILE *ofp);

void main(int argc, char *argv[])
{
  FILE *ifp;
  FILE *ofp;

  if (argc == 1) /* no args; copy standard input */
    printf("Usage: ~~~\n");
  /*else
    while(--argc > 0)
      if ((fp = fopen(*++argv, "rb")) == NULL) {
        printf("cat: can't open %s\n", *argv);
          return 1;
      } else {
        filecopy(fp, stdout);
        fclose(fp);
      }*/
  return ;
}

void processing(FILE *ifp, FILE *ofp)
{
  unsigned char c;

  while ((c = getc(ifp)) != EOF)
  {
    putc(c, ofp); 
  }
}