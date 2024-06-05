
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WebServer.h>

//const char* ssid = "mi";  //commented

//const char* password = "123456789";  //commented

uint8_t Pwm1 = D1; //Nodemcu PWM pin  ENA
uint8_t pwm2 = D2; //Nodemcu PWM pin  ENB

//Seven segment pins attachecd with nodemcu pins  
int a0 = 15;  //D8---Gpio-15 of nodemcu esp8266  
int a1 = 13;  //D7---Gpio-13 of nodemcu esp8266    
int a2 = 12;  //D6---Gpio-12 of nodemcu esp8266   
int a3 = 14;  //D5---Gpio-14 of nodemcu esp8266   


WiFiServer server(80);
 
void setup() 
{
  Serial.begin(115200);
  delay(10);
   //Declaring l293d control pins as Output
    pinMode(a0, OUTPUT);     
    pinMode(a1, OUTPUT);     
    pinMode(a2, OUTPUT);
    pinMode(a3, OUTPUT);    
 
    // Connect to WiFi network
     Serial.println();
     Serial.println();
     Serial.print("Connecting to ");
 // Serial.println(ssid);         //commented
 
 // WiFi.begin(ssid, password);   //commented
 
/*  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }*/  //commented

  //Serial.begin(115200);
  WiFi.softAP("Nagarjuna", "");
  Serial.println("softap");
  Serial.println("");
  Serial.println(WiFi.softAPIP());

  
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address on serial monitor
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");    //URL IP to be typed in mobile/desktop browser
 // Serial.print(WiFi.localIP());    //commented
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
 /* if (!client) {
    return;
  }*/
 
  // Wait until the client sends some data
 /*Serial.println("new client");
  while(!client.available()){
    delay(1);
  }*/
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
 // Match the request
 if (request.indexOf("/forward=1") != -1)  
         {  
                         front1();
                         delay(3000);
                         stop1();
                         
                        
         }

if (request.indexOf("/backward=1") != -1)  
  {
       back1();
        delay(3000);
        stop1();
       
  }

if (request.indexOf("/left=1") != -1)  
             {  
               left1();
               delay(1500); 
               stop1();
             }



if (request.indexOf("/right=1") != -1)  
             {  
              right1();
              delay(1500);
              stop1();
             }    



if (request.indexOf("/stop=1") != -1)  
             {  
              stop1();
              delay(3000);
             
             }

/*if (request.indexOf("/forwardleft=1") != -1)  
             {  
              forwardleft1();
              delay(3000);
              stop1();
             
             }*/







  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<center>");
     client.println("<h1 align=center>NODEMCU CAR CONTROL USING WIFI</h1>");
     client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
     client.println(".button1  { background-color: #017A4F; border-radius :20px; color: white;margin: 20px; margin: 20px auto; font-size:5vw; padding: 50px 250px;}"); //start button
     client.println(".button3  { background-color: #017A4F; border-radius :20px; color: white;  margin: 20px; margin: 20px auto; font-size:5vw; padding: 50px 250px;}"); //  left button  margin-right: 100px;
     client.println(".button4  { background-color: #017A4F; border-radius :20px; color: white; margin: 20px; margin: 20px auto; font-size:5vw; padding: 50px 250px;}"); // right button margin-left: 100px;
     client.println(".button2  { background-color: #017A4F; border-radius :20px; color: white; margin: 20px; margin: 20px auto; font-size:5vw; padding: 50px 250px; }");  //stop button //margin-left: 100px;
     client.println(".button5  { background-color: #017A4F; border-radius :20px; color: white;margin: 20px; margin: 20px auto; font-size:5vw; padding: 50px 250px;}");
     //client.println(".button6  { background-color: #017A4F; border-radius :20px; color: white;margin: 20px; margin: 20px auto; font-size:5vw; padding: 50px 250px; }");


         client.println(" .arrow-btn {width: 30px;height: 30px;background-color: #ccc;border: none;cursor: pointer; margin: 5px;}  ");
          client.println("  .arrow-btn:hover {background-color: #ddd;} ");
           client.println(".up-arrow::after {content: "";display: inline-block;border: solid #000;border-width: 0 3px 3px 0;padding: 3px;transform: rotate(-135deg);}   ");
            client.println(" .down-arrow::after {content: "";display: inline-block;border: solid #000;border-width: 0 3px 3px 0;padding: 3px;transform: rotate(45deg);}  ");
             client.println(" .right-arrow::after {content: "";display: inline-block;border: solid #000;border-width: 0 3px 3px 0;padding: 3px;transform: rotate(-45deg);}  ");
              client.println(" .left-arrow::after {content: "";display: inline-block;border: solid #000;border-width: 0 3px 3px 0;padding: 3px;transform: rotate(135deg);;}  ");





            client.println("</style>");
            client.println("</head>");
            
                        
                 client.println("<a href=\"/forward=1\"\"><button class=\"button1\">FRONT </button></a></br>");          
                 client.println("<a href=\"/left=1\"\"><button    class=\"button4\">LEFT</button></a></br>");
                 client.println("<a href=\"/right=1\"\"><button   class=\"button5\">RIGHT</button></a></br>");
                 client.println("<a href=\"/backward=1\"\"><button class=\"button3\">BACK</button></a></br> ");
                 client.println("<a href=\"/stop=1\"\">  <button  class=\"button2\">STOP</button></a></br>");   

                   //<!-- Up arrow button using custom graphics -->
                      client.println("<button class=\"arrow-btn up-arrow\">up arrow</button>"); 

                    //<!-- Down arrow button using custom graphics -->
                          client.println("<button class=\"arrow-btn down-arrow\">down</button>"); 

                     //<!-- Right arrow button using custom graphics -->
                           client.println("<button class=\"arrow-btn right-arrow\">right</button>"); 

                       //<!-- Left arrow button using custom graphics -->
                            client.println("<button class=\"arrow-btn left-arrow\">left</button>"); 
   

                   

               

  client.println("</center>");
  client.println("</html>");
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
}

void front1()
{
  analogWrite(Pwm1,255);
  analogWrite(pwm2,255);
  digitalWrite(a0, HIGH); 
  digitalWrite(a1, LOW);
  digitalWrite(a2, HIGH); 
  digitalWrite(a3, LOW); 
  
}
void back1()
{
 analogWrite(Pwm1,255);
 analogWrite(pwm2,255);
 digitalWrite(a0, LOW);  
 digitalWrite(a1, HIGH);
 digitalWrite(a2, LOW); 
 digitalWrite(a3, HIGH); 
  
}
void right1()
{
   analogWrite(Pwm1,255);
   analogWrite(pwm2,255);

     digitalWrite(a0, LOW);
   digitalWrite(a1, HIGH);
   digitalWrite(a2, HIGH); 
   digitalWrite(a3, LOW);
  
}
void left1()
{
   analogWrite(Pwm1,255);
   analogWrite(pwm2,255);

      digitalWrite(a0, HIGH); 
   digitalWrite(a1, LOW);
   digitalWrite(a2, LOW ); 
   digitalWrite(a3, HIGH);

}

void stop1()
{
  analogWrite(Pwm1,0);
  analogWrite(pwm2,0);
  digitalWrite(a0, LOW); 
  digitalWrite(a1, LOW);
  digitalWrite(a2, LOW); 
  digitalWrite(a3, LOW);
}

/*void forwardleft1()
{
 analogWrite(Pwm1,128);
 analogWrite(pwm2,255);           
 digitalWrite(a0, LOW); 
 digitalWrite(a1, HIGH);
 digitalWrite(a2, LOW); 
 digitalWrite(a3, HIGH); 
}*/
