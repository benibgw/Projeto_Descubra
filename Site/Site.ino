#include <WiFi.h>
#include <WebServer.h>

const char* ssid = "Your_SSID";
const char* password = "Your_PASSWORD";

#define LED_BUILTIN 2
WebServer server(80);

void WifiConnection() {
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.begin(ssid);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(200);
    digitalWrite(LED_BUILTIN, LOW);
    delay(200);
  }
  Serial.println("\nConnected");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  // server routes

  server.begin();
  Serial.println("Server started.");
}

void CheckWiFiConnection() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi connection lost. Reconnecting...");
    WifiConnection();
  }
}

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
        <a href="/escada2/buzzer" class="btn btn-buzzer">Buzzer</a>
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
        <a href="/sala/buzzer" class="btn btn-buzzer">Buzzer</a>
      </div>

      <div class="comodo">
        <h2>Escada (1º andar)</h2>
        <a href="/escada1/luz" class="btn btn-luz">Luz</a>
        <a href="/escada1/buzzer" class="btn btn-buzzer">Buzzer</a>
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
}


void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  WifiConnection();
}

void loop() {
  CheckWiFiConnection();
  server.handleClient();
}