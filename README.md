## Atak kryptograficzny

- Poniższe kroki przygotowane zostały z myślą o pracy z Linuxem.
- Wykorzystany kompilator kodu to `clang` z rozszerzeniami **OpenMP**.
  W przypadku niektórych dystrybucji może to oznaczać potrzebę odpowiednich
  bibliotek. Na Debianie jest to: `sudo apt install libomp-dev`
- Program napisany został w języku C++ w standardzie 17. W celu przyspieszenia
  czasu ataku wykorzystane zostało OpenMP.

### Wybudowanie programu (tryb interaktywny)

Aby wybudować program, który działa zgodnie z zadaniem na STOSie, wykonać
należy następujące kroki:

```bash
make
./main
```

### Złamane kody:

Aby wybudować programy rozszyfrowujące podane kody, wykonać należy komendę:

```bash
make -j4 atack
```

Następnie w folderze `atack/` pojawią się pliki wykonywalne.

Poniżej w tabeli opisane zostały wszystkie poprawnie przeprowadzone ataki:

| Długość tekstu | Zaszyfrowany tekst | Rozszyfrowany tekst | Czas złamania kodu |
| :-: | :-: | :-: | :-: |
| 2 | `58 D4 AA 81 DE 26 48 64 BB 74 14 D1 55 A9 76 14` | `t%` | < 1 sekunda |
| 3 | `3E 76 47 4E BD 2C A9 6A 8F FF FD 67 10 AE 8A 70` | `<V}` | ~ 2.5 sekundy |
| 4 | `B8 E4 65 D7 67 C5 A0 86 55 21 8A 75 62 FA 77 8B` | `&-)D` | ~ 4 sekundy |
| 5 | `AC 4B 11 14 0B 79 C0 52 39 9C 7D BD 52 91 0C 60` | `>(i5<` | ~ 9 i pół minuty |
| 6 | `46 F6 59 B1 DE DE 98 74 A6 15 55 DF E9 A8 D6 46` | `17u<8(` | ~ 11 i pół godziny |

