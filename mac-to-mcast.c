#include <stdio.h>

int main(int argc, char const *argv[]) {

/* Test input MAC address -> 01:00:5e:0b:01:02 */

char input_mac[] = "01:00:5e:0b:01:02";
unsigned int b[6];
/* multicast IP address mask - 1110 xxxx xxxx xxxx xxxx xxxx xxxx xxxx */
unsigned int ip = 0xe0000000;

/* Task 1 - get 23 LSB of input MAC address and store them in int
   I interpret each char as hex */
sscanf(input_mac, "%x:%x:%x:%x:%x:%x", &b[0], &b[1], &b[2], &b[3], &b[4], &b[5]);

/* Here I put bytes on respective positions */
ip |= b[5];
ip |= (b[4] << 8);
ip |= (b[3] << 16);

/* Now my uint looks like this:
1110 0000 0000 1011 0000 0001 0000 0010
1110 xxxx x000 1011 0000 0001 0000 0010

I have to get all combination of X, so I need to iterate 31 times
*/

for (int i = 0; i < 32; i++)
{
  unsigned int temp = ip;
  temp |= (i << 23);

  unsigned int o4 = (temp & 0xff000000) >> 24;
  unsigned int o3 = (temp & 0x00ff0000) >> 16;
  unsigned int o2 = (temp & 0x0000ff00) >> 8;
  unsigned int o1 = temp & 0x000000ff;
  char out_buffer[50];
  sprintf(out_buffer, "#%u\t%u.%u.%u.%u", i, o4, o3, o2, o1 );
  printf("%s\n", out_buffer);
}

  return 0;
}
