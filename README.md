# Leitor NFC usando PN532

Este projeto é um leitor NFC baseado no módulo PN532 usando a biblioteca `Adafruit_PN532` para leitura de cartões NFC. O código permite autenticação e leitura de dados de blocos de cartões compatíveis com o padrão MIFARE.

## Como Usar

1. **Clone o repositório:**

   ```bash
   git clone https://github.com/LeoVichi/NFC_reader.git
   cd NFC_reader
   ```

2. **Configuração do Hardware:**

   Conecte o módulo PN532 ao microcontrolador usando I2C:
   - **SDA** -> A4
   - **SCL** -> A5

3. **Bibliotecas Necessárias:**

   Certifique-se de que as seguintes bibliotecas estejam instaladas:
   - `Adafruit_PN532`
   - `Wire` (normalmente já incluída com o Arduino IDE)

4. **Carregue o Código:**

   Abra o arquivo `leitor_nfc_pn532.ino` no Arduino IDE ou o arquivo `.cpp` no seu ambiente de desenvolvimento preferido, e carregue-o no microcontrolador.

5. **Funcionamento:**

   - O código inicializa o módulo PN532 e espera por um cartão NFC.
   - Quando um cartão é detectado, ele autentica e lê os dados do bloco 1, exibindo-os no monitor serial.

## Licença

Este projeto é licenciado sob os termos da licença MIT. Veja o arquivo [LICENSE](LICENSE) para mais detalhes.

## Autor

- **L3nny_P34s4n7**
- **Email:** contact@leonardovichi.com
