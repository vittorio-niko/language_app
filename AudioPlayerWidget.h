#ifndef AUDIOPLAYERWIDGET_H
#define AUDIOPLAYERWIDGET_H
//Qt libraries
#include <QWidget>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMouseEvent>
#include <QStyle>

class AudioPlayerWidget : public QWidget {
    Q_OBJECT
public:
    explicit AudioPlayerWidget(const QString& filePath, QWidget *parent = nullptr);
    void setAudioFile(const QString& filePath);
    void setPlayLimit(int limit);
    void enableSeeking(bool isEnabled);
    void enablePause(bool isEnabled);
    void setLabelsStyle(const QString& labelStyle);

private slots:
    void playPause();
    void updatePosition(int position);
    void updateDuration(int duration);
    void setPosition(int position);
    void handleStateChanged(QMediaPlayer::PlaybackState state);
    void handleMediaStatusChanged(QMediaPlayer::MediaStatus status);
protected:
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    static QString formatTime(int milliseconds);
    void updatePlaysLeftLabel();

private:
    QMediaPlayer *player;
    QAudioOutput *audioOutput;

    QPushButton *playButton;
    QSlider *positionSlider;
    QLabel *positionLabel;
    QLabel *durationLabel;
    QLabel *playsLeftLabel;

    QString currentFile;
    int playLimit; //-1 - unlimited plays
    int playCount;
    bool seekingEnabled;
    bool pauseEnabled;
};

#endif // AUDIOPLAYERWIDGET_H
