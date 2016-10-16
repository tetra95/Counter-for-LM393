#include <stdio.h>


#define SIZE 100

int main ()	
{
  double prices[SIZE] = {}; // массив значений скорости 

  int Integral_Simpsona () 
{

        for (int i = 0; i < sizeof(prices) / sizeof(*prices); i++)
        	        	prices[i] = LineSpeed;
       

        double sum_even = 0; // сумма четных
        double sum_odd = 0;  // сумма нечетных
        const float h = 0.01f; // шаг по времени
      
        for (int i = 0; i < sizeof(prices) / sizeof(*prices); )
        {
        	int even = 2 * i; // четные члены массива 
        	int odd = even + 1;  // нечетные члены массива 
      
        	sum_odd += prices[odd];
        	sum_even += prices[even];
        }

        S = (h/3) * (prices[0] + prices[100] + 4 * (sum_odd) + 2 * (sum_even - prices[0] - prices[100])); // интеграл Симпсона
    
}


	return 0;
}
