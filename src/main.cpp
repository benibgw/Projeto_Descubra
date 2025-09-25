#include <Arduino.h>
#include <WiFi.h>
#include <WebServer.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";
LiquidCrystal_I2C lcd(0x26, 16, 2);

#define LED_BUILTIN 2
#define LED_COZINHA 15
#define LED_SALA 4
#define LED_QUARTO 18
#define LED_BANHEIRO 23
#define LED_ESCADA 14
#define BUZZER_COZINHA 5
#define BUZZER_QUARTO 19
#define BUZZER_BANHEIRO 12

WebServer server(80);

String getPage(){
    return R"rawliteral(
<!DOCTYPE html>
<html lang="pt-BR">
<head>
  <meta charset="UTF-8">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Maquete Casa IoT</title>
  <style>
    body {
      font-family: Arial, sans-serif;
      margin: 0;
      padding: 0;
      background: #303446;

      display: flex;
      flex-direction: column;
      min-height: 100vh;
    }

    header {
      background: #232634;
      color: white;
      padding: 15px;
      text-align: center;
    }

    main {
      flex: 1;
    }

    footer {
      background: #232634;
      color: white;
      padding: 10px;
      text-align: center;
      width: 100%;
    }

    .andar {
      display: grid;
      grid-template-columns: repeat(3, 1fr);
      gap: 10px;
      padding: 15px;
    }

    .comodo {
      background: #414559;
      color: white;
      border-radius: 10px;
      box-shadow: 0 2px 6px rgba(0,0,0,0.2);
      padding: 20px;
      text-align: center;
      min-height: 120px;
      display: flex;
      flex-direction: column;
      justify-content: space-between;
    }

    .comodo h2 {
      margin: 0 0 10px;
      font-size: 16px;
    }

    .btn {
      display: inline-block;
      margin: 3px;
      padding: 8px 16px;
      border: none;
      border-radius: 6px;
      cursor: pointer;
      font-size: 13px;
      text-decoration: none;
      transition: 0.3s;
    }

    .btn-luz, .btn-buzzer {
      background: #8caaee;
      color: white;
    }

    .btn:hover {
      opacity: 0.8;
    }

    @media (max-width: 768px) {
      .andar {
        grid-template-columns: repeat(2, 1fr);
      }
    }

    @media (max-width: 480px) {
      .andar {
        grid-template-columns: 1fr;
      }
    }
    
    .lcd-form {
      margin-top: 10px;
      text-align: center;
    }
    .lcd-form input[type='text'] {
      padding: 5px;
      border-radius: 5px;
      border: none;
      width: 80%;
      max-width: 180px;
    }
    .lcd-form input[type='submit'] {
      margin-left: 5px;
    }
  </style>
</head>
<body>
  <header>
    <h1>Controle da Maquete IoT</h1>
  </header>

  <main>
    <div class="andar">
      <div class="comodo">
        <h2>Quarto</h2>
        <a href="/quarto/luz" class="btn btn-luz">Luz</a>
        <a href="/quarto/buzzer" class="btn btn-buzzer">Buzzer</a>
      </div>

      <div class="comodo">
        <h2>Escada (2º andar)</h2>
        <a href="/escada2/luz" class="btn btn-luz">Luz</a>
      </div>

      <div class="comodo">
        <h2>Banheiro</h2>
        <a href="/banheiro/luz" class="btn btn-luz">Luz</a>
        <a href="/banheiro/buzzer" class="btn btn-buzzer">Buzzer</a>
      </div>
    </div>

    <div class="andar">
      <div class="comodo">
        <h2>Sala</h2>
        <a href="/sala/luz" class="btn btn-luz">Luz</a>
        <form class="lcd-form" action="/lcd" method="POST">
          <label for="lcdtext">Texto no LCD:</label><br>
          <input type="text" id="lcdtext" name="lcdtext" maxlength="32" placeholder="Digite aqui...">
          <input type="submit" value="Enviar" class="btn btn-luz">
        </form>
      </div>

      <div class="comodo">
        <h2>Escada (1º andar)</h2>
      </div>

      <div class="comodo">
        <h2>Cozinha</h2>
        <a href="/cozinha/luz" class="btn btn-luz">Luz</a>
        <a href="/cozinha/buzzer" class="btn btn-buzzer">Buzzer</a>
      </div>
    </div>
  </main>

  <footer>
    <p>Projeto Descubra - Casa IoT</p>
    <p>Desenvolvido pelos alunos Benicio, Nathan, Diogo, Lorenzo e Bernardo do Curso Técnico em Internet das Coisas CTISM - 414 - 2025</p>
  </footer>
</body>
</html>
)rawliteral";
};

