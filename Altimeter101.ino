#include <Wire.h>
#include <SPI.h>
#include <U8glib.h> //biblioteca display
#include <Button.h> //biblioteca para botao unico
#include <SFE_BMP180.h> //Biblioteca do barometro e termometro

//DEFINICAO DO LOGO SPLASHSCREEN

#define logo_ss_width 120
#define logo_ss_height 50
static unsigned char logo_ss_bits[] U8G_PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 0x00, 0xc0, 0xe1, 0x0f, 0x30, 0x00,
  0x0f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0xf0, 0xe3,
  0x1f, 0x70, 0xc0, 0x3f, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1f,
  0x00, 0xf0, 0xe7, 0x3b, 0x78, 0xe0, 0x3f, 0xde, 0x00, 0x00, 0x00, 0x00,
  0x00, 0xc0, 0x1f, 0x00, 0x30, 0xe6, 0x70, 0x78, 0xe0, 0x09, 0x0e, 0x00,
  0x00, 0x00, 0x00, 0x00, 0xe0, 0x17, 0x00, 0x70, 0xe0, 0x30, 0xfc, 0xf0,
  0x00, 0x4e, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x13, 0x00, 0xf0, 0xe3,
  0x30, 0xfc, 0x70, 0x00, 0xfe, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x09,
  0x00, 0xe0, 0xe3, 0x3f, 0xce, 0x71, 0x00, 0x7e, 0x00, 0x00, 0x00, 0xfa,
  0x01, 0xf8, 0x09, 0x00, 0x00, 0xe7, 0x1f, 0xce, 0xf1, 0x00, 0x0e, 0x00,
  0x00, 0xc0, 0xff, 0x1f, 0xfc, 0x04, 0x00, 0x30, 0xe7, 0x0f, 0xfe, 0xe3,
  0x19, 0x0e, 0x00, 0x00, 0xf0, 0xff, 0x7f, 0x7e, 0x02, 0x00, 0xf0, 0xe7,
  0x00, 0xff, 0xe3, 0x3f, 0xbe, 0x00, 0x00, 0xfc, 0xff, 0x3f, 0x3f, 0x02,
  0x00, 0xf0, 0xe3, 0x00, 0xa7, 0xc7, 0x3f, 0xfe, 0x00, 0x00, 0xfe, 0x07,
  0x9e, 0x1f, 0x01, 0x00, 0xc0, 0xe1, 0x80, 0x03, 0x07, 0x0f, 0xfe, 0x00,
  0x80, 0x7f, 0x00, 0x90, 0x8f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xc0, 0x1f, 0x00, 0xc0, 0x47, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x07, 0x00, 0xe0, 0x33, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x03, 0x00,
  0xf0, 0x13, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xf0, 0x01, 0x00, 0xf8, 0x49, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xf8, 0x00, 0xfc, 0xff, 0xe4, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0xfc, 0x7f, 0xf2, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7c, 0x00, 0xff,
  0x3f, 0xf1, 0x01, 0xc0, 0x01, 0x1e, 0x8c, 0x3f, 0x02, 0x07, 0x0f, 0xfe,
  0x3c, 0x00, 0xff, 0x9f, 0xe0, 0x01, 0xe0, 0x83, 0x7f, 0x9e, 0x3f, 0x07,
  0xc7, 0x3f, 0xfe, 0x3e, 0x00, 0xfc, 0xcf, 0xe0, 0x03, 0xf0, 0xc7, 0x3f,
  0x8e, 0x3b, 0x0e, 0xe7, 0x3f, 0xde, 0x1e, 0x00, 0xf8, 0xe7, 0xc0, 0x03,
  0x30, 0xc6, 0x13, 0x9c, 0x03, 0x9e, 0xe3, 0x09, 0x0f, 0x1e, 0x00, 0xe0,
  0xf3, 0xc0, 0x03, 0x70, 0xe0, 0x00, 0x8e, 0x13, 0x3e, 0x77, 0x00, 0x2e,
  0x0f, 0x00, 0xc0, 0xf9, 0xc0, 0x03, 0xf0, 0xe3, 0x00, 0x9c, 0x3f, 0xff,
  0x77, 0x00, 0xfe, 0x0f, 0x00, 0x80, 0xfd, 0x80, 0x07, 0xe0, 0xe7, 0x00,
  0x8e, 0x3f, 0xfe, 0x77, 0x00, 0x7e, 0x0f, 0x00, 0x00, 0xff, 0x80, 0x07,
  0x00, 0xe7, 0x00, 0x9c, 0x03, 0xee, 0xf3, 0x00, 0x0f, 0x0f, 0x00, 0x0e,
  0xfc, 0x80, 0x07, 0x30, 0xe7, 0x11, 0x8e, 0x03, 0xce, 0xe7, 0x11, 0x0e,
  0x0f, 0x00, 0x3f, 0xfc, 0x80, 0x07, 0xf0, 0xc7, 0x3f, 0x9c, 0x37, 0x8e,
  0xe7, 0x1f, 0x6e, 0x0f, 0xc0, 0x3f, 0xf8, 0x80, 0x07, 0xf0, 0x83, 0x7f,
  0x8e, 0x7f, 0x0e, 0xc7, 0x3f, 0xfe, 0x00, 0xe2, 0x7f, 0x70, 0xc0, 0x07,
  0xc0, 0x01, 0x1f, 0x9c, 0x3f, 0x0e, 0x06, 0x0f, 0xff, 0xbc, 0xff, 0x3f,
  0x60, 0x80, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xff, 0xff, 0x3f, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xfe, 0xff, 0x1f, 0x00, 0xc0, 0x03, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x1f, 0x00, 0xc0, 0x03,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0x0f,
  0x00, 0xe0, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0xfc, 0xff, 0x0f, 0x00, 0xe0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0xfc, 0xff, 0x0f, 0x00, 0xf0, 0x01, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x0f, 0x00, 0xf0, 0x00,
  0x00, 0x00, 0x00, 0x38, 0x70, 0xc0, 0x01, 0x00, 0x00, 0xf8, 0xff, 0x1f,
  0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x38, 0xf8, 0xc1, 0x01, 0x00, 0x00,
  0xf0, 0xff, 0x0f, 0x00, 0x7c, 0x00, 0x00, 0x00, 0x00, 0x38, 0xfc, 0xc1,
  0x01, 0x00, 0x00, 0xe0, 0xff, 0x0f, 0x00, 0x3e, 0x00, 0x00, 0x00, 0x00,
  0x38, 0x8c, 0xc3, 0x01, 0x00, 0x00, 0xe0, 0xff, 0x0f, 0x80, 0x1f, 0x00,
  0x00, 0x00, 0x00, 0x38, 0x9c, 0xc3, 0x01, 0x00, 0x00, 0x80, 0xff, 0x0f,
  0xc0, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x38, 0x0c, 0xc3, 0x01, 0x00, 0x00,
  0x80, 0xff, 0x0f, 0xf0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x38, 0x9c, 0xc3,
  0x01, 0x00, 0x00, 0x00, 0xfe, 0x8f, 0xfe, 0x03, 0x00, 0x00, 0x00, 0x00,
  0x38, 0x0c, 0xc3, 0x01, 0x00, 0x00, 0x00, 0xfc, 0xe7, 0xff, 0x01, 0x00,
  0x00, 0x00, 0x00, 0x38, 0x9c, 0xc3, 0x01, 0x00, 0x00, 0x00, 0xf0, 0xe7,
  0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0xdc, 0xc1, 0x01, 0x00, 0x00,
  0x00, 0xc0, 0xf7, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38, 0xf8, 0xc1,
  0x01, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x38, 0xf0, 0xc0, 0x01, 0x00, 0x00
};


