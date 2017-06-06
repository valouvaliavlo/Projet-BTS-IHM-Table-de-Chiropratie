String data;
String Etat;
void setup() {
Serial1.begin(9600);
Serial.begin(9600);
data="";
}

void loop() {
  if(data!="")
  {
    Etat=(String)data;
      data="";
    Serial.println(Etat);
  }
  delay(100);
  if(Etat.equals(String("DIAPO")))
  {
    Serial1.print("E1\n");
    delay(3000);
    Serial1.print("E2\n");
    delay(3000);
    Serial1.print("E20\n");
    delay(3000);
    Serial1.print("E24\n");
    delay(200);
    Serial1.print("C1C2\n");
    delay(3000);
    Serial1.print("E25\n");
    delay(200);
    Serial1.print("A5H\t5L\t12\t3,3\t24\n");
    delay(3000);
  }
  else if(Etat.equals(String("BTN_AV")))
  {
    delay(200);
    Serial1.print("E3\n");
    delay(200);
    for(int i =0; i<12; i++)
    {
      Serial1.print("I"+String(i)+"\n");
      delay(500);
    }
    Etat="";
  }
    else if (Etat.equals(String("BTN_AR")))
    {
      delay(200);
      Serial1.print("E12\n");
      delay(200);
      for(int i =0; i<12; i++)
      {
        Serial1.print("I"+String(i)+"\n");
        delay(500);
      }
          Etat="";
    }
  }
  
void serialEvent1()
{
   while (Serial1.available())                  // Boucle tant que la reception est active
  {
    char in = (char)Serial1.read(); //
    if(in =='\n') break;
    else data += in;               //On concatene un string avec les donnés reçus
  }
  if(data.length()>15)data="";
  Serial.println(data);
}

