# Time Menagement System

## Opis Projektu

Time Management System to aplikacja pozwalająca na planowanie dnia.
Aplikacja umożliwia tworzenie wydarzeń, zarządzanie zadaniami oraz monitorowanie postępów, co ma na celu zwiększenie efektywności użytkownika.
Dodatkowo aplikacja posaida funkcję Pomodoro, która wspiera użytkownika w prawidłowym podziale czasu na naukę/pracę oraz odpoczynek. Podział ten jest niezbędny do zachowania zdrowego trybu pracy.
Aplikacja została stworzona głównie z myślą o studentach, jednak z powodu jej dużej uniwersalności świetnie sprawdzi się również u dorosłych  oraz nastalotków, którzy chcą mieć większą kontrolą nad swoim czasem.

## Cel

Głównym celem systemu jest pomoc użytkownikom w organizacji swojego dnia, aby maksymalnie wykorzystać dostępny czas na naukę/pracę/odpoczynek oraz inne aktywności.

## Funkcjonalności

1. **Tworzenie wydarzeń**:
   - Temat, czas, miejsce, powtarzalność, osoby, przypomnienie.
   - Operacje: dodawanie, usuwanie, modyfikacja, wyświetlanie.

2. **Tworzenie listy zadań (To-Do List)**:
   - Zadania na konkretne dni, określenie czasu, priorytetowość, podzadania.
   - Operacje: dodawanie, usuwanie, modyfikacja, wyświetlanie.

1. **Praca między kilkoma użytkownikami**.
2. **Progress bar do długich zadań**.
3. **Pomodoro**:
   - Zarządzanie sesjami pracy i przerwami.
4. **Integracja plików**:
   - Przechowywanie notatek z wydarzeń, miejsce na pisanie notatek.
5. **Podział wydarzeń na grupy**:
   - Np. wykład, zajęcia, i łatwy dostęp do wszystkich danych.
6. **Statystyki pracy**:
   - Generowanie wykresów i zapis do pliku.
7. **Zarządzanie etapami projektu (Agile Scrum)**.
8. **Set revise and remind**:
   - Generowanie syntezy notatek, tworzenie fiszek do powtórzeń.

## Klasy i Struktury

### Główne Klasy

- **Plan**:
  - Atrybuty: nazwa planu, data podstawowa, typ planu (zadanie, wydarzenie, przypomnienie), odniesienie do szczegółowego obiektu planu.

- **Zadanie**:
  - Atrybuty: status wykonania, ważność, notatka progresu, status progresu, lista podzadań.
  - Struktura podzadania: nazwa, ważność, status wykonania.

- **Wydarzenie**:
  - Atrybuty: data zakończenia, lokalizacja/link do spotkania, osoby uczestniczące.

- **Przypomnienie**:
  - Atrybuty: szczegółowy opis czynności, częstotliwość powtarzania.

- **Pomodoro**:
  - Atrybuty: czas przerwy, czas bloku pracy, liczba powtórzeń.
  - Metody: zarządzanie sesjami pomodoro.

- **Użytkownik**:
  - Atrybuty: nazwa użytkownika.

## Sposób Działania Programu

### Uruchomienie Programu

Po uruchomieniu programu, użytkownik wprowadza swoją nazwę, co inicjuje spersonalizowane powitanie oraz wyświetlenie bieżących informacji, bazujących na aktualnej dacie systemowej.

### Działanie Programu

Użytkownik może przeglądać swoje plany, w tym kalendarz z wydarzeniami, listy zadań i ich statusy progresu. Może również uruchomić sesję nauki za pomocą metody Pomodoro. Program przypomina o nadchodzących zadaniach i wydarzeniach poprzez komunikaty i sygnały dźwiękowe.

## Wyzwania, które napotkałyśmy w trakcie projektu oraz przyjęte założenia

1. **Interfejs użytkownika**:
   - Początkowo myslałyśmy o użyciu QT, ale jednogłośnie stwierdziłyśmy, że wolimy się skupić na jak najlepszej
   implementacji oraz dodawaniu kolejnych funkcjonalności. Dodatkowo problemem okazała się być instalacją QT
   na naszych środowiskach.
2. **Przechowywanie notatek i plików**:
   - Aktualnie wszytskie pliki powiązane z programem przechowywane są w folderze build w postaci plików txt.
   Początkowo rozważałyśmy też użycie plików json, jednak ostatecznie prostota obsługi plików txt przekonała nas do 
   wybrania właśnie tego sposobu przechowywania danych użytkownika.
3. **Funkcjonalność 'Pomodoro'**:
   - Z powodu implementacji jaką stworzyłyśmy, nasz program działa tylko na systemach Unix, ponadto dźwięk i jego 
   słyszalność zależą od systemu, jaki posiada użytkownik.

## Autorzy

- Kornelia Błaszczuk - 3313coś
- Martyna Orzechowska - 3314coś
- Aleksandra Raczyńska - 331428