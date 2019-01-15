#ifndef DS1307_H_INCLUDED
#define DS1307_H_INCLUDED

#define ADD_SEG         0x00
#define ADD_MIN         0x01
#define ADD_HORA        0x02
#define ADD_DIA_SEMANA  0x03
#define ADD_DIA         0x04
#define ADD_MES         0x05
#define ADD_ANO         0x06

/*Cabeçalho usado para a leitura do RTC
    Autor: Alison Almeida
    Data: 12/01/2019
*/

class DS1307
{
public :
    DS1307(unsigned char address);
    /*
    funções usadas para recuperar desde o segundo
    até o ano
    */
    unsigned char get_segundo();
    unsigned char get_minuto();
    unsigned char get_hora();
    unsigned char get_dia_semana();
    unsigned char get_dia();
    unsigned char get_mes();
    unsigned char get_ano();
    unsigned char getRAM(unsigned char address);
    /*
    funções usadas para setar desde o segundo
    até o ano
    */
    void set_segundo(unsigned char _data);
    void set_minuto(unsigned char _data);
    void set_hora(unsigned char _data);
    void set_dia_semana(unsigned char _data);
    void set_dia(unsigned char _data);
    void set_mes(unsigned char _data);
    void set_ano(unsigned char _data);
    void setRAM(unsigned char address, unsigned char _data);

    /*
    Escreve a hora ou hora completa
    */
    void setHora(unsigned char *ptr);
    void setData(unsigned char *ptr);

    /*
    Le a data ou hora completa
    */
    void getHora(unsigned char *ptr, unsigned char tamanho);
    void getData(unsigned char *ptr, unsigned char tamanho);

private:
    unsigned char BcdToInit(unsigned char num);
    unsigned char IntToBcd (unsigned char num);
    unsigned char readByte_I2c(unsigned char registrador);
    void writeByte_I2c (unsigned char registrador, unsigned char _data);
    unsigned char readByte_I2c(unsigned char registrador, bool flag);
    void writeByte_I2c (unsigned char registrador, unsigned char _data, bool flag);

    unsigned char _add;
    unsigned char i;

};


#endif // DS1307_H_INCLUDED
