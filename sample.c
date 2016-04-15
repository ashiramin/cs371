


n = fread(&x,4,1,fp1);
printf("%d\n", x.a);
 version = x.a & 0xF0;
 printf("%d\n", version );
 version = version >> 4;
 printf("%d\n", version );
 printf("version = %d\n", version);

 hlen = x.a & 0x0F;
 hlen = hlen * 4;
 printf("hlen = %d\n",hlen);

printf("%d\n", x.c );
printf("%d\n", x.d);
 total_len = x.c * 256 + x.d;
 printf("total length = %d\n", total_len);
 //close(fp1);

//n = fread(&x,4,1,fp1); // IGNORE

n = fread(&x,4,1,fp1); // TTL and Checksum
printf("TTL = %d\n", x.a);
checkSum = x.c * 256 + x.d;
printf("Checksum = %d\n", checkSum);


n = fread(&a,4,1,fp1); // SOURCE IP
unsigned char *ip1 = &a;

printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);


n = fread(&a,4,1,fp1); // Destination IP

*ip1 = &a;
printf("%d.%d.%d.%d\n", ip[0], ip[1], ip[2], ip[3]);

char content1[30756];
n = fread(content1,2817,1,fp1); // DATA
printf("%s\n",content1);



 /*while (fread(&x,4,1,fp1)) {
 		 count++;

         printf("%u, %u, %u, %u\n ", x.a, x.b, x.c, x.d);
         int ip;
         if (count == 4) {

         	unsigned char bytes[4];
			//int a;
         	fread(&a,4,1,fp1);
         	printf("%d\n", a);
         	unsigned char *ips = &a;
         	//int value = 570534080;
    		printf("%d.%d.%d.%d\n", ips[0], ips[1], ips[2], ips[3]);

    		fread(&a,4,1,fp1);
         	printf("%d\n", a);
         	*ip = &a;
         	//int value = 570534080;
    		printf("%d.%d.%d.%d\n", ips[0], ips[1], ips[2], ips[3]);
    		    		//printf("%x\n", bytes);      

         }
    }
*/

