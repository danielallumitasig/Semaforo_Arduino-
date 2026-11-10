// --- PINES VEHICULARES ---
const int led_r1 = 13;
const int led_a1 = 12;
const int led_v1 = 11;

const int led_r2 = 10;
const int led_a2 = 9;
const int led_v2 = 8;

// --- PINES PEATONALES ---
const int led_pe_rojo = 5;
const int led_pe_verde = 4;

// --- BOTÓN ---
const int boton_pe = 2; // Pin libre y seguro

bool solicitud_peaton = false;

void setup() {
  pinMode(led_r1, OUTPUT);
  pinMode(led_a1, OUTPUT);
  pinMode(led_v1, OUTPUT);
  pinMode(led_r2, OUTPUT);
  pinMode(led_a2, OUTPUT);
  pinMode(led_v2, OUTPUT);
  
  pinMode(led_pe_rojo, OUTPUT);
  pinMode(led_pe_verde, OUTPUT);
  
  pinMode(boton_pe, INPUT);

  digitalWrite(led_pe_rojo, HIGH);
  digitalWrite(led_pe_verde, LOW);
}

void loop() {
  if (digitalRead(boton_pe) == HIGH) {
    solicitud_peaton = true;
  }

  // FASE 1: Vía 1 Verde / Vía 2 Rojo
  digitalWrite(led_r1, LOW);
  digitalWrite(led_v1, HIGH);
  digitalWrite(led_r2, HIGH);
  digitalWrite(led_v2, LOW);

  for (int i = 0; i < 50; i++) {
    if (digitalRead(boton_pe) == HIGH) solicitud_peaton = true;
    delay(100);
  }

  // FASE 2: Vía 1 Amarillo
  digitalWrite(led_v1, LOW);
  digitalWrite(led_a1, HIGH);
  delay(2000);

  // CRUCE PEATONAL
  if (solicitud_peaton) {
    digitalWrite(led_a1, LOW);
    digitalWrite(led_r1, HIGH);
    digitalWrite(led_r2, HIGH);
    delay(1000);

    digitalWrite(led_pe_rojo, LOW);
    digitalWrite(led_pe_verde, HIGH);
    delay(5000);

    for (int i = 0; i < 3; i++) {
      digitalWrite(led_pe_verde, LOW);
      delay(500);
      digitalWrite(led_pe_verde, HIGH);
      delay(500);
    }

    digitalWrite(led_pe_verde, LOW);
    digitalWrite(led_pe_rojo, HIGH);
    solicitud_peaton = false;
  }

  // FASE 3: Vía 1 Rojo / Vía 2 Verde
  digitalWrite(led_a1, LOW);
  digitalWrite(led_r1, HIGH);
  digitalWrite(led_r2, LOW);
  digitalWrite(led_v2, HIGH);
  delay(5000);

  // FASE 4: Vía 2 Amarillo
  digitalWrite(led_v2, LOW);
  digitalWrite(led_a2, HIGH);
  delay(2000);

  digitalWrite(led_a2, LOW);
  digitalWrite(led_r2, HIGH);
}