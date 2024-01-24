#ifndef _webserver_displaytest_H
#define _webserver_displaytest_H

#include <AsyncTCP.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <display/IDisplay.h>

// Create AsyncWebServer object on port 80
AsyncWebServer server(80);
// temporary variables to hold the input from the webpage
String wifiIcon = "";
String mqttIcon = "";
String blynkIcon = "";
unsigned int profileIconIndex = 0;

String temperatureValue = "";
String pressureValue = "";
String scaleValue = "";

String StateToString(State state) {
  switch(state) {
    case State::Undefined: return "Undefined";
    case State::ColdStart: return "ColdStart";
    case State::StabilizeTemperature: return "StabTemperature";
    case State::InnerZoneDetected: return "InnerZone";
    case State::BrewDetected: return "BrewDetected";
    case State::OuterZoneDetected: return "OuterZone";
    case State::SteamMode: return "SteamMode";
    case State::SleepMode: return "SleepMode";
    case State::CleanMode: return "CleanMode";
    default: return "Unknown";
  }
}

String AreaToString(Area area) {
   switch (area) {
    case Area::BootLogo: return "BootLogo";
    case Area::BootMessage: return "BootMessage";
    case Area::ActionImage: return "ActionImage";
    case Area::StatusMessage: return "StatusMessage";
    case Area::StatusIcons: return "StatusIcons";
    case Area::ProfileIcon: return "ProfileIcon";
    case Area::Temperature: return "Temperature";
    case Area::SoftwareUpdate: return "SoftwareUpdate";
    default: return "Unknown";
  }
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html><head>
<style>
    td {
      padding: 8px;
      vertical-align: top;
    }
</style></head>
<body>
<table>
   <tr>
      <td>
         <b>WiFi</b><br>
         <input type="radio" id="machine1" name="machine" value="rancilio"><label for="machine1">Rancilio</label>
         <input type="radio" id="machine2" name="machine" value="gaggia"><label for="machine2">Gaggia</label>
         <input type="radio" id="machine3" name="machine" value="ecm"><label for="machine3">ECM</label>
         <br><br>

         <b>Temperature: 0-130 &deg;C</b><br>
         <input type="range" id="temperature" name="temperature" min="0" max="130" value="0" onchange="onSliderChange('temperature', 'temperatureValue')">
         <span id="temperatureValue">0</span><br><br>

         <b>Pressure: 0-12 bar</b><br>
         <input type="range" id="pressure" name="pressure" min="0" max="12" value="0" onchange="onSliderChange('pressure', 'pressureValue')">
         <span id="pressureValue">0</span><br><br>

         <b>Scale: 0-70 g</b><br>
         <input type="range" id="scale" name="scale" min="0" max="70" value="0" onchange="onSliderChange('scale', 'scaleValue')">
         <span id="scaleValue">0</span>
      </td>
      <td>
         <b>WiFi</b><br>
         <input type="radio" id="wifi1" name="wifi" value="off"><label for="wifi1">off</label>
         <input type="radio" id="wifi2" name="wifi" value="ok"><label for="wifi2">ok</label>
         <input type="radio" id="wifi3" name="wifi" value="nok"><label for="wifi3">nok</label>
         <br><br>
         <b>Blynk</b><br>
         <input type="radio" id="blynk1" name="blynk" value="off"><label for="blynk1">off</label>
         <input type="radio" id="blynk2" name="blynk" value="ok"><label for="blynk2">ok</label>
         <input type="radio" id="blynk3" name="blynk" value="nok"><label for="blynk3">nok</label>
         <br><br>
         <b>MQTT</b><br>
         <input type="radio" id="mqtt1" name="mqtt" value="off"><label for="mqtt1">off</label>
         <input type="radio" id="mqtt2" name="mqtt" value="ok"><label for="mqtt2">ok</label>
         <input type="radio" id="mqtt3" name="mqtt" value="nok"><label for="mqtt3">nok</label>
         <br><br>
         <b>Profile</b><br>
         <input type='radio' id='p0' name='profile' value='0'><label for="p0">off</label>
         <input type='radio' id='p1' name='profile' value='1'><label for="p1">1</label>
         <input type='radio' id='p2' name='profile' value='2'><label for="p2">2</label>
         <input type='radio' id='p3' name='profile' value='3'><label for="p3">3</label>
      </td>
   </tr>
   <tr><td colspan="2" style="padding: 0px; text-align: center;"><b>States</b></td></tr>   
   <tr>
      <td>
         <button style="width:200px" type='submit'id="button0" name="action" value='0'>Undefined</button><br><br>
         <button style="width:200px" type='submit' id="button1" name="action" value='1'>ColdStart</button><br><br>
         <button style="width:200px" type='submit' id="button2" name="action" value='2'>StabilizeTemperature</button><br><br>
         <button style="width:200px" type='submit' id="button3" name="action" value='3'>InnerZoneDetected</button><br><br>
         <button style="width:200px" type='submit' id="button4" name="action" value='4'>BrewDetected</button><br><br>
         <button style="width:200px" type='submit' id="button5" name="action" value='5'>OuterZoneDetected</button><br><br>
         <button style="width:200px" type='submit' id="button6" name="action" value='6'>SteamMode</button><br><br>
      </td>
      <td>
         <button style="width:200px" type='submit' id="button7" name="action" value='7'>SleepMode</button><br><br>
         <button style="width:200px" type='submit' id="button8" name="action" value='8'>CleanMode</button><br><br>
         <button style="width:200px" type='submit' id="button9" name="action" value='9'>SoftwareUpdateStart</button><br><br>
         <button style="width:200px" type='submit' id="button9" name="action" value='10'>SoftwareUpdate</button><br><br>
         <button style="width:200px" type='submit' id="button10" name="action" value='11'>SceenSaver</button><br><br>
         <button style="width:200px" type='submit' id="button11" name="action" value='12'>Error</button><br><br>
         <button style="width:200px" type='submit' id="button11" name="action" value='13'>Menu</button><br><br> 
      </td>
   </tr>
   <tr><td>
<input type="checkbox" id="BootLogo" name="area" value="0"><label for="BootLogo">BootLogo</label><br>
<input type="checkbox" id="BootMessage" name="area" value="1"><label for="BootMessage">BootMessage</label><br>
<input type="checkbox" id="ActionImage" name="area" value="2"><label for="ActionImage">ActionImage</label><br>
<input type="checkbox" id="StatusMessage" name="area" value="3"><label for="StatusMessage">StatusMessage</label><br>
<input type="checkbox" id="StatusIcons" name="area" value="4"><label for="StatusIcons">StatusIcons</label><br>
<input type="checkbox" id="ProfileIcon" name="area" value="5"><label for="ProfileIcon">ProfileIcon</label><br>
<input type="checkbox" id="Temperature" name="area" value="6"><label for="Temperature">Temperature</label><br>
<input type="checkbox" id="SoftwareUpdate" name="area" value="7"><label for="SoftwareUpdate">SoftwareUpdate</label><br>   
   <td></tr>
</table>
<script>
   document.querySelectorAll('input[type=checkbox]').forEach(checkbox => {
     checkbox.addEventListener('change', function() {
       var xhr = new XMLHttpRequest();
       xhr.open("GET", '/update?name=' + encodeURIComponent(this.name) + '&value=' + encodeURIComponent(this.value) + '&checked=' + encodeURIComponent(this.checked), true);
       xhr.send();
     });
   });

   document.querySelectorAll('input[type=radio]').forEach(radio => {
     radio.addEventListener('change', function() {
       var xhr = new XMLHttpRequest();
       xhr.open("GET", '/update?name=' + encodeURIComponent(this.name) + '&value=' + encodeURIComponent(this.value), true);
       xhr.send();
     });
   });
   
   document.querySelectorAll('button').forEach(button => {
     button.addEventListener('click', function() {
       var xhr = new XMLHttpRequest();
       xhr.open("GET", '/update?name=' + encodeURIComponent(this.name) + '&value=' + encodeURIComponent(this.value), true);
       xhr.send();
     });
   });
   
   function onSliderChange(sliderId) {
   	var sliderValue = document.getElementById(sliderId).value;
       console.log(sliderId + " value changed: " + sliderValue);
   	document.getElementById(sliderId+'Value').innerHTML = sliderValue;
   
       var xhr = new XMLHttpRequest();
       xhr.open("GET", '/update?name=' + encodeURIComponent(sliderId) + '&value=' + encodeURIComponent(sliderValue), true);
       xhr.send();	
   }
</script>
</body></html>
)rawliteral";


