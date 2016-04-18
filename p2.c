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



int main(int argc, char	**argv)
{
 FILE *fp1, *fp2, *fp3, *fp4;
 

 struct line1 x;
 int n;
 int version;
 int hlen;
 int total_len;


 unsigned int a;
 int checkSum;


 char id[20], mask[20], next[20];



 fp1 = fopen(argv[1],"r");
 if (fp1 == NULL) {
 	printf("Cannot open %s\n", argv[1]);
 	exit(1);
 }

fp2 = fopen(argv[2], "r");

if (fp2 == NULL) {
 	printf("Cannot open %s\n", argv[2]);
 	exit(1);
 }

int count = 0;
int packetCount = 0;
char response[110];

fp3 = fopen("ans.txt", "w");
int ctx= 0;
short index = 0;
unsigned int newchecksum;
while(ctx !=10) {
	ctx++;
	fread(&index,sizeof(index),1,fp1);
	if (ctx !=6) {
		
		newchecksum +=index;

		if (newchecksum > 65535) {
			newchecksum -=65535;
		}
	}
}

printf("IP = %04x\n", htons(~(short)newchecksum));



rewind(fp1);

while (fread(&x,4,1,fp1)) { // read IP first line
	version = x.a & 0xF0;
	packetCount++;
 
	unsigned int checkcnt;
	


	checkcnt  = htons((x.a * 256 + x.b)) + htons((x.c * 256 + x.d));

	if  (checkcnt > 65535) {
		checkcnt -=65535;
	}


 	version = version >> 4;
 
 	//printf("version = %d\n", version);

	hlen = x.a & 0x0F;
	hlen = hlen * 4;
	//printf("hlen = %d\n",hlen);

	total_len = x.c * 256 + x.d;
	//printf("total length = %d\n", total_len);

	fread(&x,4,1,fp1); // IGNORE 

	checkcnt = checkcnt + htons((x.a * 256 + x.b));
	if  (checkcnt > 65535) {
		checkcnt -=65535;
	}


	checkcnt = checkcnt + htons((x.c * 256 + x.d));
	if  (checkcnt > 65535) {
		checkcnt -=65535;
	}





	fread(&x,4,1,fp1); // TTL and checksum
	int TTL = x.a;
	checkSum = x.c * 256 + x.d;

	//printf("TTL = %d\n", TTL);

	checkcnt = checkcnt + htons((x.a * 256 + x.b));
	if  (checkcnt > 65535) {
		checkcnt -=65535;
	}

	



	checkSum = x.c * 256 + x.d;
	
	fread(&a,4,1,fp1); // SOURCE IP
	

	short ipPart1 =  a & 0xFFFF;
	short ipPart2 = (a & 0xFFFF0000) >> 16;

	//printf("YOLLLOO %04x\n", ipPart2);
	checkcnt += ipPart1;
	if  (checkcnt > 65535) {
		checkcnt -=65535;
	}



	checkcnt += ipPart2;
	if  (checkcnt > 65535) {
		checkcnt -=65535;
	}
	
	

	unsigned char *ip = &a;


	char sourceIP[50];
	sprintf(sourceIP, " Source IP = %d.%d.%d.%d",ip[0], ip[1], ip[2], ip[3]);

	
	n = fread(&a,4,1,fp1); // Destination IP
	

	ipPart1 =  a & 0xFFFF;
	ipPart2 = (a & 0xFFFF0000) >> 16;
	
	checkcnt += ipPart1;
	if  (checkcnt > 65535) {
		checkcnt -=65535;
	}



	checkcnt += ipPart2;
	if  (checkcnt > 65535) {
		checkcnt -=65535;
	}



	unsigned char *ip1 = &a;
	char destIP[50];
	sprintf(destIP, " Destination IP = %d.%d.%d.%d ",ip1[0], ip1[1], ip1[2], ip1[3]);
	



	//// Checksume check
	
	





	//// End checksum chekc

	short finalAnswer = (short)checkcnt;
	
	//printf("%04x\n", checkSum );

	char content[total_len - 20];
	n = fread(&content,total_len - 20,1,fp1); // DATA
	//printf("Message = %s\n",content);

	unsigned int prevMask = 0;

	char packetFwdIP[25];
	
	int droppedPacket = 0 ;


	

	TTL = TTL - 1;

	
		
	char abc[20];
	char totalLength[20];
	sprintf(totalLength, "Total length = %d ", total_len);
	sprintf(abc,"TTL = %d",TTL);
	strcat(response,abc);
	strcat(response,sourceIP);
	strcat(response,destIP);
	strcat(response,totalLength);

	if (TTL ==0) {
		droppedPacket = 1;
		strcpy(packetFwdIP, " Packet was dropped TTL becomes 0\n");
	}


	printf("%04x\n", htons(~(short)checkcnt));
	checkcnt = htons(~(short)checkcnt);
	//printf("IP= %04x\n", checkcnt );
	printf("%04x\n", checkSum );

	if (checkcnt != checkSum) {
		droppedPacket = 1;
		strcpy(packetFwdIP, " Packet was dropped Checksum incorrect\n");
	}











	while (fscanf(fp2,"%s %s %s", id, mask, next) != EOF && droppedPacket == 0) {
		count++;
		fscanf(fp2,"%s %s %s", id, mask, next);
		
		unsigned int zid = inet_addr(id);
		unsigned int zmask = inet_addr(mask);
		//unsigned int znext = inet_addr(next);

		
		

		if ((a & zmask) == zid) {

			if ( zmask >= prevMask ) {
				prevMask = zmask;
				strcpy(packetFwdIP,next);
				strcat(packetFwdIP, " is next hop IP\n");
			}
		}

	}
	count = 0;
	prevMask = 0;
	rewind(fp2);

	printf("Next Hop IP= %s\n", packetFwdIP);
	strcat(response,packetFwdIP);

	//printf("%s\n",response);

	fprintf(fp3, "%s", response);

	//fprintf(fp3, "%s", response);

	memset(response, 0, sizeof response);

	printf("Next Packet \n");
	
	printf("\n");
}



 fclose(fp1);
 fclose(fp3);
 fclose(fp2);


 return 0;
}