void WifiConnection() {
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }

  server.on("/", []() {
    server.send(200, "text/html", getPage());
  });
  server.on("/quarto/luz", []() {
    digitalWrite(LED_QUARTO, !digitalRead(LED_QUARTO));
    if(digitalRead(LED_QUARTO)){
      Serial.println("Quarto: Luz ON");
    }
    else{
      Serial.println("Quarto: Luz OFF");
    }
    server.send(200, "text/html", getPage());
  });
  server.on("/quarto/buzzer", []() {
    tone(BUZZER_QUARTO, 200, 1000);
    Serial.println("Quarto: Buzzer ON");
    delay(1000);
    noTone(BUZZER_QUARTO);
    Serial.println("Quarto: Buzzer OFF");
    server.send(200, "text/html", getPage());
  });
  server.on("/escada2/luz", []() {
    digitalWrite(LED_ESCADA, !digitalRead(LED_ESCADA));
    if(digitalRead(LED_ESCADA)){
      Serial.println("Escada 2: Luz ON");
    }
    else{
      Serial.println("Escada 2: Luz OFF");
    }
    server.send(200, "text/html", getPage());
  });
  server.on("/banheiro/luz", []() {
    digitalWrite(LED_BANHEIRO, !digitalRead(LED_BANHEIRO));
    if(digitalRead(LED_BANHEIRO)){
      Serial.println("Banheiro: Luz ON");
    }
    else{
      Serial.println("Banheiro: Luz OFF");
    }
    server.send(200, "text/html", getPage());
  });
  server.on("/banheiro/buzzer", []() {
    tone(BUZZER_BANHEIRO, 200, 1000);
    Serial.println("Banheiro: Buzzer ON");
    delay(1000);
    noTone(BUZZER_BANHEIRO);
    Serial.println("Banheiro: Buzzer OFF");
    server.send(200, "text/html", getPage());
  });
  server.on("/sala/luz", []() {
    digitalWrite(LED_SALA, !digitalRead(LED_SALA));
    if(digitalRead(LED_SALA)){
      Serial.println("Sala: Luz ON");
    }
    else{
      Serial.println("Sala: Luz OFF");
    }
    server.send(200, "text/html", getPage());
  });
  server.on("/cozinha/luz", []() {
    digitalWrite(LED_COZINHA, !digitalRead(LED_COZINHA));
    if(digitalRead(LED_COZINHA)){
      Serial.println("Cozinha: Luz ON");
    }
    else{
      Serial.println("Cozinha: Luz OFF");
    }
    server.send(200, "text/html", getPage());
  });
  server.on("/cozinha/buzzer", []() {
    tone(BUZZER_COZINHA, 200, 1000);
    Serial.println("Cozinha: Buzzer ON");
    delay(1000);
    noTone(BUZZER_COZINHA);
    Serial.println("Cozinha: Buzzer OFF");
    server.send(200, "text/html", getPage());
  });

  server.on("/lcd", HTTP_POST, []() {
    if (server.hasArg("lcdtext")) {
      String text = server.arg("lcdtext");
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print(text.substring(0, 16));
      if (text.length() > 16) {
        lcd.setCursor(0, 1);
        lcd.print(text.substring(16, 32));
      }
      Serial.print("LCD: ");
      Serial.println(text);
      server.send(200, "text/html", getPage());
    } else {
      server.send(400, "text/plain", "Texto não recebido");
    }
  });

  server.begin();
  Serial.println("Server started.");
}

void CheckWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, LOW);
    Serial.println("WiFi connection lost. Reconnecting...");
    WifiConnection();
  }
  else {
    digitalWrite(LED_BUILTIN, HIGH);
    Serial.print("WiFi connected. IP address: ");
    Serial.println(WiFi.localIP());
  }
}

void setup() {
  Serial.begin(9600);
  Wire.begin();
  lcd.init();
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(LED_COZINHA, OUTPUT);
  pinMode(LED_SALA, OUTPUT);
  pinMode(LED_QUARTO, OUTPUT);
  pinMode(LED_BANHEIRO, OUTPUT);
  pinMode(LED_ESCADA, OUTPUT);
  pinMode(BUZZER_COZINHA, OUTPUT);
  pinMode(BUZZER_QUARTO, OUTPUT);
  pinMode(BUZZER_BANHEIRO, OUTPUT);
  WifiConnection();
}

void loop() {
  CheckWiFiConnection();
  server.handleClient();
  delay(1);
}
