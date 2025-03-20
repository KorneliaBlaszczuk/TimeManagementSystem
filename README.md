# Time Management System
## ENG

## Project Description

The Time Management System is an application that helps users plan their day. The app allows users to create events, manage tasks, and track progress, aiming to increase the user's efficiency. Additionally, it includes a Pomodoro feature, which supports users in properly dividing their time between work/study and rest. This time division is essential for maintaining a healthy work-life balance. The application was primarily designed for students but is versatile enough to be useful for adults and teenagers who want to gain better control over their time.

## Goal

The main goal of the system is to assist users in organizing their day to maximize available time for studying, working, resting, and other activities.

## Features

1. **Creating Events**:
   - Name, start and end times, location, attendees.
   - Operations: adding, removing, modifying, viewing.

2. **Creating Tasks (To-Do)**:
   - Name, task date, completion progress, priority, task notes, subtasks.
   - Operations: adding, removing, modifying, viewing.

3. **Creating Reminders**:
   - Name, date, description, repetition.
   - Operations: adding, removing, modifying, viewing.

4. **Collaboration between Multiple Users**:
   - The application allows multiple users, created by name.

5. **Pomodoro**:
   - Manages work sessions and breaks according to Pomodoro principles.

## Classes and Structures

### Main Classes

- **Plan**:
  - Attributes: plan name, base date.
  - This is the base class for Event, Task, and Reminder.

- **Task**:
  - Attributes: name, date, importance, progress note, progress status, subtasks.
  - Subtask structure: name, importance, subtask status.
  - Subtasks have been modified so they don't accept additional subtasks.

- **Event**:
  - Attributes: name, start, end, location, attendees.
  - Since around 90% of events are one-day events, the app doesn't allow multi-day events. However, modifying an event allows changing the end date entirely. This design saves users time.

- **Reminder**:
  - Attributes: name, date, details, repeat.

- **Pomodoro**:
  - Attributes: min - session time.
  - Methods: a timer counts down the time.
  - The terminal displays only the time during the Pomodoro session so that users can focus entirely on their task without distractions.

- **User**:
  - Attributes: name.
  - Duplicate names are not allowed.
  - Users do not have passwords due to time constraints during the project, which prevented ensuring secure login data with encryption.

## Program Operation

### Running the Program

Run the program in the folder containing the program files: `./build/TimeSystem` + the optional username if desired.
Once the program is launched, the user sees the main menu. They can create a user account, see existing user accounts, delete their account, go to their account, or exit the program.
Then the main part of the program will launch, personalized for the specific user (with their data, including events, tasks, and reminders).

### Program Operation

The user can view and manage their plans, including:
- **Calendar with events**: Can view today's events, events for a specific week or month, or any time period (in months). They can add, modify, and remove events.
- **Tasks**: Can view today's tasks (and overdue ones), tasks for a specific week or month, completed tasks for the entire month, and can add, modify, and remove tasks.
  - Completed tasks are no longer displayed, but users can see them as a summary of their achievements for the month (often serving as motivation to continue working).
- **Reminders**: Displays today's and tomorrow's reminders, with options to add, modify, or remove reminders.
- The user can also start a study session using the Pomodoro method.

## Challenges Encountered During the Project and Assumptions

1. **User Interface**:
   - Initially, we considered using QT, but we unanimously decided to focus on a better implementation and adding more features. Additionally, installing QT in our environments proved to be problematic.

2. **Storing Notes and Files**:
   - Currently, all files related to the program are stored in the `build` folder as `.txt` files. We initially considered using `.json` files, but the simplicity of handling `.txt` files convinced us to go with this method for storing user data.

3. **Pomodoro Functionality**:
   - Due to the way we implemented it, our program only works on Unix systems. Additionally, the sound and its audibility depend on the user's environment.

## Authors

- Kornelia Błaszczuk 
- Martyna Orzechowska 
- Aleksandra Raczyńska


## PL

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

Należy uruchomić program w folderze, w którym mamy pliki programowe: ./build/TimeSystem + ewentualna nazwa użytkownika, jeśli chcemy.
Po uruchomieniu programu, użytkownik widzi menu startowe użytkownika. Może stworzyć swoje konto uzytkownika, może zobaczyć jakie konta uzytkowników już istnieją, może usunąć swoje konto, przejść do swojego konta lub opuścić program.
Nastęnie zostaje uruchomiona część główna
programu - już dla konkretnego użytkownika (z jego danymi, ponieważ program zapamiętuje wydarzenia, zadania oraz przypomnienia).

Jeżeli użytkownik juz wcześniej korzystał z programu może on bezpośrednio przejść do menu związenego z zarządzaniem czasem. W tym celu uruchamiając program z linii polecenia należy podać nazwę użytkownika.

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

- Kornelia Błaszczuk
- Martyna Orzechowska 
- Aleksandra Raczyńska 