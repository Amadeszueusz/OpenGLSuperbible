OpenGL. Superbiblia - jak zbudować kod źródłowy
=====================================================

Kod źródlowy korzystuje narzędzie CMake. Przykłady korzystają również z biblioteki GLFW,
której kopia znajduje się w folderze `extern`. Można skorzystać z innej kopii biblioteki,
ale pozostawiamy to jako ćwiczenie. Oto instrukcje dla obsługiwanych platform.

Windows / Microsoft Visual Studio 2013
--------------------------------------

Zainstaluj CMake. Pliki binarne są dostępne na stronie http://www.cmake.org/.
Upewnij się, że CMake znajduje się na ścieżce wykonania.
Uruchom wiersz poleceń i przejdź do folderu z kodem.

### Budowanie GLFW

Jeśli zamierzasz skorzystać z biblioteki GLFW z archiwum, wejdź do folderu biblioteki GLFW,
czyli `extern/glfw-3.0.4` i wpisz:

    cmake -G "Visual Studio 12" .

(Tak, to nie błąd - Visual Studio 12 to 2013)

Otwórz plik GLFW.sln w Visual Studio i zbuduj wersje Debug i Release biblioteki.

Skopiuj i zmień nazwę wynikowych bibliotek glfw3:

* Skopiuj `glfw-3.0.4/src/Debug/glfw3.lib` do folderu `lib` i **zmień nazwę na glfw3_d.lib**.
* Skopiuj `glf3-3.0.4/src/Release/glfw3.lib` do folderu `lib`, ale nie zmieniaj nazwy.

### Budowanie przykładów

Uruchom wiersz poleceń i przejdź do folderu z kodem. Wpisz:

    cmake -G "Visual Studio 12" ..

Otwórz wynikowy plik projektu superbible7.sln w Visual Studio.

Przykłady po zbudowaniu znajdą się w folderze `bin`.

Linux
-----

Podobnie jak w systemie Windows, projekt używa CMake do budowania plików.
Zastosuj metodę instalacji narzędzia odpowiednią dla dystrybucji systemu Linux.
W przypadku dystrybucji bazujących na wersji Debian (na przykład Ubuntu lub Mint),
wykonaj następujące polecenie:

    sudo apt-get install cmake

Konieczne jest też zaspokjenie zależności. Potrzebne będą nagłówki i biblioteki GL i
GLX (najczęściej znajdują się w pakiecie Mesa) oraz biblioteka GLFW.
Choć można zastosować bibliotekę w wersji dołączonej do kodu, najczęściej
łatwiej będzie skorzystać z wersji dystrybuowanej wraz z systemem Linux.

Po przygotowaniach wejdź do folderu "build" w folderze z kodem źródłowym
i wykonaj polecenia:

    cmake ..
    make

Pliki zostaną skompilowane do folderu 'bin'.

Inne platformy
---------------

Kod prawdopodobnie uda się uruchomić na innych platformach, jeśli nie są
wyjątkowo nietypowe, ale nic poza Windowsem (visual Studio) i Linuksem
nie zostało przetestowane. Musisz również znaleźć odpowiedni sterownik
OpenGL 4.x dla używanej platformy. CMake nie powinien mieć trudności
z przygotowaniem kodu źródłowego do kolpilacji w innych środowiskach,
na przykład Code::Blocks lub Eclipse, ale nie było to testowane.


*Pamiętaj: NAWET JEŚLI UDA SIĘ SKOMPILOWAĆ KOD NA ULUBIONEJ PLATFORMIE,
POTRZEBNE BĘDĄ RELATYWNIE NOWE STEROWNIKI OpenGL 4.x, ABY JE URUCHOMIĆ.
PROSZĘ NIE OBWINIAĆ AUTORÓW KSIĄŻKI, ŻE KOMPUTER NIE OBSŁUGUJE OpenGL 4.x.
DZIĘKUJĘ*

Uruchamianie przykładów
-------------------

Przykłady uruchamiaj z folderu bin, bo wiele z nich do działania wymaga
elementów znajdujących się w podfolderze media folderu bin.
