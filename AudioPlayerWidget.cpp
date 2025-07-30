#include "AudioPlayerWidget.h"

AudioPlayerWidget::AudioPlayerWidget(const QString& filePath, QWidget *parent) : QWidget(parent),
    playLimit(-1), playCount(0), seekingEnabled(true), pauseEnabled(true) {
    player = new QMediaPlayer(this);
    audioOutput = new QAudioOutput(this);
    player->setAudioOutput(audioOutput);

    playButton = new QPushButton("Play", this);
    positionSlider = new QSlider(Qt::Horizontal, this);
    positionSlider->installEventFilter(this);
    positionLabel = new QLabel("00:00", this);
    durationLabel = new QLabel("00:00", this);
    playsLeftLabel = new QLabel(this);
    playsLeftLabel->setAlignment(Qt::AlignLeft);
    playsLeftLabel->hide();

    setAudioFile(filePath);

    QHBoxLayout *controlsLayout = new QHBoxLayout;
    controlsLayout->addWidget(playButton);
    controlsLayout->addWidget(positionLabel);
    controlsLayout->addWidget(positionSlider);
    controlsLayout->addWidget(durationLabel);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(controlsLayout);
    mainLayout->addWidget(playsLeftLabel);

    connect(playButton, &QPushButton::clicked, this, &AudioPlayerWidget::playPause);

    connect(player, &QMediaPlayer::positionChanged, this, &AudioPlayerWidget::updatePosition);
    connect(player, &QMediaPlayer::durationChanged, this, &AudioPlayerWidget::updateDuration);
    connect(positionSlider, &QSlider::sliderMoved, this, &AudioPlayerWidget::setPosition);
    connect(player, &QMediaPlayer::playbackStateChanged, this, &AudioPlayerWidget::handleStateChanged);
    connect(player, &QMediaPlayer::mediaStatusChanged, this, &AudioPlayerWidget::handleMediaStatusChanged);
}

void AudioPlayerWidget::setAudioFile(const QString& filePath) {
    currentFile = filePath;
    playCount = 0;
    updatePlaysLeftLabel();
    player->setSource(QUrl::fromLocalFile(filePath));
}

void AudioPlayerWidget::setPlayLimit(int limit) {
    playLimit = limit;
    playCount = 0;
    updatePlaysLeftLabel();
}

void AudioPlayerWidget::enableSeeking(bool isEnabled) {
    this->seekingEnabled = isEnabled;
    positionSlider->setEnabled(isEnabled);
    if (isEnabled) {
        positionSlider->setCursor(Qt::PointingHandCursor);
    } else {
        positionSlider->setCursor(Qt::ArrowCursor);
    }
}

void AudioPlayerWidget::enablePause(bool isEnabled) {
    this->pauseEnabled = isEnabled;
}

void AudioPlayerWidget::playPause() {
    if (player->playbackState() == QMediaPlayer::PlayingState &&
        pauseEnabled) {
        player->pause();
    } else {
        player->play();
    }
}

void AudioPlayerWidget::updatePosition(int position) {
    if (seekingEnabled) {
        positionSlider->setValue(position);
    } else {
        positionSlider->blockSignals(true);
        positionSlider->setValue(position);
        positionSlider->blockSignals(false);
    }
    positionLabel->setText(formatTime(position));
}

void AudioPlayerWidget::updateDuration(int duration) {
    positionSlider->setRange(0, duration);
    durationLabel->setText(formatTime(duration));
}

void AudioPlayerWidget::setPosition(int position) {
    if (seekingEnabled) {
        player->setPosition(position);
    }
}

void AudioPlayerWidget::handleStateChanged(QMediaPlayer::PlaybackState state) {
    switch (state) {
    case QMediaPlayer::PlayingState:
        playButton->setText("Pause");
        if (!pauseEnabled) {
            playButton->setDisabled(true);
        }
        break;
    case QMediaPlayer::PausedState:
    case QMediaPlayer::StoppedState:
        playButton->setText("Play");
        break;
    }
}

void AudioPlayerWidget::handleMediaStatusChanged(QMediaPlayer::MediaStatus status) {
    if (status == QMediaPlayer::EndOfMedia) {
        ++playCount;
        playButton->setEnabled(true);
        updatePlaysLeftLabel();
    }
}

bool AudioPlayerWidget::eventFilter(QObject *watched, QEvent *event) {
    if (watched == positionSlider &&
        event->type() == QEvent::MouseButtonPress &&
        seekingEnabled) {
        QMouseEvent *mouseEvent = dynamic_cast<QMouseEvent*>(event);
        int value = QStyle::sliderValueFromPosition(
            positionSlider->minimum(),
            positionSlider->maximum(),
            mouseEvent->pos().x(),
            positionSlider->width());
        positionSlider->setValue(value);
        player->setPosition(value);
        return true;
    }
    return QWidget::eventFilter(watched, event);
}

QString AudioPlayerWidget::formatTime(int milliseconds) {
    int seconds = milliseconds / 1000;
    int minutes = seconds / 60;
    seconds %= 60;

    return QString("%1:%2")
        .arg(minutes, 2, 10, QLatin1Char('0'))
        .arg(seconds, 2, 10, QLatin1Char('0'));
}

void AudioPlayerWidget::updatePlaysLeftLabel() {
    if (playLimit < 0) {
        playsLeftLabel->hide();
    } else {
        int left = playLimit - playCount;
        playsLeftLabel->setText(QString("Plays left: %1/%2").arg(left).arg(playLimit));
        playsLeftLabel->show();
        if (left == 0) {
            playButton->setDisabled(true);
            enableSeeking(false);
        }
    }
}

void AudioPlayerWidget::setLabelsStyle(const QString& labelStyle) {
    this->durationLabel->setStyleSheet(labelStyle);
    this->playsLeftLabel->setStyleSheet(labelStyle);
    this->positionLabel->setStyleSheet(labelStyle);
}
