#include <URTouch.h>
#include <URTouchCD.h>

#include <UTFT_Buttons.h>

#include <UTFT.h>												// Appel de la bibliotheque pour la gestion de l'ecran 
#include <UTFT_tinyFAT.h>               //Accés sd ecran
#include <tinyFAT.h>                    //Parametres d'accées a la sd
#define NOTE_B3  247
#define NOTE_C4  262

UTFT    myGLCD(ITDB32S, 38, 39, 40, 41);						// Initialise l'affichage de l'ecran pour l'arduino Mega
UTFT_tinyFAT myFiles(&myGLCD);                      // déclaration objet myFiles pour associer les images de la carte SD et notre objet écran myGLCD

URTouch  myTouch( 6, 5, 4, 3, 2); //Declaration de l'objet ecran tactile
UTFT_Buttons  myButtons(&myGLCD, &myTouch);



extern uint8_t BigFont[];										// Regle la police de caractere
String data = "E2";												// Initialise la variable data qui est une chaine de caracteres
String Etat = "";													// Initialise la variable Etat a 6 pour eviter le clignotement de l'ecran au demarage
int imp;
String Cap;
String Alim;

  int but1, but2, pressed_button;


void sound() {
  int melody[] = {NOTE_B3, NOTE_C4};
  int noteDurations[] = {4, 4};
  for (int thisNote = 0; thisNote < 3; thisNote++) {

    int noteDuration = 1000 / noteDurations[thisNote];
    tone(11, melody[thisNote], noteDuration);

    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(11);
  }
}

void repo()
{
 Serial.println("REPOS");
 myGLCD.clrScr();
 myFiles.loadBitmap(20, 27, 280, 125, "repos2.raw");

 myButtons.drawButtons();
 myGLCD.setBackColor(VGA_BLUE);
 myGLCD.setColor(VGA_WHITE);
 myGLCD.print("Drop",40,185);
 myGLCD.print("Avant",40,210);
 myGLCD.print("Drop",190,185);
 myGLCD.print("Arriere",190,210);

  
}

void manipulation()
{
  Serial.println("MANIPULATION");
  myGLCD.clrScr();
  myFiles.loadBitmap(50, 70, 220, 69, "manip.raw");  
  sound();
}

void drawBitmaps()												// Declaration de la fonction drawbuttons pour dessiner L'etat initiale de la table
{
  myGLCD.clrScr();
  myFiles.loadBitmap(0, 160, 150, 37, "testdrop.raw");			// Chargement et positionement de l'image du coussin gauche de la table
  myFiles.loadBitmap(160, 160, 150, 37, "testdrop.raw");		// Chargement et positionement de l'image du coussin droite de la table
}

