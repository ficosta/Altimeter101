#include <Wire.h>
#include <SPI.h>
#include <U8glib.h> //biblioteca display
#include <Button.h> //biblioteca para botao unico

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NO_ACK); //definicao do display oled utilizado

//Definicoes botao unico
#define BUTTON1_PIN     4
Button button1 = Button(BUTTON1_PIN, BUTTON_PULLUP_INTERNAL);

int screen = 0; // numero de cada tela
bool updateScreen = false;
#define NB_SCREENS 4  //numero maximo de telas

int value, etat = 0; //nao sei p que serve ainda

boolean longPush = false; //definir se o botao foi mto pressionado ou foi um click

void setup() {

  Serial.begin(9600);

  // put your setup code here, to run once:
  u8g.setColorIndex(1);         // pixel on / acende o fundo do led / nao funcionou para apagar.

  button1.releaseHandler(handleButtonReleaseEvents);
  button1.holdHandler(handleButtonHoldEvents, 2000);
  
  updateScreen=true;
  drawSplashScreen();
  delay(5000);

  //TODO: adicionar rotina splash screen
  button1.isPressed(); // n sei p que serve
  screen = 1;   //define a tela 1 como inicial
}

void loop() {
  // put your main code here, to run repeatedly:

  button1.isPressed();


  //Serial.println("Loop"); //Rotina de debug do loop
  
  // desenhar telas
  switch (screen) {
    case 1: // Altitude
      //     if (lastValue != altitude) {
      //showScreen("ALTITUDE", altitude, METER);
      //lastValue = altitude;
      drawHome();
      //     }
      break;

    case 2: // Altitude Max
      //     if (lastValue != altiMax) {
      //showScreen("ALTITUDE MAX", altiMax, METER);
      //lastValue = altiMax;
      drawAltiMax();
      //    }
      break;

    case 3:  // Altitude Min
      //   if (lastValue != altiMin) {
      //showScreen("ALTITUDE MIN", altiMin, METER);
      //lastValue = altiMin;
      drawAltiMin();
      //     }
      break;

    case 4:  // Pression
      //      if (lastValue != pression) {
      //showScreen("PRESSION", pression, HPA);
      //lastValue = pression;
      drawAltiAtual();
      //  }
      break;
  }

  // } while( u8g.nextPage() );
  delay(50);
}

void drawSplashScreen(void) {
  //tela 0
  //Desenha tela splash screen
  if (updateScreen) {
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_6x13);
      u8g.drawStr( 27, 22, "SPACE SCIENCE");
      u8g.setFont(u8g_font_fub20); //escolher uma fonte melhor soh com numeros
      u8g.drawStr( 38, 46, "101");
      //u8g.drawBox(10, 50, 118, 52);
    } while ( u8g.nextPage());
    Serial.println("SplashScreen");
    updateScreen = false;
  }
}

void drawHome(void) {
  //tela 1
  //Desenha tela home
  if (updateScreen) {
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_6x13);
      u8g.drawStr( 0, 12, "HOME!");
    } while ( u8g.nextPage() );
    Serial.println("Home");
    updateScreen = false;
  }
}
void drawAltiMax(void) {
  //tela 2
  //Altitude Maxima
  if (updateScreen) {
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_6x13);
      u8g.drawStr( 0, 12, "Alt maxima");
    } while ( u8g.nextPage() );
    Serial.println("AMax");
    updateScreen = false;
  }
}
void drawAltiMin(void) {
  // tela 3
  //Altitude Minima
  if (updateScreen) {
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_6x13);
      u8g.drawStr( 0, 12, "Alti Minima");
    } while ( u8g.nextPage() );
    Serial.println("Amin");
    updateScreen = false;
  }
}
void drawAltiAtual(void) {
  //tela 4
  //Altitude Atual
  if (updateScreen) {
    u8g.firstPage();
    do {
      u8g.setFont(u8g_font_6x13);
      u8g.drawStr( 0, 12, "Alti atual");
    } while ( u8g.nextPage() );
    Serial.println("ATual");
    updateScreen = false;
  }
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
  screen = 1;
  value = 0;
  if (screen == 1 && ++etat > 2) {
    etat = 0;
    delay(500);
  }
  else if (screen == 2 || screen == 3) {
    //    resetAltiMinMax();
  }
  Serial.println("Hold");
}