U8GLIB_SH1106_128X64 u8g(U8G_I2C_OPT_NO_ACK); //definicao do display oled utilizado

//Definicoes botao unico
#define BUTTON1_PIN     6
Button button1 = Button(BUTTON1_PIN, BUTTON_PULLUP_INTERNAL);

//Definicao do sensor barometrico
SFE_BMP180 pressure;
//Variavel para pressao incial
double baseline; // baseline pressure
//Varialvel da altitude
double T, alt, Pressure;
double altMax;

char voo = 0; //numero do voo

bool lancado; //registrador de lancamento

int screen = 0; // numero da tela em exbicao
bool updateScreen = false;
#define NB_SCREENS 4  //numero maximo de telas

int value, etat = 0; //nao sei p que serve ainda

boolean longPush = false; //definir se o botao foi mto pressionado ou foi um click

const int batVin = A2; //pino q a bateria esta colocado
int batValue = 0; //valor lido do sensor
int batPercent = 0; //porcentagem bateria


void setup() {

  Serial.begin(9600);

  // put your setup code here, to run once:

  button1.releaseHandler(handleButtonReleaseEvents);
  button1.holdHandler(handleButtonHoldEvents, 2000);

  updateScreen = true;
  drawSplashScreen();

  //TODO: adicionar rotina splash screen
  button1.isPressed(); // n sei p que serve
  screen = 0;   //define a tela 0 como inicial - primeiro click vai p home

  //Inicializar o sensor
  if (pressure.begin()) {
    Serial.println("BMP180 init success");
    baseline = getPressure();
  } else
  {
    // Oops, something went wrong, this is usually a connection problem,
    // see the comments at the top of this sketch for the proper connections.

    Serial.println("BMP180 init fail (disconnected?)\n\n");
  }

}

