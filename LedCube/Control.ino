int tempCounter = 0;
long timerDelay = 1900;

//--- Important: All Pins must be 8 or higher (in PORTB range)
int latchPinPORTB = latchPin - 8;
int clockPinPORTB = clockPin - 8;
int dataPinPORTB = dataPin - 8;

byte layer = 0;

void Initilize() {
 randomSeed(analogRead(1)*analogRead(2)*analogRead(3)*analogRead(4)*micros());
 //randomSeed(1);
 //set pins to output because they are addressed in the main loop
 pinMode(latchPin, OUTPUT);
 pinMode(clockPin, OUTPUT);
 pinMode(dataPin, OUTPUT);

 digitalWrite(latchPin,LOW);
 digitalWrite(dataPin,LOW);
 digitalWrite(clockPin,LOW);

 setupSPI();
 
 Timer1.initialize(timerDelay); // Timer for updating pwm pins
 Timer1.attachInterrupt(process);
}

void process() {

  if (layer == 7) {
    layer = 0;
  } else {
    layer++;
  }

  latchOff();
  for (int i = 0; i < 8; ++i) {
    spi_transfer(data[7-layer][i]);
  }
  spi_transfer(1 << layer);
  latchOn();

}

void dataOff(){
bitClear(PORTB,dataPinPORTB);
}

void clockOff(){
bitClear(PORTB,clockPinPORTB);
}

void clockOn(){
bitSet(PORTB,clockPinPORTB);
}

void dataOn(){
bitSet(PORTB,dataPinPORTB);
}

void latchOn(){
bitSet(PORTB,latchPinPORTB);
}

void latchOff(){
bitClear(PORTB,latchPinPORTB);
}

void setupSPI(){
 byte clr;
 SPCR |= ( (1<<SPE) | (1<<MSTR) ); // enable SPI as master
 //SPCR |= ( (1<<SPR1) | (1<<SPR0) ); // set prescaler bits
 SPCR &= ~( (1<<SPR1) | (1<<SPR0) ); // clear prescaler bits
 clr=SPSR; // clear SPI status reg
 clr=SPDR; // clear SPI data reg
 SPSR |= (1<<SPI2X); // set prescaler bits
 //SPSR &= ~(1<<SPI2X); // clear prescaler bits

 delay(10); 
}
byte spi_transfer(byte data)
{
 SPDR = data;                    // Start the transmission
 while (!(SPSR & (1<<SPIF)))     // Wait the end of the transmission
 {
 };
 return SPDR;                    // return the received byte, we don't need that
}


