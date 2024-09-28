### ButtonHandler
ButtonHandler adalah sebuah library sederhana untuk mendeteksi berbagai event pada tombol tekan (push button) menggunakan mikrokontroler seperti ESP32 atau Arduino. Library ini memungkinkan pengguna untuk dengan mudah mendeteksi beberapa jenis interaksi tombol, seperti short press (tekan singkat), double click (klik ganda), long press (tekan lama), serta long press release (melepas setelah tekan lama).

## Fitur Utama
Debounce: Mengatasi masalah bouncing pada tombol dengan waktu penundaan yang dapat diatur.
Short Press Detection: Mendeteksi jika tombol ditekan sebentar.
Double Click Detection: Mendeteksi dua kali klik tombol dalam waktu singkat.
Long Press Detection: Mendeteksi jika tombol ditekan dan ditahan selama durasi tertentu.
Long Press Release: Mendeteksi saat tombol dilepaskan setelah menahan selama durasi tekan lama.
## Penggunaan
Untuk menggunakan ButtonHandler, cukup inisialisasi class ini di dalam kode Anda dan panggil fungsi events() di dalam loop utama. Fungsi events() akan mengembalikan nilai berdasarkan event yang terdeteksi:

1: Short press terdeteksi.
2: Double click terdeteksi.
3: Long press hold terdeteksi (tombol masih ditekan).
4: Long press release terdeteksi (tombol dilepas setelah tekan lama).
0: Tidak ada event yang terdeteksi.
Contoh Penggunaan
cpp
Copy code
`#include <ButtonHandler.h>`

ButtonHandler button;

void setup() {
    pinMode(5, INPUT_PULLUP);  // Menggunakan internal pull-up pada pin 5
}

void loop() {
    int buttonState = digitalRead(5);
    uint8_t event = button.events(buttonState);
    
    if (event == 1) {
        // Short press
    } else if (event == 2) {
        // Double click
    } else if (event == 3) {
        // Long press hold
    } else if (event == 4) {
        // Long press release
    }
}`
## Konfigurasi
longPressDuration: Durasi untuk mendeteksi tekan lama, defaultnya 600 ms.
debounceDelay: Waktu debounce untuk menghindari bouncing, defaultnya 10 ms.
doubleClickDuration: Durasi maksimum antara dua klik untuk mendeteksi klik ganda, defaultnya 300 ms.
## Instalasi
Anda dapat menggunakan library ini dengan menyalin file header ke dalam project Arduino atau ESP32 Anda.