void loop() {
  // put your main code here, to run repeatedly:

  button1.isPressed();
  readAltitudePressure();

  calculaBateria();


  // desenhar telas
  switch (screen) {
    case 1: // Altitude
      drawHome();
      break;

    case 2:
      drawReport();
      break;

    case 3:
      drawLancamento();
      break;

    case 4:
      drawAltiAtual();
      break;
  }

  //delay(50);
}

void drawSplashScreen(void) {
  //tela 0
  //Desenha tela splash screen
  u8g.firstPage();
  do {
    u8g.drawXBMP( 0, 0, logo_ss_width, logo_ss_height, logo_ss_bits);
    u8g.setFont(u8g_font_6x13);
    u8g.drawStr(0, 60, "ficosta/Altimeter101");
  } while ( u8g.nextPage() );

  // rebuild the picture after some delay
  delay(500);

  updateScreen = false;
}

void drawHome(void) {
  //tela 1
  //Desenha tela home
  if (updateScreen) {
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_6x13);
      u8g.drawStr( 30, 10, "SENSORES:");

      u8g.drawStr( 0, 30, "Bat:");
      u8g.drawStr( 0, 45, "Temp:");
      u8g.drawStr( 0, 60, "Pres:");

      //Sensor bateria
      char buf[9];
      sprintf(buf, " %d", batPercent);
      u8g.setFont(u8g_font_6x13);
      u8g.drawStr(30, 30, buf);

      //Sensor Temperatura
      char outBufferT[8];
      dtostrf(T, 0, 2, outBufferT);
      u8g.drawStr(30, 45, outBufferT);

      //Sensor Barometrico
      // ACERTAR CONVERSAO PARA DOUBLE
      u8g.setFont(u8g_font_6x13);

      char outBuffer[8];
      dtostrf(Pressure, 0, 2, outBuffer);
      u8g.drawStr(30, 60, outBuffer);




    } while ( u8g.nextPage() );
    Serial.println("Home");
    updateScreen = true;
  }
}
void drawReport(void) {
  //tela 2
  //Altitude Maxima
  if (updateScreen) {
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_6x13);
      u8g.drawStr(25, 10, "RELATORIO:");
      u8g.drawStr(0, 30, "Alt:");
      u8g.drawStr(0, 45, "Vel:");

      u8g.drawStr(70, 30, "metros");
      u8g.drawStr(70, 45, "km/h");

      u8g.setFont(u8g_font_6x13);
      char outBufferAltMax[8];
      dtostrf(altMax, 0, 2, outBufferAltMax);
      u8g.drawStr(25, 30, outBufferAltMax);
      u8g.drawStr(25, 45, "--");



    } while ( u8g.nextPage() );
    updateScreen = false;
  }
}
void drawLancamento(void) {
  // tela 3
  //Altitude Minima
  if (updateScreen) {
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_6x13);
      u8g.drawStr(30, 10, "LANCAMENTO:");

      if (lancado) {
        u8g.drawStr(20, 32, "Registrando...");
        u8g.drawStr(20, 52, "Finalizar?");
        updateScreen = false;

      } else {
        u8g.drawStr(0, 32, "Voo n:");
        u8g.drawStr(0, 52, "Hold para lancar...");

        u8g.setFont(u8g_font_6x13);
        u8g.drawStr(40, 32, "0");
        updateScreen = false;
      }

    } while ( u8g.nextPage() );
    Serial.println("Lancamento");
  }
}
void drawAltiAtual(void) {
  //tela 4
  //Altitude Atual
  if (updateScreen) {
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_6x13);
      u8g.drawStr( 0, 12, "ALTITUDE ATUAL:");
      u8g.drawStr(70, 30, "metros");

      char outBufferAlt[8];
      dtostrf(alt, 0, 2, outBufferAlt);
      u8g.setFont(u8g_font_6x13);
      u8g.drawStr(25, 30, outBufferAlt);
    } while ( u8g.nextPage() );
    updateScreen = true;
  }
}

