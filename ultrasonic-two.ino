#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inisialisasi LCD I2C dengan alamat yang sesuai (sesuaikan jika perlu)
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Konstanta untuk pin sensor ultrasonik
const int TRIG_PIN = 7;  // Pin TRIG pada Arduino
const int ECHO_PIN = 6;  // Pin ECHO pada Arduino

// Variabel untuk menyimpan durasi dan jarak
float duration_us, distance_cm;

void setup() {
  // Inisialisasi Serial Monitor untuk debugging
  Serial.begin(9600);

  // Konfigurasi pin TRIG sebagai output dan pin ECHO sebagai input
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // Inisialisasi LCD
  lcd.begin(16, 2);   // Mengatur LCD dengan ukuran 16 kolom dan 2 baris
  lcd.init();         // Inisialisasi LCD
  lcd.backlight();    // Menyalakan backlight LCD
}

void loop() {
  // Mengirim sinyal TRIG (10 mikrodetik)
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // Membaca durasi pantulan sinyal dari ECHO
  duration_us = pulseIn(ECHO_PIN, HIGH);

  // Menghitung jarak dalam cm (rumus: jarak = (kecepatan suara di udara * waktu) / 2)
  distance_cm = duration_us * 0.034 / 2;

  // Menampilkan jarak di Serial Monitor
  Serial.print("Jarak: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  // Menampilkan jarak di LCD
  lcd.clear();
  lcd.setCursor(0, 0);  // Menampilkan di baris pertama
  lcd.print("Distance: ");
  lcd.print(distance_cm);
  lcd.print(" cm");

  // Menunggu 500 ms sebelum pembacaan berikutnya
  delay(500);
}
