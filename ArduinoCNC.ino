#define xdirpin 13
#define xsteppin 12
#define ydirpin 11
#define ysteppin 10
#define zdirpin 9
#define zsteppin 8
String motor;
String deger;
int adim;
int xcurrent = 0;
int ycurrent = 0;
int zcurrent = 0;
int xsum = 0;
int ysum = 0;
int zsum = 0;

void konum()  {
  Serial.print("X motorunun mevcut konumu =  ");
  Serial.println(xsum);
  Serial.print("Y motorunun mevcut konumu =  ");
  Serial.println(ysum);
  Serial.print("Z motorunun mevcut konumu =  ");
  Serial.println(zsum);
}

void setup()
{
  Serial.begin(9600);
  pinMode(xdirpin, OUTPUT);
  pinMode(xsteppin, OUTPUT);
  pinMode(ydirpin, OUTPUT);
  pinMode(ysteppin, OUTPUT);
  pinMode(zdirpin, OUTPUT);
  pinMode(zsteppin, OUTPUT);
  Serial.println("\t\t\t<<CNC MAKINESININ KONTROL MENUSUNE HOSGELDINIZ!! >>\n");
  Serial.println("<< Motor ve yon komutlari = XF..(forward), XB..(backward), XR(reset), YF.., YB.., YR, ZF.., ZB.., ZR >>");
  Serial.println("\n\t\t\t\t\tDIKKAT!!");
  Serial.println("Limitimiz yaklasik 35 - 40 cm'dir. Mevcut konumlar -2000 ile 2000 arasinda kalmalidir!!\n");
}

