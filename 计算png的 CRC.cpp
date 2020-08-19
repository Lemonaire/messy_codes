#include<iostream>
using namespace std;
typedef unsigned char byte; 
 
 
 
//===================================================ԭʼ�����
 /* Table of CRCs of all 8-bit messages. ÿ��Ԫ�ؽ����� һ���ֽ�Ҳ����8λ*/
   unsigned long crc_table[256];
   
   /* Flag: has the table been computed? Initially false.
   ���ȫ�ֱ��������ж��Ƿ���Ѿ���ʼ�����ˣ���������һ���������������͵ĳ������еĶ������棬�����־���Խ�ʡʱ�䲻�ö�γ�ʼ��by datrilla */
   int crc_table_computed = 0;
   
   /* Make the table for a fast CRC. ����һ����ʼ��һ��CRC-32���ֽڵĿ��ٲ��ı� 
   ���˺þã���ô���ѭ���������Ǹ�˵��CRC-32�����ϲ�һ����
   ����������ȥ����edb88320��������˳����
   1+1*x^1+1*x^2+0*x^3+1*x^4+1*x^5+0*x^6+1+x^7+1*x^8����+1*x^32=CRC-32
   1110 1101 1011 1000 1000 0011 0010 0000 (1)
   EDB88320 (1) �����1������CRC�̶������λҪΪ1.  
   ����crc_table[1]��128��crc-32����������n=0000 0001   ����ֵΪ 1000 0000��
   by datrilla*/
   void make_crc_table(void)
   {
     unsigned long c;
     int n, k;
     /*��Ϊǰ��ע�͵�(1)�����⣬���Դ�[0,255]��������������⣬����1��Ӧ������0000 0001 ��1��ʼ����by datrilla*/
     for (n = 0; n < 256; n++) {
       c = (unsigned long) n;
       for (k = 0; k < 8; k++) { 
		   if (c & 1)/*�����������λΪ1����Ҫģ�����㣬��crc-32��(1)�϶������¸������У�������ʽ������ֱ��ԭ������by datrilla*/
           c = 0xedb88320L ^ (c >> 1);  
         else
           c = c >> 1;
       }
       crc_table[n] = c;
     }
     crc_table_computed = 1;
   }
   
   /* Update a running CRC with the bytes buf[0..len-1]--the CRC
      should be initialized to all 1's, and the transmitted value
      is the 1's complement of the final running CRC (see the
      crc() routine below)). */
   unsigned long update_crc(unsigned long crc, unsigned char *buf,
                            int len)
   {
     unsigned long c = crc;
     int n;
   
     if (!crc_table_computed)
       make_crc_table();
     for (n = 0; n < len; n++) {
       c = crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8);
	   /*�ʼ������cΪ0xffffffffL���μ��������crc()�������ĵ�һ������
	    (c ^ buf[n]) & 0xff ����ǰbuf[n]������c���ֽڰ�λ���
	    crc_table[(c ^ buf[n]) & 0xff]�����ֽڱ��ж�ȡ��Ӧ��������
	   crc_table[(c ^ buf[n]) & 0xff] ^ (c >> 8)���Ѷ�ȡ��������������c�����������ֽڰ�λ��򣬲���ֵ����c*/
     }
     return c;
   }
   
   /* Return the CRC of the bytes buf[0..len-1]. */
   unsigned long crc(unsigned char *buf, int len)
   {
     return update_crc(0xffffffffL, buf, len) ^ 0xffffffffL;/*�ѵõ���ֵ�����Ժ���*/
   }
 
 
 
   //============================��ȡ�̶������Ƿ����
void readImageFile(const char* Imgname)  
{   
    FILE* imgP = fopen(Imgname, "rb");  
    //����vs��ô��ȫ�Ե�ԭ�򣬲���ʹ��fopen���������fopen_s���棻  
    //FILE*imgP;  
    //fopen_s(&imgP,Imgname,"rb");//�������ö����ƶ�ȡ��read-r��binary-b����ΪֻŪr���������Ū�˺����Ǹ�������������ŷ�������������⣡��  
    if (imgP == NULL)return ;  
    fseek(imgP, 0L, SEEK_END);  
    long size = ftell(imgP);       
    byte*imgbuf = new byte[size+ 1];    
 
 
	//IHDR���ݶ�
	fseek(imgP,0xCL,SEEK_SET);
	size=17;//IHDR���ݶβ���ѭ��������������ֽ���  
    fread(imgbuf, sizeof(imgbuf[0]), size, imgP);  
    cout<<hex<<"����õ���CRC��"<<(crc(imgbuf,size)&0xffffffffL)<<endl;
 
   
	//��λIHDRͼƬ��ѭ���������λ�ö�ȡ���
	size=0x1D; 
	fseek(imgP,size,SEEK_SET);
	size=4;
    fread(imgbuf, sizeof(imgbuf[0]), size, imgP); 
	fclose(imgP); 
	cout<<"ͼƬ�ж�ȡ�õ���CRC��";
    for (int j = 0; j < size; j++) 
        cout << (imgbuf[j] & 0xff) ; 
	cout<<endl;
}  
   int main()
   { 
	  readImageFile("1af012e7f3fc4b83972dfc19c2d65a36.png");//C/C++��  
	   return 0;
   }
