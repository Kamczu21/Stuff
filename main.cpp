#include <iostream>
#include <vector>
#include <string>
#include <filesystem>
#include <exception>

#include "PlaybackAction.hpp"
#include "AudioSource.hpp"
#include "Song.hpp"
#include "Podcast.hpp"
#include "Playlist.hpp"

int main()
{
    std::vector<Playlist> MyPlaylists;
    MyPlaylists.push_back(Playlist("Ulubione"));

    Playlist Rock("Rock");
    Rock += new Song("Even Flow", "Pearl Jam", 271.2, "Even_Flow-Pearl_Jam.ogg");
    Rock += new Song("Rock Bottom", "UFO", 188.7, "Rock_Bottom-UFO.ogg");
    Rock += new Song("Would?", "Alice In Chains", 195.6, "Would-Alice_In_Chains.ogg");
    MyPlaylists.push_back(Playlist(Rock));

    Playlist Metal("Metal");
    Metal += new Song("Parabola", "Tool", 363.0, "Parabola-Tool.ogg");
    Metal += new Song("REPULSIVE IN ITS SPLENDID BEAUTY", "Crowbar", 214.8, "REPULSIVE_IN_ITS_SPLENDID_BEAUTY-Crowbar.ogg");
    Metal += new Song("976-EVIL", "Deftones", 259.2, "976_EVIL-Deftones.ogg");
    MyPlaylists.push_back(Playlist(Metal));

    Playlist Rap("Rap");
    Rap += new Song("C.R.E.A.M.", "Wu-Tang Clan", 247.8, "C.R.E.A.M.-Wu_tang_Clan.ogg");
    Rap += new Song("Feel The Music", "Guru", 214.2, "Feel_The_Music-Guru.ogg");
    Rap += new Song("Righteous Minds", "Joey Bada$$", 206.4, "Righteous_Minds-Joey_Bada$$.ogg");
    MyPlaylists.push_back(Playlist(Rap));

    Playlist Podcasty("Podcasty");
    Podcasty += new Podcast("Niezidentyfikowany Plywajacy Dzik", 119, "Dwoch Typow Podcast", 1029.0, "Dwoch_Typow_Podcast-Epizod_119.ogg");
    MyPlaylists.push_back(Playlist(Podcasty));

    int choice = 0;

    do {
        std::cout << "\n\n================================================" << std::endl;
        std::cout << "Lista playlist/utworow:" << std::endl;
        for (size_t i = 0; i < MyPlaylists.size(); ++i) {
            std::cout << "   [" << i + 1 << "] " << MyPlaylists[i].getName() << std::endl;
            size_t trackCount = MyPlaylists[i].getTrackCount();
            if (trackCount == 0) {
                std::cout << "       (Ta playlista jest pusta)" << std::endl;
            } else {
                for (size_t j = 0; j < trackCount; ++j) {
                    AudioSource* track = MyPlaylists[i].getTrack(j);
                    std::cout << "       -> " << j + 1 << ". \"" << track->getTitle() << "\"";
                    if (Song* song = dynamic_cast<Song*>(track)) {
                        std::cout << " [Wykonawca: " << song->getArtist() << "]";
                    } 
                    else if (Podcast* podcast = dynamic_cast<Podcast*>(track)) {
                        std::cout << " [Host: " << podcast->getHost() << ", Epizod: " << podcast->getEpisodeN() << "]";
                    }
                    std::cout << std::endl;
                }
            }
        }

        std::cout << "\n+----------------------------------+" << std::endl;
        std::cout << "|  SYSTEM ZARZADZANIA PLAYLISTAMI  |" << std::endl;
        std::cout << "+----------------------------------+" << std::endl;
        std::cout << "Wybierz opcje z ponizszych: \n";
        std::cout << "1. Dodaj nowa playliste" << std::endl;
        std::cout << "2. Usun playliste" << std::endl;
        std::cout << "3. Edytuj playliste (dodaj/usun utwory, zmien nazwe)" << std::endl;
        std::cout << "4. Odtworz konkretny utwor (piosenke/podcast)" << std::endl;
        std::cout << "5. Odtworz wybrana playliste" << std::endl;
        std::cout << "0. Wyjdz z programu" << std::endl;
        std::cout << "\n===============================================\n" << std::endl;

        std::cout << "Twoj wybor: ";

        if (!(std::cin >> choice)) {
            std::cin.clear(); 
            std::cin.ignore(1000, '\n'); 
            choice = -1; 
        }
        std::cout << std::endl;

        switch (choice) {
            case 1: {
                std::cout << "   <<<   Tworzenie nowej playlisty   >>>" << std::endl;
                std::cout << "      Podaj nazwe nowej playlisty: ";

                std::cin.ignore(1000, '\n');

                std::string playlistName;
                std::getline(std::cin, playlistName);
                MyPlaylists.push_back(Playlist(playlistName));
                std::cout << "\n      Playlista '" << playlistName << "' zostala dodana!" << std::endl;
                break;
            }
            case 2:
                std::cout << "   <<<   Usuwanie playlisty   >>>" << std::endl;
                std::cout << "      Podaj nazwe playlisty do usuniecia: " << std::endl;
                if (MyPlaylists.empty()) {
                    std::cout << "      Brak playlist!" << std::endl;
                    break;
                }
                std::cout << "      Dostepne playlisty:" << std::endl;
                for (size_t i = 0; i < MyPlaylists.size(); ++i) {
                    std::cout << "         [" << i + 1 << "] " << MyPlaylists[i].getName() << std::endl;
                }
                std::cout << "      Podaj indeks playlisty do usuniecia: ";
                int toRemove;
                
                if (std::cin >> toRemove) {
                    if (toRemove > 0 && static_cast<size_t>(toRemove) <= MyPlaylists.size()) {
                        std::cout << "\n      Usunieto playliste: '" << MyPlaylists[toRemove - 1].getName() << "'\n";
                        MyPlaylists.erase(MyPlaylists.begin() + (toRemove - 1));
                    } else {
                        std::cout << "      Niepoprawny numer playlisty!" << std::endl;
                    }
                } else {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "      Musisz podac liczbe!" << std::endl;
                }
                break;

            case 3: {
                std::cout << "   <<<   EDYCJA PLAYLISTY   >>>" << std::endl;
                if (MyPlaylists.empty()) {
                    std::cout << "      Brak playlist w systemie. Stworz najpierw playliste w opcji 1!" << std::endl;
                    break;
                }

                std::cout << "      Dostepne playlisty:\n";
                for (size_t i = 0; i < MyPlaylists.size(); ++i) {
                    std::cout << "         " << i + 1 << ". " << MyPlaylists[i].getName() << "\n";
                }

                std::cout << "      Wybierz numer playlisty do edycji: ";
                int playlistIdx;
                if (!(std::cin >> playlistIdx) || playlistIdx <= 0 || static_cast<size_t>(playlistIdx) > MyPlaylists.size()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "      Niepoprawny numer playlisty!" << std::endl;
                    break;
                }
                std::cin.ignore(1000, '\n');

                Playlist& selectedPlaylist = MyPlaylists[playlistIdx - 1];
                char subChoice = ' ';
                
                do {
                    std::cout << "\n         >>>   EDYCJA '" << selectedPlaylist.getName() << "'   <<<" << std::endl;
                    std::cout << "             1. Zmien nazwe playlisty" << std::endl;
                    std::cout << "             2. Dodaj utwor" << std::endl;
                    std::cout << "            'm'. Powrot do menu glownego" << std::endl;
                    std::cout << "         Twoj wybor: ";

                    if (!(std::cin >> subChoice)) {
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        subChoice = -1;
                    } else {
                        std::cin.ignore(1000, '\n');
                    }

                    switch (subChoice) {
                        case '1': {
                            std::cout << "\n            ---   ZMIANA NAZWY PLAYLISTY   ---" << std::endl;
                            std::cout << "               Podaj nowa nazwe: ";
                            std::string newName;
                            std::getline(std::cin, newName);
                            
                            selectedPlaylist.setName(newName);
                            std::cout << "      Nazwa zostala zmieniona na " << newName << std::endl;
                            break;
                        }
                        case '2': {
                            std::cout << "\n            ---   Dodawanie nowego utworu   ---" << std::endl;
                            std::cout << "               Co chcesz dodac?\n                  1. Piosenka\n                  2. Podcast\n               Wybor: ";
                            char trackType;
                            std::cin >> trackType;
                            std::cin.ignore(1000, '\n');

                            if (trackType == '1') {
                                std::cout << "\n                     Dodawanie piosenki" << std::endl;
                                std::cout << "                        Podaj tytul: ";
                                std::string title; std::getline(std::cin, title);
                                
                                std::cout << "                        Podaj wykonawce: ";
                                std::string artist; std::getline(std::cin, artist);
                                
                                std::cout << "                        Podaj czas trwania (w sekundach): ";
                                double duration; 
                                if (!(std::cin >> duration)) {
                                    std::cin.clear(); std::cin.ignore(1000, '\n');
                                    std::cout << "                        Blad! Czas trwania musi byc liczba." << std::endl;
                                    break;
                                }
                                std::cin.ignore(1000, '\n');
                                
                                std::cout << "                        Podaj nazwe pliku (.ogg): ";
                                std::string filename; std::getline(std::cin, filename);

                                selectedPlaylist += new Song(title, artist, duration, filename);
                                std::cout << "                     Piosenka \"" << title << "\" zostala dodana!" << std::endl;

                            } else if (trackType == '2') {
                                std::cout << "\n                     Dodawanie podcastu" << std::endl;
                                std::cout << "                        Podaj tytul odcinka: ";
                                std::string title; std::getline(std::cin, title);
                                
                                std::cout << "                        Podaj numer odcinka: ";
                                int episodeN;
                                if (!(std::cin >> episodeN)) {
                                    std::cin.clear(); std::cin.ignore(1000, '\n');
                                    std::cout << "                        Blad! Numer odcinka musi byc liczba calkowita." << std::endl;
                                    break;
                                }
                                std::cin.ignore(1000, '\n');
                                
                                std::cout << "                        Podaj prowadzacego: ";
                                std::string host; std::getline(std::cin, host);
                                
                                std::cout << "                        Podaj czas trwania (w sekundach): ";
                                double duration;
                                if (!(std::cin >> duration)) {
                                    std::cin.clear(); std::cin.ignore(1000, '\n');
                                    std::cout << "                        Blad! Czas musi byc liczba." << std::endl;
                                    break;
                                }
                                std::cin.ignore(1000, '\n');
                                
                                std::cout << "                        Podaj nazwe pliku (.ogg): ";
                                std::string filename; std::getline(std::cin, filename);

                                selectedPlaylist += new Podcast(title, episodeN, host, duration, filename);
                                std::cout << "                    Podcast \"" << title << "\" (Epizod " << episodeN << ") zostal dodany!" << std::endl;

                            } else {
                                std::cout << "                    Niepoprawny wybor rodzaju utworu! Anulowano." << std::endl;
                            }
                            break;
                        }
                        case 'm':
                        case 'M':
                            std::cout << "Wracam do menu glownego..." << std::endl;
                            break;

                        default:
                            std::cout << "Niepoprawny wybor w podmenu!" << std::endl;
                            break;
                    }

                } while (subChoice != 'm' && subChoice != 'M');

                break;
            }
            case 4: {
                std::cout << "   <<<   ODTWARZANIE MUZYKI Z FOLDERU PROGRAMU   >>>\n" << std::endl;

                std::vector<std::string> oggFiles;
                try {
                    for (const auto& entry : std::filesystem::directory_iterator(".")) {
                        if (entry.is_regular_file() && entry.path().extension() == ".ogg") {
                            oggFiles.push_back(entry.path().filename().string());
                        }
                    }
                } catch (const std::exception& e) {
                    std::cout << "Blad podczas skanowania katalogu: " << e.what() << std::endl;
                    break;
                }

                if (oggFiles.empty()) {
                    std::cout << "Nie znaleziono zadnych plikow .ogg w katalogu programu!" << std::endl;
                    break;
                }

                struct TrackInfo {
                    std::string filename;
                    std::string title;
                    std::string artistOrHost;
                    AudioSource* sourcePtr;
                };

                std::vector<TrackInfo> availableTracks;

                for (const auto& file : oggFiles) {
                    TrackInfo info;
                    info.filename = file;
                    info.title = file;
                    info.artistOrHost = "Nieznany wykonawca";
                    info.sourcePtr = nullptr;

                    for (size_t i = 0; i < MyPlaylists.size(); ++i) {
                        for (size_t j = 0; j < MyPlaylists[i].getTrackCount(); ++j) {
                            AudioSource* track = MyPlaylists[i].getTrack(j);
                            if (track->getFilename() == file) {
                                info.title = track->getTitle();
                                if (Song* song = dynamic_cast<Song*>(track)) {
                                    info.artistOrHost = song->getArtist();
                                } else if (Podcast* podcast = dynamic_cast<Podcast*>(track)) {
                                    info.artistOrHost = podcast->getHost() + " (Podcast)";
                                }
                                info.sourcePtr = track;
                                break;
                            }
                        }
                        if (info.sourcePtr != nullptr) break;
                    }
                    availableTracks.push_back(info);
                }

                std::cout << "Znalezione pliki .ogg w katalogu:\n";
                for (size_t i = 0; i < availableTracks.size(); ++i) {
                    std::cout << "   [" << i + 1 << "] Tytul: \"" << availableTracks[i].title 
                              << "\" | Wykonawca: " << availableTracks[i].artistOrHost 
                              << " (Plik: " << availableTracks[i].filename << ")\n";
                }

                std::cout << "\nWybierz numer pliku do odtworzenia (lub 0, aby anulowac): ";
                int trackChoice;
                if (std::cin >> trackChoice) {
                    if (trackChoice > 0 && static_cast<size_t>(trackChoice) <= availableTracks.size()) {
                        const auto& selected = availableTracks[trackChoice - 1];
                        std::cout << "\n>>> Odtwarzanie utworu <<<\n";

                        if (selected.sourcePtr != nullptr) {
                            selected.sourcePtr->play();
                        } else {
                            playAudioFileWithControls(selected.filename, selected.filename);
                        }
                    } else if (trackChoice != 0) {
                        std::cout << "Niepoprawny numer utworu!" << std::endl;
                    }
                } else {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "Niepoprawny wybor!" << std::endl;
                }
                break;
            }
            case 5: {
                std::cout << "   <<<   ODTWARZANIE PLAYLISTY   >>>\n" << std::endl;

                if (MyPlaylists.empty()) {
                    std::cout << "      Brak playlist w systemie!" << std::endl;
                    break;
                }

                std::cout << "      Dostepne playlisty:\n";
                for (size_t i = 0; i < MyPlaylists.size(); ++i) {
                    std::cout << "         [" << i + 1 << "] " << MyPlaylists[i].getName() 
                              << " (" << MyPlaylists[i].getTrackCount() << " utworow)\n";
                }

                std::cout << "\n      Wybierz numer playlisty do odtworzenia: ";
                int playlistChoice;
                if (!(std::cin >> playlistChoice) || playlistChoice <= 0 || static_cast<size_t>(playlistChoice) > MyPlaylists.size()) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "      Niepoprawny numer playlisty!" << std::endl;
                    break;
                }
                std::cin.ignore(1000, '\n');

                Playlist& selectedPlaylist = MyPlaylists[playlistChoice - 1];

                if (selectedPlaylist.getTrackCount() == 0) {
                    std::cout << "\n      Ta playlista jest pusta! Dodaj najpierw utwory (opcja 3)." << std::endl;
                    break;
                }

                std::cout << "\n      >>> Wybrana playlista: " << selectedPlaylist.getName() << " <<<\n";
                std::cout << "         1. Odtworz cala playliste" << std::endl;
                std::cout << "         2. Odtworz od wybranego utworu" << std::endl;
                std::cout << "         3. Wymieszaj i odtworz (Shuffle)" << std::endl;
                std::cout << "      Twoj wybor: ";

                int playMode;
                if (!(std::cin >> playMode)) {
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    std::cout << "      Niepoprawny wybor!" << std::endl;
                    break;
                }

                try {
                    switch (playMode) {
                        case 1:
                            std::cout << "\n--- Rozpoczynanie odtwarzania playlisty ---\n";
                            selectedPlaylist.playAll();
                            break;
                        case 2: {
                            std::cout << "\n      Utwory na playliste:\n";
                            for (size_t j = 0; j < selectedPlaylist.getTrackCount(); ++j) {
                                std::cout << "         [" << j + 1 << "] " << selectedPlaylist.getTrack(j)->getTitle() << "\n";
                            }
                            std::cout << "      Od ktorego utworu zaczac? ";
                            size_t trackIdx;
                            if (std::cin >> trackIdx && trackIdx > 0 && trackIdx <= selectedPlaylist.getTrackCount()) {
                                std::cout << "\n--- Rozpoczynanie odtwarzania od utworu " << trackIdx << " ---\n";
                                selectedPlaylist.playFromIndex(trackIdx - 1);
                            } else {
                                std::cin.clear();
                                std::cin.ignore(1000, '\n');
                                std::cout << "      Niepoprawny numer utworu!" << std::endl;
                            }
                            break;
                        }
                        case 3:
                            std::cout << "\n--- Mieszanie utworow i rozpoczynanie odtwarzania ---\n";
                            selectedPlaylist.shuffle();
                            selectedPlaylist.playAll();
                            break;
                        default:
                            std::cout << "      Niepoprawny tryb odtwarzania!" << std::endl;
                            break;
                    }
                } catch (const std::exception& e) {
                    std::cout << "      Blad podczas odtwarzania: " << e.what() << std::endl;
                }

                break;
            }
            case 0:
                std::cout << "Do zobaczenia!" << std::endl;
                break;
            default:
                std::cout << "Niepoprawny wybor!" << std::endl;
                break;
        }

        if (choice != 0 && choice != 3) {
            std::cout << "Wpisz 'm' a nastepnie nacisnij enter by wrocic do menu!" << std::endl;
            char backChoice;
            while (std::cin >> backChoice) {
                if (backChoice == 'm' || backChoice == 'M') {
                    std::cin.ignore(1000, '\n');
                    break;
                }
                std::cout << "Niepoprawny znak! Wpisz 'm' i zatwierdz Enterem: ";
            }
        }
    } while (choice != 0);

    return 0;
}