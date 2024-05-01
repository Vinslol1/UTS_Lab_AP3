// TODO 1: Ubah nama file ini menjadi NIM Anda. Cth: 001.cpp, 042.cpp, 080.cpp

// TODO 2: Buat program anda di file ini. INGAT BERI KOMENTAR PADA SETIAP PROSES DALAM PROGRAM ANDA

// TODO 3: Selesaikan dan kumpulkan sebelum deadline yang telah ditentukan; Details ada dalam file README.md

// Tetap semangat walau sulit ;p

#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm> // Menambahkan header yang diperlukan

using namespace std;

// Fungsi untuk mengecek apakah karakter merupakan digit
bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

// Fungsi untuk mengembalikan tipe kartu berdasarkan digit awal
string getCardType(const string& cardNumber) {
    if (cardNumber.length() == 16 && cardNumber[0] == '5' && (cardNumber[1] >= '1' && cardNumber[1] <= '5'))
        return "MASTERCARD";
    else if ((cardNumber.length() == 13 || cardNumber.length() == 16) && cardNumber[0] == '4')
        return "VISA";
    else
        return "TIDAK DIKETAHUI";
}

// Fungsi untuk melakukan validasi Algoritma Luhn
bool isValidLuhn(const string& cardNumber) {
    int sum = 0;
    bool alternate = false;

    // Iterasi dari digit terakhir ke digit pertama
    for (int i = cardNumber.length() - 1; i >= 0; i--) {
        if (!isDigit(cardNumber[i])) // Memeriksa apakah karakter adalah digit
            return false;

        int digit = cardNumber[i] - '0'; // Mengubah karakter menjadi bilangan bulat

        if (alternate) {
            digit *= 2; // Menggandakan digit setiap digit kedua dari kanan
            if (digit > 9)
                digit = (digit % 10) + 1; // Menambahkan digit hasil ganda jika digit > 9
        }

        sum += digit; // Menambahkan digit ke dalam jumlah total
        alternate = !alternate; // Mengubah status alternatif setiap iterasi
    }

    return (sum % 10 == 0); // Mengembalikan true jika jumlah modulo 10 sama dengan 0 (valid)
}

int main() {
    string cardNumber;

    cout << "Masukkan nomor kartu: ";
    cin >> cardNumber;

    // Menghilangkan spasi atau karakter non-digit dari nomor kartu
    cardNumber.erase(remove_if(cardNumber.begin(), cardNumber.end(), [](char c) { return !isdigit(c); }), cardNumber.end());

    if (cardNumber.length() < 13 || cardNumber.length() > 16) {
        cout << "TIDAK VALID" << endl;
        return 0;
    }

    if (!isValidLuhn(cardNumber)) { // Memeriksa apakah nomor kartu valid menggunakan Algoritma Luhn
        cout << "TIDAK VALID" << endl;
        return 0;
    }

    string cardType = getCardType(cardNumber); // Mendapatkan tipe kartu
    cout << cardType << endl;
    cout << "Checksum: " << isValidLuhn(cardNumber) << endl; // Menampilkan hasil checksum dari validasi Algoritma Luhn

    return 0;
}