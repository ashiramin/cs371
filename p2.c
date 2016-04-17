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
 FILE *fp1, *fp2, *fp3;
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

fp2 = fopen(argv[2], "r");

int count = 0;
int packetCount = 0;
char response[1000];


while (fread(&x,4,1,fp1)) { // read IP first line
	version = x.a & 0xF0;
	packetCount++;
 
 	version = version >> 4;
 
 	//printf("version = %d\n", version);

	hlen = x.a & 0x0F;
	hlen = hlen * 4;
	//printf("hlen = %d\n",hlen);

	total_len = x.c * 256 + x.d;
	//printf("total length = %d\n", total_len);

	fread(&x,4,1,fp1); // IGNORE 

	fread(&x,4,1,fp1); // TTL and checksum
	int TTL = x.a;
	printf("TTL = %d\n", TTL);
	checkSum = x.c * 256 + x.d;
	//printf("Checksum = %d\n", checkSum);

	fread(&a,4,1,fp1); // SOURCE IP
	unsigned char *ip = &a;
	char sourceIP[50];
	sprintf(sourceIP, " Source IP = %d.%d.%d.%d",ip[0], ip[1], ip[2], ip[3]);




	printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);
	n = fread(&a,4,1,fp1); // Destination IP
	unsigned char *ip1 = &a;
	char destIP[50];
	sprintf(destIP, " Destination IP = %d.%d.%d.%d",ip1[0], ip1[1], ip1[2], ip1[3]);

	//*ip1 = &a;
	printf("%d.%d.%d.%d\n", ip1[0], ip1[1], ip1[2], ip1[3]);





	char content[total_len - 20];
	n = fread(&content,total_len - 20,1,fp1); // DATA
	printf("Message = %s\n",content);

	unsigned int prevMask = 0;

	char packetFwdIP[20];
	char line[100];
	int droppedPacket = 0 ;


	fp3 = fopen("ans.txt", "w");


	if (TTL <=1) {
		droppedPacket = 1;
		strcpy(packetFwdIP, " Packet was dropped TTL becomes 0");
		
		char abc[20];
		//char *some_addr = inet_ntoa(ip1);
		//char sourceIP[50];
		
		//sprintf(sourceIP, " Source IP = %d.%d.%d.%d",ip[0], ip[1], ip[2], ip[3]);
		//sprintf(destIP, " Destination IP = %d.%d.%d.%d",ip1[0], ip1[1], ip1[2], ip1[3]);

		sprintf(abc,"TTL = %d",TTL);
		strcat(response,abc);
		strcat(response,sourceIP);
		strcat(response,destIP);
		strcat(response,packetFwdIP);

		//strcat(response, TTL);
		//strcat(response, );
		//strcat(response, );
		//strcat(response, );
		//printf("%s\n",abc);
		printf("%s\n",response );
	}

	while (count < 7 && droppedPacket == 0) {
		count++;
		fscanf(fp2,"%s %s %s", id, mask, next);
		
		unsigned int zid = inet_addr(id);
		unsigned int zmask = inet_addr(mask);
		unsigned int znext = inet_addr(next);

		
		

		if ((a & zmask) == zid) {

			//printf("%s\n", "There is a match");
			//printf("Mask number = %d\n", zmask );
			//printf("prevMask number = %d\n", prevMask );
			if ( zmask >= prevMask ) {
				prevMask = zmask;
				
				//printf("BALSALDLASDASDLASDASDLS %d\n", prevMask);
				strcpy(packetFwdIP,next);
				//packetFwdIP = next;
			}
			//printf("id=%s, mask=%s, next=%s\n",id, mask, next);
		}

	}
	count = 0;
	prevMask = 0;
	rewind(fp2);

	printf("IP= %s\n",packetFwdIP);

	printf("Next Packet \n");
	printf("\n");
}







 fp1 = fopen(argv[1],"r");
 n = fread(&y, 4, 1, fp1);
 printf("y first total length= %d\n", y.c);
 y.c = ntohs(y.c);
 printf("y second total total length= %d\n", y.c);
 close(fp1);

// fp2 = fopen(argv[2], "r");
 

 //printf("z = %d\n",zid);
 fclose(fp2);


 return 0;
}
