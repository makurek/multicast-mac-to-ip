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

printf("%d\n", b[3]);

/* Here I put bytes on respective positions */
unsigned int b0 = b[5];
unsigned int b1 = b[4] << 8;
unsigned int b2 = b[3] << 16;

unsigned int ip1 = b0 | b1;
unsigned int ip2 = ip1 | b2;

printf("%x\n", ip2);

unsigned int ip3 = ip2 | ip;

printf("%x\n", ip3);
int z;
for (int i = 0; i < 32; i++)
{
  z = ip3 | (i << 23);
  printf("%x\n", z);
  unsigned int o4 = (z & 0xff000000) >> 24;
  unsigned int o3 = (z & 0x00ff0000) >> 16;
  unsigned int o2 = (z & 0x0000ff00) >> 8;
  unsigned int o1 = z & 0x000000ff;
  char buffer[50];
  sprintf(buffer, "%u %u %u %u\n", o4, o3, o2, o1 );
  printf("%s\n", buffer);
}

  return 0;
}
