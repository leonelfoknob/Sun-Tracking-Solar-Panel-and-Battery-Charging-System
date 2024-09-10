#include <Servo.h> //Servo kullamak için kütüphane eklendik

Servo myservo; // myservo nesne olarak oluşturuyoruz

#define ldr1 PA3 // birin sensor bağlı olan pini
#define ldr2 PA4 // ikinci sensor bağlı olan pini
#define servoPin PA0 //servo motor bağlı olan pin

int pos = 100; // servo motor ilk çalıştığında düz dursun diye 100 derecelik bir değer veriyoruz ilk başta ve pos servo motor açıları tutacak değişkeni
int tolerance = 20; // servo motor sureki hareket halinde olmasın diye tolerans veriyoruz
   
void setup(){
myservo.attach(servoPin); // servo motor pine ve myservo nesneni ile bağlıyoruz
pinMode(ldr1, INPUT); //birinci sensor pini input olarak yapıyoruz
pinMode(ldr2, INPUT); //ikinci sensor pini input olarak yapıyoruz
myservo.write(pos); // servo motor ilk çalıştığında düz dursun diye 100 derecelik bir değer veriyoruz ilk başta 
Serial.begin(9600); // sensor değeleri görmek için serial port açıyoruz    
delay(5000); // sistem kendine ayarlasın diye 5 saniye bekliyoruz
}

void loop(){
int val1 = analogRead(ldr1); // birinci sensor değerleri okuyoruz
int val2 = analogRead(ldr2); // ikinci sensor değerleri okuyoruz

/*Serial.print("val1 : ");Serial.println(val1); // sensor değeleri yazdırıyoruz serial porta
Serial.print("val2 : ");Serial.println(val2); // sensor değeleri yazdırıyoruz serial porta */
      
if((abs(val1 - val2) <= tolerance) || (abs(val2 - val1) <= tolerance)) {
//ldr değeri izin verilen tolerans dahilindeyse hiçbir servo motor yatay hareketi gerçekleşmez
}
else {
  if(val1 > val2 && val1 > 2200){ // ldr1, ldr2'den daha fazla ışık algılıyorsa ve ldr1>2200 değeri geçiyorsa (2200 orta normal ışık değeri olduğu için ldr1 sensoru için)  
    pos = pos-1; // servo motoru var olan açısı bire bir azaltılır
  }
  else if(val1 < val2 && val2 > 2580){ // ldr2, ldr1'den daha fazla ışık algılıyorsa ve ldr2>2580 değeri geçiyorsa (2580 orta normal ışık değeri olduğu için ldr1 sensoru için) 
    pos = pos+1; // servo motoru var olan açısı bire bir artırılır
  }
  else{
    pos = pos; // servo motoru var olan açısıda kalır
  }
}     
if(pos > 180) {pos = 180;} // pos değeri 180 açarsa 180 olarak kalıyor çünkü servo motor max 180 derece alabliyor
if(pos < 0) {pos = 0;} // pos değeri 0 altında olursa 0 olarak kalıyor çünkü servo motor en duşuk 0 derece alabliyor
myservo.write(pos); // servo motora değeri yazılıyor
delay(20);//20 millisaniye gecikme
}
