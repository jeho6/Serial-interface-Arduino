#include <Servo.h>
char buffer[50];
float pos = 90.0;

Servo servo_recyclable;
Servo servo_kitchen;
Servo servo_harm;
Servo servo_other;

boolean is_recyclable;
boolean is_kitchen,is_harm,is_other;
boolean temp;

int True = 1;
int False = 0;

int clk_recyclable = 0;
int clk_kitchen = 0;
int clk_harm = 0;
int clk_other = 0;

int recyclable_open = False;
int kitchen_open = False;
int harm_open = False;
int other_open = False;

void setup() {
  servo_recyclable.attach(3);
  servo_kitchen.attach(5);
  servo_harm.attach(6);
  servo_other.attach(9);

  servo_recyclable.write(pos);
  servo_kitchen.write(pos);
  servo_harm.write(pos);
  servo_other.write(pos);

  Serial.begin(9600); //启动串口通讯，传输波特率9600
}
 
void loop() {          // 检查串口缓存是否有数据等待传输 
  
  if (Serial.available() > 0) {
    int bytesRead = Serial.readBytesUntil('\n', buffer, 50);
    buffer[bytesRead] = '\0';  // 添加字符串终止符
    //Serial.println(buffer); // 输出接收到的字符串，用于调试

    char* saveptr; // 用于保存 strtok_r() 解析过的位置
    char* token = strtok_r(buffer, ",", &saveptr);
    if (token != NULL) {
      temp = atoi(token);
      token = strtok_r(NULL, ",", &saveptr);
      if (token != NULL) {
        is_recyclable = atoi(token);
        token = strtok_r(NULL, ",", &saveptr);
        if (token != NULL) {
          is_kitchen = atoi(token);
          token = strtok_r(NULL, ",", &saveptr);
          if (token != NULL) {
            is_harm = atoi(token);
            token = strtok_r(NULL, ",", &saveptr);
            if (token != NULL) {
              is_other = atoi(token);
            }
          }
        }
      }
    }

    // Serial.print("is_recyclable: ");
    // Serial.println(is_recyclable);
    // Serial.print("is_kitchen: ");
    // Serial.println(is_kitchen);
    // Serial.print("is_harm: ");
    // Serial.println(is_harm);
    // Serial.print("is_other: ");
    // Serial.println(is_other);
    
    memset(buffer, 0, sizeof(buffer));
  }
  else{
    is_recyclable = is_kitchen = is_harm = is_other = 0;
  }
    if(is_recyclable==1){
      if(clk_recyclable<4){
      clk_recyclable+=1;
      }
      else{
        clk_recyclable = 4;
      }
    }
    else{
      clk_recyclable-=2;
    }
    if(clk_recyclable<0){
      clk_recyclable = 0;
    }
    if(clk_recyclable>=3){
      if(recyclable_open==False){
        //clk_recyclable+=1;
        recyclable_open = True;
      }
    }
    else{
      recyclable_open = False;
    }

//################################################################
    if(is_kitchen==1){
      if(clk_kitchen<4){
      clk_kitchen+=1;
      }
      else{
        clk_kitchen = 4;
      }
    }
    else{
      clk_kitchen-=2;
    }
    if(clk_kitchen<0){
      clk_kitchen = 0;
    }
    if(clk_kitchen>=3){
      if(kitchen_open==False){
      kitchen_open = True;
      //clk_kitchen+=1;
      }
    }
    else{
      kitchen_open = False;
    }

//#################################################################
    if(is_harm==1){
      if(clk_harm<4){
      clk_harm+=1;
      }
      else{
        clk_harm = 4;
      }
    }
    else{
      clk_harm-=2;
    }
    if(clk_harm<0){
      clk_harm = 0;
    }
    if(clk_harm>=3){
      if(harm_open==False){
      //clk_harm+=1;
      harm_open = True;
      }
    }
    else{
      harm_open = False;
    }

//#################################################################
    if(is_other==1){
      if(clk_other<4){
      clk_other+=1;
      }
      else{
        clk_other = 4;
      }
    }
    else{
      clk_other-=2;
    }
    if(clk_other<0){
      clk_other = 0;
    }
    if(clk_other>=3){
      if(other_open==False){
      //clk_other+=1;
      other_open = True;
      }
    }
    else{
      other_open = False;
    }

//#################################################################
    if(recyclable_open==True){
      servo_recyclable.write(pos*2);
    }
    else{
      servo_recyclable.write(pos);
    }

    if(kitchen_open==True){
      servo_kitchen.write(pos*2);
    }
    else{
      servo_kitchen.write(pos);
    }

    if(harm_open==True){
      servo_harm.write(pos*2);
    }
    else{
      servo_harm.write(pos);
    }

    if(other_open==True){
      servo_other.write(pos*2);
    }
    else{
      servo_other.write(pos);
    }
   
  delay(800);
}
