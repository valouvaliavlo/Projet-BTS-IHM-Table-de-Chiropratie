String data;
String Etat;
void setup() {
Serial.begin(9600);
data="DIAPO";
}

void loop() {
  if(data!="")Etat=(String)data;
  data="";
  if(Etat.equals(String("DIAPO")))
  {
    Serial.print("E1\n");
    delay(3000);
    Serial.print("E2\n");
    delay(3000);
    Serial.print("E20\n");
    delay(3000);
    Serial.print("E24\n");
    delay(200);
    Serial.print("C1C2\n");
    delay(3000);
    Serial.print("E25\n");
    delay(200);
    Serial.print("A5H\t5L\t12\t3,3\t24\n");
    delay(3000);
  }
  else if(Etat.equals(String("DROP")))
  {
    Serial.print("E3\n");
    delay(200);
    for(int i =0; i<50; i++)
    {
      Serial.print("I"+String(i)+"\n");
      delay(500);
    }
    delay(10000);
    Serial.print("E12\n");
    delay(200);
    for(int i =0; i<50; i++)
    {
      Serial.print("I"+String(i)+"\n");
      delay(500);
    }
  }
  
}
void serialEvent()
{
   while (Serial.available())                  // Boucle tant que la reception est active
  {
    char in = (char)Serial.read(); //
    if(in =='\n') break;
    else data += in;               //On concatene un string avec les donnés reçus
  }
  if(data.length()>15)data="";
  Serial.println(data);
}