void calculaBateria(void) {
  batValue = analogRead(batVin);
  // map it to the range of the analog out:
  batPercent = map(batValue, 927, 1023, 0, 100);
}

void readAltitudePressure(void) {
  Pressure = getPressure();

  // Show the relative altitude difference between
  // the new reading and the baseline reading:

  alt = pressure.altitude(Pressure, baseline);
  if (lancado) {
    if (alt > altMax) {
      altMax = alt;
      Serial.println(altMax);
    }
  }
}

double getPressure()
{
  char status;
  double P, p0, a;

  // You must first get a temperature measurement to perform a pressure reading.

  // Start a temperature measurement:
  // If request is successful, the number of ms to wait is returned.
  // If request is unsuccessful, 0 is returned.

  status = pressure.startTemperature();
  if (status != 0)
  {
    // Wait for the measurement to complete:

    delay(status);

    // Retrieve the completed temperature measurement:
    // Note that the measurement is stored in the variable T.
    // Use '&T' to provide the address of T to the function.
    // Function returns 1 if successful, 0 if failure.

    status = pressure.getTemperature(T);
    if (status != 0)
    {
      // Start a pressure measurement:
      // The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
      // If request is successful, the number of ms to wait is returned.
      // If request is unsuccessful, 0 is returned.

      status = pressure.startPressure(0);
      if (status != 0)
      {
        // Wait for the measurement to complete:
        delay(status);

        // Retrieve the completed pressure measurement:
        // Note that the measurement is stored in the variable P.
        // Use '&P' to provide the address of P.
        // Note also that the function requires the previous temperature measurement (T).
        // (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
        // Function returns 1 if successful, 0 if failure.

        status = pressure.getPressure(P, T);
        if (status != 0)
        {
          return (P);
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
}

// Management release the button
void handleButtonReleaseEvents(Button &btn) {
  //debugMsg = "Release";
  if (!longPush) {
    if (etat != 0 ) { // Settings
      if (etat == 1) value = 1;
      if (etat == 2) value = -1;
    }
    else { // Change screen
      screen++;
      updateScreen = true;
      if (screen > NB_SCREENS) screen = 1;
      //  lastValue = 0;
    }
  }
  longPush = false;
  Serial.println("Release");
}

// Management support extended on the button
void handleButtonHoldEvents(Button &btn) {
  //debugMsg = "Hold";
  longPush = true;
  if (screen == 3) {
    if (lancado) {
      lancado = false;
    } else {
      lancado = true;
      altMax = 0;
    }
    updateScreen = true;
    delay(500);
  }
  else if (screen == 2 || screen == 3) {
    //    resetAltiMinMax();
  }
  Serial.println("Hold");
}
