#define   BSP_STRING_C

#include "stdio.h"
#include "sysctrl.h"

#include "driver_lptim.h"

/*---------------------------------------------------------------------------
 * @brief bcd转十六进制
 * @output
 * @return
---------------------------------------------------------------------------*/
int BcdToDecimal(int bcd)
{
    int decimal = 0;
    int multiplier = 1;

    while (bcd > 0)
    {
        // Extract the last nibble (4 bits)
        int digit = bcd & 0x0F;
        // Add the decimal value of the BCD digit to the result
        decimal += digit * multiplier;
        // Shift right by 4 bits to process the next BCD digit
        bcd >>= 4;
        // Update the multiplier for the next decimal place
        multiplier *= 10;
    }
    return decimal;
}
/*---------------------------------------------------------------------------
 * @brief 十六进制转bcd
 * @output
 * @return
---------------------------------------------------------------------------*/
int DecimalToBcd(int decimal)
{
    unsigned long bcd = 0;
    int shift = 0;

    while (decimal > 0)
    {
        // Get the last digit of the decimal number
        int digit = decimal % 10;
        // Shift the BCD number left by 4 bits and add the new digit
        bcd |= (digit << shift);
        shift += 4;
        // Remove the last digit from the decimal number
        decimal /= 10;
    }
    return bcd;
}

/*---------------------------------------------------------------------------
 * @brief  
 * @output
 * @return
---------------------------------------------------------------------------*/
unsigned char convert_hexTostr(unsigned char hexValue)
{
    hexValue = hexValue & 0xF;
    //------------------------
    if (hexValue > 9)
    {
        return ('A' + (hexValue - 10));
    }
    else
    {
        return ('0' + hexValue);
    }
}

/*---------------------------------------------------------------------------
 * @brief
 * @output
 * @return
---------------------------------------------------------------------------*/
unsigned char convert_strTOhex(char str)
{
	unsigned char asc=0 ;
    
    if((str>='0')&&(str<='9'))
	{
		asc = str -0x30 ;
	}	
	else if((str>='a')&&(str<='f'))
	{
		asc = str -0x57 ;
	}
	else if((str>='A')&&(str<='F'))
	{
		asc = str -0x37 ;
	}
    return asc;    
}

/*---------------------------------------------------------------------------
 * @brief
 * @output
 * @return
---------------------------------------------------------------------------*/
void convert_charTOstring(unsigned char *in_char,char *out_str,unsigned char len)
{
    unsigned char i,j ;
	
	if(len>127)
	{
		len=127;
	}	
	for(i=0,j=0;i<len;i++)
	{
		out_str[j++] = convert_hexTostr(in_char[i]>>4);
		out_str[j++] = convert_hexTostr(in_char[i]&0xf);		
	}
	out_str[j] = '\0';
}


/*---------------------------------------------------------------------------
 * @brief
 * @output
 * @return
---------------------------------------------------------------------------*/
void convert_intTOstring(int param,char *str)
{
	char len =0 ;
	char count=0 ;
	char buf[15] ;
	int temp = param ;
	
	if (temp < 0) 
	{
		str[len++] = '-' ;
		temp = (~(temp-1)) ;
	}	
    do 
    {
        buf[count++] = temp%10;
        temp /=10 ;        
    }while(temp!=0);	
	while(count>0)
	{
		count -- ;
		str[len++] = buf[count]+'0';
	}
	str[len]='\0';
}	