void loop() {

  Serial.println("<<*****************************************>>");
  Serial.print("Gecerli motor, yon ve adim sayisini girin =   ");
  while (Serial.available() == 0) {
  }

  String serialread = Serial.readString();
  motor = serialread.substring(0, 2);
  deger = serialread.substring(2, 6);
  adim = deger.toInt();
  //                                                                             X MOTORU
  if (motor == "XF" && adim > 0) {
    digitalWrite(xdirpin, HIGH);
    xcurrent = adim;
    xsum += xcurrent;
    Serial.print("X motoru ILERI yönde ");
    Serial.print(xcurrent);
    Serial.println(" adim devrede..");
    delay(500);

    if (xsum <= 2000) {
      for (int i = 0; i < xcurrent; i++) {
        digitalWrite(xsteppin, HIGH);
        delayMicroseconds(500);
        digitalWrite(xsteppin, LOW);
        delayMicroseconds(500);
      }
    }
    else  {
      Serial.println("DIKKAT MAKSIMUM LIMITI ASTINIZ VERILEN KOMUT UYGULANAMADI!! Tekrar giriniz..");
      xsum -= xcurrent;
    }
    konum();
  }

  if (motor == "XB" && adim > 0) {
    digitalWrite(xdirpin, LOW);
    xcurrent = adim;
    xsum -= xcurrent;
    Serial.print("X motoru GERI yönde ");
    Serial.print(xcurrent);
    Serial.println(" adim devrede..");
    delay(500);

    if (xsum >= -2000) {
      for (int i = 0; i < xcurrent; i++) {
        digitalWrite(xsteppin, HIGH);
        delayMicroseconds(500);
        digitalWrite(xsteppin, LOW);
        delayMicroseconds(500);
      }
    }
    else  {
      Serial.println("DIKKAT MAKSIMUM LIMITI ASTINIZ VERILEN KOMUT UYGULANAMADI!! Tekrar giriniz..");
      xsum += xcurrent;
    }
    konum();
  }

  if (motor == "XR" && deger == '\0') {
    Serial.println("X motorunun konumu sifirlaniyor..");
    delay(500);
    if ( xsum < 0)  {
      digitalWrite(xdirpin, HIGH);

      for (int i = 0; i < -xsum; i++)  {
        digitalWrite(xsteppin, HIGH);
        delayMicroseconds(500);
        digitalWrite(xsteppin, LOW);
        delayMicroseconds(500);
      }
    }

    if ( xsum > 0)  {
      digitalWrite(xdirpin, LOW);
      for (int i = 0; i < xsum; i++)  {
        digitalWrite(xsteppin, HIGH);
        delayMicroseconds(500);
        digitalWrite(xsteppin, LOW);
        delayMicroseconds(500);
      }
    }
    xsum = 0;
    Serial.println("X motorunun konumu sifirlandi..");
    konum();
  }
  //                                                                             Y MOTORU
  if (motor == "YF" && adim > 0) {
    digitalWrite(ydirpin, HIGH);
    ycurrent = adim;
    ysum += ycurrent;
    Serial.print("Y motoru ILERI yönde ");
    Serial.print(ycurrent);
    Serial.println(" adim devrede..");
    delay(500);

    if (ysum <= 2000) {
      for (int i = 0; i < ycurrent; i++) {
        digitalWrite(ysteppin, HIGH);
        delayMicroseconds(500);
        digitalWrite(ysteppin, LOW);
        delayMicroseconds(500);
      }
    }
    else  {
      Serial.println("DIKKAT MAKSIMUM LIMITI ASTINIZ VERILEN KOMUT UYGULANAMADI!! Tekrar giriniz..");
      ysum -= ycurrent;
    }
    konum();
  }

  if (motor == "YB" && adim > 0) {
    digitalWrite(ydirpin, LOW);
    ycurrent = adim;
    ysum -= ycurrent;
    Serial.print("Y motoru GERI yönde ");
    Serial.print(ycurrent);
    Serial.println(" adim devrede..");
    delay(500);

    if (ysum >= -2000) {
      for (int i = 0; i < ycurrent; i++) {
        digitalWrite(ysteppin, HIGH);
        delayMicroseconds(500);
        digitalWrite(ysteppin, LOW);
        delayMicroseconds(500);
      }
    }
    else  {
      Serial.println("DIKKAT MAKSIMUM LIMITI ASTINIZ VERILEN KOMUT UYGULANAMADI!! Tekrar giriniz..");
      ysum += ycurrent;
    }
    konum();
  }

  if (motor == "YR" && deger == '\0') {
    Serial.println("Y motorunun konumu sifirlaniyor..");
    delay(500);
    if ( ysum < 0)  {
      digitalWrite(ydirpin, HIGH);

      for (int i = 0; i < -ysum; i++)  {
        digitalWrite(ysteppin, HIGH);
        delayMicroseconds(500);
        digitalWrite(ysteppin, LOW);
        delayMicroseconds(500);
      }
    }

    if ( ysum > 0)  {
      digitalWrite(ydirpin, LOW);
      for (int i = 0; i < ysum; i++)  {
        digitalWrite(ysteppin, HIGH);
        delayMicroseconds(500);
        digitalWrite(ysteppin, LOW);
        delayMicroseconds(500);
      }
    }
    ysum = 0;
    Serial.println("Y motorunun konumu sifirlandi..");
    konum();
  }
  //                                                                             Z MOTORU
  if (motor == "ZF" && adim > 0) {
    digitalWrite(zdirpin, HIGH);
    zcurrent = adim;
    zsum += zcurrent;
    Serial.print("Z motoru ILERI yönde ");
    Serial.print(zcurrent);
    Serial.println(" adim devrede..");
    delay(500);

    if (zsum <= 2000) {
      for (int i = 0; i < zcurrent; i++) {
        digitalWrite(zsteppin, HIGH);
        delayMicroseconds(500);
        digitalWrite(zsteppin, LOW);
        delayMicroseconds(500);
      }
    }
    else  {
      Serial.println("DIKKAT MAKSIMUM LIMITI ASTINIZ VERILEN KOMUT UYGULANAMADI!! Tekrar giriniz..");
      zsum -= zcurrent;
    }
    konum();
  }

  if (motor == "ZB" && adim > 0) {
    digitalWrite(zdirpin, LOW);
    zcurrent = adim;
    zsum -= zcurrent;
    Serial.print("Z motoru GERI yönde ");
    Serial.print(zcurrent);
    Serial.println(" adim devrede..");
    delay(500);

    if (zsum >= -2000) {
      for (int i = 0; i < zcurrent; i++) {
        digitalWrite(zsteppin, HIGH);
        delayMicroseconds(500);
        digitalWrite(zsteppin, LOW);
        delayMicroseconds(500);
      }
    }
    else  {
      Serial.println("DIKKAT MAKSIMUM LIMITI ASTINIZ VERILEN KOMUT UYGULANAMADI!! Tekrar giriniz..");
      zsum += zcurrent;
    }
    konum();
  }

  if (motor == "ZR" && deger == '\0') {
    Serial.println("Z motorunun konumu sifirlaniyor..");
    delay(500);
    if ( zsum < 0)  {
      digitalWrite(zdirpin, HIGH);

      for (int i = 0; i < -zsum; i++)  {
        digitalWrite(zsteppin, HIGH);
        delayMicroseconds(500);
        digitalWrite(zsteppin, LOW);
        delayMicroseconds(500);
      }
    }

    if ( zsum > 0)  {
      digitalWrite(zdirpin, LOW);
      for (int i = 0; i < zsum; i++)  {
        digitalWrite(zsteppin, HIGH);
        delayMicroseconds(500);
        digitalWrite(zsteppin, LOW);
        delayMicroseconds(500);
      }
    }
    zsum = 0;
    Serial.println("Z motorunun konumu sifirlandi..");
    konum();
  }
  Serial.println("<<*****************************************>>\n");
}

