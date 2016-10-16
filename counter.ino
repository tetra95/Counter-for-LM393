#include <math.h> 

#define PIN_DO 2 // выход с прерыванием на ардуино
#define HOLES_DISC 20 // количество отверстий на диске
#define WHEELS_RAD 65 // радиус колеса 
#define SIZE 100
volatile unsigned int pulses;
double rpm, LineSpeed, I;  
long double S; // S- пройденное расстояни, I-интегралл Симпсона 
unsigned long timeOld;

 
void counter(void)
{
 pulses++;
}

double prices[SIZE] = {}; // массив значений скорости 

int Integral_Simpsona() 
{
        for (int i = 0; i < sizeof(prices) / sizeof(*prices); i++)
                  prices[i] = LineSpeed;

        
        double sum_even = 0; // сумма четных
        double sum_odd = 0;  // сумма нечетных
        const double h = 0.01; // шаг по времени
      
        for (int i = 0; i < sizeof(prices) / sizeof(*prices); )
        {
          double even = 2 * i; // четные члены массива 
          double odd = even + 1;  // нечетные члены массива 
      
          sum_odd += prices[odd];
          sum_even += prices[even];
        }

I = (h/3) * ((*prices[1]) + (*prices[100]) + 4 * (sum_odd) + 2 * (sum_even)); // интеграл Симпсона
    
}
 
void setup()
{
 Serial.begin(9600);
 pinMode(PIN_DO, INPUT);
 pulses = 0;
 timeOld = 0;
 S = 0;
 attachInterrupt(digitalPinToInterrupt(PIN_DO), counter, FALLING); //запускаю прерывание на 2 ножке, прибавляю
                                                                   // к pulses значение. 
                                                                   // прерывание запускается при переходе с High на Low 
}
 
void loop()
{
 if (millis() - timeOld >= 10) // каждые 10 милисекунд заходим в цикл для этого берём разность между текущим временем и 
                               // временем последнего изменения состояния на оптопаре
 {
 detachInterrupt(digitalPinToInterrupt(PIN_DO));  // убираю прерывание
 rpm = (pulses * 60) / (HOLES_DISC);      // формула количества оборотов/минуту
 LineSpeed = (rpm *  PI / 30) * WHEELS_RAD; // формула линейной скорости колеса
 Integral_Simpsona();
 S += I;
 
  
 Serial.print("rpm = ");
 Serial.println(rpm);
 Serial.print("LineSpeed = ");
 Serial.println(LineSpeed);
 Serial.print("S =  ");
 Serial.println(S);
  
 timeOld = millis(); 
 pulses = 0;
 attachInterrupt(digitalPinToInterrupt(PIN_DO), counter, FALLING);
 
  
 }
}
