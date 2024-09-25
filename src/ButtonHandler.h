#ifndef LIBS_BUTTONHANDLER_H
#define LIBS_BUTTONHANDLER_H
class ButtonHandler
{
private:
    bool reading;
    const uint32_t longPressDuration = 600;   // Durasi untuk mendeteksi long press (ms)
    const uint32_t debounceDelay = 10;        // Debounce untuk menghindari bouncing (ms)
    const uint32_t doubleClickDuration = 300; // Durasi maksimum antara dua klik untuk deteksi double click (ms)

    bool buttonState = HIGH;         // Status tombol saat ini (HIGH karena menggunakan pull-up)
    bool lastButtonState = HIGH;     // Status tombol sebelumnya
    bool isLongPress = false;        // Flag untuk mendeteksi apakah long press sedang berlangsung
    uint32_t buttonPressTime = 0;    // Waktu saat tombol mulai ditekan
    uint32_t buttonReleaseTime = 0;  // Waktu saat tombol dilepaskan
    uint32_t lastDebounceTime = 0;   // Mengatasi debounce
    uint32_t lastClickTime = 0;      // Waktu klik terakhir
    bool clickDetected = false;      // Flag untuk mendeteksi klik tunggal
    bool doubleClickPending = false; // Flag untuk menunda deteksi double click

public:
    ButtonHandler() {}

    // Fungsi untuk mendeteksi event tombol (short press, double click, long press)
    uint8_t events(bool rd)
    {
        reading = rd;

        // Debounce: cek apakah ada perubahan status tombol
        if (reading != lastButtonState)
        {
            lastDebounceTime = millis(); // Reset waktu debounce
        }

        // Jika tidak ada perubahan status tombol selama waktu debounce
        if ((millis() - lastDebounceTime) > debounceDelay)
        {
            if (reading != buttonState)
            {
                buttonState = reading;

                // Jika tombol ditekan (LOW)
                if (buttonState == LOW)
                {
                    buttonPressTime = millis(); // Catat waktu saat tombol ditekan
                    isLongPress = false;        // Reset flag long press
                    if (!clickDetected)
                    {
                        doubleClickPending = false; // Reset flag double click pending
                    }
                }
                // Jika tombol dilepaskan (HIGH)
                else if (buttonState == HIGH)
                {
                    buttonReleaseTime = millis(); // Catat waktu saat tombol dilepaskan
                    uint32_t pressDuration = buttonReleaseTime - buttonPressTime;

                    // Jika durasi lebih dari longPressDuration (long press release)
                    if (pressDuration >= longPressDuration)
                    {
                        return 4; // Long press release detected
                    }
                    else
                    {
                        // Deteksi double click
                        if (clickDetected && (millis() - lastClickTime < doubleClickDuration))
                        {
                            clickDetected = false;      // Reset flag click setelah double click
                            doubleClickPending = false; // Reset flag double click pending
                            return 2;                   // Double click detected
                        }
                        else
                        {
                            if (doubleClickPending)
                            {
                                doubleClickPending = false; // Reset flag double click pending
                                clickDetected = false;      // Reset flag click
                                return 1;                   // Short press detected
                            }
                            else
                            {
                                clickDetected = true;      // Set flag click
                                lastClickTime = millis();  // Catat waktu klik
                                doubleClickPending = true; // Set flag double click pending
                            }
                        }
                    }
                }
            }

            // Jika tombol masih ditekan lebih lama dari longPressDuration
            if (buttonState == LOW && (millis() - buttonPressTime >= longPressDuration) && !isLongPress)
            {
                isLongPress = true; // Set flag long press agar tidak mendeteksi berkali-kali
                return 3;           // Long press hold detected
            }
        }

        // Cek jika waktu dari klik terakhir melebihi doubleClickDuration dan doubleClickPending belum direset
        if (doubleClickPending && (millis() - lastClickTime >= doubleClickDuration))
        {
            doubleClickPending = false; // Reset flag double click pending
            clickDetected = false;      // Reset flag click
            return 1;                   // Short press detected
        }

        lastButtonState = reading; // Simpan status tombol saat ini untuk loop berikutnya
        return 0;                  // Tidak ada event
    }
};

#endif