/*----------------------------------------------------------------------
 * @brief  
 * @param  
 * @output
----------------------------------------------------------------------*/
void convert_bcdTOstring(int param,char *str)
{  
    unsigned char i=0;
    unsigned char len=0;
	char buf[15] ;

    if(param<0)
    {
	    str[len++]='-';
	    param = (~(param-1)) ;						  
    }
    //-----------------------------------------------
    while((param>0)&&(i<14))
	{
		buf[i]= param & 0x0F;
		param >>=4;
		i++ ;
	}	
	while(i>0)
	{
		i--;
		str[len++]=convert_hexTostr(buf[i]);
	}	
	str[len]='\0';	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
signed int convert_stringTOhex(char * buf)
{
    unsigned char i,len,flag=0 ;
    signed int params=0 ;

    len = strlen(buf);
    if(buf[0]=='-')
    {
        len--;
        buf++;
        flag =1 ;
    }
    for(i=0;i<len;i++)
    {
        params <<=4;
        params |= convert_strTOhex(buf[i]);          
    }
    if(flag==1)
    {
        params = (~params)+1 ;
    }
    return params ;
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
signed int convert_stringTObcd(char * buf)
{
    unsigned char i,len,flag=0 ;
    signed int decimal = 0;

    len = strlen(buf);
    if(buf[0]=='-')
    {
        len--;
        buf++;
        flag =1 ;
    }
    for(i=0;i<len;i++)
    {
        if(decimal>0)
		{
			decimal *=10 ;
		}	
		decimal += convert_strTOhex(buf[i]) ; 
    }
    if(flag==1)
    {
        decimal = (~decimal)+1 ;
    }
    return decimal ;
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
float convert_stringTOfloat(char* str) 
{
    float sign = 1.0f;
    float value = 0.0f;
    float decimal_scale = 0.1f;
    unsigned char decimal_found = 0; // 标记是否找到小数点
    // 处理符号
    if (*str == '-') 
	{
        sign = -1.0f;
        str++;
    }else if (*str == '+') 
	{
        str++; // 跳过正号
    }
    // 逐字符解析
    while (*str != '\0')
    {
        if (*str == '.')
        {
            decimal_found = 1;
        } 
		else if (*str >= '0' && *str <= '9')
        {
            if (!decimal_found)
            {
                value = value * 10.0f + (*str - '0');// 如果还未找到小数点，按整数部分处理
            } else
            {
                value += (*str - '0') * decimal_scale;// 如果已经找到小数点，按小数部分处理
                decimal_scale *= 0.1f;                // 缩小小数位的缩放因子
            }
        }
        str++;
    }
    return sign * value;
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
char string_compare(char *str1,char *str2)
{    
    char * p;
	for(p=str2; *str1!='\0' && *p!='\0';str1++)    
    {        				
		if(*str1 == *p)    			
		   p++ ;
		else
		{
		   if(*str1 == *str2)
		   {
		      p=str2+1;
		   }
		   else
		      p=str2;
		}		   		    
    }            
    if(*p == '\0')   
        return 1;
	else
	    return 0;	    
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
char string_place(char *str1,char *str2,char **out_str) 
{    
	char * p1;
    char * p2;
	
    if((*str1 == '\0')||(*str2 == '\0'))
	{
		return 0 ;
	}
	for(p1=str1,p2=str2 ; *p1!='\0' && *p2!='\0';p1++)
	{
		if(*p1 != *p2)
		{
			p2 =str2 ;
		}
		else
		{
			p2++ ;
		}	
	}
    if(*p2=='\0')
    {
        *out_str = p1 ;
		return 1;
    }
    else
    {
        return 0 ;
    }   
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void string_splicing(char*buf,char*part)
{
    unsigned char i;
    unsigned short len_buf,len_part;

    len_buf=strlen(buf);
    len_part=strlen(part);

    buf+=len_buf;
    for(i=0;i<len_part;i++)
    {
        buf[i]= part[i];
    }
    buf[i]='\0';
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void string_fixed(char *dst,char *src,unsigned char len) 
{ 
    unsigned char i ;
	
	for(i=0;i<len;i++)
	{
		dst[i]=src[i];
	}
	dst[len]='\0';
}

/*---------------------------------------------------------------------------
 * @brief
 * @output
 * @return
---------------------------------------------------------------------------*/
unsigned int string_copy(char*dst,char*input)	
{
	unsigned int len=0;
	while(*input!='\0')
	{
	    *dst = *input ;
		len++;
		dst++;
		input++;
	}
    *dst='\0';
    return len ;	
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void string_get_params(char *buf,char symbol,char *params)
{   
    char *p ;
	unsigned char i ;

    p = buf ;
    if(p[0] == symbol) 
    {
        p++;
    }
    for(i=0;i<16;i++)
    {
        if((p[i]==0x0D)||(p[i]==symbol))
        {
            break;
        }
        params[i] = p[i];
    }
    params[i] = '\0';
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char string_get_symbol(char *buf,char symbol)
{
    char *p ;
	unsigned char num=0;

    p = buf ;
    if(p[0] == symbol) 
    {
        p++;
    }
    while(*p!='\r')
    {
        if(*p==symbol)
        {
            num++;
        }
    }
    return num ;
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
unsigned char string_get_bool(char *dat)
{
    int i ;  
    char temp[8]={0};
    for(i=0;i<8;i++)
    {
        if((dat[i]=='\r')||(dat[i]==' '))
        {
            break;
        }
        temp[i] = dat[i];
    }	
	temp[i]='\0';
	if(string_compare(&temp[0],"true")==1)
	{
		return 1 ;
	}
	if(string_compare(&temp[0],"false")==1)
	{
		return 0 ;
	}
	return 2 ;		
}

/*-----------------------------------------------------------------------------
 * @brief: 
 * @input: 
 * @return:
-----------------------------------------------------------------------------*/
void string_output_bool(char in_bit,char *buf)
{
	if(in_bit==1)
	{
		string_copy(buf,"true");
	}
    else
    {
		string_copy(buf,"false");
	}		
}	

















