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
   - Nazwa, czasy rozpoczecia i zakończenia, miejsce, osoby.
   - Operacje: dodawanie, usuwanie, modyfikacja, wyświetlanie.

2. **Tworzenie zadań (To-Do)**:
   - Nazwa, data zadania, stopień ukończenia, priorytetowość, notatka do zadania, podzadania.
   - Operacje: dodawanie, usuwanie, modyfikacja, wyświetlanie.

3. **Tworzenie przypomnień**:
   - Nazwa, data, opis, powtarzalność.
   - Operacje: dodawanie, usuwanie, modyfikacja, wyświetlanie.

4. **Praca między kilkoma użytkownikami**.
   - Aplikacja posiada użytkowników, tworzonych porzez nazwę.

5. **Pomodoro**:
   - Zarządzanie sesjami pracy i przerwami zgodnie z założeniami Pomodoro.


## Klasy i Struktury

### Główne Klasy

- **Plan**:
  - Atrybuty: nazwa planu, data podstawowa.
  - Jest to klasa bazowa dla Event, Task oraz Reminder.

- **Task**:
  - Atrybuty: name, date, important, progressNote, progressStatus, subtasks.
  - Struktura podzadania: name, important, subtaskStatus.
  - Podzadania zostały zmodyfikowane tak, aby nie przyjmować kolejnych podzadań.

- **Event**:
  - Atrybuty: name, start, end, location, attendees.
  - Z racji, ze ok 90% wydarzeń jest 1-dniowych dodawanie nie daję opcji wydarzeń kilkudniowych, jednak modyfikacja
   wydarzenia pozwala na całkowitą zmianę daty dnia zakończenia. Założenie to ma oszczędzić czas użytkownikowi.

- **Przypomnienie**:
  - Atrybuty: name, date, details, repeat.

- **Pomodoro**:
  - Atrybuty: min - czas sesji.
  - Metody: timer odlicza w dół czas.
  - Terminal wyświetla tylko czas w trakcie działania Pomodoro, aby użytkownik maksymalnie skupił się na tym co robi bez żadnych rozpraszaczy.

- **Użytkownik**:
  - Atrybuty: name.
  - Nie pozwalamy na powtarzanie się nazw.
  - Użytkownicy nie posiadają haseł, ponieważ czasowe ograniczenia projekty nie pozwoliły nam na zapewnienie  bezpieczeństwa danych logowania użytkowników poprzez m.in. szyfrowanie.

## Sposób Działania Programu

### Uruchomienie Programu

Po uruchomieniu programu, użytkownik widzi menu startowe użytkownika. Może stworzyć swoje konto uzytkownika, może zobaczyć jakie konta uzytkowników już istnieją, może usunąć swoje konto, przejść do swojego konta lub opuścić program.
Nastęnie zostaje uruchomiona część główna
programu - już dla konkretnego użytkownika (z jego danymi, ponieważ program zapamiętuje wydarzenia, zadania oraz przypomnienia).

Jezeli uzytkownik ma juz wcześniej korzystał z programu moze on bezpośrednio przejsc do menu zwiazenego z zarządzaniem czasem. W tym celu uruchamiając program z linii polecenia nalezy podać nazwę uzytkownika.

### Działanie Programu

Użytkownik może przeglądać swoje plany, w tym:
- kalendarz z wydarzeniami - może wyświetlać dzisiejsze wydarzenia, wydarzenia na dany tydzień, miesiąć lub z dowolnego zakresu czasowego (w miesiącach) oraz dodawać, modyfikować i usuwać wydarzenia;
- zadania - może wyświetlać dzisiejsze zadania (oraz zaległe), zadania na dany tydzień, miesiąc, wyświetlać ukończone zadania z całego miesiąca, dodawać, modyfikować i usuwać zadania;
Docelowo nie wyświetlają się już ukończone zadania, ale można zobaczyć je jako podsumowanie swoich osiagnięć z danego miesiąca (często jest to dużą motywacją dla użytkownika do dalszej systematycznej pracy);
- przypomnienia - wyswietlanie dzisiejszych i jutrzejszych przypomnień, dodawanie, modyfikowanie i usuwanie przypomnień;
- użytkownik może również uruchomić sesję nauki za pomocą metody Pomodoro;

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
   słyszalność zależą od środowiska, jaki posiada użytkownik.

## Autorzy

- Kornelia Błaszczuk - 331361
- Martyna Orzechowska - 331417
- Aleksandra Raczyńska - 331428