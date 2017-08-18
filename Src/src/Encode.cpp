#include "encode.h"

int AEncode::ansi_to_wchar(const char* AnsiStr, wchar_t* pDst)
{
	int ret;
	wchar_t* pws = NULL;

	//计算需要的宽字符的个数
	ret = MultiByteToWideChar(CP_ACP, 0, AnsiStr, -1, NULL, 0);
	if(ret<=0){
		*pDst = 0;
		return 0;
	}
	//分配需要的宽字符的空间(*2)
	pws =  new wchar_t[ret*2];
	if(pws == NULL){
		*pDst = 0;
		return 0;
	}
	//将ANSI字符串转换为UNICODE
	MultiByteToWideChar(CP_ACP, 0, AnsiStr, -1, pws, ret);
	wcscpy(pDst,pws);
	delete[] pws;
	return 1;
}

int AEncode::ansi_to_utf8(const char* AnsiStr, char* pDst)
{
	int ret,ret2;
	wchar_t* pws = NULL;

	//计算需要的宽字符的个数
	ret = MultiByteToWideChar(CP_ACP, 0, AnsiStr, -1, NULL, 0);
	if(ret<=0){
		*pDst = 0;
		return 0;
	}
	//分配需要的宽字符的空间(*2)
	pws =  new wchar_t[ret*2];
	if(pws == NULL){
		*pDst = 0;
		return 0;
	}
	//将ANSI字符串转换为UNICODE
	MultiByteToWideChar(CP_ACP, 0, AnsiStr, -1, pws, ret);
	//计算需要的UTF-8的空间
	ret2 = WideCharToMultiByte(CP_UTF8, 0, pws, -1, NULL, 0, NULL, NULL);
	if(ret2<=0){
		delete[] pws;
		return 0;
	}

	//将UNICODE转换为UTF-8
	if(WideCharToMultiByte(CP_UTF8, 0, pws, ret, pDst, ret2, NULL, NULL)){
		//utils.free_mem(NULL,(void**)&pws,"<ansi_to_utf8.putf==NULL>");
		delete[] pws;
		return 1;
	}else{
		//utils.free_mem(NULL,(void**)&pws,"<ansi_to_utf8.pws==NULL>");
		delete[] pws;
		*pDst = 0;
		return 0;
	}
}

int AEncode::utf8_to_ansi(const char* UTF8Str, char* pAnsi)
{
	int ret, ret2;
	wchar_t* pws = NULL;
	//计算需要的宽字符的空间
	ret = MultiByteToWideChar(CP_UTF8, 0, UTF8Str, -1, NULL, 0);
	if(ret<=0){
		*pAnsi = 0;
		return 0;
	}
	//分配宽字符的空间
	pws = new wchar_t[ret*2];
	if(pws == NULL){
		*pAnsi = 0;
		return 0;
	}
	//将UTF-8转换为UNICODE
	MultiByteToWideChar(CP_UTF8, 0, UTF8Str, -1, pws, ret);
	//计算所需ANSI的字符数
	ret2 = WideCharToMultiByte(CP_ACP, 0, pws, -1, NULL, 0, NULL, NULL);
	if(ret2<=0){
		//delete[] pws;
		//utils.free_mem(NULL,(void**)&pws,"<utf8_to_ansi.putf==NULL>");
		delete[] pws;
		return 0;
	}

	//UNICODE -> ANSI
	if(WideCharToMultiByte(CP_ACP, 0, pws, -1, pAnsi, ret2, NULL, NULL)){
		//utils.free_mem(NULL,(void**)&pws,"pws");
		delete[] pws;
		return 1;
	}else{
		*pAnsi = 0;
		//utils.free_mem(NULL,(void**)&pws,"pws");
		delete[] pws;
		return 0;
	}
}
