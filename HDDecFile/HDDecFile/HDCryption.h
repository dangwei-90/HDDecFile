
enum{
	ENCRYPTION = 0x00000001,
	DECRYPTION = 0x00000002
};

enum{
	ALG_RC4 = 0x00000010
};

void Mydebug(char * infor);

extern "C" __declspec(dllexport) int HangDunCryptographyChars(int EncryptOrDecrypt,int EditionAlgorithm,int Length,char *InPut,char *OutPut);

extern "C" __declspec(dllexport) int HangDunCryptographyFile(int EncryptOrDecrypt,int EditionAlgorithm,char *InPut,char *OutPut);