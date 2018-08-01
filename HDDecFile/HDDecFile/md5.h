////////////////////////////////////////////////////////
////本程序主要用于制作进程或者动态库文件指纹
//// 公司：上海全防隐形软件开发有限公司
//// 作者:史建刚
//// 时间：2006-2-13
////////////////////////////////////////////////////////


#ifndef WISE_MD5_H
#define WISE_MD5_H

#define MD5_LEN		16

typedef unsigned char *POINTER;
typedef unsigned long ULONG ;
typedef unsigned char UCHAR ;


/* MD5 context. */
typedef struct {
  ULONG			 state[4];         /* state (ABCD) */
  ULONG			 count[2];         /* number of bits, modulo 2^64 (lsb first) */
  UCHAR          buffer[64];        /* input buffer */
} MD5_CTX;

//MD5 initialization
extern VOID
MD5Init(
	 MD5_CTX	*pContext
	);

extern VOID
MD5Update(
	 MD5_CTX  *pContext, 
	 UCHAR    *pInputData, 
	 ULONG    InputLen 
	);

extern VOID
MD5Final(
	 UCHAR		*pDigest, 
	  MD5_CTX		*pContext
	);
	
int Hztc_DigestBuffer(char *Buffer,int BuffLen,char *Digest);
int Hztc_DigestFile(char *FileName,char *Digest);

#endif//WISE_MD5_H 