void SetupDisplayTest() {
     // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Route for receiving the AJAX POST request
server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request) {
  if(request->hasParam("name") && request->hasParam("value")){
    String name = request->getParam("name")->value();
    String value = request->getParam("value")->value();
    DEBUG_print("%s: %s\n", name, value);

    if (name == "temperature") temperatureValue = value;
    if (name == "pressure") pressureValue = value;
    if (name == "scale") scaleValue = value;

    if (name == "wifi") wifiIcon = value;
    if (name == "mqtt") mqttIcon = value;
    if (name == "blynk") blynkIcon = value;
    if (name == "profile") profileIconIndex = value.toInt();
    if (name == "action") activeState = static_cast<State>(value.toInt());

    bool isChecked = false;
    if (name == "area") {
       String checked = request->getParam("checked")->value();
       isChecked = checked.equals("true");

       if (isChecked) {
        //display.drawBorder(static_cast<Area>(value.toInt()));
       }
    }

    DEBUG_print("checked: %d\n", isChecked);

    DEBUG_print("Wifi: %s\n", wifiIcon);
    DEBUG_print("Mqtt: %s\n", mqttIcon);
    DEBUG_print("Blynk: %s\n", blynkIcon);
    DEBUG_print("profile: %d\n", profileIconIndex);
    DEBUG_print("action: %s\n", StateToString(activeState));
    DEBUG_print("area: %s\n", AreaToString(static_cast<Area>(value.toInt())));
  }
  request->send(200);
});

  server.begin();
  DEBUG_print("Webserver running\n");
}

#endif