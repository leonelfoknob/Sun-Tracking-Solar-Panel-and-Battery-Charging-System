#include <WiFi.h>
#include <ESPAsyncWebServer.h>

http://dan.drown.org/stm32duino/package_STM32duino_index.json

//batarya değişkenleri
String Yuzdebatarya = "";
String Voltajbatarya = "";

unsigned long lastTime = 0;  
unsigned long timerDelay = 1000;

// wifi ayarlar
const char* ssid = "TurkTelekom_ZY48C7";
const char* password = "9Ng3CXsyYRCa";


AsyncWebServer server(80);

const int MAX_ANALOG_VAL = 4095;
const float MAX_BATTERY_VOLTAGE = 8.4;
int rawValue;
float voltageLevel;
float batteryFraction;
  
void calcul_batery(){
  rawValue = analogRead(33);
  voltageLevel = ((rawValue / 4095.0) * 2 * 1.2 * 3.278)+0.66; // calculate voltage level
  batteryFraction = voltageLevel / MAX_BATTERY_VOLTAGE;
}

String yuzlu_energy(){
  calcul_batery();
  float batteryLevel = batteryFraction*100;
  Serial.print("kalan enerji : ");Serial.println(batteryLevel);
  return String(batteryLevel);
}

String voltaj(){
  calcul_batery();
  float batteryLevelvolt = voltageLevel;
  Serial.print("kalan enerji : ");Serial.println(batteryLevelvolt);
  return String(batteryLevelvolt);
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <style>
    html {
     font-family: Arial;
     display: inline-block;
     margin: 0px auto;
     text-align: center;
    }
    h2 { font-size: 3.0rem; }
    p { font-size: 3.0rem; }
    .units { font-size: 1.2rem; }
    .ds-labels{
      font-size: 1.5rem;
      vertical-align:middle;
      padding-bottom: 15px;
    }
  </style>
</head>
<body>
  <h2>STM32 Batarya Yonetimi</h2>
  <p>
    <i class="fas fa-battery-half" style="color:#059e8a;"></i>
    <span class="ds-labels">Gerilim</span> 
    <span id="yuzdebatarya">%YUZDEBATARYA%</span>
    <sup class="units">V</sup>
  </p>
  <p>
    <i class="fas fa-battery-half" style="color:#059e8a;"></i>
    <span class="ds-labels">Enerji</span>
    <span id="voltajbatarya">%VOLTAJBATARYA%</span>
    <sup class="units">%</sup>
  </p>
</body>
<script>
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("yuzdebatarya").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/yuzdebatarya", true);
  xhttp.send();
}, 1) ;
setInterval(function ( ) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState == 4 && this.status == 200) {
      document.getElementById("voltajbatarya").innerHTML = this.responseText;
    }
  };
  xhttp.open("GET", "/voltajbatarya", true);
  xhttp.send();
}, 1) ;
</script>
</html>)rawliteral";

String processor(const String& var){
  //Serial.println(var);
  if(var == "YUZDEBATARYA"){
    return Yuzdebatarya;
  }
  else if(var == "VOLTAJBATARYA"){
    return Voltajbatarya;
  }
  return String();
}

void setup(){
  Serial.begin(115200);
  Serial.println();
  

  Yuzdebatarya = yuzlu_energy();
  Voltajbatarya = voltaj();


  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  
  // IP Adressi görmek için
  Serial.println(WiFi.localIP());

  
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  server.on("/yuzdebatarya", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", Yuzdebatarya.c_str());
  });
  server.on("/voltajbatarya", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", Voltajbatarya.c_str());
  });
  
  server.begin();
}
 
void loop(){
  if ((millis() - lastTime) > timerDelay) {
    Yuzdebatarya = yuzlu_energy();
    Voltajbatarya = voltaj();
    lastTime = millis();
  }  
}