void Erreur()													// Declaration de la fonction drawbuttons pour le cas d'erreur
{
  myGLCD.clrScr();
  Serial.print("ERREUR");

  myGLCD.setColor(255, 0, 0);									// Choix de la couleur pour le crayon en R, G, B : Rouge
  myGLCD.fillRoundRect(108, 5, 213, 35);            // Dessine un rectangle plein
  myGLCD.setColor(255, 255, 255);               // Choix de la couleur pour le crayon en R, G, B : Blanc
  myGLCD.drawRoundRect(108, 5, 213, 35);
  myGLCD.setBackColor(255, 0, 0);								// Regle la couleur de fond : Rouge
  myGLCD.print("ERREUR", 113, 12);							// Affiche "ERREUR" sur l'ecran

  myGLCD.setColor(255, 0, 0);									// Choix de la couleur pour le crayon en R, G, B : Rouge
  myGLCD.fillRoundRect(18, 200, 303, 235);					// Dessine un rectangle plein
  myGLCD.setColor(255, 255, 255);								// Choix de la couleur pour le crayon en R, G, B : Blanc
  myGLCD.drawRoundRect(18, 200, 303, 235);					// Dessine un rectangle vide
  myGLCD.setBackColor(255, 0, 0);								// Regle la couleur de fond : Rouge
  myGLCD.print("Relancer la table", 24, 210);					// Affiche "Relancer la table" sur l'ecran

  //myGLCD.drawBitmap(85, 50, 150, 40, danger);
  myFiles.loadBitmap(85,98,150,40, "danger.RAW");
}
void Erreur_Alim()                          // Declaration de la fonction drawbuttons pour le cas d'erreur
{
  myGLCD.clrScr();
  Serial.println("ALIM");

  myGLCD.setColor(255, 0, 0);                 // Choix de la couleur pour le crayon en R, G, B : Rouge
  myGLCD.fillRoundRect(108, 5, 213, 35);            // Dessine un rectangle plein
  myGLCD.setColor(255, 255, 255);               // Choix de la couleur pour le crayon en R, G, B : Blanc
  myGLCD.drawRoundRect(108, 5, 213, 35);
  myGLCD.setBackColor(255, 0, 0);               // Regle la couleur de fond : Rouge
  myGLCD.print("ERREUR", 113, 12);              // Affiche "ERREUR" sur l'ecran

  myGLCD.setColor(255, 0, 0);                 // Choix de la couleur pour le crayon en R, G, B : Rouge
  myGLCD.fillRoundRect(18, 185, 303, 235);          // Dessine un rectangle plein
  myGLCD.setColor(255, 255, 255);               // Choix de la couleur pour le crayon en R, G, B : Blanc
  myGLCD.drawRoundRect(18, 185, 303, 235);          // Dessine un rectangle vide
  myGLCD.setBackColor(255, 0, 0);               // Regle la couleur de fond : Rouge
  myGLCD.print("Alimentation", 75, 190);         // Affiche "Relancer la table" sur l'ecran
  myGLCD.print(Alim, 20, 210);         // Affiche "Relancer la table" sur l'ecran
  Alim="";
  Etat="";

  myFiles.loadBitmap(85,98,150,40, "danger.RAW");
}
void Erreur_Temp()                          // Declaration de la fonction drawbuttons pour le cas d'erreur
{
  myGLCD.clrScr();
  Serial.println("TEMP");

  myGLCD.setColor(255, 0, 0);                 // Choix de la couleur pour le crayon en R, G, B : Rouge
  myGLCD.fillRoundRect(108, 5, 213, 35);            // Dessine un rectangle plein
  myGLCD.setColor(255, 255, 255);               // Choix de la couleur pour le crayon en R, G, B : Blanc
  myGLCD.drawRoundRect(108, 5, 213, 35);
  myGLCD.setBackColor(255, 0, 0);               // Regle la couleur de fond : Rouge
  myGLCD.print("ERREUR", 113, 12);              // Affiche "ERREUR" sur l'ecran

  myGLCD.setColor(255, 0, 0);                 // Choix de la couleur pour le crayon en R, G, B : Rouge
  myGLCD.fillRoundRect(18, 185, 303, 235);          // Dessine un rectangle plein
  myGLCD.setColor(255, 255, 255);               // Choix de la couleur pour le crayon en R, G, B : Blanc
  myGLCD.drawRoundRect(18, 185, 303, 235);          // Dessine un rectangle vide
  myGLCD.setBackColor(255, 0, 0);               // Regle la couleur de fond : Rouge
  myGLCD.print("Surchauffe", 75, 190);         // Affiche "Relancer la table" sur l'ecran
  myGLCD.print(Cap, 85, 210);         // Affiche "Relancer la table" sur l'ecran
  Cap="";
  Etat="";

  myFiles.loadBitmap(85,98,150,40, "danger.RAW");
}

void DropArriere(int y)											// Declaration de la fonction pour monter le coussin avant
{
  myGLCD.setColor(0, 0, 0);
  myGLCD.drawRoundRect(160, 0, 260, 240);

  myGLCD.setColor(0, 0, 0);
  myGLCD.fillRoundRect(160, 0, 260, 240);

  myFiles.loadBitmap(160,160-y, 100,80,"DROP_D.raw");
  imp = 0;
}

void DropAvant(int y)											// Déclaration de la fonction pour monter le coussin arriere
{
  myGLCD.setColor(0, 0, 0);                  // Choix de la couleur pour le crayon en R, G, B : Noir
  myGLCD.drawRoundRect(0, 0, 100, 240);          // Dessine un rectangle vide pour eviter que les images se superposent

  myGLCD.setColor(0, 0, 0);                 // Choix de la couleur pour le crayon en R, G, B : Noir
  myGLCD.fillRoundRect(0, 0, 100, 240);          // Dessine un rectangle plein pour eviter que les images se superposent

  myFiles.loadBitmap(0,203-y, 100, 80, "testdrop.raw");

  imp = 0;
}
void test()
{
  Serial.println("INIT");
  myGLCD.clrScr();
  myFiles.loadBitmap(20, 58, 280, 125, "init.raw");
}

