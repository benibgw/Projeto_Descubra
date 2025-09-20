# Descubra  
### Ideia Geral  

**Descubra UFSM**, desenvolvida pelos alunos do **Curso Técnico em Internet das Coisas (CTISM – integrado ao Ensino Médio)**.  
Consiste em uma **maquete de casa inteligente**, onde cada cômodo pode ser controlado remotamente através de um **ESP32** que hospeda uma interface web.  
O usuário, ao acessar a página pelo navegador (PC ou celular), pode acionar **luzes (LEDs)** e **buzzers** de cada cômodo, simulando um ambiente IoT residencial.  

---

### Funcionamento Detalhado  

1. **Inicialização do sistema**  

   - Ao ser ligado, o **ESP32** inicia todos os sistemas internos e conecta-se à rede Wi-Fi.  
   - Durante a tentativa de conexão:  
     - O LED_BUILTIN pisca alternadamente para indicar que está tentando se conectar.  
   - Quando a conexão é estabelecida:  
     - O LED_BUILTIN permanece aceso, indicando que o dispositivo está online.  
     - O IP do ESP32 é exibido no Serial Monitor para que o usuário acesse a interface web.  

2. **Hospedagem da interface web**  

   - O ESP32 hospeda uma página web responsiva na porta 80.  
   - A interface contém:  
     - Um painel com os cômodos organizados por **andares da maquete**.  
     - Para cada cômodo, dois botões:  
       - **Luz** (liga/desliga um LED).  
       - **Buzzer** (aciona o som).  

3. **Divisão da maquete**  

   - **1º andar:** Sala, Escada (1º andar), Cozinha.  
   - **2º andar:** Quarto, Escada (2º andar), Banheiro.  

4. **Controle do usuário**  

   - O usuário acessa o IP exibido no Serial Monitor pelo navegador.  
   - Ao clicar em um botão da interface:  
     - O ESP32 interpreta a rota HTTP recebida (`/comodo/acao`).  
     - O GPIO correspondente é acionado (ligando o LED ou buzzer do cômodo selecionado).  

5. **Operação contínua**  

   - O ESP32 entra em um loop de funcionamento:  
     - Mantém o servidor HTTP ativo.  
     - Monitora constantemente a conexão Wi-Fi.  
   - Caso a conexão caia:  
     - O LED_BUILTIN desliga.  
     - O sistema tenta reconectar automaticamente.  
     - Quando reconectar, o LED acende e a interface volta a ficar disponível.  

---

### 👨‍💻 Autores  
Projeto desenvolvido por:  
- Benicio 
- Nathan  
- Diogo  
- Lorenzo  
- Bernardo  

**Curso Técnico em Internet das Coisas – CTISM – 414 – 2025**  
