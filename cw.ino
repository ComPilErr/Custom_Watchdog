volatile int i = 0;
const byte ledPin = 13;
volatile byte state = LOW;

ISR ( TIMER1_COMPA_vect )
{
 poop();
}

void setup() {
  // put your setup code here, to run once:
    
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, state);
    cli(); 
    TCCR1A=0; // нормальный режим работы таймера
    TCCR1B=0;
    OCR1A=0x3d08;
    TCCR1B = (1<<CS12|0<<CS11|1<<CS10|0<<WGM13|1<<WGM12); // режим сравнения, делитель 1024
    TIMSK1 = (0<<ICIE1|0<<OCIE1B|1<<OCIE1A|0<<TOIE1); // разрешение прерываний по сравнению
    sei();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (i >= 5) {
    TIMSK1 &= ~(1<<OCIE1A);
    state = !state;
    digitalWrite(ledPin, state);
    i = 0;
    TIMSK1 |= (1<<OCIE1A);
  } // 5 seconds action
 }

void poop() {
i++;
}
