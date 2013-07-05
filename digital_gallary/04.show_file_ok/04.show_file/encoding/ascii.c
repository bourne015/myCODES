
#include <config.h>
#include <encoding_manager.h>
#include <string.h>

static int isAsciiCoding(unsigned char *pucBufHead);
static int AsciiGetCodeFrmBuf(unsigned char *pucBufStart, unsigned char *pucBufEnd, unsigned int *pdwCode);

static T_EncodingOpr g_tAsciiEncodingOpr = {
	.name          = "ascii",
	.iHeadLen      = 0,
	.isSupport     = isAsciiCoding,
	.GetCodeFrmBuf = AsciiGetCodeFrmBuf,
};

static int isAsciiCoding(unsigned char *pucBufHead)
{
	const char aStrUtf8[]    = {0xEF, 0xBB, 0xBF, 0};
	const char aStrUtf16le[] = {0xFF, 0xFE, 0};
	const char aStrUtf16be[] = {0xFE, 0xFF, 0};
	
	if (strncmp((const char*)pucBufHead, aStrUtf8, 3) == 0)
	{
		/* UTF-8 */
		return 0;
	}
	else if (strncmp((const char*)pucBufHead, aStrUtf16le, 2) == 0)
	{
		/* UTF-16 little endian */
		return 0;
	}
	else if (strncmp((const char*)pucBufHead, aStrUtf16be, 2) == 0)
	{
		/* UTF-16 big endian */
		return 0;
	}
	else
	{
		return 1;
	}
}

static int AsciiGetCodeFrmBuf(unsigned char *pucBufStart, unsigned char *pucBufEnd, unsigned int *pdwCode)
{
	unsigned char *pucBuf = pucBufStart;
	unsigned char c = *pucBuf;
	
	if ((pucBuf < pucBufEnd) && (c < (unsigned char)0x80))
	{
		/* ����ASCII�� */
		*pdwCode = (unsigned int)c;
		return 1;
	}

	if (((pucBuf + 1) < pucBufEnd) && (c >= (unsigned char)0x80))
	{
		/* ����GBK�� */
		*pdwCode = pucBuf[0] + (((unsigned int)pucBuf[1])<<8);
		return 2;
	}

	if (pucBuf < pucBufEnd)
	{
		/* �����ļ�����, ���ǻ��Ƿ���һ����, ��ʹ���Ǵ���� */
		*pdwCode = (unsigned int)c;
		return 1;
	}
	else
	{
		/* �ļ�������� */
		return 0;
	}
}

int AsciiEncodingInit(void)
{
	g_tAsciiEncodingOpr.aptFontOprSupported[0] = GetFontOpr("ascii");
	g_tAsciiEncodingOpr.aptFontOprSupported[1] = GetFontOpr("gbk");
	g_tAsciiEncodingOpr.aptFontOprSupported[2] = NULL;	
	return RegisterEncodingOpr(&g_tAsciiEncodingOpr);
}
