#include <Wire.h>
#include "DS1307.h"

DS1307::DS1307(unsigned char  add){
	_add = add;
	Wire.begin();
}

/***********************************
    Funções para a leitura do relogio
*/
unsigned char DS1307::get_segundo(){
    return readByte_I2c(ADD_SEG);
}

unsigned char DS1307::get_minuto(){
    return readByte_I2c(ADD_MIN);
}

unsigned char DS1307::get_hora(){
    return readByte_I2c(ADD_HORA);
}

unsigned char DS1307::get_dia_semana(){
    return readByte_I2c(ADD_DIA_SEMANA);
}

unsigned char DS1307::get_dia(){
    return readByte_I2c(ADD_DIA);
}

unsigned char DS1307::get_mes(){
    return readByte_I2c(ADD_MES);
}

unsigned char DS1307::get_ano(){
    return readByte_I2c(ADD_ANO);
}

unsigned char DS1307::getRAM(unsigned char address){
    return readByte_I2c(address, true);
}

/**********************************************
    Funções para ajuste fino do relogio
*/
void DS1307::set_segundo(unsigned char _data){
    writeByte_I2c(ADD_SEG, _data);
}

void DS1307::set_minuto(unsigned char _data){
    writeByte_I2c(ADD_MIN, _data);
}

void DS1307::set_hora(unsigned char _data){
    writeByte_I2c(ADD_HORA, _data);
}

void DS1307::set_dia_semana(unsigned char _data){
    writeByte_I2c(ADD_DIA_SEMANA, _data);
}

void DS1307::set_dia(unsigned char _data){
    writeByte_I2c(ADD_DIA, _data);
}

void DS1307::set_mes(unsigned char _data){
    writeByte_I2c(ADD_MES, _data);
}

void DS1307::set_ano(unsigned char _data){
    writeByte_I2c(ADD_ANO, _data);
}
void DS1307::setRAM(unsigned char address, unsigned char _data){
    writeByte_I2c(address, _data, true);
}

/*
    Escreve a hora no RTC
    0 - seg
    1 - minutos
    2 - horas
    Recebe um ponteiro para o inicio do vetor
*/
void DS1307::setHora(unsigned char *ptr){

    for(i = 0; i < 3; i++){
        writeByte_I2c(i, *ptr);
        ptr++;                 //Incrementa o ponteiro
    }
}

/*
    Escreve a data no RTC
    0 - dia da semana
    1 - dia
    2 - mes
    3 - ano
    Recebe um ponteiro para o inicio de um vetor
*/

void DS1307::setData(unsigned char *ptr){

    for(i = 0; i < 4; i++){
        //Escreve um byte, iniciando do endereço 3
        writeByte_I2c(i + 3, *ptr);
        ptr++;                 //Incrementa o ponteiro
    }
}

/*
    Função que busca a hora completa no RTC
    Salva os dados na estrutura
*/
void DS1307:: getHora(unsigned char *ptr, unsigned char tamanho){
    //*ptr = conteudo
    // ptr = endereco
    for (i = 0; i < tamanho; i++){
        *ptr = readByte_I2c(i);
        ptr++;                      //incrementa o ponteiro
    }
}

/*
    Função que busca a data completa no RTC
    Salva os dados na estrutura
*/
void DS1307:: getData(unsigned char *ptr, unsigned char tamanho){
    //*ptr = conteudo
    // ptr = endereco
    for (i = 0; i < tamanho; i++){
        *ptr = readByte_I2c(i + 3);
        ptr++;                      //incrementa o ponteiro, passa pra o proximo endereco
    }
}


unsigned char DS1307::readByte_I2c(unsigned char registrador){
    Wire.beginTransmission(_add);   //Inicia a transmissão
    Wire.write(registrador);        //chama o registrador
    Wire.endTransmission();         //Finaliza a transmissão
    Wire.requestFrom(_add, 1);      //Lê um unico byte do registrador solicitado
    return BcdToInit(Wire.read());  //Le o valor do registrador
}

unsigned char DS1307::readByte_I2c(unsigned char registrador, bool flag){
    Wire.beginTransmission(_add);   //Inicia a transmissão
    Wire.write(registrador);        //chama o registrador
    Wire.endTransmission();         //Finaliza a transmissão
    Wire.requestFrom(_add, 1);      //Lê um unico byte do registrador solicitado
    return Wire.read();             //Le o valor do registrador
}

void DS1307::writeByte_I2c(unsigned char registrador, unsigned char _data){
    Wire.beginTransmission(_add);
    Wire.write(registrador);
    Wire.write(IntToBcd(_data));
    Wire.endTransmission();
}

void DS1307::writeByte_I2c(unsigned char registrador, unsigned char _data, bool flag){
    Wire.beginTransmission(_add);
    Wire.write(registrador);
    Wire.write(_data);
    Wire.endTransmission();
}

unsigned char DS1307::BcdToInit(unsigned char num){
    return ((num/16*10) + (num%16));
}

unsigned char DS1307::IntToBcd(unsigned char num){
    return ((num/10*16) + (num%10));
}
