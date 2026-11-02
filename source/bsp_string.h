
#ifndef  BSP_STRING_H
#define  BSP_STRING_H


#ifdef      BSP_STRING_C
    #define BSP_STRING_C
#else
    #define BSP_STRING_C extern 
#endif

int BcdToDecimal(int bcd);	
int DecimalToBcd(int decimal);	
	
unsigned char convert_hexTostr(unsigned char hexValue);
unsigned char convert_strTOhex(char str);
	
void convert_charTOstring(unsigned char *in_char,char *out_str,unsigned char len);	
void convert_intTOstring(int param,char *str);
void convert_bcdTOstring(int param,char *str);
	
signed int convert_stringTOhex(char * buf);
signed int convert_stringTObcd(char * buf);
float convert_stringTOfloat(char* str);	
	
char string_compare(char *str1,char *str2);
char string_place(char *str1,char *str2,char **out_str);

void string_splicing(char*buf,char*part);
void string_fixed(char *dst,char *src,unsigned char len);
unsigned int string_copy(char*dst,char*input);		
	
void string_get_params(char *buf,char symbol,char *params);	
unsigned char string_get_symbol(char *buf,char symbol);
unsigned char string_get_bool(char *dat);
void string_output_bool(char in_bit,char *buf);
#endif
