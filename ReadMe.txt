Kamil Czuj, 19.07.2026

Opis:
    Poniższy program to narzędzie do zarządzania oraz odtwarzania playlist muzycznych i podcastów.
    Stworzony został w języku C++ z wykorzystaniem biblioteki <SFML/Audio.hpp> do obsługi dźwięku
    oraz nagłówka <filesystem> do dynamicznego skanowania plików w formacie .ogg (działanie innych dźwiękowych rozszerzeń plików jest możliwe lecz nie gwarantowane).
    Aplikacja umożliwia tworzenie i edycję playlist, dodawanie utworów, a także odtwarzanie muzyki w różnych trybach z poziomu konsoli.
    Wraz z pakietem programowym dołączony jest również poglądowy zestaw playlist utworów.

Na Linuksie:
    Instalacja biblioteki SFML
        sudo apt install libsfml-dev
    Komenda kompilacji z odpowiednimi flagami:
        g++ -std=c++17 main.cpp -o main -lstdc++fs -lsfml-audio -lsfml-system

Działanie:
    (UWAGA) Zaleca się użycie słuchawek na początkowo niskim poziomie głośności, ze względu na nagłe rozpoczęcie odtwarzania playlist.

    Upewnić się że domyślne urządzenie dźwiękowe jest aktywne. Należy uruchomić program, w oknie konsoli powinno się wyświetlić intuicyjne menu stworzone z segmentów rozpiski playlist i zawartych w nich utworów, oraz systemu zarządzania playlistami w którego menu dostępne
    są opcje operacji na playlistach i plikach muzycznych.

    Aby dodać własną muzykę/podcast do programu:
    1. Przenieś plik dźwiękowy (np. w formacie .ogg) do folderu z projektem.
    2. W menu głównym przejdź do opcji nr 3 ("Edytuj playlistę") i dodaj nowy utwór/podcast podając jego dane oraz nazwę pliku.
    
    Możesz także skorzystać z opcji nr 4, aby odtworzyć wykryty na dysku plik bezpośrednio. (Jest to możliwe tylko dla plików z rozszerzeniem .ogg) 
    Odtwarzaniem utworu można sterować z poziomu klawiatury podczas odtwarzania.

Zawartość:
ReadMe:
    ReadMe.txt

Pliki naglowkowe i wykonawcze:
    main.cpp
    Song.hpp
    Podcast.hpp
    Playlist.hpp
    PlaybackAction.hpp
    AudioSource.hpp

Pliki muzyczne/podcastowe:
    976_EVIL-Deftones.ogg
    C.R.E.A.M.-Wu_tang_Clan.ogg
    Dwoch_Typow_Podcast-Epizod_119.ogg
    Even_Flow-Pearl_Jam.ogg
    Feel_The_Music-Guru.ogg
    Parabola-Tool.ogg
    REPULSIVE_IN_ITS_SPLENDID_BEAUTY-Crowbar.ogg
    Righteous_Minds-Joey_Bada.ogg
    Rock_Bottom-UFO.ogg
    Would-Alice_In_Chains.ogg