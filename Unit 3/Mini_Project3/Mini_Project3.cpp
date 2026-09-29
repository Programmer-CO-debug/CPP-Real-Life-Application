#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Media {
protected:
    string name;

public:
    Media(string n) {
        name = n;
    }

    virtual void play() = 0;
    virtual void pause() = 0;
    virtual void stop() = 0;
    virtual void showDetails() = 0;

    virtual ~Media() {}
};


class Audio : public Media {
public:
    Audio(string n) : Media(n) {}

    void play() {
        cout << "Playing Audio: " << name << endl;
    }

    void pause() {
        cout << "Audio Paused" << endl;
    }

    void stop() {
        cout << "Audio Stopped" << endl;
    }

    void showDetails() {
        cout << "Audio: " << name << endl;
    }
};


class Video : public Media {
public:
    Video(string n) : Media(n) {}

    void play() {
        cout << "Playing Video: " << name << endl;
    }

    void pause() {
        cout << "Video Paused" << endl;
    }

    void stop() {
        cout << "Video Stopped" << endl;
    }

    void showDetails() {
        cout << "Video: " << name << endl;
    }
};


class Image : public Media {
public:
    Image(string n) : Media(n) {}

    void play() {
        cout << "Showing Image: " << name << endl;
    }

    void pause() {
        cout << "Image Paused" << endl;
    }

    void stop() {
        cout << "Image Closed" << endl;
    }

    void showDetails() {
        cout << "Image: " << name << endl;
    }
};


int main() {

    vector<Media*> mediaList;

    Audio audio("Song.mp3");
    Video video("Movie.mp4");
    Image image("Photo.jpg");

    mediaList.push_back(&audio);
    mediaList.push_back(&video);
    mediaList.push_back(&image);

    cout << "=== Media Player ===" << endl;

    for (Media* media : mediaList) {

        media->showDetails();
        media->play();
        media->pause();
        media->stop();

        cout << endl;
    }

    return 0;
}
