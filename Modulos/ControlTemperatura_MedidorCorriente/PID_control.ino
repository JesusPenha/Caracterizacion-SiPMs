////Juan Carlos Sánchez Villafrades ///////
// Algoritmo para implementar el control de temperatura y la lectura de la corriente en el SiPM
#include "PID_v1.h"
#define TemPin1 1
#define TemPin2 2
#define Heating  10
#define Cooling  11
int cont_tem=0;
int tem_adc1;
int tem_adc2;
float tem_avg, tem_amb;
float tem_sum=0;
float temp;
bool flagTemp = true;
unsigned long time1;
unsigned long time2;
unsigned long deltatime;
int sample_time = 2000; //tiempo de muestreo de la temperatura en el interior 
int sample_time_amb = 2000; // tiempo hasta donde se promedia la temperara ambiente
float time_label;
/// nanoAmperimetro ////
int pinCorriente = 3;
int cor_adc;
float cor;
float cor_avg;
float cor_sum;
//// PID ///
double Setpoint, Input, Output;
// Parametros del controlador PID
double Kp=11.0576, Ki=0.043684, Kd=41.4475;
PID myPID(&Input, &Output, &Setpoint, Kp, Ki, Kd, DIRECT);

void setup() 
{
  Serial.begin(9600);
  pinMode(TemPin1, INPUT);
  pinMode(TemPin2, INPUT);
  pinMode (Heating, OUTPUT); 
  pinMode (Cooling, OUTPUT); 
  Serial.print(" Tiempo");
  Serial.print("              ");
  Serial.print(" Temperatura");
  Serial.print("              ");
  Serial.println("Corriente nA");
  Setpoint = 25;
  myPID.SetMode(AUTOMATIC);   //turn the PID on
  time2 = millis()-sample_time;
}

void loop() 
{
  //*****************************TEMPERATURA***************************// 
  time1 = millis();
  deltatime = time1 - time2;
  tem_adc1 = analogRead(TemPin1);
  tem_adc2 = analogRead(TemPin2);
  temp = (((float(tem_adc1)-float(tem_adc2))*500)/1024);
  //temp =((float(tem_adc1)*500)/1024);
  cor_adc = analogRead(pinCorriente); // lectura del valor de corriente en el SiPM
  cor = (float(cor_adc)*50/1024);
  cor_sum += cor;
  tem_sum += temp;
  cont_tem += 1;
  if ((time1 >= sample_time_amb) && flagTemp) // Realiza la lectura de temperatura durante sample_time_amb segundos para establecer la temperatura ambiente
  {
    tem_amb = tem_sum/cont_tem;         
    tem_sum = tem_amb;
    Input = tem_amb; 
    cont_tem = 1;
    flagTemp = false;
    
  }   
  if (!flagTemp) /// a partir de aqui se realiza el control y se empieza a mostrar la temperatura
  { 
    //*****************************CONTROL***************************//  
    //*****************************CALENTAMIENTO********************//  
    if(Setpoint >= tem_amb)
    {   
      // Acción de control para realizar calentamiento
      myPID.SetTunings(11.0576, 0.043684, 41.4475);
      myPID.SetOutputLimits(-6, 90);
      myPID.SetSampleTime(sample_time);
      myPID.SetControllerDirection(DIRECT);
      myPID.Compute();
      if (Output >= 0)
      {
       analogWrite(Heating, Output);
       analogWrite(Cooling, 0); 
      }
      else
      {
       analogWrite(Heating, 0);
       analogWrite(Cooling, abs(Output)); 
      }
      //se promedia el valor de temperatura para intervalos de sample_time segundos 
      if((deltatime>=sample_time))
      {
        tem_avg = tem_sum/cont_tem;
        time_label = (time1 - sample_time_amb)*0.001; 
        cor_avg = cor_sum/cont_tem;
        Serial.print("    ");
        Serial.print(time_label); 
        Serial.print("                     ");
        Serial.print(tem_avg,1);
        Serial.print("                ");
        Serial.print(cor_avg);
        Serial.print("                ");
        Serial.println(cont_tem);
//        Serial.print("                ");
//        Serial.println("Calentandoooooooooooo");
        Input = tem_avg;
        tem_sum = 0;  
        cont_tem = 0;
        time2 = time1; 
        cor_sum = 0;       
      } 
    }
    //*****************************REFRIGEREACION********************//  
    else
    {
     // Acción de control para realizar refrigeracion
      myPID.SetTunings(30.36, 0.148, 100);
      myPID.SetOutputLimits(-6, 243);
      myPID.SetSampleTime(sample_time);
      myPID.SetControllerDirection(REVERSE);
      myPID.Compute();
      if (Output >= 0)
      {
       analogWrite(Heating, 0);
       analogWrite(Cooling, Output); 
      }
      else
      {
        analogWrite(Heating, abs(Output));
        analogWrite(Cooling, 0); 
       }
       
      if((deltatime>=sample_time))
      {
        tem_avg = tem_sum/cont_tem;
        time_label= (time1 - sample_time_amb)*0.001;
        cor_avg = cor_sum/cont_tem; 
        Serial.print("    ");
        Serial.print(time_label); 
        Serial.print("                     ");
        Serial.print(tem_avg,1);
        Serial.print("                ");
        Serial.print(cor_avg);
        Serial.print("                ");
        Serial.println(cont_tem);
//        Serial.print("                ");
//        Serial.println("Enfriando............");
        Input = tem_avg;
        tem_sum = 0;  
        cont_tem = 0;
        time2 = time1;
        cor_sum = 0;        
      } 
    } 
  }
}
