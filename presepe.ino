/**********************************************************
   Centralina Alba-Tramonto per presepe

   Created on 12 december 2014
   Modified on 15 decebre 2014

   by Mauro Alfieri
   web:    mauroalfieri.it
   Twitter: @mauroalfieri
  /**********************************************************/

#define pin_down   3
#define pin_sun    5
#define pin_sunset 6
#define pin_moon   9
#define pin_starsA 10
#define pin_starsB 11

int oneminrome[4] = { 4194, 22958, 4195, 28651 };
int oneminbtlm[4] = { 3668, 25189, 3668, 27474 };
int timeStepOld = 0;
int timeStep = 0;

long timeCurr = 0;

byte fade[]  = {255, 250, 245, 240, 235, 230, 225, 220, 215, 210, 205, 200, 195, 190, 185, 180, 175, 170, 165, 160, 155, 150, 145, 140, 135, 130, 125, 120, 115, 110, 105, 100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5, 0}; // 52 step
byte curr   = 0;

void setup() {
  Serial.begin( 9600 );

  pinMode( pin_down  , OUTPUT );
  pinMode( pin_sun   , OUTPUT );
  pinMode( pin_sunset, OUTPUT );
  pinMode( pin_moon  , OUTPUT );
  pinMode( pin_starsA, OUTPUT );
  pinMode( pin_starsB, OUTPUT );

  analogWrite( pin_down  , LOW );
  analogWrite( pin_sun   , LOW );
  analogWrite( pin_sunset, LOW );
  analogWrite( pin_moon  , LOW );
  analogWrite( pin_starsA, LOW );
  analogWrite( pin_starsB, LOW );

  Serial.println("-- START --");
}

void loop() {
  timeCurr = oneminrome[curr];
  timeStep = (timeCurr / 52);

  Serial.print("Current: "); Serial.println(curr);
  Serial.print("Time current: "); Serial.println(timeCurr);
  Serial.print("Time single step: "); Serial.println(timeStep);

  // down
  if ( curr == 0 ) {
    Serial.print("Fase: "); Serial.println("DOWN");
    for ( int i = 0; i < 52; i++) {
      analogWrite(pin_down,   fade[(51 - i)]);
      analogWrite(pin_sun,    0 );
      analogWrite(pin_sunset, 0 );
      analogWrite(pin_moon,   fade[i] );
      analogWrite(pin_starsA, fade[i] );
      analogWrite(pin_starsB, fade[i] );
      delay( timeStep );
    }
    timeStepOld = timeStep;
  }

  // sun
  if ( curr == 1 ) {
    Serial.print("Fase: "); Serial.println("SUN");
    for ( int i = 0; i < 52; i++) {
      analogWrite(pin_down,   fade[i]);
      if ( fade[i] < 125) analogWrite(pin_sun,    fade[(51 - i)] * 2 );
      analogWrite(pin_sunset, 0 );
      analogWrite(pin_moon,   0 );
      analogWrite(pin_starsA, 0 );
      analogWrite(pin_starsB, 0 );
      delay( timeStepOld );
    }
    timeStepOld = (timeStepOld * 52); // elapsed time
    timeCurr = (timeCurr - timeStepOld);
    delay( timeCurr );
  }

  // sunset
  if ( curr == 2 ) {
    Serial.print("Fase: "); Serial.println("SUNSET");
    for ( int i = 0; i < 52; i++) {
      analogWrite(pin_down,   0);
      analogWrite(pin_sun,    fade[i] );
      analogWrite(pin_sunset, fade[(51 - i)] );
      analogWrite(pin_moon,   0 );
      analogWrite(pin_starsA, 0 );
      analogWrite(pin_starsB, 0 );
      delay( timeStep );
    }
    timeStepOld = timeStep;
  }

  // moon
  if ( curr == 3 ) {
    Serial.print("Fase: "); Serial.println("MOON");
    for ( int i = 0; i < 52; i++) {
      analogWrite(pin_down,   0);
      analogWrite(pin_sun,    0 );
      analogWrite(pin_sunset, fade[i] );
      if ( fade[i] < 125) analogWrite(pin_moon,   fade[(51 - i)] * 2 );
      if ( fade[i] < 125) analogWrite(pin_starsA, fade[(51 - i)] * 2 );
      if ( fade[i] < 125) analogWrite(pin_starsB, fade[(51 - i)] * 2 );
      delay( timeStepOld );
    }
    timeStepOld = (timeStepOld * 52); // elapsed time
    timeCurr = (timeCurr - timeStepOld);
    delay( timeCurr );
  }
  curr++;
  if ( curr >= 4 ) {
    curr = 0;
  }
}
