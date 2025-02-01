# Matrix LED Task - Projeto com Interrupções no RP2040

## 📚 Descrição do Projeto

Este projeto foi desenvolvido para consolidar conceitos relacionados ao uso de interrupções no microcontrolador RP2040 e explorar funcionalidades da placa de desenvolvimento BitDogLab. Ele combina hardware e software para manipular uma matriz de LEDs WS2812, LEDs RGB e botões com funcionalidades específicas. 

---

## 🎯 Funcionalidades Implementadas

1. **Controle da Matriz de LEDs WS2812 (5x5)**
   - Exibe números de 0 a 9 utilizando um padrão fixo, no estilo de caracteres digitais. 
   - A matriz responde aos botões:
     - Botão A: Incrementa o número exibido na matriz. ➕
     - Botão B: Decrementa o número exibido na matriz. ➖

2. **Controle do LED RGB** 🔴
   - O LED vermelho pisca continuamente a uma frequência de 5 Hz (100 ms ON, 100 ms OFF).

3. **Debouncing dos Botões**
   - Implementação de software para evitar o efeito de bouncing, garantindo uma leitura precisa de eventos dos botões.

4. **Uso de Interrupções**
   - A funcionalidade dos botões é gerenciada através de rotinas de interrupção (IRQ).

---

## 🛠️ Componentes Utilizados

### Hardware
- **Matriz 5x5 de LEDs WS2812**: Conectada à GPIO 7.
- **LED RGB**: Conectado às GPIOs 11, 12 e 13.
- **Botão A**: Conectado à GPIO 5.
- **Botão B**: Conectado à GPIO 6.

### Software
- **RP2040 SDK**
- **PIO para controle do WS2812**
- **Linguagem C**

---

## ⚙️ Diagrama de Conexões

| Componente    | GPIO   | Descrição                     |
|---------------|--------|-------------------------------|
| Matriz WS2812 | 7      | Dados da matriz de LEDs       |
| LED Vermelho  | 11     | Canal vermelho do LED RGB     |
| LED Verde     | 12     | Canal verde do LED RGB        |
| LED Azul      | 13     | Canal azul do LED RGB         |
| Botão A       | 5      | Incrementa o número da matriz |
| Botão B       | 6      | Decrementa o número da matriz |

---

## 📂 Organização do Código

- **`matrix_led.c`**: Arquivo principal do projeto contendo:
  - Inicialização do hardware.
  - Loop principal e controle do LED RGB.
  - Configuração e manipulação da matriz de LEDs.
  - Rotinas de interrupção para os botões.

- **`ws2812.pio`**: Código PIO para comunicação com LEDs endereçáveis WS2812.

---

## 🛠️ Instruções de Compilação e Execução

1. Clone o repositório para o ambiente local.
2. Certifique-se de ter o RP2040 SDK configurado corretamente.
3. Compile o projeto com o `Compile Project`
4. Após a compilação, carregue o firmware gerado (`matrix_led.uf2`) na placa BitDogLab.

---

## 📹 Demonstração do Projeto

### Vídeo de Demonstração
- O vídeo de demonstração exibe:
  - Funcionamento do LED RGB piscando em vermelho.
  - Incremento e decremento dos números exibidos na matriz de LEDs ao pressionar os botões A e B.
  - Explicação das funcionalidades implementadas.

[Video Demonstrativo](https://youtu.be/)
---

## 💻 Autor
- **Matheus Gouveia de Deus Bastos**

---

## 📜 Licença
Este projeto é de uso acadêmico e segue as diretrizes da Embarcatech.
