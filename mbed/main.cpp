
#include "mbed.h"
#include "DHT.h" 
#include "stdio.h"
 
#define DHTPIN D7 
DHT dht(DHTPIN, DHT22);

AnalogIn pot(PA_0);
AnalogIn pot2(PA_1);

//#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
//#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
//#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

//#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
//#define TRCENA          0x01000000



//int _write(int file, char *ptr, int len)
//{
//  /* */
//  int i=0;
//  for(i=0 ; i<len ; i++) 
//    ITM_SendChar((*ptr++));
//  return len;
//}
//wiatr
class Counter {
public:
    Counter(PinName pin) : _interrupt(pin) {        // create the InterruptIn on the pin specified to Counter
        _interrupt.rise(this, &Counter::increment); // attach increment function of this counter instance
    }
 
    void increment() {
        _count++;
    }
 
    int read() {
        return _count;
    }
 
private:
    InterruptIn _interrupt;
    float _count;
};
 
Counter counter(D13);

int main() { 
	char odczyt[10];
	char odczyt2[10];
	
	
	float sample;
	float sample2;
	
	//wiatr
	char odczyt3[10];
	unsigned long intv = 0;
	float RPM = 0;
	const float pi = 3.14159265;  // pi number
	float speedwind = 0;
		int radio = 65;
float last;
	
    while(1) {
					
			//wiatr				
			float cou1 = counter.read();
			cou1 = cou1 - last;
			last += cou1;
			
			RPM = ((cou1 / 2) * 60) / (10000 / 1000);
		
			speedwind = ((2 * pi * radio * RPM)/60) / 100;  // Calculate wind speed on m/s
			
			
			sprintf(odczyt3, "%f", speedwind);
			
//			_write(0, odczyt3, 10);
			printf("\r\nPredkosc wiatru:    %f\r\n",cou1);
			
        switch(dht.read())
        {
            case ERROR_NONE: {
								float hum1 = dht.ReadHumidity();
								float hum2 = dht.ReadTemperature();
						
								sprintf(odczyt, "%f", hum1);
								sprintf(odczyt2, "%f", hum2);
						
               printf("\r\nWilgotnosc:    %.1f\r\n",hum1); 
               printf("Temperatura: %.1f\r\n",hum2); 
//								_write(0, odczyt, 10);
//						
//								_write(1, odczyt2, 10);
							 break;
						}
            case ERROR_NOT_PRESENT:
                printf("\r\nDHT NOT PRESENT\r\n");break;
            case ERROR_TIMEOUT:
                printf("\r\nDHT TIMEOUT EEROR\r\n");break;
            case ERROR_CHECKSUM:
                printf("\r\nDHT CHECKSUM ERROR\r\n");break;
            default:
                printf("\r\nUNKNOWN EEROR\r\n");break;
        } 
				
				
			sample = pot;
			sample2 = pot2;
       char odczytt[10];
char odczytt2[10];
			float v = (float)sample * 5.0f / 4096.0f *100000;
		//sprintf(odczytt, "%f", v);
			
			float v2 = (float)sample2 * 5.0f / 4096.0f*100000;
		//sprintf(odczytt2, "%f", v2);
			
		printf("\r\nNapiecie 1:    %.6f\r\n",v); 
    printf("Napiecie 2: %.6f\r\n",v2); 
//		_write(0, odczytt, 10);
//						
//		_write(1, odczytt2, 10);
				
				//0 - 600 wschod, 600 - max zachod
				if(v > 0 && v < 600) {
					printf("\r\nWiatr wschodni");					
				}
				else {
					printf("\r\nWiatr zachodni");			
				}
				
				//0 - 600 polnoc, 600 - max poludnie
				if(v2 > 0 && v2 < 600) {
					printf("\r\nWiatr polnocny");					
				}
				else {
					printf("\r\nWiatr poludniowy");			
				}
        wait(2);
    }
}

