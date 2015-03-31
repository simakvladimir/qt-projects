#ifndef PORTAUDIOWRAPPER_H
#define PORTAUDIOWRAPPER_H

#include "portaudio/portaudio.h"
#include "buffer/safebuffer.h"

#include <QThread>

class PortAudioWrapper : public QObject
{
    Q_OBJECT
public:
    explicit PortAudioWrapper(QObject *parent = 0, SafeBuffer *buf = 0);
    ~PortAudioWrapper();

    int   get_device_count( void );

    QHash <QString,int> get_devices_names( void );
    void capture_audio_stream_stop( void );
    void configure_stream( int input_device, int output_device );
    void capture_audio_stream_start( void );

    int handler_routine( const void *inputBuffer, void *outputBuffer,
                          unsigned long framesPerBuffer,
                          const PaStreamCallbackTimeInfo* timeInfo,
                          PaStreamCallbackFlags statusFlags,
                          void *userData );


private:
    PaStream   *stream;
    SafeBuffer *fifo;

signals:
    
public slots:
    
};

#endif // PORTAUDIOWRAPPER_H
