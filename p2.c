/* Hello World program */


#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct line1 {
unsigned char a;
unsigned char b;
unsigned char c;
unsigned char d;
};

struct line2 {
unsigned char a;
unsigned char b;
unsigned short c;
};

int main(int argc, char	**argv)
{
 FILE *fp1, *fp2;
 int i;
 int rslt;

 struct line1 x;
 int n;
 int version;
 int hlen;
 int total_len;


 unsigned int a;
 int checkSum;
 
 struct line2 y;
 char id[20], mask[20], next[20];
 unsigned int z;

 fp1 = fopen(argv[1],"r");
 if (fp1 == NULL) {
 	printf("Cannot open %s\n", argv[1]);
 	exit(1);
 }



while (fread(&x,4,1,fp1)) { // read IP first line
	version = x.a & 0xF0;
 
 	version = version >> 4;
 
 	printf("version = %d\n", version);

	hlen = x.a & 0x0F;
	hlen = hlen * 4;
	printf("hlen = %d\n",hlen);

	total_len = x.c * 256 + x.d;
	printf("total length = %d\n", total_len);

	fread(&x,4,1,fp1); // IGNORE 

	fread(&x,4,1,fp1); // TTL and checksum

	printf("TTL = %d\n", x.a);
	checkSum = x.c * 256 + x.d;
	printf("Checksum = %d\n", checkSum);

	fread(&a,4,1,fp1); // SOURCE IP
	unsigned char *ip = &a;

	printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
	n = fread(&a,4,1,fp1); // Destination IP
	unsigned char *ip1 = &a;
	//*ip1 = &a;
	printf("%d.%d.%d.%d\n", ip1[0], ip1[1], ip1[2], ip1[3]);

	char content[total_len - 20];
	n = fread(&content,total_len - 20,1,fp1); // DATA
	printf("Message = %s\n",content);

	printf("Next Packer\n");
	printf("\n");
}

/*
n = fread(&x,4,1,fp1);

 
 
 //close(fp1);

n = fread(&x,4,1,fp1); // IGNORE

n = fread(&x,4,1,fp1); // TTL and Checksum


printf("TTL = %d\n", x.a);
checkSum = x.c * 256 + x.d;
printf("Checksum = %d\n", checkSum);


n = fread(&a,4,1,fp1); // SOURCE IP
unsigned char *ip = &a;

printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
n = fread(&a,4,1,fp1); // Destination IP
*ip = &a;
printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);




char content[total_len];
n = fread(&content,sizeof(content),1,fp1); // DATA
printf("Message = %s\n",content);

printf("Next Packer\n");
printf("\n");


n = fread(&x,4,1,fp1);

//printf("%d\n", x.a);
 version = x.a & 0xF0;
 //printf("%d\n", version );
 version = version >> 4;
 //printf("%d\n", version );
 printf("version = %d\n", version);

 hlen = x.a & 0x0F;
 hlen = hlen * 4;
 printf("hlen = %d\n",hlen);

 total_len = x.c * 256 + x.d;
 printf("total length = %d\n", total_len);
 //close(fp1);



n = fread(&x,4,1,fp1);



n = fread(&x,4,1,fp1);// TTL and Checksum

printf("TTL = %d\n", x.a);
checkSum = x.c * 256 + x.d;
printf("Checksum = %d\n", checkSum);


n = fread(&a,4,1,fp1); // SOURCE IP
unsigned char *ip1 = &a;

printf("%d.%d.%d.%d\n", ip1[0], ip1[1], ip1[2], ip1[3]);


n = fread(&a,4,1,fp1); // Destination IP
*ip1 = &a;
printf("%d.%d.%d.%d\n", ip1[0], ip1[1], ip1[2], ip1[3]);


char content1[total_len];

n = fread(&content1,sizeof(content1),1,fp1);
printf("%s\n",content1);
*/




































/*
 fp1 = fopen(argv[1],"r");
 n = fread(&y, 4, 1, fp1);
 printf("y first total length= %d\n", y.c);
 y.c = ntohs(y.c);
 printf("y second total total length= %d\n", y.c);
 close(fp1);

 fp2 = fopen(argv[2], "r");
 fscanf(fp2,"%s %s %s", id, mask, next);
 printf("id=%s, mask=%s, next=%s\n",id, mask, next);
 fscanf(fp2,"%s %s %s", id, mask, next);
 printf("id=%s, mask=%s, next=%s\n",id, mask, next);

 int zid = inet_addr(id);
 int zmask = inet_addr(mask);
 int znext = inet_addr(next);

 printf("z = %u\n",zid);
 fclose(fp2);

*/
 return 0;
}
