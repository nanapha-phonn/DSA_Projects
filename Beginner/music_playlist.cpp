
#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Song {
    int id;
    string title;
    string artist;
    Song* next;
    Song* prev;

    Song(int songId, const string& songTitle,
         const string& songArtist)
        : id(songId),
          title(songTitle),
          artist(songArtist),
          next(this),
          prev(this) {}
};

class MusicPlaylist {
private:
    Song* head = nullptr;
    Song* current = nullptr;
    int nextId = 1;
    int songCount = 0;

public:
    ~MusicPlaylist() {
        clearPlaylist();
    }

    bool isEmpty() const {
        return head == nullptr;
    }

    void addSong(const string& title, const string& artist) {
        if (title.empty() || artist.empty()) {
            cout << "Title and artist cannot be empty.\n";
            return;
        }

        Song* song = new Song(nextId++, title, artist);

        if (head == nullptr) {
            head = song;
            current = song;
        } else {
            Song* tail = head->prev;

            tail->next = song;
            song->prev = tail;

            song->next = head;
            head->prev = song;
        }

        songCount++;

        cout << "Song added: " << title
             << " by " << artist << '\n';
    }

    void playCurrent() const {
        if (isEmpty()) {
            cout << "Playlist is empty.\n";
            return;
        }

        cout << "\nNow playing: " << current->title
             << " - " << current->artist << '\n';
    }

    void nextSong() {
        if (isEmpty()) {
            cout << "Playlist is empty.\n";
            return;
        }

        current = current->next;
        playCurrent();
    }

    void previousSong() {
        if (isEmpty()) {
            cout << "Playlist is empty.\n";
            return;
        }

        current = current->prev;
        playCurrent();
    }

    void displayPlaylist() const {
        if (isEmpty()) {
            cout << "Playlist is empty.\n";
            return;
        }

        Song* temp = head;

        cout << "\n===== MUSIC PLAYLIST =====\n";

        do {
            cout << (temp == current ? ">> " : "   ")
                 << "ID: " << temp->id
                 << " | " << temp->title
                 << " | " << temp->artist << '\n';

            temp = temp->next;
        } while (temp != head);
    }

    void searchSong(const string& title) const {
        if (isEmpty()) {
            cout << "Playlist is empty.\n";
            return;
        }

        Song* temp = head;
        bool found = false;

        do {
            if (temp->title == title) {
                cout << "Found: ID " << temp->id
                     << " | " << temp->title
                     << " | " << temp->artist << '\n';
                found = true;
            }

            temp = temp->next;
        } while (temp != head);

        if (!found) {
            cout << "Song not found.\n";
        }
    }

    void removeSong(int id) {
        if (isEmpty()) {
            cout << "Playlist is empty.\n";
            return;
        }

        Song* temp = head;

        do {
            if (temp->id == id) {
                if (temp->next == temp) {
                    // Only one song remains.
                    head = nullptr;
                    current = nullptr;
                } else {
                    temp->prev->next = temp->next;
                    temp->next->prev = temp->prev;

                    if (head == temp) {
                        head = temp->next;
                    }

                    if (current == temp) {
                        current = temp->next;
                    }
                }

                cout << "Removed: " << temp->title << '\n';

                delete temp;
                songCount--;
                return;
            }

            temp = temp->next;
        } while (temp != head);

        cout << "Song ID not found.\n";
    }

    void showStatistics() const {
        cout << "\nTotal songs: " << songCount << '\n';

        if (current != nullptr) {
            cout << "Current song: " << current->title << '\n';
        } else {
            cout << "Current song: None\n";
        }
    }

    void clearPlaylist() {
        if (head == nullptr) {
            return;
        }

        Song* temp = head->next;

        while (temp != head) {
            Song* next = temp->next;
            delete temp;
            temp = next;
        }

        delete head;

        head = nullptr;
        current = nullptr;
        songCount = 0;
    }
};

int main() {
    MusicPlaylist playlist;
    int choice;

    do {
        cout << "\n===== MUSIC PLAYLIST MANAGER =====\n";
        cout << "1. Add song\n";
        cout << "2. Play current song\n";
        cout << "3. Next song\n";
        cout << "4. Previous song\n";
        cout << "5. Display playlist\n";
        cout << "6. Search song\n";
        cout << "7. Remove song\n";
        cout << "8. Show statistics\n";
        cout << "9. Clear playlist\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );
            cout << "Invalid input.\n";
            continue;
        }

        cin.ignore(
            numeric_limits<streamsize>::max(), '\n'
        );

        switch (choice) {
        case 1: {
            string title, artist;

            cout << "Enter song title: ";
            getline(cin, title);

            cout << "Enter artist: ";
            getline(cin, artist);

            playlist.addSong(title, artist);
            break;
        }

        case 2:
            playlist.playCurrent();
            break;

        case 3:
            playlist.nextSong();
            break;

        case 4:
            playlist.previousSong();
            break;

        case 5:
            playlist.displayPlaylist();
            break;

        case 6: {
            string title;

            cout << "Enter song title to search: ";
            getline(cin, title);

            playlist.searchSong(title);
            break;
        }

        case 7: {
            int id;

            cout << "Enter song ID to remove: ";

            if (!(cin >> id)) {
                cin.clear();
                cin.ignore(
                    numeric_limits<streamsize>::max(), '\n'
                );
                cout << "Invalid ID.\n";
                break;
            }

            cin.ignore(
                numeric_limits<streamsize>::max(), '\n'
            );

            playlist.removeSong(id);
            break;
        }

        case 8:
            playlist.showStatistics();
            break;

        case 9:
            playlist.clearPlaylist();
            cout << "Playlist cleared.\n";
            break;

        case 0:
            cout << "Exiting music player.\n";
            break;

        default:
            cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
