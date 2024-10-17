#include <Servo.h>      // Thư viện điều khiển servo

#define ON  70    // Góc mở thùng rác (servo)
#define OFF 180   // Góc đóng thùng rác (servo)

Servo myservo;         
const int servoPin = 9;  // Chân kết nối servo (thay đổi theo kết nối thực tế)
const int trigPin = 8;   // Chân TRIG của cảm biến nối với chân số 8
const int echoPin = 7;   // Chân ECHO của cảm biến nối với chân số 7
long duration;
float distance;

void setup() {
  pinMode(trigPin, OUTPUT);  // Đặt chân TRIG là đầu ra
  pinMode(echoPin, INPUT);   // Đặt chân ECHO là đầu vào
  myservo.attach(servoPin); 
  Serial.begin(115200);      // Mở giao tiếp Serial ở baudrate 115200
  myservo.write(OFF);        // Ban đầu đóng thùng rác
}

void loop() {
  // Đảm bảo rằng chân TRIG ở mức thấp trước khi gửi xung
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  
  // Gửi xung cao trong 10 microseconds từ chân TRIG
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Đo thời gian từ khi ECHO nhận được tín hiệu phản xạ
  duration = pulseIn(echoPin, HIGH);
  
  // Tính toán khoảng cách dựa trên thời gian (đơn vị là cm)
  distance = duration * 0.034 / 2;
  
  // Hiển thị kết quả khoảng cách trên Serial Monitor
  Serial.print("Khoang cach: ");
  Serial.print(distance);
  Serial.println(" cm");
  
  // Kiểm tra khoảng cách, nếu nhỏ hơn 20 cm thì mở thùng rác
  if (distance < 20) {
    myservo.write(ON);    // Mở thùng rác
    Serial.println("Mo thung rac");
    delay(3000);          // Đợi 3 giây trước khi đóng lại
  }
  else {
    myservo.write(OFF);   // Đóng thùng rác
  }

  delay(500);  // Đợi nửa giây trước khi đo lại
}