void setup()													// Initialisation du programme
{
  Serial.begin(9600);// Initialisation Serie debug
  Serial1.begin(9600);//Initialisation Serie comm.

  
  myGLCD.InitLCD();											// Initialisation de l'ecran
  
  file.buffer[511];
  file.setSSpin(53);
  file.initFAT(SPISPEED_HIGH);

  Serial.print(data);
  
  myGLCD.clrScr();                      // Efface tout ce qu'il y a sur l'ecran
  myGLCD.fillScr(0, 0, 0);									// Rempli l'ecran avec une couleur specifiee : Noir
  myGLCD.setFont(BigFont);									// choisi la police de caractere
  myGLCD.setBackColor(0, 0, 255);								// Choix de la couleur de fond : Bleu

  myTouch.InitTouch(); //initialisation du tactile
  myTouch.setPrecision(PREC_MEDIUM);//Definition de la precsion du tactile
  
   but1 = myButtons.addButton( 5,  180, 150,  50, "");
  but2 = myButtons.addButton( 165,  180, 150,  50, "");
  pressed_button = 10;
  
  drawBitmaps();												// Appel de la fonction drawButtons
}

void loop()														    // Boucle principale
{
  if(data[0]=='I') //Incrementation verin
  {
    data.remove(0,1); // On eneleve le premier caractere
    imp=data.toInt();//Conversion en entier
    data="";         // Remise de data a zero
  }
  else if(data[0]=='E') //Etat de la table
  {
    Etat=data;
     data="";         // Remise de data a zero
  }
  else if (data[0]=='C') //Numéro de capteurs
  {
    Cap=data; 
    Cap.replace("\t", "   "); //Remplacement du "\t" par un espace
    data="";         // Remise de data a zero
  }
  else if (data[0]=='A') // Alimentation
  {
    Alim=data;
    Alim.replace("A", ""); //enlevement du "A"
    Alim.replace("\t", " ");//Remplacement du "\t" par un espace
    data="";         // Remise de data a zero
  }

  delay(100);
  
  if (Etat.equals(String("E1"))) {										// Cas No1
      test();
      Etat="";
  }
  else if (Etat.equals(String("E2"))) { //Table au repos
    repo();
    Etat = "E2BIS";                          // Remise de la variable etat a zero pour eviter le clignotement ecran
    }
  else if(Etat.equals(String("E2BIS")))
  {
      if (myTouch.dataAvailable() == true)
      {
        pressed_button = myButtons.checkButtons();
        if (pressed_button==but1)
        {
          Serial.print("BTN_AV\n");
          }
        if (pressed_button==but2)
        {
          Serial.print("BTN_AR\n");
        }
      }
  }
  else if (Etat.equals(String("E3"))) {
    Etat="E3BIS";
    myGLCD.clrScr();
    drawBitmaps();
  }
  else if(Etat.equals(String("E3BIS"))) {
    if (imp>0)DropAvant(imp);
  }
  else if (Etat.equals(String("E4"))) {
    if (imp>0)DropAvant(imp);
  }
  else if(Etat.equals(String("E12"))) {
    Etat="E12BIS";
    myGLCD.clrScr();
    drawBitmaps();
  }
  else if(Etat.equals(String("E12BIS"))) {
    if (imp>0)DropArriere(imp);
    }
  else if (Etat.equals(String("E13"))) {
    if (imp>0)DropArriere(imp);
    }
  else if (Etat.equals(String("E20"))) { //Pret a la manipulation
    manipulation();
    Etat = "";                          // Remise de la variable etat a zero pour eviter le clignotement ecran
    }
  else if (Etat.equals(String("E24"))) { //Erreur sur la temperatur de l'alimentation
    if(Cap!="")Erreur_Temp();            //On attend de savoir quelle capteur a u probleme
  }
  else if (Etat.equals(String("E25"))) { //Erreur tension d'alimentation 
    if(Alim!="")Erreur_Alim();           //On attend de savoir quelle tension ne va pas
  }
}

void serialEvent()									// Declaration de la fonction pour ouvrir la reception de l'I2C
{
  while (Serial.available())                  // Boucle tant que la reception est active
  {
    char in = (char)Serial.read(); //
    if(in =='\n') break;           //Si on recoit le caractere de fin, on sort de la boucle
    else data += in;               //On concatene un string avec les donnés reçus
  }
  if(data.length()>30)data="";      //Si il y a eu un probleme lors de la reception, la variable ne correspond a rien et donc n'est pas remise a zero et continue a se concatener donc on la remets a zero
  Serial.println(data);             //Debug de la reception
}
